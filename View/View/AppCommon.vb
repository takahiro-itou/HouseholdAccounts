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

Public g_appRootDir As String
Public g_appRunPath As String
Public g_iniFileName As String

'解像度
Public glngScreenWidth As Integer
Public glngScreenHeight As Integer
Public glngTwipsPerPixelX As Integer
Public glngTwipsPerPixelY As Integer

Public gstrMonthName() As String
Public gstrWeekdayName() As String

'=========================================================================
'
'パブリックプロシージャ
'

Public Sub ChangeFonts(ByRef objForm As Form,
        ByVal strFontName As String, ByVal lngFontSize As Integer)
'---------------------------------------------------------------------
'指定したフォームのコントロールのフォントを変更する
'変更されるのは、フォント名とフォントサイズのみ
'---------------------------------------------------------------------

End Sub

Public Function ChangeFormLanguage(
        ByRef objForm As Form, ByVal strLanguageFile As String) As String
'---------------------------------------------------------------------
'フォーム上のコントロールの言語を変更する
'フォームのキャプションだけは変更しないで文字列を返す
'（フォームのキャプションにはファイル名などの情報が入る可能性があるため）
'---------------------------------------------------------------------
Dim strCaption As String

    strCaption = ""
    ChangeFormLanguage = strCaption
End Function

Public Function ChangeLanguage(ByVal strLanguageFile As String) As Boolean
'---------------------------------------------------------------------
'使用言語を変更する
'---------------------------------------------------------------------

    ChangeLanguage = True
End Function

Public Sub ExitApplication()
'---------------------------------------------------------------------
'プログラムを終了する
'[RET] なし
'---------------------------------------------------------------------

End Sub

Public Function GetDayStringFromInfo(
        ByRef utDayInfo As Wrapper.ParsedDate,
        ByVal blnYear As Boolean,
        ByVal blnWeekday As Boolean) As String
'---------------------------------------------------------------------
'日付情報から、日付を表す文字列を得る
'[ IN] utDayInfo : 日付情報
'[ IN] blnYear   : Trueならば西暦年も加える
'[ IN] blnWeekday: Trueならば曜日も加える
'[RET] String
'  日付を表す文字列
'[ACT]
'  文字列の書式は、[yy/]mm/dd[(weekday)]
'---------------------------------------------------------------------
Dim strTemp As String

    With utDayInfo
        strTemp = .nMonth & "/" & .nDay
        If (blnYear) Then
            strTemp = .nYear & "/" & strTemp
        End If
        If (blnWeekday) Then
            strTemp = strTemp & "(" & gstrWeekdayName(.nWeekday) & ")"
        End If
    End With
    GetDayStringFromInfo = strTemp
End Function

Public Sub initializeTables()
''--------------------------------------------------------------------
''    必要なテーブルを初期化する。
''--------------------------------------------------------------------

#If NET48
#Else
    System.Text.Encoding.RegisterProvider(System.Text.CodePagesEncodingProvider.Instance)
#End If

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

Public Function IsLegalInputFileName(ByVal strFileName As String) As Boolean
'---------------------------------------------------------------------
'入力ファイル名が有効かどうか確認する
'[ IN] strFileName : ファイル名
'[RET] Boolean
'  有効なファイル名ならばTrue, 無効なファイル名ならば False
'[ACT]
'  ユーザーの意思でResourceディレクトリからは読み込みできない
'---------------------------------------------------------------------
Dim strDir As String

    strDir = GetDirFromPath(strFileName)
    If (LCase$(Right$(strDir, 9)) = "\resource") Then
        IsLegalInputFileName = False
        Exit Function
    End If

    IsLegalInputFileName = True
End Function

