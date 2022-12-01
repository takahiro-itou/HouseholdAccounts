Option Explicit

Module AccountBook

'*****************************************************************************
' AccountBook
' AccountBook モジュール
'
' 家計簿を管理する
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2006/09/23 - 2008/01/09
'*****************************************************************************

Public gutTempBook As Wrapper.AccountBook

Public Function AccountBookUpdateItemHandleInYearRecord(
        ByRef lpBookItems As Wrapper.BookItems,
        ByRef lpNewIndex() As Integer,
        ByRef utYearRecord As Wrapper.AnnualRecords) As Integer
'---------------------------------------------------------------------
'家計簿の項目を並べ替えにあわせて、
'指定された年のデータの、項目毎の集計データを並べなおし、
'さらに全レシートの項目番号を設定しなおす。
'lpBookItems 内の項目データは既に並べたなおした後の状態になっている必要がある
'---------------------------------------------------------------------
Dim i As Integer, lngNew As Integer, lngBufferSize As Integer
Dim j As Integer, lngFlags As Integer, lngCount As Integer
Dim lngDay As Integer
'Dim utAnnualCounts() As tBookItemAnnualCounts
Dim utDetailCounts() As Wrapper.BookItemDetailCounts

    lngBufferSize = lpBookItems.nItemBufferSize

    With utYearRecord
        '項目毎の集計データを更新する
'        utAnnualCounts() = .utItemAnnualCounts()
        utDetailCounts = .utItemDetailCounts
        For i = 0 To lngBufferSize - 1
'            .utItemAnnualCounts(lngNew) = utAnnualCounts(i)
            .utItemDetailCounts(lngNew) = utDetailCounts(i)
        Next i

        'レシートの項目番号を設定しなおす
        For lngDay = 0 To MAXDAYS - 1
        With .utDayRecords(lngDay)
            For i = 0 To .nNumReceipt - 1
            With .utReceipts(i)
                lngFlags = .nFlags
                lngCount = .nNumGoods
                If (lngFlags <> RECEIPT_FLAG_NOTUSED) Then
                    For j = 0 To lngCount - 1
                    With .utGoods(j)
                        lngNew = lpNewIndex(.nItemType)
                        .nItemType = lngNew
                        .nRootItemType = lpBookItems.getRootItemHandle(lngNew)
                    End With
                    Next j
                End If
            End With
            Next i
        End With
        Next lngDay
    End With

    AccountBookUpdateItemHandleInYearRecord = 0
End Function

Public Function AddDataToItemTotal(
        ByRef utBook As Wrapper.AccountBook,
        ByVal lngYearIndex As Integer, ByVal lngDayIndex As Integer,
        ByVal lngItemIndex As Integer, ByVal lngValue As Integer) As Boolean
'---------------------------------------------------------------------
'---------------------------------------------------------------------
Dim lngFlags() As Integer
Dim lngParentHandle As Integer
Dim lngYear As Integer, lngWeek As Integer, lngMonth As Integer
Dim utDate As Wrapper.ParsedDate
Dim blnAddToParent As Boolean, blnAddToRoot As Boolean

    blnAddToParent = True
    blnAddToRoot = True

    '項目フラグを取り出しておく
    With utBook
        lngYear = .nStartYear + lngYearIndex
        With .utBookItems
            lngFlags = .nFlags
        End With
    End With

    '日付から、週と月を計算しておく
    GetDayFromIndex(utDate, lngYear, lngDayIndex, -1)
    With utDate
        lngWeek = .nWeek
        lngMonth = .nMonth
        lngYear = .nYear
    End With

    With utBook.utAnnualRecords
        Do While (lngItemIndex >= 0)
            lngParentHandle = utBook.utBookItems.utItemEntries(lngItemIndex).nParentHandle

            If (lngFlags(lngItemIndex) And Wrapper.ItemFlag.ITEM_FLAG_NOCOUNT_PARENT) Then
                blnAddToParent = False
                blnAddToRoot = False
            End If
            If (lngFlags(lngItemIndex) And Wrapper.ItemFlag.ITEM_FLAG_NOCOUNT_ROOT) Then
                blnAddToRoot = False
            End If

            If (lngParentHandle = -1) And (blnAddToRoot = False) Then Exit Do

            With .utItemDetailCounts(lngItemIndex)
                .nDayTotal(lngDayIndex) = .nDayTotal(lngDayIndex) + lngValue
                .nWeekTotal(lngWeek) = .nWeekTotal(lngWeek) + lngValue
                .nMonthTotal(lngMonth) = .nMonthTotal(lngMonth) + lngValue
            End With
            With .utItemAnnualCounts(lngItemIndex)
                .nYearTotal(lngYearIndex) = .nYearTotal(lngYearIndex) + lngValue
            End With

            If ((blnAddToParent = False) Or (lngParentHandle = -1)) Then Exit Do
            lngItemIndex = lngParentHandle
        Loop
    End With

    AddDataToItemTotal = blnAddToRoot
