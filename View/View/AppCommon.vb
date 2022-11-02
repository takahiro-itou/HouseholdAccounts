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

Module AppCommon

Public g_appPath As String
Public g_iniFileName As String

'解像度
Public glngScreenWidth As Integer
Public glngScreenHeight As Integer
Public glngTwipsPerPixelX As Integer
Public glngTwipsPerPixelY As Integer

Public Enum eWeekday
    ewdSunday = 0
    ewdMonday = 1
    ewdTuesday = 2
    ewdWednesday = 3
    ewdThursday = 4
    ewdFriday = 5
    ewdSaturday = 6
End Enum

Public Structure tParsedDate
    Public nYear As Long           '西暦年
    Public nMonth As Long          '月
    Public nDay As Long            '日
    Public nDayInYear As Long      'その年で何日目か。つまり、元日からの経過日数（元日を０）
    Public nDayOffset As Long      '元日の前に何日分のデータがあるか＝１週間の端数処理
    Public nDayIndex As Long       'その日が去年の端数を含むデータ内で何番目か
    Public nWeek As Long           '何週目
    Public nWeekday As eWeekday    '曜日
End Structure

''========================================================================
Public Sub moveWindowToStartPosition(
        ByVal iniFileName As String,
        ByVal iniSecName As String,
        ByRef targetForm As System.Windows.Forms.Form,
        ByRef ownerForm As System.Windows.Forms.Form)
''--------------------------------------------------------------------
''    ウィンドウを初期位置に移動する。
''--------------------------------------------------------------------
Dim fx As Integer, fy As Integer, fw As Integer, fh As Integer
Dim bx As Integer, by As Integer, bw As Integer, bh As Integer
Dim sc As System.Windows.Forms.Screen
Dim sx As Integer, sy As Integer, sw As Integer, sh As Integer
Dim sr As Integer, sb As Integer

    With targetForm
        fw = .Width
        fh = .Height
    End With

    sc = System.Windows.Forms.Screen.FromControl(targetForm)
    With sc.Bounds
        sx = .Left
        sy = .Top
        sw = .Width
        sh = .Height
        sr = .Right
        sb = .Bottom
    End With
    If (ownerForm Is Nothing) Then
        bx = sx
        by = sy
        bw = sw
        bh = sh
    Else
        With ownerForm
            bx = .Left
            by = .Top
            bw = .Width
            bh = .Height
        End With
    End If

    fx = getSettingINI(iniFileName, iniSecName, "Left", -1)
    fy = getSettingINI(iniFileName, iniSecName, "Top", -1)
    If (fx < sx) Or (fx + fw > sr) Then
        ' ウィンドウが画面からはみ出す場合は、オーナー中央に移動させる。 '
        fx = bx + (bw - fw) \ 2
    End If
    If (fy < sy) Or (fy + fh > sb) Then
        ' ウィンドウが画面からはみ出す場合は、オーナー中央に移動させる。 '
        fy = by + (bh - fh) \ 2
    End If

    targetForm.Bounds = New Rectangle(fx, fy, fw, fh)

End Sub

''========================================================================
Public Sub saveWindowPrefs(
        ByVal iniFileName As String,
        ByVal iniSecName As String,
        ByRef sourceForm As System.Windows.Forms.Form)
''--------------------------------------------------------------------
''    ウィンドウの現在位置を保存する。
''--------------------------------------------------------------------

    With sourceForm
        saveSettingINI(iniFileName, iniSecName, "Left", .Left)
        saveSettingINI(iniFileName, iniSecName, "Height", .Height)
        saveSettingINI(iniFileName, iniSecName, "Top", .Top)
        saveSettingINI(iniFileName, iniSecName, "Width", .Width)
    End With

End Sub

End Module
