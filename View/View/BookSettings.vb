Option Explicit

Module BookSettings

'*****************************************************************************
' AccountBook
' BookSettings  モジュール
'
' 家計簿を管理する
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2006/09/23 - 2008/01/06
'*****************************************************************************

'=========================================================================
'
'パブリックプロシージャ
'

Public Function AllocBookItems(
        ByRef utBook As Wrapper.AccountBook,
        ByVal lngItemBufferSize As Integer) As Integer
'---------------------------------------------------------------------
'項目データ用バッファを確保する
'[I/O] utBook            : 家計簿データ
'[ IN] lngItemBufferSize : 確保する項目数
'[RET] Long
'  増えた部分の先頭のインデックス
'---------------------------------------------------------------------
Dim lngBufferSize As Integer
Dim lngStartYear As Integer, lngNumYears As Integer
Dim lngResult As Integer

    With utBook
        lngStartYear = .nStartYear
        lngNumYears = .nNumYears

        'バッファをリサイズし、増えた部分の先頭を記録しておく
        With .utBookItems
            lngResult = .nItemBufferSize
            lngBufferSize = (lngItemBufferSize + 15) And &H7FFFFFF0
            .nItemBufferSize = lngBufferSize

            ReDim .nFlags(0 To lngBufferSize - 1)
            ReDim .utItemEntries(0 To lngBufferSize - 1)
        End With

        .utAnnualRecords.reallocBuffers(
                lngBufferSize, lngStartYear, lngNumYears)
    End With

    AllocBookItems = lngResult
End Function

Public Function BookItemAllocNewItem(
        ByRef utBook As Wrapper.AccountBook) As Integer
'---------------------------------------------------------------------
'新しい項目用の領域を確保し、そのハンドルを返す
'[I/O] utBook: 家計簿データ
'[RET] Long
'  新しい項目用のハンドル
'---------------------------------------------------------------------
Dim i As Integer
Dim lngResult As Integer

    With utBook
        'バッファサイズと登録済み項目数を比較し、
        'バッファに空きがある場合は、
        '空きを探してそのバンドル(インデックス)を返す
        lngResult = -1
        With .utBookItems
            If (.nRegisteredItemCount < .nItemBufferSize) Then
                For i = .nRootItemCount To .nItemBufferSize - 1
                    If (.nFlags(i) = Wrapper.ItemFlag.ITEM_FLAG_NOTUSED) Then
                        lngResult = i
                        Exit For
                    End If
                Next i
            End If
        End With
    End With

    If (lngResult >= 0) Then
        BookItemAllocNewItem = lngResult
        Exit Function
    End If

    'バッファをリサイズし、増えた部分の先頭を確保する
    BookItemAllocNewItem = AllocBookItems(utBook, lngResult)
End Function

Public Function InsertNewBookItem(
        ByRef utBook As Wrapper.AccountBook,
        ByVal lngParentItemHandle As Integer, ByVal strName As String,
        ByVal lngFlags As Integer, ByVal lngStartDate As Integer,
        ByVal lngStartBalance As Integer) As Integer
'---------------------------------------------------------------------
'指定した項目に新しいサブ項目を追加する
'[I/O] utBookItems         : 項目一覧データ
'[I/O] utYearRecord        : 年間レコードデータ
'[ IN] lngParentItemHandle : 親項目のハンドル
'[ IN] strName             : 項目名
'[ IN] lngFlags            : 項目フラグ
'[ IN] lngStartDate        : 開始日
'[ IN] lngStartBalance     : 開始時金額
'[RET] Long
'  追加した項目のハンドル
'---------------------------------------------------------------------
Dim lngNewItemHandle As Integer

    '新しい項目用のインデックスを取得する
    lngNewItemHandle = BookItemAllocNewItem(utBook)

    With utBook.utBookItems
        'この項目に初期値を書き込む
        .nFlags(lngNewItemHandle) = lngFlags
        With .utItemEntries(lngNewItemHandle)
            .nParentHandle = lngParentItemHandle
            .sItemName = strName
            .nSubItemCount = 0
            .nStartDate = lngStartDate
            .nStartBalance = lngStartBalance
        End With

        .nRegisteredItemCount = .nRegisteredItemCount + 1

        '親項目の内容を更新する
        With .utItemEntries(lngParentItemHandle)
            ReDim Preserve .nSubItems(0 To .nSubItemCount)
            .nSubItems(.nSubItemCount) = lngNewItemHandle
            .nSubItemCount = .nSubItemCount + 1
        End With
    End With

    '追加した新しい項目のハンドルを返す
    InsertNewBookItem = lngNewItemHandle
End Function

Public Function ReadAccountBookSettings(
        ByRef utBook As Wrapper.AccountBook) As Boolean
