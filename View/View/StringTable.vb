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
Public Const STRINGSORTNONE As Long = 0         'ソートなし
Public Const STRINGSORTASCENDING As Long = 1    '昇順

Public Structure tStringTable
    Public nTableBufferSize As Long            'テーブル用のバッファサイズ
    Public nNumEntry As Long                   '実際に格納されているデータ数
    Public nSorted As Long                     'ソート状態
    Public nEntryFlags() As Long               '各エントリのフラグ
    Public sTableEntries() As String           '文字列テーブル
    Public nSortIndex() As Long                '昇順にソートしたときの、インデックステーブル
End Structure

Public Function FindString(ByRef utStringTable As tStringTable, _
    ByVal strText As String) As Long
'---------------------------------------------------------------------
'[ IN] utStringTable: 文字列テーブル
'[ IN] strText      : 検索する文字列
'[RET] Long
'  検索結果
'[ACT]
'  指定された文字列テーブルから、
'strText で指定された文字列を検索し、そのインデックスを返す。
'  見つからなければ、-1を返す。
'---------------------------------------------------------------------
Dim lngIndex As Long, lngResult As Long
Dim lngLeft As Long, lngRight As Long, lngTarget As Long
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

Public Function InsertStringToTable(ByRef utStringTable As tStringTable, _
    ByVal strNewText As String) As Long
'---------------------------------------------------------------------
'[I/O] utStringTable: 文字列テーブル
'[ IN] strNewText   : 新しく挿入するデータ
'[RET] Long
'  挿入したデータのインデックス
'[ACT]
'  指定した文字列テーブルに、新しいデータを挿入する。
'  挿入された場合は、そのインデックスを返す。
'  すでにデータが存在していた場合は何もせず、そのインデックスを返す。
'---------------------------------------------------------------------
Dim i As Long
Dim lngIndex As Long, lngResult As Long, lngInsertPos As Long
Dim lngLeft As Long, lngRight As Long, lngTarget As Long
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

Public Function ReadStringTable(ByRef utStringTable As tStringTable, _
    ByVal lngFileNumber As Long) As Long
'---------------------------------------------------------------------
'ファイルから、文字列テーブルを読み込む
'[OUT] utStringTable: 文字列テーブル
'[ IN] lngFileNumber: ファイル番号
'[RET] Long
'---------------------------------------------------------------------
End Function

Public Sub SortStringTable(ByRef utStringTable As tStringTable)
'---------------------------------------------------------------------
'文字列テーブルを昇順にソートする
'[I/O] utStringTable: 文字列テーブル
'---------------------------------------------------------------------

    With utStringTable
    End With
End Sub

Public Function WriteStringTable(ByRef utStringTable As tStringTable, _
    ByVal lngFileNumber As Long) As Long
'---------------------------------------------------------------------
'ファイルに、文字列テーブルを書き込む
'[ IN] utStringTable: 文字列テーブル
'[ IN] lngFileNumber: ファイル番号
'[RET] Long
'  書き込んだバイト数
'---------------------------------------------------------------------
End Function

End Module