Public Function IsLegalOutputFileName(ByVal strFileName As String) As Boolean
'---------------------------------------------------------------------
'出力ファイル名が有効かどうか確認する
'[ IN] strFileName : ファイル名
'[RET] Boolean
'  有効なファイル名ならばTrue, 無効なファイル名ならば False
'[ACT]
'  ユーザーの意思でResourceディレクトリには書き込みできない
'---------------------------------------------------------------------
Dim strDir As String

    strDir = GetDirFromPath(strFileName)
    If (LCase$(Right$(strDir, 9)) = "\resource") Then
        IsLegalOutputFileName = False
        Exit Function
    End If

    IsLegalOutputFileName = True
End Function

Public Function OpenTemporaryFile(ByVal strTempPath As String, _
    ByVal blnErase As Boolean) As Integer
'---------------------------------------------------------------------
'テンポラリファイルを開く
'[ IN] strTempPath : テンポラリファイルのフルパス
'[ IN] blnErase    : 既存のファイルを削除するか
'[RET] Long
'  ファイル番号を返す
'  失敗した場合は-1を返す
'[ACT]
'  blnEraseにTrueを指定した時、
'既にファイルが存在すれば、一度削除してから開きなおす。
'---------------------------------------------------------------------
Dim lngTempFileNumber As Integer

    If (blnErase) Then
        If (Dir$(strTempPath) <> "") Then
            '既存のファイルを削除する
            System.IO.File.Delete(strTempPath)
        End If
    End If

    'ファイルを開く
    lngTempFileNumber = FreeFile()
    FileOpen(lngTempFileNumber, strTempPath, OpenMode.Binary)

    '開いたファイルのファイル番号を返す
    OpenTemporaryFile = lngTempFileNumber
End Function

Public Sub ParseDate(
        ByVal lngDate As integer,
        ByRef utResult As Wrapper.ParsedDate)
'---------------------------------------------------------------------
'本ソフトで使われている日付の形式を解析して、
'西暦年・月・日・週・曜日に分解する
'[ IN] lngDate :
'[OUT] utResult:
'[RET] なし
'[ACT]
'  週は最初の週を０と数える
'---------------------------------------------------------------------
Dim lngYear As Integer, lngMonth As Integer, lngDay As Integer
Dim lngDayInYear As Integer, lngDayOffset As Integer, lngDayIndex As Integer

    lngYear = (lngDate \ 65536)
    lngMonth = (lngDate \ 256) And 255
    lngDay = (lngDate And 255)
    lngDayInYear = Wrapper.ManagedDate.getDayInYear(lngYear, lngMonth, lngDay)
    lngDayOffset = Wrapper.ManagedDate.getWeekday(lngYear, 1, 1)
    lngDayIndex = lngDayInYear + lngDayOffset

    With utResult
        .nYear = lngDate
        .nMonth = lngMonth
        .nDay = lngDay
        .nDayInYear = lngDayInYear
        .nDayOffset = lngDayOffset
        .nDayIndex = lngDayIndex
        .nWeek = (lngDayIndex \ 7)
        .nWeekday = (lngDayIndex Mod 7)
    End With

End Sub

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

Public Function WriteVariablesInString(ByVal strText As String, _
    ByVal lngYear As Long, ByVal lngWeek As Long, _
    ByVal lngMonth As Long, ByVal lngDay As Long) As String
'---------------------------------------------------------------------
'文字列中にある変数(<と>でくくられた特別な名前の変数)に
'値を書き込んで返す
'[ IN] strText : 変数を含む文字列
'[ IN] lngYear : 西暦年
'[ IN] lngWeek : 週
'[ IN] lngMonth: 月
'[ IN] lngDay  : 日
'[RET] String
'  変数に値を書き込んだ文字列
'---------------------------------------------------------------------
Dim strNames(0 To 4) As String
Dim strValues(0 To 4) As String

    strNames(0) = "<year>"
    strNames(1) = "<week>"
    strNames(2) = "<month>"
    strNames(3) = "<day>"
    strNames(4) = "<monthname>"

    strValues(0) = lngYear
    strValues(1) = lngWeek
    strValues(2) = lngMonth
    strValues(3) = lngDay
    strValues(4) = gstrMonthName(lngMonth)

    WriteVariablesInString = ReplaceConstant(strText, strNames, strValues)
End Function

End Module