End Function

Public Function ChangeAccountBookYear(
        ByRef utBook As Wrapper.AccountBook,
        ByVal lngNewYear As Integer) As Long
'---------------------------------------------------------------------
'カレントの年を変更する
'[I/O] utBook    : 家計簿データ
'[ IN] lngNewYear: 西暦年
'[RET] Long
'  変更後の年の週数を返す
'  変更に失敗した場合は-1を返す
'---------------------------------------------------------------------
Dim lngLastDay As Integer
Dim lngNumWeeks As Integer
Dim lngCurrentYear As Integer
Dim lngStartYear As Integer, lngNumYears As Integer
Dim blnResult As Boolean

    With utBook
        lngCurrentYear = .nCurrentYear
        lngStartYear = .nStartYear
        lngNumYears = .nNumYears
    End With

    '開始日より前には移動できない
    If (lngNewYear < lngStartYear) Then
        ChangeAccountBookYear = -1
        Exit Function
    End If

    '新しい年の週数を計算しておく
    lngLastDay = GetDayInYear(lngNewYear, 12, 31) + GetWeekday(lngNewYear, 1, 1)
    lngNumWeeks = (lngLastDay \ 7) + 1

    If (lngNewYear = lngCurrentYear) Then
        '週数だけ計算して結果を返す
        utBook.nNumWeeks = lngNumWeeks
        ChangeAccountBookYear = lngNumWeeks
        Exit Function
    End If

    '現在の年のデータを書き込む
    If ((lngStartYear <= lngCurrentYear) And _
            (lngCurrentYear < lngStartYear + lngNumYears)) Then
        blnResult = WriteAccountBookRecords(utBook, lngCurrentYear)
        If (blnResult = False) Then
            'セーブ失敗
            ChangeAccountBookYear = -1
            Exit Function
        End If
    End If

    '新しい年のデータを読み込む
    If (lngNewYear >= lngStartYear + lngNumYears) Then
        lngNumYears = lngNewYear - lngStartYear + 1
        ReallocAnnualRecordsBuffers(utBook.utAnnualRecords, -1, lngStartYear, lngNumYears)
        utBook.nNumYears = lngNumYears
    End If

    blnResult = ReadAccountBookRecords(utBook, lngNewYear)
    If (blnResult = False) Then
        'ロード失敗
        ChangeAccountBookYear = -1
        Exit Function
    End If

    '現在操作中の年を新しい年に変更する
    utBook.nCurrentYear = lngNewYear

    '新しい年の週数を返す
    utBook.nNumWeeks = lngNumWeeks
    ChangeAccountBookYear = lngNumWeeks
End Function

Public Sub CloseAccountBook(ByRef utBook As Wrapper.AccountBook)
'---------------------------------------------------------------------
'家計簿のデータファイルを閉じる
'[I/O] utBook: 家計簿データ
'[RET] なし
'[ACT]
'  テンポラリファイルをすべて削除する
'---------------------------------------------------------------------
Dim lngYear As Integer
Dim strTempDir As String
Dim strTempFileName As String

    With utBook
        'テンポラリファイルの置かれているパスを取得する
        strTempDir = .sTempFileDir

        'ヘッダ
        strTempFileName = strTempDir & "\.set"
        If (Dir$(strTempFileName) <> "") Then
            System.IO.File.Delete(strTempFileName)
        End If

        '共通レコード
        strTempFileName = strTempDir & "\.common"
        If (Dir$(strTempFileName) <> "") Then
            System.IO.File.Delete(strTempFileName)
        End If

        '年毎のデータ
        For lngYear = 0 To .nNumYears - 1
            strTempFileName = strTempDir & "\." & Trim$(Str$(.nStartYear + lngYear))
            If (Dir$(strTempFileName) <> "") Then
                System.IO.File.Delete(strTempFileName)
            End If
        Next lngYear

        '閉じる
        .bEnabled = False
    End With

    'インデックスファイル
    strTempFileName = strTempDir & "\.index"
    If (Dir$(strTempFileName) <> "") Then
        System.IO.File.Delete(strTempFileName)
    End If
End Sub

Public Function CreateEmptyAccountBook(
        ByRef utBook As Wrapper.AccountBook) As Boolean
'---------------------------------------------------------------------
'家計簿の内容を初期状態にセットする
'[OUT] utBook : 家計簿データ
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------
Dim blnResult As Boolean

    '空のデータをロードする
    blnResult = OpenAccountBook(utBook, g_appRootDir & "\Resources\Empty.abd")
    If (blnResult = True) Then
        blnResult = ReadAccountBookSettings(utBook)
    End If

    CreateEmptyAccountBook = blnResult
End Function

Public Function GetAccountBookNumYears(
        ByRef utBook As Wrapper.AccountBook) As Integer
'---------------------------------------------------------------------
'家計簿のデータが何年分あるかを返す
'[ IN] utBook: 家計簿データ
'[RET] Long
'  データの年数
'---------------------------------------------------------------------
    GetAccountBookNumYears = utBook.nNumYears
