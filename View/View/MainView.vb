﻿''************************************************************************
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
Dim lngDefaultWidth As Integer
Dim lngDefaultHeight As Integer

    g_appRunPath = getAppPath()
    g_iniFileName = g_appRunPath & "\ApplicationSettings.ini"
    g_appRootDir = Wrapper.Common.FilePathUtils.getProjectRootDir(
                        g_appRunPath, "bin")

    initializeTables()
    moveWindowToStartPosition(g_iniFileName, INI_SEC_MAIN_VIEW, Me, Nothing)

    With picBook
        If .Image Is Nothing Then
            .Image = New System.Drawing.Bitmap(.Width, .Height)
        End If
    End With
    Dim g As Graphics = Graphics.FromImage(picBook.Image)

    StartupBookView(mutBookView, Me)
    With mutBookView
        lngDefaultWidth = 8
        lngDefaultHeight = 8

        With .utUserInterface
            .imgIcons = New Bitmap(g_appRootDir & "\Resources\Icons.bmp")
            .nCharWidth = lngDefaultWidth
            .nCharHeight = lngDefaultHeight
            .nCellWidth = lngDefaultWidth * 12
            .nCellHeight = lngDefaultHeight + 4
            If (.nCellHeight < 18) Then .nCellHeight = 18
        End With
        StartupUserInterface(
                .utUserInterface, picBook,
                Nothing, Nothing, Nothing,
                New HScrollBar(),
                New VScrollBar(),
                New System.Windows.Forms.StatusStrip())
    End With

    g.FillRectangle(Brushes.Black, g.VisibleClipBounds)
    g.DrawString(DateTime.Now.ToLongTimeString(), _
        SystemFonts.DefaultFont, Brushes.White, 10, 10)
    g.Dispose()
    picBook.Invalidate()

End Sub

Private Sub MainView_ResizeEnd(sender As Object, e As EventArgs) _
    Handles Me.ResizeEnd
''--------------------------------------------------------------------
''    フォームのリサイズイベントハンドラ。
''--------------------------------------------------------------------
Dim bInvalid As Boolean

    With mutBookView
        bInvalid = ChangeCellSize(.utUserInterface, .utAccountBook, -1, -1)
        If bInvalid Then
            UpdateBook(.utUserInterface, .utAccountBook, -1, -1)
        End If
        RefreshBook(.utUserInterface, .utAccountBook, -1, -1)
    End With
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
    mutBookView.utAccountBook = New Wrapper.AccountBook()
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
Dim selFileName As String

    With dlgOpen
        .DefaultExt = ".abd"
        .Filter = "Account Book Data (*.abd)|*.abd|All Files (*.*)|*.*"
        .FilterIndex = 1
        .InitialDirectory = g_appRootDir

        If .ShowDialog() = DialogResult.OK Then
            selFileName = .FileName
        Else
            Exit Sub
        End If
    End With

    With mutBookView
        If (.utAccountBook IsNot Nothing) Then
            .utAccountBook = Nothing
        End If
        .utAccountBook = New Wrapper.AccountBook()
    End With
    LoadFromFile(mutBookView, selFileName)

End Sub

''========================================================================
Private Sub mnuFileSave_Click(sender As Object, e As EventArgs) _
    Handles mnuFileSave.Click
''--------------------------------------------------------------------
''    メニュー「ファイル」－「上書き保存」
''--------------------------------------------------------------------
Dim curFileName As String

    curFileName = mutBookView.sCurrentBookFile
    If (curFileName = "")  Then
        ' 名前を付けて保存する
        mnuFileSaveAs_Click(sender, e)
        Exit Sub
    End If

    ' 現在の名前で保存する
    SaveToFile(mutBookView, curFileName)

End Sub

''========================================================================
Private Sub mnuFileSaveAs_Click(sender As Object, e As EventArgs) _
    Handles mnuFileSaveAs.Click
''--------------------------------------------------------------------
''    メニュー「ファイル」－「名前を付けて保存」
''--------------------------------------------------------------------
Dim strFileName As String

    ' 暫定処理
    strFileName = g_appRootDir & "\Test.abd"

    SaveToFile(mutBookView, strFileName)

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

Private Sub picBook_MouseDoubleClick(sender As Object, e As MouseEventArgs) _
    Handles picBook.MouseDoubleClick
''--------------------------------------------------------------------
''    セルをダブルクリックした時の処理。
''--------------------------------------------------------------------
    HandleSheetDoubleClickEvent(mutBookView)
End Sub

Private Sub picBook_MouseDown(sender As Object, e As MouseEventArgs) _
    Handles picBook.MouseDown
''--------------------------------------------------------------------
''    マウスを押したセルを調べる。
''--------------------------------------------------------------------
    HandleSheetMouseDownEvent(
            mutBookView, e.Button, Control.ModifierKeys, e.X, e.Y)
End Sub

End Class
