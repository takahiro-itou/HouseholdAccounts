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
Dim lngX As Integer, lngY As Integer
Dim lngYear As Integer, lngWeek As Integer
Dim blnShiftDown As Boolean
Dim blnCtrlDown As Boolean
Dim blnAltDown As Boolean
Dim blnRefresh As Boolean

    With utBookView
        With .utUserInterface
            .oBookPicture.Focus()
            lngX = .nCurrentMouseX
            lngY = .nCurrentMouseY
            lngYear = .nCurrentYear
            lngWeek = .nCurrentWeek
        End With
        blnRefresh = False

        blnShiftDown = ((lngShift And Keys.Shift) > 0)
        blnCtrlDown = ((lngShift And Keys.Control) > 0)
        blnAltDown = ((lngShift And Keys.Alt) > 0)

        Select Case lngKeyCode
            Case Keys.Return:
                ExecuteCellAction(.utUserInterface, .utAccountBook, lngX, lngY)
                blnRefresh = True

            Case Keys.Left:
                If ((blnCtrlDown) And (blnShiftDown)) Then
                    If (lngWeek >= 4) Then
                        UpdateBook(.utUserInterface, .utAccountBook,
                                   -1, lngWeek - 4)
                    Else
                        UpdateBook(.utUserInterface, .utAccountBook, -1, 0)
                    End If
                    blnRefresh = True
                ElseIf (blnShiftDown) Then
                    If (lngWeek >= 1) Then
                        UpdateBook(.utUserInterface, .utAccountBook,
                                    -1, lngWeek - 1)
                        blnRefresh = True
                    End If
                Else
                    If (lngX > BOOKFIXEDCOLS) Then
                        SelectCell(.utUserInterface, .utAccountBook,
                                   lngX - 1, lngY)
                        blnRefresh = True
                    Else
                        SelectCell(.utUserInterface, .utAccountBook, 0, lngY)
                        blnRefresh = True
                    End If
                End If
            Case Keys.Up:
                If (lngY > BOOKFIXEDROWS) Then
                    SelectCell(.utUserInterface, .utAccountBook, lngX, lngY - 1)
                    blnRefresh = True
                Else
                    SelectCell(.utUserInterface, .utAccountBook, lngX, 0)
                    blnRefresh = True
                End If
            Case Keys.Right:
                If ((blnCtrlDown) And (blnShiftDown)) Then
                    If (lngWeek < .nNumWeeks - 4) Then
                        UpdateBook(.utUserInterface, .utAccountBook,
                                   -1, lngWeek + 4)
                    Else
                        UpdateBook(.utUserInterface, .utAccountBook,
                                   -1, .nNumWeeks - 1)
                    End If
                    blnRefresh = True
                ElseIf (blnShiftDown) Then
                    If (lngWeek < .nNumWeeks - 1) Then
                        UpdateBook(.utUserInterface, .utAccountBook,
                                    -1, lngWeek + 1)
                        blnRefresh = True
                    End If
                Else
                    If (lngX < BOOKFIXEDCOLS) Then
                        SelectCell(.utUserInterface, .utAccountBook,
                                   BOOKFIXEDCOLS, lngY)
                        blnRefresh = True
                        lngX = BOOKFIXEDCOLS
                    ElseIf (lngX < BOOKNUMCOLUMNS - 1) Then
                        SelectCell(.utUserInterface, .utAccountBook,
                                   lngX + 1, lngY)
                        blnRefresh = True
                    End If
                End If

            Case Keys.Down:
                If (lngY < BOOKFIXEDROWS) Then
                    SelectCell(.utUserInterface, .utAccountBook,
                               lngX, BOOKFIXEDROWS)
                    blnRefresh = True
                ElseIf (lngY < .utUserInterface.nNowShowingItemCount + BOOKFIXEDROWS - 1) Then
                    SelectCell(.utUserInterface, .utAccountBook, lngX, lngY + 1)
                    blnRefresh = True
                End If
        End Select

        '必要があれば表示内容をリフレッシュする
        If (blnRefresh) Then
            RefreshBook(.utUserInterface, .utAccountBook, -1, -1)
        End If
    End With

End Sub