End Function

Public Function GetAccountBookStartYear(
        ByRef utBook As Wrapper.AccountBook) As Integer
'---------------------------------------------------------------------
'家計簿の開始年を返す
'[ IN] utBook: 家計簿データ
'[RET] Long
'  開始西暦年
'---------------------------------------------------------------------
    GetAccountBookStartYear = utBook.nStartYear
End Function

Public Function IsDayBeforeStart(
        ByRef utBook As Wrapper.AccountBook,
        ByVal lngYear As Integer, ByVal lngDayIndex As Integer) As Boolean
'---------------------------------------------------------------------
'指定した日付が、家計簿の開始日より前かどうか調べる
'[ IN] utBook      : 家計簿データ
'[ IN] lngYear     : 西暦年
'[ IN] lngDayIndex : 元日からの日数(オフセット付)
'[RET] Boolean
'  開始日より前ならTrue, そうでなければ False
'---------------------------------------------------------------------
Dim blnResult As Boolean

    With utBook
        If (CompareDates(lngYear, lngDayIndex, .nStartYear, .nStartDayIndex) < 0) Then
            blnResult = True
        Else
            blnResult = False
        End If
    End With
    IsDayBeforeStart = blnResult
End Function

Public Function OpenAccountBook(
        ByRef utBook As Wrapper.AccountBook,
        ByVal strFileName As String) As Boolean
'---------------------------------------------------------------------
'家計簿のデータファイルを開く
'[OUT] utBook     : 家計簿データ
'[ IN] strFileName: ファイル名
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'[ACT]
'  ヘッダと、年毎にデータを分解して、テンポラリファイルに保存する。
'---------------------------------------------------------------------
Dim i As Integer, lngYear As Integer
Dim lngPos As Integer, lngSize As Integer, lngReserved As Integer
Dim lngHeaderSize As Integer
Dim lngHeader() As Integer
Dim bytBuffer() As Byte
Dim lngReadFileNumber As Integer
Dim lngTempFileNumber As Integer, lngIndexFileNumber As Integer
Dim strTempDir As String
Dim strTempFileName As String, strIndexFileName As String

    '指定された入力ファイルが存在するか確認する
    If (Dir$(strFileName) = "") Then
        OpenAccountBook = False
        Exit Function
    End If

    With utBook
        'テンポラリファイルを置くディレクトリを決定する
        strTempDir = g_appRootDir & "\Resources"
        utBook.sTempFileDir = strTempDir

        '入力ファイルを開く
        lngReadFileNumber = FreeFile()
        FileOpen(lngReadFileNumber, strFileName, OpenMode.Binary)

        'インデックスファイルを開く
        strIndexFileName = .sTempFileDir & "\.index"
        lngIndexFileNumber = FreeFile()
        FileOpen(lngIndexFileNumber, strIndexFileName, OpenMode.Binary)

        'ヘッダ部分のテンポラリファイルを開く
        strTempFileName = .sTempFileDir & "\.set"
        lngTempFileNumber = FreeFile()
        FileOpen(lngTempFileNumber, strTempFileName, OpenMode.Binary)

        '入力ファイルのヘッダ部分を取り出す
        ReDim lngHeader(0 To 63)
        FileGet(lngReadFileNumber, lngHeader, 1)

        'ヘッダの 6番目の項目(0x00000014)から、ヘッダと設定部分のデータサイズを得る
        lngPos = 1
        lngHeaderSize = lngHeader(5)
        lngReserved = 0
        FilePut(lngIndexFileNumber, lngPos, 1)
        FilePut(lngIndexFileNumber, lngHeaderSize, 5)
        FilePut(lngIndexFileNumber, lngReserved, 9)
        FilePut(lngIndexFileNumber, lngReserved, 13)

        'ヘッダと設定部分のデータを読み込んで、テンポラリファイルに書き込む
        ReDim bytBuffer(0 To lngHeaderSize - 1)
        FileGet(lngReadFileNumber, bytBuffer, 1)
        FilePut(lngTempFileNumber, bytBuffer, 1)
        FileClose(lngTempFileNumber)

        'ヘッダから、データの開始年と年数を読み出す
        .nStartYear = lngHeader(16)
        .nStartDayIndex = lngHeader(17)
        .nNumYears = lngHeader(18)

        '共通レコードのデータを読み込んで、テンポラリファイルに書き込む
        FileGet(lngReadFileNumber, lngPos, lngHeaderSize + 17)
        FileGet(lngReadFileNumber, lngSize, lngHeaderSize + 21)
        lngReserved = 0
        FilePut(lngIndexFileNumber, lngPos, 17)
        FilePut(lngIndexFileNumber, lngSize, 21)
        FilePut(lngIndexFileNumber, lngReserved, 25)
        FilePut(lngIndexFileNumber, lngReserved, 29)

        If (lngSize > 0) Then
            ReDim bytBuffer(0 To lngSize - 1)
            FileGet(lngReadFileNumber, bytBuffer, lngPos + 1)

            strTempFileName = strTempDir & "\.common"
            lngTempFileNumber = FreeFile()
            FileOpen(lngTempFileNumber, strTempFileName, OpenMode.Binary)
                FilePut(lngTempFileNumber, bytBuffer, 1)
            FileClose(lngTempFileNumber)
        End If

        'インデックスファイルに予約領域を作る
        For i = 2 To 3
            FilePut(lngIndexFileNumber, lngReserved, i * 16 + 1)
            FilePut(lngIndexFileNumber, lngReserved, i * 16 + 5)
            FilePut(lngIndexFileNumber, lngReserved, i * 16 + 9)
            FilePut(lngIndexFileNumber, lngReserved, i * 16 + 13)
        Next i

        '各年のデータを読み込んで、テンポラリファイルに書き込む
        For lngYear = 0 To .nNumYears - 1
            'ヘッダと設定の直後から、インデックステーブルを読み出す
            FileGet(lngReadFileNumber, lngPos, lngYear * 16 + lngHeaderSize + 65)
            FileGet(lngReadFileNumber, lngSize, lngYear * 16 + lngHeaderSize + 69)
            lngReserved = 0

            FilePut(lngIndexFileNumber, lngPos, lngYear * 16 + 65)
            FilePut(lngIndexFileNumber, lngSize, lngYear * 16 + 69)
            FilePut(lngIndexFileNumber, lngReserved, lngYear * 16 + 73)
            FilePut(lngIndexFileNumber, lngReserved, lngYear * 16 + 77)

            'その年のデータを読み出す
            ReDim bytBuffer(0 To lngSize - 1)
            FileGet(lngReadFileNumber, bytBuffer, lngPos + 1)

            'テンポラリファイルの名前を決定して、データを書き込む
            strTempFileName = .sTempFileDir & "\." & Trim$(Str$(.nStartYear + lngYear))
            lngTempFileNumber = FreeFile()
            FileOpen(lngTempFileNumber, strTempFileName, OpenMode.Binary)
                FilePut(lngTempFileNumber, bytBuffer, 1)
            FileClose(lngTempFileNumber)
        Next lngYear
    End With

    'すべてのファイルを閉じる
    FileClose(lngIndexFileNumber)
    FileClose(lngReadFileNumber)

    'ロード完了
    OpenAccountBook = True
