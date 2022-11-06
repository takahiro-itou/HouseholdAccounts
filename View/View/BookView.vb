Option Explicit

Module Declarations

'*****************************************************************************
' AccountBook
' BookView  モジュール
'
' 家計簿の表示および入力を管理する
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2006/09/23 - 2008/01/10
'*****************************************************************************

'=========================================================================
'
'パブリックプロシージャ
'

Public Sub CleanupBookView(ByRef utBookView As tBookView)
'---------------------------------------------------------------------
'家計簿ビューのクリーンナップ
'[I/O] utBookView  : 家計簿ビュー
'[RET] なし
'---------------------------------------------------------------------
    With utBookView
        Set .oBookForm = Nothing
    End With
End Sub

End Module
