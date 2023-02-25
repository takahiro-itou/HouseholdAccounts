Option Explicit

Module StringTable

'*****************************************************************************
' AccountBook
' StringTable モジュール
'
' 家計簿内の文字列テーブルを管理する
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2006/09/23 - 2023/02
'*****************************************************************************

'*****************************************************************************
'
'文字列テーブル
'

'ソート状態
Public Const STRINGSORTNONE As Integer = 0         'ソートなし
Public Const STRINGSORTASCENDING As Integer = 1    '昇順

Public Function ReadStringTable(
        ByRef utStringTable As Wrapper.DocCls.StringTable,
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
Dim sortIndex() As Integer

    '現在の位置を保存しておく
    lngFirstPos = Seek(lngFileNumber) - 1

    'データの個数とソート状態を読み込む
    FileGet(lngFileNumber, lngCount)
    FileGet(lngFileNumber, lngSorted)
    FileGet(lngFileNumber, lngFlags)      '予約
    FileGet(lngFileNumber, lngFlags)      '予約

    With utStringTable
        ' .nTableBufferSize = (lngCount + 15) And &H7FFFFFF0
        ' .nNumEntry = 0
        ' .nSorted = lngSorted

        ' If (.nTableBufferSize > 0) Then
        '     ReDim .nEntryFlags(0 To .nTableBufferSize - 1)
        '     ReDim .sTableEntries(0 To .nTableBufferSize - 1)
        '     ReDim .nSortIndex(0 To .nTableBufferSize - 1)
        ' End If
        .reserveBuffer(lngCount)

        'ソートインデックステーブルを読み込む
        If (lngSorted <> STRINGSORTNONE) And (.BufferCapacity > 0) Then
            ReDim sortIndex(0 To .BufferCapacity - 1)
            FileGet(lngFileNumber, sortIndex)
            .setSortIndexArray(sortIndex)
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
                .appendString(strTemp)
            End If
            .EntryFlag(i) = lngFlags
        Next i

        If (.NumEntries <> lngCount) Then
            MessageBox.Show(
                "文字列テーブルのエントリ数が一致しません。" & vbCrLf & _
                "NumEntries = " & .NumEntries & vbCrLf & _
                "ファイル中の記録値 = " & lngCount)
        End If
        .SortFlag = STRINGSORTASCENDING
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
        ByRef utStringTable As Wrapper.DocCls.StringTable)
'---------------------------------------------------------------------
'文字列テーブルを昇順にソートする
'[I/O] utStringTable: 文字列テーブル
'---------------------------------------------------------------------

    With utStringTable
    End With
End Sub

Public Function WriteStringTable(
        ByRef utStringTable As Wrapper.DocCls.StringTable,
        ByVal lngFileNumber As Integer) As Integer
'---------------------------------------------------------------------
'ファイルに、文字列テーブルを書き込む
'[ IN] utStringTable: 文字列テーブル
'[ IN] lngFileNumber: ファイル番号
'[RET] Integer
'  書き込んだバイト数
'---------------------------------------------------------------------
Dim i As Integer, lngCount As Integer
Dim lngSorted As Integer
Dim lngFlags As Integer, lngLength As Integer, lngRecordSize As Integer
Dim lngFirstPos As Integer, lngEndPos As Integer
Dim strTemp As String
Dim bytBuffer() As Byte

    '現在の位置を保存しておく
    lngFirstPos = Seek(lngFileNumber) - 1

    With utStringTable
        lngCount  = .NumEntries
        lngSorted = .SortFlag
        lngLength = 0

        FilePut(lngFileNumber, lngCount)
        FilePut(lngFileNumber, lngSorted)
        FilePut(lngFileNumber, lngLength)     '予約
        FilePut(lngFileNumber, lngLength)     '予約

        'ソートインデックステーブルを書き込む
        If (lngSorted <> STRINGSORTNONE) Then
            FilePut(lngFileNumber, .SortIndex)
        End If

        For i = 0 To lngCount - 1
            lngFlags = .EntryFlag(i)
            strTemp = .TableEntry(i)

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

End Module