End Function

Public Function PopAccountBook(
        ByRef utBook As Wrapper.AccountBook) As Long
'---------------------------------------------------------------------
'一時変数の内容を、指定した家計簿データに転送する
'[ IN] utBook: 家計簿データ
'[RET] Long
'  成功したら 1以上の整数
'  失敗したら 0
'---------------------------------------------------------------------

    utBook = gutTempBook
    PopAccountBook = 1
End Function

Public Function PushAccountBook(
        ByRef utBook As Wrapper.AccountBook) As Long
'---------------------------------------------------------------------
'一時変数に、家計簿のコピーを書き込む
'[ IN] utBook: 家計簿データ
'[RET] Long
'  成功したら 1以上の整数
'  失敗したら 0
'[VAR] gutTempBook : 一時変数。家計簿データのコピーが書き込まれる
'---------------------------------------------------------------------

    gutTempBook = utBook
    PushAccountBook = 1
End Function

Public Function ReadAccountBookCommons(
        ByRef utBook As Wrapper.AccountBook) As Boolean
'---------------------------------------------------------------------
'テンポラリファイルから、家計簿の共通レコードを読み込む
'[I/O] utBook : 家計簿データ
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------

    ReadAccountBookCommons = False
End Function

Public Function ReadAccountBookRecords(
        ByRef utBook As Wrapper.AccountBook,
        ByVal lngYear As Integer) As Boolean
'---------------------------------------------------------------------
'テンポラリファイルから、家計簿の指定された年のデータを読み込む
'[I/O] utBook : 家計簿データ
'[ IN] lngYear: 西暦年
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------
Dim lngYearIndex As Integer, lngSize As Integer
Dim lngItemBufferSize As Integer
Dim lngTempFileNumber As Integer
Dim strTempFileName As String

    lngYearIndex = lngYear - (utBook.nStartYear)
    If (lngYearIndex < 0) Then
        ReadAccountBookRecords = True
        Exit Function
    End If

    With utBook
        'テンポラリファイルを開く
        strTempFileName = .sTempFileDir & "\." & Trim$(Str$(lngYear))
        lngItemBufferSize = .utBookItems.getItemBufferSize()
        lngTempFileNumber = OpenTemporaryFile(strTempFileName, False)

        'データを読み込む
        lngSize = ReadAnnualRecords(.utAnnualRecords, lngTempFileNumber, lngItemBufferSize)
    End With

    'テンポラリファイルを閉じる
    FileClose(lngTempFileNumber)

    '読み込み完了
    ReadAccountBookRecords = True
