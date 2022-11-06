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

Public Function GetAccountBookNumYears(ByRef utBook As tAccountBook) As Integer
'---------------------------------------------------------------------
'家計簿のデータが何年分あるかを返す
'[ IN] utBook: 家計簿データ
'[RET] Long
'  データの年数
'---------------------------------------------------------------------
    GetAccountBookNumYears = utBook.nNumYears
End Function

Public Function GetAccountBookStartYear(ByRef utBook As tAccountBook) As Integer
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
        strTempDir = gstrAppDir & "\Resource"
        utBook.sTempFileDir = strTempDir

        '入力ファイルを開く
        lngReadFileNumber = FreeFile()
        Open strFileName For Binary As #lngReadFileNumber

        'インデックスファイルを開く
        strIndexFileName = .sTempFileDir & "\.index"
        lngIndexFileNumber = FreeFile()
        Open strIndexFileName For Binary As #lngIndexFileNumber

        'ヘッダ部分のテンポラリファイルを開く
        strTempFileName = .sTempFileDir & "\.set"
        lngTempFileNumber = FreeFile()
        Open strTempFileName For Binary As #lngTempFileNumber

        '入力ファイルのヘッダ部分を取り出す
        ReDim lngHeader(0 To 63)
        Get #lngReadFileNumber, 1, lngHeader()

        'ヘッダの 6番目の項目(0x00000014)から、ヘッダと設定部分のデータサイズを得る
        lngPos = 1
        lngHeaderSize = lngHeader(5)
        lngReserved = 0
        Put #lngIndexFileNumber, 1, lngPos
        Put #lngIndexFileNumber, 5, lngHeaderSize
        Put #lngIndexFileNumber, 9, lngReserved
        Put #lngIndexFileNumber, 13, lngReserved

        'ヘッダと設定部分のデータを読み込んで、テンポラリファイルに書き込む
        ReDim bytBuffer(0 To lngHeaderSize - 1)
        Get #lngReadFileNumber, 1, bytBuffer()
        Put #lngTempFileNumber, 1, bytBuffer()
        Close #lngTempFileNumber

        'ヘッダから、データの開始年と年数を読み出す
        .nStartYear = lngHeader(16)
        .nStartDayIndex = lngHeader(17)
        .nNumYears = lngHeader(18)

        '共通レコードのデータを読み込んで、テンポラリファイルに書き込む
        Get #lngReadFileNumber, lngHeaderSize + 17, lngPos
        Get #lngReadFileNumber, lngHeaderSize + 21, lngSize
        lngReserved = 0
        Put #lngIndexFileNumber, 17, lngPos
        Put #lngIndexFileNumber, 21, lngSize
        Put #lngIndexFileNumber, 25, lngReserved
        Put #lngIndexFileNumber, 29, lngReserved

        If (lngSize > 0) Then
            ReDim bytBuffer(0 To lngSize - 1)
            Get #lngReadFileNumber, lngPos + 1, bytBuffer()

            strTempFileName = strTempDir & "\.common"
            lngTempFileNumber = FreeFile()
            Open strTempFileName For Binary As #lngTempFileNumber
                Put #lngTempFileNumber, 1, bytBuffer()
            Close #lngTempFileNumber
        End If

        'インデックスファイルに予約領域を作る
        For i = 2 To 3
            Put #lngIndexFileNumber, i * 16 + 1, lngReserved
            Put #lngIndexFileNumber, i * 16 + 5, lngReserved
            Put #lngIndexFileNumber, i * 16 + 9, lngReserved
            Put #lngIndexFileNumber, i * 16 + 13, lngReserved
        Next i

        '各年のデータを読み込んで、テンポラリファイルに書き込む
        For lngYear = 0 To .nNumYears - 1
            'ヘッダと設定の直後から、インデックステーブルを読み出す
            Get #lngReadFileNumber, lngYear * 16 + lngHeaderSize + 65, lngPos
            Get #lngReadFileNumber, lngYear * 16 + lngHeaderSize + 69, lngSize
            lngReserved = 0

            Put #lngIndexFileNumber, lngYear * 16 + 65, lngPos
            Put #lngIndexFileNumber, lngYear * 16 + 69, lngSize
            Put #lngIndexFileNumber, lngYear * 16 + 73, lngReserved
            Put #lngIndexFileNumber, lngYear * 16 + 77, lngReserved

            'その年のデータを読み出す
            ReDim bytBuffer(0 To lngSize - 1)
            Get #lngReadFileNumber, lngPos + 1, bytBuffer()

            'テンポラリファイルの名前を決定して、データを書き込む
            strTempFileName = .sTempFileDir & "\." & Trim$(Str$(.nStartYear + lngYear))
            lngTempFileNumber = FreeFile()
            Open strTempFileName For Binary As #lngTempFileNumber
                Put #lngTempFileNumber, 1, bytBuffer()
            Close #lngTempFileNumber
        Next lngYear
    End With

    'すべてのファイルを閉じる
    Close #lngIndexFileNumber
    Close #lngReadFileNumber

    'ロード完了
    OpenAccountBook = True
End Function

End Module