Public Sub HandleSheetDoubleClickEvent(ByRef utBookView As tBookView)
'---------------------------------------------------------------------
'セルをダブルクリックした時の処理
'[I/O] utBookView: 家計簿ビュー
'[RET] なし
'---------------------------------------------------------------------
Dim lngX As Integer, lngY As Integer

    With utBookView
        With .utUserInterface
            lngX = .nCurrentMouseX
            lngY = .nCurrentMouseY
        End With

        'セル以外の部分は無視する
        If ((lngX >= 0) And (lngY >= 0)) Then
            'セルに対するアクションを実行する
            ExecuteCellAction(.utUserInterface, .utAccountBook, lngX, lngY)
        End If
    End With

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
Dim lngMouseX As Integer, lngMouseY As Integer
Dim lngRightCol As Integer, lngBottomRow As Integer
Dim blnHitSomeCell As Boolean
Dim blnRefresh As Boolean

    With utBookView
        With .utUserInterface
            '範囲チェック
            blnHitSomeCell = True
            If (lngX < .nLeftMargin) Or (lngY < .nTopMargin) Then
                blnHitSomeCell = False
            End If

            'ピクセル座標をセル座標に変換する
            lngMouseX = (lngX - .nLeftMargin) \ .nCellWidth
            lngMouseY = (lngY - .nTopMargin) \ .nCellHeight
            lngRightCol = .nColumnsInSheet
            lngBottomRow = .nNowShowingItemCount + BOOKFIXEDROWS

            '範囲チェック
            If (lngMouseX >= lngRightCol) Or (lngMouseY >= lngBottomRow) Then
                blnHitSomeCell = False
            End If

            If (blnHitSomeCell) Then
                '固定行でなければ、スクロール分を加味する
                If (lngMouseX >= BOOKFIXEDCOLS) Then
                    lngMouseX = lngMouseX + .nLeftCol
                End If
                If (lngMouseY >= BOOKFIXEDROWS) Then
                    lngMouseY = lngMouseY + .nTopRow
                End If

                If ((.nCurrentMouseX <> lngMouseX) Or (.nCurrentMouseY <> lngMouseY)) Then
                    blnRefresh = True
                End If
            End If
        End With

        If (blnHitSomeCell) Then
            'セルを選択する
            SelectCell(.utUserInterface, .utAccountBook, lngMouseX, lngMouseY)

            '必要があれば表示内容をリフレッシュする
            If (blnRefresh) Then
                RefreshBook(.utUserInterface, .utAccountBook, -1, -1)
            End If
        End If
    End With

End Sub

Public Sub LoadFromFile(ByRef utBookView As tBookView,
        ByVal strFileName As String)
'---------------------------------------------------------------------
'家計簿をファイルからロードする
'[I/O] utBookView  : 家計簿ビュー
'[ IN] strFileName : ファイル名
'[RET] なし
'---------------------------------------------------------------------
Dim blnLegal As Boolean
Dim blnOpen As Boolean, blnRead As Boolean

    With utBookView
        blnLegal = IsLegalInputFileName(strFileName)
        If (blnLegal = False) Then
            MessageBox.Show("ロードできません。" & _
                "指定されたファイルまたはディレクトリに対する読み込み権限がありません")
            blnOpen = False
        Else
            blnOpen = OpenAccountBook(.utAccountBook, strFileName)
        End If

        If (blnOpen = False) Then
            blnRead = False
        Else
            blnRead = ReadAccountBookSettings(.utAccountBook)
        End If

        If (blnRead = False) Then
            MessageBox.Show("ロードに失敗しました。")
        Else
            .sCurrentBookFile = strFileName
        End If
    End With

    If (blnRead = False) Then
        Exit Sub
    End If

    'ロード後の処理を行う
    PostLoadingFile(utBookView)
    MessageBox.Show("ロードは正常に完了しました")

End Sub

