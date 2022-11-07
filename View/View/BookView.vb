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

Public Sub HandleKeyDownEvent(ByRef utBookView As tBookView,
        ByVal lngKeyCode As Integer, ByVal lngShift As Integer)
'---------------------------------------------------------------------
'キーボードによる操作
'[I/O] utBookView: 家計簿ビュー
'[ IN] lngKeyCode: 押下したキーのキーコード
'[ IN] lngShift  : 修飾キーの状態
'[RET] なし
'---------------------------------------------------------------------

End Sub

Public Sub HandleSheetDoubleClickEvent(ByRef utBookView As tBookView)
'---------------------------------------------------------------------
'セルをダブルクリックした時の処理
'[I/O] utBookView: 家計簿ビュー
'[RET] なし
'---------------------------------------------------------------------

End Sub

Public Sub HandleSheetMouseDownEvent(ByRef utBookView As tBookView,
       ByVal lngButton As Integer, ByVal lngShift As Integer,
       ByVal lngX As Integer, ByVal lngY As Integer)
'---------------------------------------------------------------------
'マウスを押したセルを調べる
'[I/O] utBookView: 家計簿ビュー
'[ IN] lngButton : 押したマウスボタン
'[ IN] lngShift  : 修飾キーの状態
'[ IN] lngX      : マウスを押したときのカーソルの水平位置
'[ IN] lngY      : マウスを押したときのカーソルの垂直位置
'[RET] なし
'---------------------------------------------------------------------

End Sub

Public Sub LoadFromFile(ByRef utBookView As tBookView,
        ByVal strFileName As String)
'---------------------------------------------------------------------
'家計簿をファイルからロードする
'[I/O] utBookView  : 家計簿ビュー
'[ IN] strFileName : ファイル名
'[RET] なし
'---------------------------------------------------------------------

End Sub

Public Sub PostLoadingFile(ByRef utBookView As tBookView)
'---------------------------------------------------------------------
'ファイルをロードした後の処理をする
'[I/O] utBookView: 家計簿ビュー
'[RET] なし
'[ACT]
'  新規作成によって初期化データがロードされた場合も同様。
'---------------------------------------------------------------------

End Sub

Public Sub SaveToFile(ByRef utBookView As tBookView,
        ByVal strFileName As String)
'---------------------------------------------------------------------
'家計簿をファイルに保存する
'[I/O] utBookView  : 家計簿ビュー
'[ IN] strFileName : ファイル名
'[RET] なし
'---------------------------------------------------------------------

End Sub

Public Sub SetControlSize(ByRef utBookView As tBookView)
'---------------------------------------------------------------------
'フォーム上のコントロールのサイズを設定する
'[I/O] utBookView: 家計簿ビュー
'[RET] なし
'---------------------------------------------------------------------

End Sub

Public Function StartupBookView(ByRef utBookView As tBookView,
        ByVal objBookForm As MainView) As Boolean
'---------------------------------------------------------------------
'家計簿ビューのセットアップ
'[OUT] utBookView  : 家計簿ビュー
'[ IN] objBookForm : フォームオブジェクト
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------

End Function

Public Function UpdateWindowCaption(ByRef utBookView As tBookView)
'---------------------------------------------------------------------
'ウィンドウキャプションを更新する
'[I/O] utBookView: 家計簿ビュー
'[RET] なし
'[ACT]
'  現在作業しているファイルの名前と状態を表示する。
'---------------------------------------------------------------------

End Function

End Module