End Function

Public Sub Recount(
        ByRef utBook As Wrapper.AccountBook, ByVal lngYear As Integer)
'---------------------------------------------------------------------
'---------------------------------------------------------------------
Dim i As Integer, lngItemBufferSize As Integer
Dim lngYearIndex As Integer, lngDate As Integer
Dim lngType As Integer, lngSubCount As Integer
Dim lngValue As Integer
Dim lngStartDayIndex As Integer, lngEndDayIndex As Integer
Dim lngItemFlags() As Integer
Dim blnResult As Boolean

    With utBook
        .nCurrentYear = lngYear
        lngYearIndex = lngYear - .nStartYear

        'すべての項目のフラグを取り出す
        With .utBookItems
            lngItemBufferSize = .nItemBufferSize
            lngItemFlags = .nFlags
        End With
    End With

    '初期値を書き込む
    With utBook.utAnnualRecords
        For i = 0 To lngItemBufferSize - 1
            If ((lngItemFlags(i) And Wrapper.ItemFlag.ITEM_FLAG_TYPEMASK) = Wrapper.ItemFlag.ITEM_FLAG_BALANCE) Then
                .utItemDetailCounts(i).nDayTotal(0) = .utItemAnnualCounts(i).nStartValues(lngYearIndex)
            End If
        Next i

        lngStartDayIndex = GetWeekday(lngYear, 1, 1)
        lngEndDayIndex = GetDayInYear(lngYear, 12, 31) + lngStartDayIndex

        'すべてのレシートを集計する
        For lngDate = 0 To utBook.nNumWeeks * NUMDAYSPERWEEK - 1
            'バッファをクリアする
            For i = 0 To lngItemBufferSize - 1
                If ((lngItemFlags(i) And Wrapper.ItemFlag.ITEM_FLAG_TYPEMASK) = Wrapper.ItemFlag.ITEM_FLAG_BALANCE) Then

                Else
                    .utItemDetailCounts(i).nDayTotal(lngDate) = 0
                End If
            Next i

            If (IsDayBeforeStart(utBook, lngYear, lngDate)) Then

            Else
                'データを書き込む
                For i = 0 To lngItemBufferSize - 1
                    lngSubCount = utBook.utBookItems.utItemEntries(i).nSubItemCount
                    If ((lngItemFlags(i) <> Wrapper.ItemFlag.ITEM_FLAG_NOTUSED) And (lngSubCount = 0)) Then
                        lngType = utBook.utBookItems.getItemType(i)

                        If (lngType = Wrapper.ItemFlag.ITEM_FLAG_INCOME) Or (lngType = Wrapper.ItemFlag.ITEM_FLAG_BANK_WITHDRAW) Then
                            If (Int(Rnd * 100) < 25) Then
                                lngValue = Int(Rnd * 11500)

                                'このデータを加算する
                                blnResult = AddDataToItemTotal(utBook, lngYearIndex, lngDate, i, lngValue)
                                If (blnResult) Then
                                    '残高に加える
                                    AddDataToItemTotal(utBook, lngYearIndex, lngDate, 3, lngValue)
                                End If
                            End If
                        ElseIf (lngType = Wrapper.ItemFlag.ITEM_FLAG_OUTLAY) Or (lngType = Wrapper.ItemFlag.ITEM_FLAG_BANK_DEPOSIT) Then
                            If (Int(Rnd * 100) < 15) Then
                                lngValue = Int(Rnd * 1000)

                                'このデータを加算する
                                blnResult = AddDataToItemTotal(utBook, lngYearIndex, lngDate, i, lngValue)
                                If (blnResult) Then
                                    '残高から引く
                                    AddDataToItemTotal(utBook, lngYearIndex, lngDate, 3, -lngValue)
                                End If
                            End If
                        End If
                    End If
                Next i
            End If

            'この日の残高を次の日の残高にコピーする
            For i = 0 To lngItemBufferSize - 1
                If ((lngItemFlags(i) And Wrapper.ItemFlag.ITEM_FLAG_TYPEMASK) = Wrapper.ItemFlag.ITEM_FLAG_BALANCE) Then
                    With .utItemDetailCounts(i)
                        .nDayTotal(lngDate + 1) = .nDayTotal(lngDate)
                    End With
                End If
            Next i
        Next lngDate
    End With
End Sub

Public Function SaveAccountBook(
        ByRef utBook As Wrapper.AccountBook,
        ByVal strFileName As String) As Boolean
