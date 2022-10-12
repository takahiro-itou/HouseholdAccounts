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

End Module
