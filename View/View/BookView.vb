Option Explicit

Module BookView

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
        .oBookForm = Nothing
    End With
End Sub

Public Sub EnableControls(ByRef utBookView As tBookView)
'---------------------------------------------------------------------
'コントロールの有効／無効状態を設定する
'[I/O] utBookView: 家計簿ビュー
'[RET] なし
'---------------------------------------------------------------------
Dim objfBook As MainView
Dim lngBookFormType As Long
Dim blnEnabled As Boolean

    '家計簿の状態を確認する
    With utBookView
        blnEnabled = IsAccountBookEnabled(utBookView.utAccountBook)

        'コントロール
        With .utUserInterface
            .oBookHScrollBar.Visible = blnEnabled
            .oBookVScrollBar.Visible = blnEnabled
        End With

        'フォーム
        If (TypeOf .oBookForm Is MainView) Then
            lngBookFormType = 1
            objfBook = .oBookForm
        Else
            lngBookFormType = 0
            objfBook = Nothing
        End If
    End With

    'メニュー
    If (lngBookFormType = 1) Then
        With objfBook
            .mnuFileNew.Enabled = True
            .mnuFileOpen.Enabled = True
            .mnuFileSave.Enabled = blnEnabled
            .mnuFileSaveAs.Enabled = blnEnabled
            .mnuFileExit.Enabled = True
            .mnuEdit.Enabled = blnEnabled
            .mnuViewToolbar.Enabled = True
            .mnuViewStatusbar.Enabled = True
            ' .mnuOptionLanguage.Enabled = True
            ' .mnuOptionDiscard.Enabled = True
            ' .mnuOptionNoload.Enabled = True
            ' .mnuOptionSettingItems.Enabled = blnEnabled
        End With
    End If
End Sub

End Module