'---------------------------------------------------------------------
'家計簿のデータをファイルに保存する
'[I/O] utBook     : 家計簿データ
'[ IN] strFileName: ファイル名
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'[ACT]
'  分解されて保存されているテンポラリファイルを連結して
'指定されたファイル名で保存する。
'---------------------------------------------------------------------
Dim i As Integer
Dim lngYear As Integer, lngNumYears As Integer, lngStartYear As Integer
Dim lngPos As Integer, lngSize As Integer, lngReserved As Integer
Dim lngTailPos As Integer, lngNextPos As Integer, lngSkipBytes As Integer
Dim lngHeaderSize As Integer
Dim bytBuffer() As Byte
Dim lngCommonRecordPos As Integer, lngYearRecordPos() As Integer
Dim lngCommonRecordSize As Integer, lngYearRecordSize() As Integer
Dim lngCommonRecordSkip As Integer, lngYearRecordSkip() As Integer
Dim lngWriteFileNumber As Integer
Dim lngTempFileNumber As Integer, lngIndexFileNumber As Integer
Dim strTempDir As String
Dim strTempFileName As String, strIndexFileName As String

    '-------------------------------------------------------------
    '家計簿データから必要なデータを取り出す
    With utBook
        strTempDir = .sTempFileDir
        lngNumYears = .nNumYears
        lngStartYear = .nStartYear
    End With

    '-------------------------------------------------------------
    '既にファイルがあれば、いったん削除する
    If (Dir$(strFileName) <> "") Then
        System.IO.File.Delete(strFileName)
    End If

    '-------------------------------------------------------------
    '出力ファイルを開く
    lngWriteFileNumber = FreeFile()
    FileOpen(lngWriteFileNumber, strFileName, OpenMode.Binary)

    '-------------------------------------------------------------
    'インデックスファイルを開く
    strIndexFileName = strTempDir & "\.index"
    lngIndexFileNumber = FreeFile()
    FileOpen(lngIndexFileNumber, strIndexFileName, OpenMode.Binary)

    '-------------------------------------------------------------
    'ヘッダ部分のテンポラリファイルを開く
    strTempFileName = strTempDir & "\.set"
    lngTempFileNumber = FreeFile()
    FileOpen(lngTempFileNumber, strTempFileName, OpenMode.Binary)

    '-------------------------------------------------------------
    'ヘッダ部分を書き込む
    lngPos = 1
    FileGet(lngIndexFileNumber, lngHeaderSize, 5)
    ReDim bytBuffer(0 To lngHeaderSize - 1)
    FileGet(lngTempFileNumber, bytBuffer, 1)
    FilePut(lngWriteFileNumber, bytBuffer, 1)
    FileClose(lngTempFileNumber)

    '-------------------------------------------------------------
    'インデックステーブルを書き込む
    lngReserved = 0
    FilePut(lngWriteFileNumber, lngReserved, (lngHeaderSize + 1))
    FilePut(lngWriteFileNumber, lngReserved, (lngHeaderSize + 5))
    FilePut(lngWriteFileNumber, lngReserved, (lngHeaderSize + 9))
    FilePut(lngWriteFileNumber, lngReserved, (lngHeaderSize + 13))

    lngCommonRecordPos = lngHeaderSize + 64 + (lngNumYears * 16)
    FileGet(lngIndexFileNumber, lngCommonRecordSize, 21)
    lngTailPos = lngCommonRecordPos + lngCommonRecordSize
    lngNextPos = (lngTailPos + 255) And &H7FFFFF00
    lngCommonRecordSkip = (lngNextPos - lngTailPos)
    lngReserved = 0

    FilePut(lngWriteFileNumber, lngCommonRecordPos, (lngHeaderSize + 17))
    FilePut(lngWriteFileNumber, lngCommonRecordSize, (lngHeaderSize + 21))
    FilePut(lngWriteFileNumber, lngCommonRecordSkip, (lngHeaderSize + 25))
    FilePut(lngWriteFileNumber, lngReserved, (lngHeaderSize + 29))
    lngPos = lngNextPos

    lngReserved = 0
    For i = 2 To 3
        FilePut(lngWriteFileNumber, lngReserved, (lngHeaderSize + i * 16 + 1))
        FilePut(lngWriteFileNumber, lngReserved, (lngHeaderSize + i * 16 + 5))
        FilePut(lngWriteFileNumber, lngReserved, (lngHeaderSize + i * 16 + 9))
        FilePut(lngWriteFileNumber, lngReserved, (lngHeaderSize + i * 16 + 13))
    Next i

    If (lngNumYears > 0) Then
        ReDim lngYearRecordPos(0 To lngNumYears - 1)
        ReDim lngYearRecordSize(0 To lngNumYears - 1)
        ReDim lngYearRecordSkip(0 To lngNumYears - 1)
    Else
        ReDim lngYearRecordPos(0)
        ReDim lngYearRecordSize(0)
        ReDim lngYearRecordSkip(0)
    End If

    For lngYear = 0 To lngNumYears - 1
        FileGet(lngIndexFileNumber, lngSize, (lngYear * 16 + 69))

        lngTailPos = lngPos + lngSize
        lngNextPos = (lngTailPos + 255) And &H7FFFFF00
        lngSkipBytes = (lngNextPos - lngTailPos)

        lngYearRecordPos(lngYear) = lngPos
        lngYearRecordSize(lngYear) = lngSize
        lngYearRecordSkip(lngYear) = lngSkipBytes

        FilePut(lngWriteFileNumber, lngPos, (lngYear * 16 + lngHeaderSize + 65))
        FilePut(lngWriteFileNumber, lngSize, (lngYear * 16 + lngHeaderSize + 69))
        FilePut(lngWriteFileNumber, lngSkipBytes,
                (lngYear * 16 + lngHeaderSize + 73))
        FilePut(lngWriteFileNumber, lngReserved,
               (lngYear * 16 + lngHeaderSize + 77))

        lngPos = lngNextPos
    Next lngYear

    '-------------------------------------------------------------
    '共通レコードを書き込む
    lngPos = lngCommonRecordPos
    lngSize = lngCommonRecordSize
    lngSkipBytes = lngCommonRecordSkip

    If (lngSize > 0) Then
        strTempFileName = strTempDir & "\.common"
        lngTempFileNumber = FreeFile()
        FileOpen(lngTempFileNumber, strTempFileName, OpenMode.Binary)

        ReDim bytBuffer(0 To lngSize - 1)
        FileGet(lngTempFileNumber, bytBuffer, 1)
        FilePut(lngWriteFileNumber, bytBuffer, lngPos + 1)

        FileClose(lngTempFileNumber)
    End If

    If (lngSkipBytes > 0) Then
        ReDim bytBuffer(0 To lngSkipBytes - 1)
        FilePut(lngWriteFileNumber, bytBuffer, lngPos + lngSize + 1)
    End If

    '-------------------------------------------------------------
    '各年のデータを書き込む
    For lngYear = 0 To lngNumYears - 1
        lngPos = lngYearRecordPos(lngYear)
        lngSize = lngYearRecordSize(lngYear)
        lngSkipBytes = lngYearRecordSkip(lngYear)

        If (lngSize > 0) Then
            'テンポラリファイルを開く
            strTempFileName = strTempDir & "\." & Trim$(Str$(lngStartYear + lngYear))
            lngTempFileNumber = FreeFile()
            FileOpen(lngTempFileNumber, strTempFileName, OpenMode.Binary)

            'テンポラリファイルから、データを読み込む
            ReDim bytBuffer(0 To lngSize - 1)
            FileGet(lngTempFileNumber, bytBuffer, 1)

            '出力ファイルの指定された位置に書き込む
            FilePut(lngWriteFileNumber, bytBuffer, lngPos + 1)

            'テンポラリファイルを閉じる
            FileClose(lngTempFileNumber)
        End If

        '次のデータの開始位置まで、空のデータを埋める
        If (lngSkipBytes > 0) Then
            ReDim bytBuffer(0 To lngSkipBytes - 1)
            FilePut(lngWriteFileNumber, bytBuffer, lngPos + lngSize + 1)
        End If
    Next lngYear

    'すべてのファイルを閉じる
    FileClose(lngWriteFileNumber)
    FileClose(lngIndexFileNumber)

    'セーブ完了
    SaveAccountBook = True
