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
    Public nYear As Integer           '西暦年
    Public nMonth As Integer          '月
    Public nDay As Integer            '日
    Public nDayInYear As Integer      'その年で何日目か。つまり、元日からの経過日数（元日を０）
    Public nDayOffset As Integer      '元日の前に何日分のデータがあるか＝１週間の端数処理
    Public nDayIndex As Integer       'その日が去年の端数を含むデータ内で何番目か
    Public nWeek As Integer           '何週目
    Public nWeekday As eWeekday    '曜日
End Structure

Public glngFirstDayTable(,) As Integer   '各月の一日が元日から数えて何日目か。(元日を０とする)
Public gstrMonthName() As String
Public gstrWeekdayName() As String

Public Function CompareDates( _
    ByVal lngYear1 As Integer, ByVal lngDayIndex1 As Integer, _
    ByVal lngYear2 As Integer, ByVal lngDayIndex2 As Integer) As Integer
'---------------------------------------------------------------------
'二つの日付を比較する
'[ IN] lngYear1    :
'[ IN] lngDayIndex1:
'[ IN] lngYear2    :
'[ IN] lngDayIndex2:
'[RET] Long
'  一番目の日付の方が前ならば-1,
'  等しければ 0,
'  二番目の日付のほうが前ならば+1
'---------------------------------------------------------------------

    If (lngYear1 < lngYear2) Then
        CompareDates = -1
        Exit Function
    ElseIf (lngYear1 > lngYear2) Then
        CompareDates = 1
        Exit Function
    End If

    If (lngDayIndex1 < lngDayIndex2) Then
        CompareDates = -1
        Exit Function
    ElseIf (lngDayIndex1 > lngDayIndex2) Then
        CompareDates = 1
        Exit Function
    End If

    CompareDates = 0
End Function

Public Sub GetDayFromIndex( _
    ByRef utDate As tParsedDate, _
    ByVal lngYear As Integer, ByVal lngDayIndex As Integer, _
    ByVal lngDayOffset As Integer)
'---------------------------------------------------------------------
'指定された日から、日付情報に分解する
'[OUT] utDate      : 結果を格納する日付構造体
'[ IN] lngYear     : 西暦年
'[ IN] lngDayIndex : 元日からの日数
'[ IN] lngDayOffset: オフセット
'[RET] なし
'[ACT]
'  lngOffsetDay番目が元日になるように調整された
'インデックスlngDayIndex と西暦年lngYear から
'日付情報を取得して指定した構造体に格納する。
'  オフセットにマイナスを指定すると、その年の元日が
'何曜日であるかを調べて自動的に適切な値を使用する。
'---------------------------------------------------------------------
Dim i As Integer
Dim lngMonth As Integer, lngDay As Integer
Dim lngDayInYear As Integer
Dim lngTempDay As Integer, lngUruu As Integer

    'まず、オフセットを除いて、指定された日が元日から数えて何日目かを調べる
    If (lngDayOffset < 0) Then
        lngDayOffset = GetWeekday(lngYear, 1, 1)
    End If
    lngDayInYear = lngDayIndex - lngDayOffset
    lngTempDay = (lngDayInYear + 1)

    If (lngDayInYear < 0) Then
        '去年の余り
        lngMonth = 12
        lngYear = lngYear - 1
        lngDay = lngTempDay + 31
    Else
        lngMonth = MAXMONTH + 1
        lngUruu = IsUruuYear(lngYear)
        For i = 1 To MAXMONTH
            If (lngDayInYear < glngFirstDayTable(lngUruu, i + 1)) Then
                lngMonth = i
                Exit For
            End If
        Next i
        If (lngMonth = MAXMONTH + 1) Then
            '来年分
            lngMonth = 1
            lngYear = lngYear + 1
            lngDay = lngTempDay - glngFirstDayTable(lngUruu, MAXMONTH + 1)
        Else
            lngDay = lngTempDay - glngFirstDayTable(lngUruu, lngMonth)
        End If
    End If

    With utDate
        .nYear = lngYear
        .nMonth = lngMonth
        .nDay = lngDay
        .nDayInYear = lngDayInYear
        .nDayOffset = lngDayOffset
        .nDayIndex = lngDayIndex
        .nWeek = (lngDayIndex \ 7)
        .nWeekday = (lngDayIndex Mod 7)
    End With
