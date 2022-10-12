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

End Module
