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
Dim startBalance As Wrapper.Common.DecimalCurrency

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
        With utBook.BookCategories
            .reserveRootCategories(lngRootItemCount)
            .InnerTaxHandle = lngHeader(36)
            .OuterTaxHandle = lngHeader(37)
        End With
        utBook.allocItemBuffers(lngItemCount)

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
                startBalance = New Wrapper.Common.DecimalCurrency(lngStartBalance)
                .BookCategories.setupRootCategory(
                        i, strTemp, lngFlags, lngStartDate, startBalance)
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
                lngResult = utBook.insertNewCategory(
                                lngHandle, strTemp, lngFlags,
                                lngStartDate, lngStartBalance)
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
        With .BookCategories
            lngItemCount = .RegisteredCategoryCount
            lngHeader(32) = lngItemCount
            lngHeader(33) = .RootCategoryCount

            lngHeader(36) = .InnerTaxHandle
            lngHeader(37) = .OuterTaxHandle
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
        Seek(lngTempFileNumber, lngStartPos + lngDataPos + 1)
        For i = 0 To lngItemCount - 1
            With .BookCategories(i)
                lngFlags = .Flags
                lngHandle = .ParentHandle
                strTemp = .CategoryName
                lngStartDate = .StartDate
                lngStartBalance = .StartBalance.InternalValue
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