End Function

Public Sub SetAccountBookStartDate(
        ByRef utBook As Wrapper.AccountBook,
        ByVal lngStartYear As Integer,
        ByVal lngStartMonth As Integer,
        ByVal lngStartDay As Integer)
'---------------------------------------------------------------------
'開始日を設定する
'[I/O] utBook        : 家計簿データ
'[ IN] lngStartYear  : 開始年
'[ IN] lngStartMonth : 開始月
'[ IN] lngStartDay   : 開始日
'[RET] なし
'---------------------------------------------------------------------
Dim lngDayIndex As Integer, lngDayOffset As Integer

    lngDayOffset = GetWeekday(lngStartYear, 1, 1)
    lngDayIndex = GetDayInYear(lngStartYear, lngStartMonth, lngStartDay)
    lngDayIndex = lngDayIndex + lngDayOffset

    With utBook
        GetDayFromIndex(.utStartDate, lngStartYear, lngDayIndex, lngDayOffset)

        .nStartYear = .utStartDate.nYear
        .nStartDayIndex = lngDayIndex
    End With
End Sub

Public Sub SetAccountBookNumYears(
        ByRef utBook As Wrapper.AccountBook, ByVal lngNumYears As Integer)
'---------------------------------------------------------------------
'データの年数を設定する
'[I/O] utBook        : 家計簿データ
'[ IN] lngNumYears   : 家計簿の年数
'[RET] なし
'---------------------------------------------------------------------

    With utBook
        ReallocAnnualRecordsBuffers(
                .utAnnualRecords, -1, .nStartYear, lngNumYears)
        .nNumYears = lngNumYears
    End With
End Sub

Public Function UpdateIndexFile(
        ByVal strTempDir As String,
        ByVal lngKey As Integer, ByVal lngPos As Integer,
        ByVal lngSize As Integer) As Boolean