Public Sub PostLoadingFile(ByRef utBookView As tBookView)
'---------------------------------------------------------------------
'ファイルをロードした後の処理をする
'[I/O] utBookView: 家計簿ビュー
'[RET] なし
'[ACT]
'  新規作成によって初期化データがロードされた場合も同様。
'---------------------------------------------------------------------
Dim lngStartYear As Integer, lngNumYears As Integer
Dim lngStartMonth As Integer, lngStartDay As Integer
Dim blnEnabled As Boolean, blnCancel As Boolean
Dim lngToday As Integer, lngYear As Integer, lngOffset As Integer
Dim dtmToday As System.DateTime
Dim utDate As tParsedDate
Dim objfDate As DateSelect
Dim msgAns As System.Windows.Forms.DialogResult
Dim dtmSelect As System.DateTime

    With utBookView
        blnEnabled = EnableAccountBook(.utAccountBook, True)
        .bBackupedBookFile = False
        .bModifyCurrentBook = False

        '今日の日付を取得する
        dtmToday = Now
        lngYear = dtmToday.Year

        lngStartYear = GetAccountBookStartYear(.utAccountBook)
        lngNumYears = GetAccountBookNumYears(.utAccountBook)
    End With

    If ((lngStartYear = 0) Or (lngNumYears = 0)) Then
        msgAns = MessageBox.Show(
            "データの開始日と年数が指定されていません。" & vbCrLf & "今すぐ指定しますか？", "Question",
              MessageBoxButtons.YesNo, MessageBoxIcon.Question)
        If (msgAns = Windows.Forms.DialogResult.No) Then
            With utBookView
                blnEnabled = EnableAccountBook(.utAccountBook, False)
                .bBackupedBookFile = False
                .bModifyCurrentBook = False
            End With
            Exit Sub
        End If

        objfDate = New DateSelect()
        'Load objfDate
        With objfDate
            .selectDate(dtmToday)
            .ShowDialog(utBookView.oBookForm)

            ' blnCancel = .IsCanceled()
            dtmSelect = .getSelectedDate()
            lngStartYear = dtmSelect.Year   ' .GetSelectYear()
            lngStartMonth = dtmSelect.Month ' .GetSelectMonth()
            lngStartDay = dtmSelect.Day     ' .GetSelectDay()
            lngNumYears = (lngYear - lngStartYear + 1)

            .Dispose()
        End With
        objfDate = Nothing

        If (lngNumYears <= 0) Then lngNumYears = 0

        If (blnCancel) Then
            With utBookView
                blnEnabled = EnableAccountBook(.utAccountBook, False)
                .bBackupedBookFile = False
                .bModifyCurrentBook = False
            End With
            Exit Sub
        End If

        With utBookView
            SetAccountBookStartDate(.utAccountBook, lngStartYear,
                                    lngStartMonth, lngStartDay)
            SetAccountBookNumYears(.utAccountBook, lngNumYears)
        End With
    End If

    '今日の日付を含む週を表示する
    With utBookView
        lngOffset = GetWeekday(lngYear, 1, 1)
        lngToday = GetDayInYear(lngYear, dtmToday.Month, dtmToday.Day)
        lngToday = lngToday + lngOffset
        GetDayFromIndex(utDate, lngYear, lngToday, lngOffset)

        .nNumWeeks = ChangeAccountBookYear(.utAccountBook, utDate.nYear)
        Recount(.utAccountBook, utDate.nYear)

        'テスト
        ChangeCellSize(.utUserInterface, .utAccountBook, -1, -1)
        UpdateBook(.utUserInterface, .utAccountBook,
                   utDate.nYear, utDate.nWeek)

        '固定ではない部分の一番左上のセルを選択する
        SelectCell(.utUserInterface, .utAccountBook,
                   BOOKFIXEDCOLS, BOOKFIXEDROWS)
        RefreshBook(.utUserInterface, .utAccountBook, -1, -1)

        'ウィンドウのキャプションを更新する
        .oBookForm.Text = UpdateWindowCaption(utBookView)
    End With

    'メニューの状態を更新する
    EnableControls(utBookView)

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

    StartupBookView = True
End Function

Public Function UpdateWindowCaption(ByRef utBookView As tBookView)
'---------------------------------------------------------------------
'ウィンドウキャプションを更新する
'[I/O] utBookView: 家計簿ビュー
'[RET] なし
'[ACT]
'  現在作業しているファイルの名前と状態を表示する。
'---------------------------------------------------------------------
Dim strTemp As String
Dim strNames(0 To 2) As String
Dim strValues(0 To 2) As String

    strNames(0) = "<year>"
    strNames(1) = "<filename>"
    strNames(2) = "<modify>"

    With utBookView
        strValues(0) = .utUserInterface.nCurrentYear

        If (.sCurrentBookFile = "") Then
            strValues(1) = .sNoNameCaption
        Else
            strValues(1) = .sCurrentBookFile
        End If

        If (.bModifyCurrentBook) Then
            strValues(2) = .sModifyCaption
        Else
            strValues(2) = ""
        End If

        strTemp = .sWindowCaption
    End With

    UpdateWindowCaption = ReplaceConstant(strTemp, strNames, strValues)
End Function

End Module
