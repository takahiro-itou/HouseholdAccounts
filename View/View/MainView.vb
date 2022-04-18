Public Class MainView

    ''================================================================================
    ''    ウィンドウを初期位置に移動する。
    ''================================================================================
    Private Sub MoveWindowToStartPosition()
        Dim fx As Integer = My.Settings.WindowLeft
        Dim fy As Integer = My.Settings.WindowTop
        Dim fw As Integer = My.Settings.WindowWidth
        Dim fh As Integer = My.Settings.WindowHeight

        Dim sc As System.Windows.Forms.Screen = System.Windows.Forms.Screen.FromControl(Me)
        Dim sx As Integer = sc.Bounds.Left
        Dim sy As Integer = sc.Bounds.Top

        If (fw < 0) Then
            fw = 640
        End If
        If (fh < 0) Then
            fh = 480
        End If
        If (fx + fw < sx) Or (fx + fw > sc.Bounds.Right) Then
            ' ウィンドウが画面からはみ出す場合は、画面中央に移動させる。 '
            fx = sx + (sc.Bounds.Width - fw) \ 2
        End If
        If (fy + fh < sy) Or (fy + fh >= sc.Bounds.Bottom) Then
            ' ウィンドウが画面からはみ出す場合は、画面中央に移動させる。 '
            fy = sy + (sc.Bounds.Height - fh) \ 2
        End If

        Me.Bounds = New Rectangle(fx, fy, fw, fh)
        Me.WindowState = My.Settings.WindowState
    End Sub

    ''================================================================================
    ''    ウィンドウの現在位置を保存する。
    ''================================================================================
    Private Sub SaveWindowPrefs()
        With My.Settings
            If Me.WindowState = FormWindowState.Normal Then
                .WindowLeft = Me.Left
                .WindowTop = Me.Top
                .WindowWidth = Me.Width
                .WindowHeight = Me.Height
            End If
            .WindowState = Me.WindowState

            .Save()
        End With
    End Sub

    Private Sub MainView_Disposed(sender As Object, e As EventArgs) Handles Me.Disposed
    End Sub

    Private Sub MainView_FormClosing(sender As Object, e As FormClosingEventArgs) Handles Me.FormClosing
        SaveWindowPrefs()
    End Sub

    Private Sub MainView_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        MoveWindowToStartPosition()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        MsgBox("Width = " & My.Settings.WindowWidth)
    End Sub
End Class