'---------------------------------------------------------------------
'インデックスファイルの一部を書き換える
'[ IN] strTempDir: テンポラリファイルの格納されるディレクトリ
'[ IN] lngKey    : インデックスデータのキー
'[ IN] lngPos    : インデックステーブルに書き込む「位置」の値
'[ IN] lngSize   : インデックステーブルに書き込む「サイズ」の値
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'[ACT]
'  テンポラリディレクトリにある".index"ファイルを更新する
'  指定されたキー(1レコード16Bytes)の、
'位置(第 1フィールド)とサイズ(第 2フィールド)を指定した値で更新する
'---------------------------------------------------------------------
Dim lngWritePos As Integer
Dim lngIndexFileSize As Integer
Dim lngFillLength As Integer
Dim lngIndexFileNumber As Integer
Dim strIndexFileName As String
Dim bytBuffer() As Byte

    'インデックスファイルのファイルサイズを取得する
    strIndexFileName = strTempDir & "\.index"
    lngIndexFileSize = FileLen(strIndexFileName)

    '書き込む位置を決定する
    lngWritePos = lngKey * 16

    'インデックスファイルを開く
    lngIndexFileNumber = FreeFile()
    FileOpen(lngIndexFileNumber, strIndexFileName, OpenMode.Binary)

    '書き込む位置がファイルの終端を越えていれば
    'その直前まで０を埋める
    lngFillLength = (lngWritePos + 16) - lngIndexFileSize
    If (lngFillLength > 0) Then
        ReDim bytBuffer(0 To lngFillLength - 1)
        FilePut(lngIndexFileNumber, bytBuffer, lngIndexFileSize + 1)
    End If

    'データを更新する
    If (lngPos >= 0) Then
        FilePut(lngIndexFileNumber, lngPos, lngWritePos + 1)
    End If
    If (lngSize >= 0) Then
        FilePut(lngIndexFileNumber, lngSize, lngWritePos + 5)
    End If

'    lngReserved = 0
'    Put #lngIndexFileNumber, lngWritePos + 9, lngReserved
'    Put #lngIndexFileNumber, lngWritePos + 13, lngReserved

    'インデックスファイルを閉じる
    FileClose(lngIndexFileNumber)

    '更新完了
    UpdateIndexFile = True
End Function

Public Function WriteAccountBookCommons(
        ByRef utBook As Wrapper.AccountBook) As Boolean
'---------------------------------------------------------------------
'テンポラリファイルに、家計簿の共通レコードを書き込む
'[ IN] utBook: 家計簿データ
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------
Dim lngItemBufferSize As Integer
Dim lngFileLen As Integer
Dim lngTempFileNumber As Integer
Dim strTempDir As String, strTempFileName As String

    With utBook
        strTempDir = .sTempFileDir

        'テンポラリファイルを開く
        strTempFileName = strTempDir & "\.common"
        lngItemBufferSize = .utBookItems.getItemBufferSize()
        lngTempFileNumber = OpenTemporaryFile(strTempFileName, True)

        'データを書き込む
    End With

    'テンポラリファイルを閉じる
    FileClose(lngTempFileNumber)

    'インデックスファイルを更新する
    lngFileLen = FileLen(strTempFileName)
    WriteAccountBookCommons = UpdateIndexFile(strTempDir, 1, -1, lngFileLen)
End Function

Public Function WriteAccountBookRecords(
        ByRef utBook As Wrapper.AccountBook,
        ByVal lngYear As Integer) As Boolean
'---------------------------------------------------------------------
'テンポラリファイルに、家計簿の指定された年のデータを書き込む
'[ IN] utBook : 家計簿データ
'[ IN] lngYear: 西暦年
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------
Dim lngYearIndex As Integer, lngSize As Integer, lngFileLen As Integer
Dim lngItemBufferSize As Integer
Dim lngTempFileNumber As Integer
Dim strTempDir As String
Dim strTempFileName As String
Dim blnResult As Boolean

    lngYearIndex = lngYear - (utBook.nStartYear)
    If (lngYearIndex < 0) Then
        WriteAccountBookRecords = True
        Exit Function
    End If

    blnResult = True

    With utBook
        strTempDir = .sTempFileDir

        'テンポラリファイルを開く
        strTempFileName = strTempDir & "\." & Trim$(Str$(lngYear))
        lngItemBufferSize = .utBookItems.getItemBufferSize()
        lngTempFileNumber = OpenTemporaryFile(strTempFileName, True)

        'データを書き込む
        lngSize = WriteAnnualRecords(.utAnnualRecords, lngTempFileNumber, lngItemBufferSize)
    End With

    'テンポラリファイルを閉じる
    FileClose(lngTempFileNumber)

    'インデックスファイルを更新する
    lngFileLen = FileLen(strTempFileName)
    If (lngSize <> lngFileLen) Then
        MessageBox.Show("設定の保存に失敗しました。")
        blnResult = False
    Else
        blnResult = UpdateIndexFile(strTempDir, lngYearIndex + 4, -1, lngFileLen)
    End If

    '書き込み完了
    WriteAccountBookRecords = blnResult
End Function

End Module
