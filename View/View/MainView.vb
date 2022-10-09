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