'---------------------------------------------------------------------
'テンポラリファイル(.set)から、家計簿の設定を読み込む
'[I/O] utBook : 家計簿データ
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------
Dim i As Integer, lngItemCount As Integer, lngRootItemCount As Integer
Dim lngResult As Integer
Dim lngHandle As Integer, lngFlags As Integer
Dim lngStartDate As Integer, lngStartBalance As Integer
Dim lngNameID As Integer, lngReserved As Integer
Dim lngHeader() As Integer
Dim strTemp As String

Dim lngStartPos As Integer
Dim lngTablePos As Integer, lngTableSize As Integer
Dim lngDataPos As Integer, lngDataSize As Integer
Dim lngTempFileNumber As Integer
Dim strTempDir As String, strTempFileName As String

    With utBook
        'テンポラリファイルを開く
        strTempDir = .sTempFileDir
        strTempFileName = strTempDir & "\.set"
        lngTempFileNumber = OpenTemporaryFile(strTempFileName, False)

        lngStartPos = 0

        'ヘッダを読み込む
        ReDim lngHeader(0 To 63)
        FileGet(lngTempFileNumber, lngHeader, lngStartPos + 1)
        lngTablePos = lngHeader(8)
        lngTableSize = lngHeader(9)
        lngDataPos = lngHeader(10)
        lngDataSize = lngHeader(11)

        .nStartYear = lngHeader(16)
        .nStartDayIndex = lngHeader(17)
        .nNumYears = lngHeader(18)
        If ((.nStartYear > 0) And (.nNumYears > 0)) Then
            .utStartDate = Wrapper.ManagedDate.getDayFromIndex(
                                .nStartYear, .nStartDayIndex, -1)
        End If

        lngItemCount = lngHeader(32)
        lngRootItemCount = lngHeader(33)

        'バッファを確保する
        AllocBookItems(utBook, lngItemCount)

        With .utBookItems
            .nRootItemCount = lngRootItemCount
            .nRegisteredItemCount = lngRootItemCount
            .nInnerTaxItemHandle = lngHeader(36)
            .nOuterTaxItemHandle = lngHeader(37)
        End With

        'ヘッダ用の文字列テーブルを読み込む
        Seek(lngTempFileNumber, lngStartPos + lngTablePos + 1)
        ReadStringTable(.utSettingsStringTable, lngTempFileNumber)

        '項目データ
        Seek(lngTempFileNumber, lngStartPos + lngDataPos + 1)
        For i = 0 To lngItemCount - 1
            FileGet(lngTempFileNumber, lngHandle)
            FileGet(lngTempFileNumber, lngFlags)
            FileGet(lngTempFileNumber, lngStartDate)
            FileGet(lngTempFileNumber, lngStartBalance)
            FileGet(lngTempFileNumber, lngNameID)
            FileGet(lngTempFileNumber, lngReserved)
            FileGet(lngTempFileNumber, lngReserved)
            FileGet(lngTempFileNumber, lngReserved)
            strTemp = .utSettingsStringTable.sTableEntries(lngNameID)

            If (i < lngRootItemCount) Then
                With .utBookItems
                    .nFlags(i) = lngFlags
                    With .utItemEntries(i)
                        .nParentHandle = -1
                        .sItemName = strTemp
                        .nSubItemCount = 0
                        .nStartDate = lngStartDate
                        .nStartBalance = lngStartBalance
                    End With
                End With
            Else
                lngResult = InsertNewBookItem(utBook, lngHandle, strTemp, lngFlags, lngStartDate, lngStartBalance)
                If (lngResult <> i) Then
                    MessageBox.Show("エラー：追加されたサブアイテムのインデックスが一致しません。" & _
                        vbCrLf & "インデックス：" & i & vbCrLf & _
                        "　　追加位置：" & lngResult)
                End If
            End If
        Next i
    End With

    'テンポラリファイルを閉じる
    FileClose(lngTempFileNumber)

    '読み込み完了
    ReadAccountBookSettings = True
End Function

Public Function WriteAccountBookSettings(
        ByRef utBook As Wrapper.AccountBook) As Boolean