End Sub

Public Function GetWeekday( _
    ByVal lngYear As Integer, _
    ByVal lngMonth As Integer, _
    ByVal lngDay As Integer) As eWeekday
'---------------------------------------------------------------------
'指定した日付（西暦年・月・日）から曜日を得る
'[ IN] lngYear : 西暦年
'[ IN] lngMonth: 月
'[ IN] lngDay  : 日
'[RET] Long
'  0=日,1=月,...,6=土
'---------------------------------------------------------------------
Dim lngWeekday As Integer

    'ツエラーの公式
    If (lngMonth <= 2) Then
        lngMonth = lngMonth + 12
        lngYear = lngYear - 1
    End If

    lngWeekday = (lngYear + (lngYear \ 4) - (lngYear \ 100) + (lngYear \ 400))
    lngWeekday = lngWeekday + ((lngMonth * 13 + 8) \ 5) + lngDay

    GetWeekday = (lngWeekday Mod 7)
End Function

Public Sub initializeTables()
''--------------------------------------------------------------------
''    必要なテーブルを初期化する。
''--------------------------------------------------------------------

    ReDim glngFirstDayTable(0 To 1, 0 To MAXMONTH + 1)
    glngFirstDayTable(0, 1) = 0
    glngFirstDayTable(0, 2) = 31
    glngFirstDayTable(0, 3) = 59
    glngFirstDayTable(0, 4) = 90
    glngFirstDayTable(0, 5) = 120
    glngFirstDayTable(0, 6) = 151
    glngFirstDayTable(0, 7) = 181
    glngFirstDayTable(0, 8) = 212
    glngFirstDayTable(0, 9) = 243
    glngFirstDayTable(0, 10) = 273
    glngFirstDayTable(0, 11) = 304
    glngFirstDayTable(0, 12) = 334
    glngFirstDayTable(0, 13) = 365

    glngFirstDayTable(1, 1) = 0
    glngFirstDayTable(1, 2) = 31
    For i = 3 To MAXMONTH + 1
        glngFirstDayTable(1, i) = glngFirstDayTable(0, i) + 1
    Next i

    ReDim gstrMonthName(0 To 12)
    For i = 1 To 12
        gstrMonthName(i) = i & "月"
    Next i

    ReDim gstrWeekdayName(0 To 6)
    gstrWeekdayName(0) = "日"
    gstrWeekdayName(1) = "月"
    gstrWeekdayName(2) = "火"
    gstrWeekdayName(3) = "水"
    gstrWeekdayName(4) = "木"
    gstrWeekdayName(5) = "金"
    gstrWeekdayName(6) = "土"

    ReDim gstrExtraColumnName(0 To NUMBEROFEXTRACOLUMNS - 1)
    gstrExtraColumnName(EXTRACOLUMN_WEEKTOTAL) = "週計"
    gstrExtraColumnName(EXTRACOLUMN_MONTHTOTAL) = "<month>月計"
    gstrExtraColumnName(EXTRACOLUMN_YEARTOTAL) = "<year>年計"
    gstrExtraColumnName(EXTRACOLUMN_BUDGETOFMONTH) = "予算"
    gstrExtraColumnName(EXTRACOLUMN_BUDGETBALANCE) = "予算残高"

End Sub

Public Function IsUruuYear(ByVal lngYear As Integer) As Integer
'---------------------------------------------------------------------
'指定した西暦年が閏年かどうかを判定する
'[ IN] lngYear : 西暦年
'[RET] Long
'  閏年であれば 1を、平年であれば 0を返す
'---------------------------------------------------------------------

    If ((lngYear Mod 4) <> 0) Then
        IsUruuYear = 0
    ElseIf ((lngYear Mod 100) = 0) And ((lngYear Mod 400) <> 0) Then
        IsUruuYear = 0
    Else
        IsUruuYear = 1
    End If
End Function

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
