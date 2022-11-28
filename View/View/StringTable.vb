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

Public Function FindString(
        ByRef utStringTable As Wrapper.StringTable,
        ByVal strText As String) As Integer
'---------------------------------------------------------------------
'[ IN] utStringTable: 文字列テーブル
'[ IN] strText      : 検索する文字列
'[RET] Integer
'  検索結果
'[ACT]
'  指定された文字列テーブルから、
'strText で指定された文字列を検索し、そのインデックスを返す。
'  見つからなければ、-1を返す。
'---------------------------------------------------------------------
Dim lngIndex As Integer, lngResult As Integer
Dim lngLeft As Integer, lngRight As Integer, lngTarget As Integer
Dim strCheck As String

    With utStringTable
        lngLeft = 0
        lngRight = .nNumEntry - 1
        lngResult = -1

        Do While (lngRight - lngLeft >= 8)
            lngTarget = (lngLeft + lngRight) \ 2
            lngIndex = .nSortIndex(lngTarget)
            strCheck = .sTableEntries(lngIndex)

            If (strCheck = strText) Then
                '見つかった
                lngResult = lngIndex
                lngLeft = lngIndex
                lngRight = lngIndex
                Exit Do
            End If

            '検索範囲を絞る
            If (strCheck < strText) Then
                '検索しているデータは、現在位置lngTarget より右にある
                lngLeft = lngTarget + 1
            Else
                '検索しているデータは、現在位置lngTarget より左にある
                lngRight = lngTarget - 1
            End If
        Loop

        'ある程度範囲が小さくなったところで、単純検索に切り替える
        For lngTarget = lngLeft To lngRight
            lngIndex = .nSortIndex(lngTarget)
            strCheck = .sTableEntries(lngIndex)

            If (strCheck = strText) Then
                '見つかった
                lngResult = lngIndex
                Exit For
            End If
        Next lngTarget
    End With

    '結果を返す
    FindString = lngResult
End Function

Public Function InsertStringToTable(
        ByRef utStringTable As Wrapper.StringTable,
        ByVal strNewText As String) As Integer
'---------------------------------------------------------------------
'[I/O] utStringTable: 文字列テーブル
'[ IN] strNewText   : 新しく挿入するデータ
'[RET] Integer
'  挿入したデータのインデックス
'[ACT]
'  指定した文字列テーブルに、新しいデータを挿入する。
'  挿入された場合は、そのインデックスを返す。
'  すでにデータが存在していた場合は何もせず、そのインデックスを返す。
'---------------------------------------------------------------------
Dim i As Integer
Dim lngIndex As Integer, lngResult As Integer, lngInsertPos As Integer
Dim lngLeft As Integer, lngRight As Integer, lngTarget As Integer
Dim strCheck As String

    '指定されたデータの検索、および挿入位置の決定を行う
    With utStringTable
        lngLeft = 0
        lngRight = .nNumEntry - 1
        lngResult = -1

        Do While (lngRight - lngLeft >= 8)
            lngTarget = (lngLeft + lngRight) \ 2
            lngIndex = .nSortIndex(lngTarget)
            strCheck = .sTableEntries(lngIndex)

            If (strCheck = strNewText) Then
                '見つかった
                lngResult = lngIndex
                lngLeft = lngTarget
                lngRight = lngTarget
                Exit Do
            End If

            '検索範囲を絞る
            If (strCheck < strNewText) Then
                '検索しているデータは、現在位置lngTarget より右にある
                lngLeft = lngTarget + 1
            Else
                '検索しているデータは、現在位置lngTarget より左にある
                lngRight = lngTarget - 1
            End If
        Loop

        'ある程度範囲が小さくなったところで、単純検索に切り替える
        lngInsertPos = lngRight + 1
        For lngTarget = lngLeft To lngRight
            lngIndex = .nSortIndex(lngTarget)
            strCheck = .sTableEntries(lngIndex)

            If (strCheck = strNewText) Then
                '見つかった
                lngResult = lngIndex
                Exit For
            ElseIf (strCheck > strNewText) Then
                'この時点で、指定されたデータが、テーブル内に存在しない
                'このときの、lngTargetの位置に新しいデータを挿入する
                lngResult = -1
                lngInsertPos = lngTarget
                Exit For
            End If
        Next lngTarget
    End With

    'データが見つかった場合はそのインデックスを返して終了
    If (lngResult >= 0) Then
        InsertStringToTable = lngResult
        Exit Function
    End If

    'データをテーブルの最後尾に追加し、
    'ソートインデックステーブルを更新する
    With utStringTable
        lngIndex = .nNumEntry

        .nNumEntry = .nNumEntry + 1
        If (.nNumEntry > .nTableBufferSize) Then
            .nTableBufferSize = (.nNumEntry + 15) And &H7FFFFFF0
            ReDim Preserve .nEntryFlags(0 To .nTableBufferSize - 1)
            ReDim Preserve .sTableEntries(0 To .nTableBufferSize - 1)
            ReDim Preserve .nSortIndex(0 To .nTableBufferSize - 1)
        End If

        'テーブルの最後尾にデータを追加する
        .sTableEntries(lngIndex) = strNewText

        '挿入位置より後ろにあるデータをずらす
        For i = .nNumEntry - 1 To lngInsertPos + 1 Step -1
            .nSortIndex(i) = .nSortIndex(i - 1)
        Next i

        '挿入位置にデータを書き込む
        .nSortIndex(lngInsertPos) = lngIndex
    End With

    '挿入したデータのインデックスを返す
    InsertStringToTable = lngIndex
End Function

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

            strTemp = ByteToString(bytBuffer, 0, lngLength - 1, True)

            If (lngSorted = STRINGSORTNONE) Then
                'データがソートされていない場合は、基本挿入法を使う
                InsertStringToTable(utStringTable, strTemp)
            Else
                'データがソートされている場合は、単純に最後に追加していく
                .sTableEntries(i) = strTemp
            End If
            .nEntryFlags(i) = lngFlags
        Next i

        .nNumEntry = lngCount
        .nSorted = STRINGSORTASCENDING
    End With

    If (TestStringTable(utStringTable) = False) Then
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
            lngLength = StringToByte(strTemp, bytBuffer, 0, 255, False)
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
