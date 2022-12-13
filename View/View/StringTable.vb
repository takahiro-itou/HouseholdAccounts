Option Explicit

Module StringTable

'*****************************************************************************
' AccountBook
' StringTable モジュール
'
' 家計簿内の文字列テーブルを管理する
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2006/09/23 - 2008/01/06
'*****************************************************************************

'*****************************************************************************
'
'文字列テーブル
'

'ソート状態
Public Const STRINGSORTNONE As Integer = 0         'ソートなし
Public Const STRINGSORTASCENDING As Integer = 1    '昇順

Public Function ReadStringTable(
        ByRef utStringTable As Wrapper.StringTable,
        ByVal lngFileNumber As Integer) As Integer
'---------------------------------------------------------------------
'ファイルから、文字列テーブルを読み込む
'[OUT] utStringTable: 文字列テーブル
'[ IN] lngFileNumber: ファイル番号
'[RET] Integer
'---------------------------------------------------------------------
Dim i As Integer, lngCount As Integer
Dim lngSorted As Integer
Dim lngFlags As Integer, lngLength As Integer
Dim lngFirstPos As Integer, lngEndPos As Integer
Dim strTemp As String
Dim bytBuffer() As Byte

    '現在の位置を保存しておく
    lngFirstPos = Seek(lngFileNumber) - 1

    'データの個数とソート状態を読み込む
    FileGet(lngFileNumber, lngCount)
    FileGet(lngFileNumber, lngSorted)
    FileGet(lngFileNumber, lngFlags)      '予約
    FileGet(lngFileNumber, lngFlags)      '予約

    With utStringTable
        .nTableBufferSize = (lngCount + 15) And &H7FFFFFF0
        .nNumEntry = 0
        .nSorted = lngSorted

        If (.nTableBufferSize > 0) Then
            ReDim .nEntryFlags(0 To .nTableBufferSize - 1)
            ReDim .sTableEntries(0 To .nTableBufferSize - 1)
            ReDim .nSortIndex(0 To .nTableBufferSize - 1)
        End If

        'ソートインデックステーブルを読み込む
        If (lngSorted <> STRINGSORTNONE) And (.nTableBufferSize > 0) Then
            FileGet(lngFileNumber, .nSortIndex)
        End If

        '各レコードを読み込む
        For i = 0 To lngCount - 1
            FileGet(lngFileNumber, lngFlags)
            FileGet(lngFileNumber, lngLength)
            ReDim bytBuffer(0 To lngLength - 1)
            FileGet(lngFileNumber, bytBuffer)

            strTemp = Wrapper.TextOperation.toStringFromBytes(
                            bytBuffer, 0, lngLength - 1, True)

            If (lngSorted = STRINGSORTNONE) Then
                'データがソートされていない場合は、基本挿入法を使う
                .insertString(strTemp)
            Else
                'データがソートされている場合は、単純に最後に追加していく
                .sTableEntries(i) = strTemp
            End If
            .nEntryFlags(i) = lngFlags
        Next i

        .nNumEntry = lngCount
        .nSorted = STRINGSORTASCENDING
    End With

    If (utStringTable.checkIntegrity() = False) Then
        MessageBox.Show("文字列テーブルが正しくソートされていません。" & vbCrLf & "ソートしなおします。")
        SortStringTable(utStringTable)
    End If

    'アライメント調整
    lngCount = Seek(lngFileNumber) - 1
    lngEndPos = (lngCount + 64) And &H7FFFFFC0
    lngLength = lngEndPos - lngCount
    ReDim bytBuffer(0 To lngLength - 1)
    FileGet(lngFileNumber, bytBuffer)

    '読み込んだバイト数を返す
    ReadStringTable = (lngEndPos - lngFirstPos)
End Function

Public Sub SortStringTable(
        ByRef utStringTable As Wrapper.StringTable)
'---------------------------------------------------------------------
'文字列テーブルを昇順にソートする
'[I/O] utStringTable: 文字列テーブル
'---------------------------------------------------------------------

    With utStringTable
    End With
End Sub

Public Function WriteStringTable(
        ByRef utStringTable As Wrapper.StringTable,
        ByVal lngFileNumber As Integer) As Integer
'---------------------------------------------------------------------
'ファイルに、文字列テーブルを書き込む
'[ IN] utStringTable: 文字列テーブル
'[ IN] lngFileNumber: ファイル番号
'[RET] Integer
'  書き込んだバイト数
'---------------------------------------------------------------------
Dim i As Integer, lngCount As Integer
Dim lngSorted As Integer, lngIndex As Integer
Dim lngFlags As Integer, lngLength As Integer, lngRecordSize As Integer
Dim lngFirstPos As Integer, lngEndPos As Integer
Dim strTemp As String
Dim bytBuffer() As Byte

    '現在の位置を保存しておく
    lngFirstPos = Seek(lngFileNumber) - 1

    With utStringTable
        lngCount = .nNumEntry
        lngSorted = .nSorted
        lngLength = 0

        FilePut(lngFileNumber, lngCount)
        FilePut(lngFileNumber, lngSorted)
        FilePut(lngFileNumber, lngLength)     '予約
        FilePut(lngFileNumber, lngLength)     '予約

        'ソートインデックステーブルを書き込む
        If (lngSorted <> STRINGSORTNONE) Then
            FilePut(lngFileNumber, .nSortIndex)
        End If

        For i = 0 To lngCount - 1
            lngFlags = .nEntryFlags(i)
            lngIndex = .nSortIndex(i)
            strTemp = .sTableEntries(i)

            ReDim bytBuffer(0 To 255)
            lngLength = Wrapper.TextOperation.toBytesFromString(
                              strTemp, bytBuffer, 0, 255, False)
            If (lngLength And 1) Then lngLength = lngLength + 1

            lngRecordSize = (lngLength + 8 + 15) And &H7FFFFFF0
            lngLength = lngRecordSize - 8

            ReDim Preserve bytBuffer(0 To lngLength - 1)

            FilePut(lngFileNumber, lngFlags)
            FilePut(lngFileNumber, lngLength)
            FilePut(lngFileNumber, bytBuffer)
        Next i
    End With

    'アライメント調整
    lngCount = Seek(lngFileNumber) - 1
    lngEndPos = (lngCount + 256) And &H7FFFFF00
    lngLength = lngEndPos - lngCount
    ReDim bytBuffer(0 To lngLength - 1)
    FilePut(lngFileNumber, bytBuffer)

    '書き込んだバイト数を返す
    WriteStringTable = (lngEndPos - lngFirstPos)
End Function

Public Function TestStringTable(
        ByRef lpTable As Wrapper.StringTable) As Boolean
'---------------------------------------------------------------------
'---------------------------------------------------------------------
Dim i As Integer
Dim j0 As Integer, j1 As Integer

    For i = 1 To lpTable.nNumEntry - 1
        j0 = lpTable.nSortIndex(i - 1)
        j1 = lpTable.nSortIndex(i)

        If lpTable.sTableEntries(j0) >= lpTable.sTableEntries(j1) Then
            Debug.Print("NumEntry=", lpTable.nNumEntry)
            TestStringTable = False
            Exit Function
        End If
    Next i

    TestStringTable = True
End Function

End Module
