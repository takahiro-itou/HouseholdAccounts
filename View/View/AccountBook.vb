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

Public gutTempBook As tAccountBook

Public Function AccountBookUpdateItemHandleInYearRecord(
        ByRef lpBookItems As tBookItems,
        ByRef lpNewIndex() As Integer,
        ByRef utYearRecord As tAnnualRecords) As Integer
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
Dim utDetailCounts() As tBookItemDetailCounts

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
                        .nRootItemType = BookItemGetRootItemHandle(lpBookItems, lngNew)
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

Public Function AddDataToItemTotal(ByRef utBook As tAccountBook,
        ByVal lngYearIndex As Integer, ByVal lngDayIndex As Integer,
        ByVal lngItemIndex As Integer, ByVal lngValue As Integer) As Boolean
'---------------------------------------------------------------------
'---------------------------------------------------------------------
Dim lngFlags() As Integer
Dim lngParentHandle As Integer
Dim lngYear As Integer, lngWeek As Integer, lngMonth As Integer
Dim utDate As tParsedDate
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

            If (lngFlags(lngItemIndex) And ITEM_FLAG_NOCOUNT_PARENT) Then
                blnAddToParent = False
                blnAddToRoot = False
            End If
            If (lngFlags(lngItemIndex) And ITEM_FLAG_NOCOUNT_ROOT) Then
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

Public Function ChangeAccountBookYear(ByRef utBook As tAccountBook,
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
        ReallocAnnualRecordsBuffers utBook.utAnnualRecords, -1, lngStartYear, lngNumYears
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

Public Sub CloseAccountBook(ByRef utBook As tAccountBook)
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
        ByRef utBook As tAccountBook) As Boolean
'---------------------------------------------------------------------
'家計簿の内容を初期状態にセットする
'[OUT] utBook : 家計簿データ
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------
    CreateEmptyAccountBook = False
End Function

Public Function EnableAccountBook(ByRef utBook As tAccountBook, _
    ByVal blnEnabled As Boolean) As Boolean
'---------------------------------------------------------------------
'家計簿を有効／無効にする
'[I/O] utBook    : 家計簿データ
'[ IN] blnEnabled: Trueなら有効にし, False なら無効にする
'[RET] Boolean
'  変更後の状態をそのまま返す
'---------------------------------------------------------------------
    utBook.bEnabled = blnEnabled
    EnableAccountBook = blnEnabled
End Function

Public Function GetAccountBookNumYears(
        ByRef utBook As tAccountBook) As Integer
'---------------------------------------------------------------------
'家計簿のデータが何年分あるかを返す
'[ IN] utBook: 家計簿データ
'[RET] Long
'  データの年数
'---------------------------------------------------------------------
    GetAccountBookNumYears = utBook.nNumYears
End Function

Public Function GetAccountBookStartYear(
        ByRef utBook As tAccountBook) As Integer
'---------------------------------------------------------------------
'家計簿の開始年を返す
'[ IN] utBook: 家計簿データ
'[RET] Long
'  開始西暦年
'---------------------------------------------------------------------
    GetAccountBookStartYear = utBook.nStartYear
End Function

Public Function IsAccountBookEnabled(ByRef utBook As tAccountBook) As Boolean
'---------------------------------------------------------------------
'家計簿データが有効なデータかどうか判断する
'[ IN] utBook : 家計簿データ
'[RET] Boolean
'  有効ならTrue, 無効なら False
'[ACT]
'  初期化されていない状態などは無効なデータである。
'  新規作成、ロードなどを行って、家計簿の処理ができる状態に
'移行していれば有効なデータである。
'---------------------------------------------------------------------
    IsAccountBookEnabled = utBook.bEnabled
End Function

Public Function IsDayBeforeStart(ByRef utBook As tAccountBook, _
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

Public Function OpenAccountBook(ByRef utBook As tAccountBook, _
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
        strTempDir = g_appPath & "\Resource"
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

Public Function PopAccountBook(ByRef utBook As tAccountBook) As Long
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

Public Function PushAccountBook(ByRef utBook As tAccountBook) As Long
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
        ByRef utBook As tAccountBook) As Boolean
'---------------------------------------------------------------------
'テンポラリファイルから、家計簿の共通レコードを読み込む
'[I/O] utBook : 家計簿データ
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------

    ReadAccountBookCommons = False
End Function

Public Function ReadAccountBookRecords(ByRef utBook As tAccountBook, _
        ByVal lngYear As Integer) As Boolean
'---------------------------------------------------------------------
'テンポラリファイルから、家計簿の指定された年のデータを読み込む
'[I/O] utBook : 家計簿データ
'[ IN] lngYear: 西暦年
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------

    ReadAccountBookRecords = True
End Function

Public Sub Recount(ByRef utBook As tAccountBook, ByVal lngYear As Integer)
'---------------------------------------------------------------------
'---------------------------------------------------------------------

End Sub

Public Function SaveAccountBook(ByRef utBook As tAccountBook,
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

    SaveAccountBook = True
End Function

Public Sub SetAccountBookStartDate(ByRef utBook As tAccountBook,
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

End Sub

Public Sub SetAccountBookNumYears(
        ByRef utBook As tAccountBook, ByVal lngNumYears As Integer)
'---------------------------------------------------------------------
'データの年数を設定する
'[I/O] utBook        : 家計簿データ
'[ IN] lngNumYears   : 家計簿の年数
'[RET] なし
'---------------------------------------------------------------------

End Sub

Public Function UpdateIndexFile(ByVal strTempDir As String, _
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

    UpdateIndexFile = True
End Function

Public Function WriteAccountBookCommons(
        ByRef utBook As tAccountBook) As Boolean
'---------------------------------------------------------------------
'テンポラリファイルに、家計簿の共通レコードを書き込む
'[ IN] utBook: 家計簿データ
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------

    WriteAccountBookCommons = False
End Function

Public Function WriteAccountBookRecords(ByRef utBook As tAccountBook, _
    ByVal lngYear As Long) As Boolean
'---------------------------------------------------------------------
'テンポラリファイルに、家計簿の指定された年のデータを書き込む
'[ IN] utBook : 家計簿データ
'[ IN] lngYear: 西暦年
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------

    WriteAccountBookRecords = False
End Function

End Module
