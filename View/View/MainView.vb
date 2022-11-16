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

'家計簿ビュー(家計簿データとユーザーインターフェイスを含む)
Private mutBookView As tBookView

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

    If picBook.Image Is Nothing Then
        picBook.Image = New System.Drawing.Bitmap(200, 100)
    End If
    Dim g As Graphics = Graphics.FromImage(picBook.Image)

    g.FillRectangle(Brushes.Black, g.VisibleClipBounds)
    g.DrawString(DateTime.Now.ToLongTimeString(), _
        SystemFonts.DefaultFont, Brushes.White, 10, 10)
    g.Dispose()
    picBook.Invalidate()

End Sub

''========================================================================
Private Sub mnuEditMove_Click(sender As Object, e As EventArgs) _
    Handles mnuEditMove.Click
''--------------------------------------------------------------------
''    メニュー「編集」－「指定した日付に移動」
''--------------------------------------------------------------------
Dim frmDate As DateSelect
Dim dlgAns As System.Windows.Forms.DialogResult
Dim selDate As System.DateTime

    frmDate = New DateSelect()
    With frmDate
        dlgAns = .ShowDialog(Me)

        If (dlgAns = System.Windows.Forms.DialogResult.Cancel) Then
            MessageBox.Show("キャンセルされました。")
        Else
            selDate = .getSelectedDate()
            MessageBox.Show("日付" & selDate & "が選択されました。")
        End If

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

    '家計簿オブジェクトを初期化する
    If (CreateEmptyAccountBook(mutBookView.utAccountBook)) = False Then
        MessageBox.Show("空の家計簿データの作成に失敗しました。必要なファイルが見つかりません。")
        Exit Sub
    End If

    'ロード後の処理を行う
    mutBookView.sCurrentBookFile = ""
    PostLoadingFile(mutBookView)

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
