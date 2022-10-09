''************************************************************************
''                                                                      ''
''                  ---  Household Accounts View.  ---                  ''
''                                                                      ''
''          Copyright (C), 2017-2022, Takahiro Itou                     ''
''          All Rights Reserved.                                        ''
''                                                                      ''
''          License: (See COPYING and LICENSE files)                    ''
''          GNU Affero General Public License (AGPL) version 3,         ''
''          or (at your option) any later version.                      ''
''                                                                      ''
''************************************************************************

Public Class MainView

Private Const INI_SEC_MAIN_VIEW As String = "MainView"

''========================================================================
Private Sub MainView_FormClosing(
        sender As Object, e As FormClosingEventArgs) _
    Handles Me.FormClosing
''--------------------------------------------------------------------
''    フォームを閉じる時に現在位置等を保存する。
''--------------------------------------------------------------------

    saveWindowPrefs(g_iniFileName, INI_SEC_MAIN_VIEW, Me)

End Sub

''========================================================================
Private Sub MainView_Load(sender As Object, e As EventArgs) _
    Handles MyBase.Load
''--------------------------------------------------------------------
''    フォームのロードイベントハンドラ。
''--------------------------------------------------------------------

    g_appPath = getAppPath()
    g_iniFileName = g_appPath & "\ApplicationSettings.ini"

    moveWindowToStartPosition(g_iniFileName, INI_SEC_MAIN_VIEW, Me, Nothing)

End Sub

''========================================================================
Private Sub mnuEditMove_Click(sender As Object, e As EventArgs) _
    Handles mnuEditMove.Click
''--------------------------------------------------------------------
''    メニュー「編集」－「指定した日付に移動」
''--------------------------------------------------------------------
Dim frmDate As DateSelect

    frmDate = New DateSelect()
    With frmDate
        .ShowDialog(Me)

        .Dispose()
    End With

End Sub

''========================================================================
Private Sub mnuFileExit_Click(sender As Object, e As EventArgs) _
    Handles mnuFileExit.Click
''--------------------------------------------------------------------
''    メニュー「ファイル」－「終了」
''--------------------------------------------------------------------
    Application.Exit()
End Sub

''========================================================================
Private Sub mnuFileNew_Click(sender As Object, e As EventArgs) _
    Handles mnuFileNew.Click
''--------------------------------------------------------------------
''    メニュー「ファイル」－「新規作成」
''--------------------------------------------------------------------

End Sub

''========================================================================
Private Sub mnuFileOpen_Click(sender As Object, e As EventArgs) _
    Handles mnuFileOpen.Click
''--------------------------------------------------------------------
''    メニュー「ファイル」－「開く」
''--------------------------------------------------------------------

End Sub

''========================================================================
Private Sub mnuFileSave_Click(sender As Object, e As EventArgs) _
    Handles mnuFileSave.Click
''--------------------------------------------------------------------
''    メニュー「ファイル」－「上書き保存」
''--------------------------------------------------------------------

End Sub

''========================================================================
Private Sub mnuFileSaveAs_Click(sender As Object, e As EventArgs) _
    Handles mnuFileSaveAs.Click
''--------------------------------------------------------------------
''    メニュー「ファイル」－「名前を付けて保存」
''--------------------------------------------------------------------

End Sub

''========================================================================
Private Sub mnuViewStatusBar_Click(sender As Object, e As EventArgs) _
    Handles mnuViewStatusBar.Click
''--------------------------------------------------------------------
''    メニュー「表示」－「ステータスバー」
''--------------------------------------------------------------------

End Sub

''========================================================================
Private Sub mnuViewToolBar_Click(sender As Object, e As EventArgs) _
    Handles mnuViewToolBar.Click
''--------------------------------------------------------------------
''    メニュー「表示」－「ツールバー」
''--------------------------------------------------------------------

End Sub

End Class
