Public Class MainView

Private Const INI_SEC_MAIN_VIEW As String = "MainView"

''------------------------------------------------------------------------
''    フォームを閉じる時に現在位置等を保存する。
''------------------------------------------------------------------------
Private Sub MainView_FormClosing(sender As Object, e As FormClosingEventArgs) _
        Handles Me.FormClosing

    saveWindowPrefs(g_iniFileName, INI_SEC_MAIN_VIEW, Me)

End Sub

''------------------------------------------------------------------------
''    フォームのロードイベントハンドラ。
''------------------------------------------------------------------------
Private Sub MainView_Load(sender As Object, e As EventArgs) Handles _
            MyBase.Load

    g_appPath = getAppPath()
    g_iniFileName = g_appPath & "\ApplicationSettings.ini"

    moveWindowToStartPosition(g_iniFileName, INI_SEC_MAIN_VIEW, Me, Nothing)

End Sub

End Class