'---------------------------------------------------------------------
'テンポラリファイル(.set)に、家計簿の設定を書き込む
'[ IN] utBook : 家計簿データ
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------
Dim i As Integer, lngItemCount As Integer
Dim lngHandle As Integer, lngFlags As Integer
Dim lngStartDate As Integer, lngStartBalance As Integer
Dim lngNameID As Integer, lngReserved As Integer
Dim lngStartPos As Integer, lngEndPos As Integer
Dim lngTablePos As Integer, lngTableSize As Integer
Dim lngDataPos As Integer, lngDataSize As Integer
Dim lngHeader() As Integer
Dim strTemp As String
Dim lngFileLen As Integer
Dim lngTempFileNumber As Integer, lngIndexFileNumber As Integer
Dim strTempDir As String
Dim strTempFileName As String, strIndexFileName As String
Dim blnResult As Boolean

    blnResult = True

    'ヘッダを用意する
    ReDim lngHeader(0 To 63)

    lngHeader(0) = 0                '0
    lngHeader(1) = &H1A444241       'シグネチャ:ABD^
    lngHeader(2) = &H10000          'バージョン
    lngHeader(3) = 0                '識別コード
    lngHeader(63) = &HAA550000      'シグネチャ

    With utBook
        '開始日と年数をヘッダに書き込む
        lngHeader(16) = .nStartYear
        lngHeader(17) = .nStartDayIndex
        lngHeader(18) = .nNumYears

        '各データの件数をヘッダに書き込む
        With .utBookItems
            lngItemCount = .getRegisteredItemCount()
            lngHeader(32) = lngItemCount
            lngHeader(33) = .getRootItemCount()

            lngHeader(36) = .nInnerTaxItemHandle
            lngHeader(37) = .nOuterTaxItemHandle
        End With

        'テンポラリファイルのディレクトリを取得する
        strTempDir = .sTempFileDir

        'テンポラリファイルを開く
        strTempFileName = strTempDir & "\.set"
        lngTempFileNumber = OpenTemporaryFile(strTempFileName, True)

        'ヘッダを書き込む
        lngStartPos = 0
        FilePut(lngTempFileNumber, lngHeader, lngStartPos + 1)

        'ヘッダ用の文字列テーブルを書き込む
        lngTablePos = 256
        Seek(lngTempFileNumber, lngStartPos + lngTablePos + 1)
        lngTableSize = WriteStringTable(.utSettingsStringTable, lngTempFileNumber)
        lngDataPos = lngTablePos + lngTableSize

        '項目データ
        With .utBookItems
            Seek(lngTempFileNumber, lngStartPos + lngDataPos + 1)
            For i = 0 To lngItemCount - 1
                lngFlags = .nFlags(i)
                With .utItemEntries(i)
                    lngHandle = .nParentHandle
                    strTemp = .sItemName
                    lngStartDate = .nStartDate
                    lngStartBalance = .nStartBalance
                    lngReserved = 0
                End With

                lngNameID = utBook.utSettingsStringTable.findString(strTemp)

                FilePut(lngTempFileNumber, lngHandle)
                FilePut(lngTempFileNumber, lngFlags)
                FilePut(lngTempFileNumber, lngStartDate)
                FilePut(lngTempFileNumber, lngStartBalance)
                FilePut(lngTempFileNumber, lngNameID)
                FilePut(lngTempFileNumber, lngReserved)
                FilePut(lngTempFileNumber, lngReserved)
                FilePut(lngTempFileNumber, lngReserved)
            Next i
        End With
    End With

    '書き込んだバイト数をチェックする
    lngEndPos = Seek(lngTempFileNumber) - 1
    lngDataSize = lngEndPos - lngDataPos

    'ヘッダの0x0010 - 0x002F にファイルやデータの位置とサイズを記録する
    lngHeader(4) = 256                          'ヘッダサイズ
    lngHeader(5) = lngEndPos - lngStartPos      'ファイルサイズ
    lngHeader(6) = 0
    lngHeader(7) = 0
    lngHeader(8) = lngTablePos              '文字列テーブルの開始位置
    lngHeader(9) = lngTableSize             '文字列テーブルのサイズ
    lngHeader(10) = lngDataPos              'データの開始位置
    lngHeader(11) = lngDataSize             'データのサイズ
    lngHeader(12) = 0
    lngHeader(13) = 0
    lngHeader(14) = 0
    lngHeader(15) = 0
    FilePut(lngTempFileNumber, lngHeader, lngStartPos + 1)

    'テンポラリファイルを閉じる
    FileClose(lngTempFileNumber)

    'インデックスファイルを更新する
    lngFileLen = FileLen(strTempFileName)
    If (lngEndPos <> lngFileLen) Then
        MessageBox.Show("設定の保存に失敗しました。")
        blnResult = False
    Else
        blnResult = UpdateIndexFile(strTempDir, 0, -1, lngFileLen)
    End If

    '書き込み完了
    WriteAccountBookSettings = blnResult
    Exit Function

    With utBook
        'インデックスファイルを開いて、書き込んだバイト数を保存する
        strIndexFileName = strTempDir & "\.index"
        lngIndexFileNumber = FreeFile()
        FileOpen(lngIndexFileNumber, strIndexFileName, OpenMode.Binary)
    End With

    FilePut(lngIndexFileNumber, lngFileLen, 5)

    'すべてのファイルを閉じる
    FileClose(lngIndexFileNumber)

    '書き込み完了
    WriteAccountBookSettings = blnResult
End Function

End Module
