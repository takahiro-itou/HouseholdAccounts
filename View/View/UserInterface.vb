Option Explicit

Module UserInterface

'*****************************************************************************
' AccountBook
' UserInterface モジュール
'
' 家計簿のユーザーインターフェイスを管理する
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2006/09/23 - 2008/01/08
'*****************************************************************************

'=========================================================================
'
'パブリックプロシージャ
'

Public Sub ChangeCellSize(ByRef utUI As tUserInterface,
        ByRef utBook As tAccountBook,
        ByVal lngNewWidth As Integer, ByVal lngNewHeight As Integer)
'---------------------------------------------------------------------
'セルの幅と高さを変更する
'[I/O] utUI        : ユーザーインターフェイス
'[ IN] utBook      : 家計簿データ
'[ IN] lngNewWidth : セルの幅
'[ IN] lngNewHeight: セルの高さ
'[RET] なし
'---------------------------------------------------------------------
Dim lngCount As Integer
Dim lngCellWidth As Integer, lngCellHeight As Integer

    If (False) Then
        lngCount = 32
    Else
        lngCount = BookItemGetRegisteredItemCount(utBook.utBookItems)
    End If

    With utUI
        If (lngNewWidth >= 16) Then
            .nCellWidth = lngNewWidth
        End If
        If (lngNewHeight >= 18) Then
            .nCellHeight = lngNewHeight
        End If

        lngCellWidth = .nCellWidth
        lngCellHeight = .nCellHeight

        'マージンと表示領域を計算する
        .nLeftMargin = .nCharWidth
        .nTopMargin = .nCharHeight
        .nBookWidth = .oBookPicture.Width - .nLeftMargin * 2
        .nBookHeight = .oBookPicture.Height - .nTopMargin * 2

        '一画面にどれだけ入るか計算する
        .nColumnsInSheet = .nBookWidth \ .nCellWidth
        .nRowsInSheet = .nBookHeight \ .nCellHeight

        'ピクチャボックスのサイズを変更する
        .imgCell = New System.Drawing.Bitmap(
                            lngCellWidth * 4, lngCellHeight * 4)

        .imgCanvas = New System.Drawing.Bitmap(
                            (lngCellWidth * (BOOKNUMCOLUMNS + 1) + 16),
                            (lngCellHeight * (lngCount + BOOKFIXEDROWS + 1))
        )
    End With

    'スクロールバーの範囲を設定する
    SetScrollRange(utUI)
End Sub

Public Sub CleanupUserInterface(ByRef utUI As tUserInterface)
'---------------------------------------------------------------------
'ユーザーインターフェイスのクリーンナップ
'[I/O] utUI: ユーザーインターフェイス
'[RET] なし
'---------------------------------------------------------------------

    With utUI
        .oBookPicture = Nothing
        .imgCanvas = Nothing
        .imgCell = Nothing
        .imgIcons = Nothing
        .oBookHScrollBar = Nothing
        .oBookVScrollBar = Nothing
    End With

End Sub

Public Function ExecuteCellAction(ByRef utUI As tUserInterface, _
    ByRef utBook As tAccountBook, ByVal lngX As Integer, ByVal lngY As Integer) As Boolean
'---------------------------------------------------------------------
'セルに対するアクションを実行する
'[I/O] utUI    : ユーザーインターフェイス
'[I/O] utBook  : 家計簿データ
'[ IN] lngX    : 列番号
'[ IN] lngY    : 行番号
'[RET] Boolean
'  何か変化が生じて画面を更新する必要があればTrue
'---------------------------------------------------------------------
Dim lngIndex As Integer
Dim blnExpand As Boolean
Dim blnResult As Boolean

    '家計簿オブジェクトの状態をチェックする
    If (IsAccountBookEnabled(utBook) = False) Then
        ExecuteCellAction = False
        Exit Function
    End If

    '変化無し(戻り値=False)
    blnResult = False

    If (lngX < BOOKFIXEDCOLS) Then
        If (lngY < BOOKFIXEDROWS) Then
            '左上の、セル以外の部分は、何もしない
            ExecuteCellAction = False
            Exit Function
        End If

        '選択した項目を閉じたり、開いたりする
        With utBook
            lngIndex = utUI.nNowShowingItems(lngY - BOOKFIXEDROWS)
            blnExpand = BookItemGetItemExpanded(.utBookItems, lngIndex)
            BookItemExpandItem(.utBookItems, lngIndex, Not (blnExpand))
            blnResult = True
        End With
    End If

    '何か変化があれば、表示を更新する
    If (blnResult) Then
        UpdateBook(utUI, utBook, -1, -1)
        SetScrollRange(utUI)
        RefreshBook(utUI, utBook, -1, -1)
    End If

    '何か変化があればTrueを返す
    ExecuteCellAction = blnResult
End Function

Public Sub RefreshBook(ByRef utUI As tUserInterface, _
    ByRef utBook As tAccountBook, _
    ByVal lngLeftCol As Integer, ByVal lngTopRow As Integer)
'---------------------------------------------------------------------
'家計簿の表示を更新する
'[I/O] utUI      : ユーザーインターフェイス
'[ IN] utBook    : 家計簿データ
'[ IN] lngLeftCol: 一番左に表示される列
'[ IN] lngTopRow : 一番上に表示される行
'[RET] なし
'---------------------------------------------------------------------
Dim lngLeft As Integer, lngTop As Integer
Dim lngWidth As Integer, lngHeight As Integer
Dim lngShowX As Integer, lngShowY As Integer
Dim lngSrcX As Integer, lngSrcY As Integer
Dim imgSrc As System.Drawing.Image
Dim grpDest As Graphics, grpSrc As Graphics
Dim rectSrc As System.Drawing.Rectangle

    '家計簿オブジェクトの状態をチェックする
    If (IsAccountBookEnabled(utBook) = False) Then
        With utUI
             grpDest = Graphics.FromImage(.oBookPicture.Image)
             grpDest.Clear(Color.White)
             grpDest.Dispose()

            .oBookPicture.Refresh
        End With
        Exit Sub
    End If

    With utUI
        imgSrc = .oBookPicture.Image

        '指定された左端の行、上端の列がマイナスであれば、
        'スクロールバーの現在の値にセットする
        If (lngLeftCol < 0) Then lngLeftCol = .oBookHScrollBar.Value
        If (lngTopRow < 0) Then lngTopRow = .oBookVScrollBar.Value
        .nLeftCol = lngLeftCol
        .nTopRow = lngTopRow

        'コピー元の座標を決定する
        lngSrcX = (lngLeftCol + BOOKFIXEDCOLS) * .nCellWidth
        lngSrcY = (lngTopRow + BOOKFIXEDROWS) * .nCellHeight

        grpSrc = Graphics.FromImage(.imgCanvas)
        ' hSrcDC = .oCanvasPicture.hDC

        grpDest = Graphics.FromImage(.oBookPicture.Image)
        grpDest.Clear(Color.White)

        '左上の固定行・固定列が交差する部分をコピーする
        lngWidth = .nCellWidth * BOOKFIXEDCOLS
        lngHeight = .nCellHeight * BOOKFIXEDROWS
        rectSrc = New System.Drawing.Rectangle(0, 0, lngWidth, lngHeight)
        grpDest.DrawImage(
             imgSrc, .nLeftMargin, .nTopMargin,
             rectSrc, GraphicsUnit.Pixel)

        '固定行をコピーする
        lngLeft = .nCellWidth * BOOKFIXEDCOLS
        lngTop = 0
        lngWidth = .nBookWidth - lngLeft
        lngHeight = .nBookHeight
        rectSrc = New System.Drawing.Rectangle(lngSrcX, 0, lngWidth, lngHeight)
        grpDest.DrawImage(
                imgSrc, lngLeft + .nLeftMargin, .nTopMargin,
                rectSrc, GraphicsUnit.Pixel)

        '固定列をコピーする
        lngLeft = 0
        lngTop = .nCellHeight * BOOKFIXEDROWS
        lngWidth = .nBookWidth
        lngHeight = .nBookHeight - lngTop
        rectSrc = New System.Drawing.Rectangle(0, lngSrcY, lngWidth, lngHeight)
        grpDest.DrawImage(
                imgSrc, lngTop + .nTopMargin, lngWidth,
                rectSrc, GraphicsUnit.Pixel)

        '残りの部分を表示する
        lngLeft = .nCellWidth * BOOKFIXEDCOLS
        lngTop = .nCellHeight * BOOKFIXEDROWS
        lngWidth = .nBookWidth - lngLeft
        lngHeight = .nBookHeight - lngTop
        rectSrc = New System.Drawing.Rectangle(
                lngSrcX, lngSrcY, lngWidth, lngHeight)
        grpDest.DrawImage(
                imgSrc, lngLeft + .nLeftMargin, lngTop + .nTopMargin,
                rectSrc, GraphicsUnit.Pixel)

        '選択しているセルを強調表示する
        lngShowX = .nCurrentMouseX - .nLeftCol
        lngShowY = .nCurrentMouseY - .nTopRow

        If (.nCurrentMouseX < BOOKFIXEDCOLS) Then
            '固定列を選択
            lngLeft = .nLeftMargin
            lngWidth = .nCellWidth * BOOKFIXEDCOLS
        ElseIf (lngShowX < BOOKFIXEDCOLS) Then
            '画面外(左)、表示しない
            lngLeft = .nBookWidth
            lngWidth = 0
        Else
            lngLeft = (.nCellWidth * lngShowX) + .nLeftMargin
            lngWidth = .nCellWidth
        End If

        If (.nCurrentMouseY < BOOKFIXEDROWS) Then
            '固定行を選択
            lngTop = .nTopMargin
            lngHeight = .nCellHeight * BOOKFIXEDROWS
        ElseIf (lngShowY < BOOKFIXEDROWS) Then
            '画面外(上)、表示しない
            lngTop = .nBookHeight
            lngHeight = 0
        Else
            lngTop = (.nCellHeight * lngShowY) + .nTopMargin
            lngHeight = .nCellHeight
        End If

        If ((lngLeft < .nBookWidth) And (lngTop < .nBookHeight)) Then
           Dim p As New Pen(Color.FromArgb(BOOKSELECTEDCOLOR))
           grpDest.DrawRectangle(p,
                    lngLeft + 1, lngTop + 1,
                    lngLeft + lngWidth - 1, lngTop + lngHeight - 1)
        End If

        grpSrc.Dispose()
        grpDest.Dispose()

        '更新する
        .oBookPicture.Refresh
    End With
End Sub

Public Sub SelectCell(ByRef utUI As tUserInterface, _
        ByRef utBook As tAccountBook,
        ByVal lngX As Integer, ByVal lngY As Integer)
'---------------------------------------------------------------------
'指定したセルを選択状態にする
'[I/O] utUI  : ユーザーインターフェイス
'[ IN] utBook: 家計簿データ
'[ IN] lngX  : 行
'[ IN] lngY  : 列
'[RET] なし
'---------------------------------------------------------------------
Dim lngItemIndex As Integer, lngColumnIndex As Integer
Dim lngYear As Integer, lngWeek As Integer, lngMonth As Integer
Dim blnResult As Boolean
Dim strTemp As String
Dim strItemName As String, strColumnTitle As String
Dim utDayInfo As tParsedDate

    blnResult = False

    '家計簿オブジェクトの状態をチェックする
    If (IsAccountBookEnabled(utBook) = False) Then Exit Sub

    With utUI
        'カーソル位置を保存する
        .nCurrentMouseX = lngX
        .nCurrentMouseY = lngY

        '現在のカーソル位置の日付を得る
        lngYear = .nCurrentYear
        lngWeek = .nCurrentWeek
        GetDayFromIndex(utDayInfo, lngYear, (lngWeek * 7), -1)
        lngMonth = utDayInfo.nMonth

        'カーソルが画面外にはみ出す場合は、スクロールバーを調整する
        If (lngX < BOOKFIXEDCOLS) Then
        ElseIf (lngX < (.nLeftCol + BOOKFIXEDCOLS)) Then
            .nLeftCol = lngX - BOOKFIXEDCOLS
            blnResult = True
        ElseIf (lngX >= (.nLeftCol + .nColumnsInSheet)) Then
            .nLeftCol = lngX - .nColumnsInSheet + 1
            blnResult = True
        End If

        If (lngY < BOOKFIXEDROWS) Then
        ElseIf (lngY < (.nTopRow + BOOKFIXEDROWS)) Then
            .nTopRow = lngY - BOOKFIXEDROWS
            blnResult = True
        ElseIf (lngY >= (.nTopRow + .nRowsInSheet)) Then
            .nTopRow = lngY - .nRowsInSheet + 1
            blnResult = True
        End If
        '選択したセルの項目インデックスと日付を得る
        If (lngY < BOOKFIXEDROWS) Then
            lngItemIndex = -1
            strItemName = ""
        Else
            lngItemIndex = .nNowShowingItems(lngY - BOOKFIXEDROWS)
            strItemName = BookItemGetItemName(utBook.utBookItems, lngItemIndex)
        End If

        If (lngX < BOOKFIXEDCOLS) Then
            lngColumnIndex = -1
            strTemp = ""
        Else
            lngColumnIndex = lngX - BOOKFIXEDCOLS
            If (lngColumnIndex < STARTOFEXTRACOL) Then
                strTemp = GetDayStringFromInfo(.utNowShowingDates(lngColumnIndex), True, True)
            Else
                strTemp = gstrExtraColumnName(lngColumnIndex - STARTOFEXTRACOL)
            End If
        End If
        strColumnTitle = WriteVariablesInString(strTemp, lngYear, lngWeek, lngMonth, 0)

        '選択したセルをステータスバーに表示する
        If ((strColumnTitle = "") Or (strItemName = "")) Then
            ' .oInfoStatusBar.Panels("sbpSubInfo").Text = strColumnTitle & strItemName
        Else
            ' .oInfoStatusBar.Panels("sbpSubInfo").Text = strColumnTitle & " , " & strItemName
        End If

        If (blnResult) Then
            .oBookHScrollBar.Value = .nLeftCol
            .oBookVScrollBar.Value = .nTopRow
        End If
    End With

End Sub

Public Sub SetScrollRange(ByRef utUI As tUserInterface)
'---------------------------------------------------------------------
'スクロールの範囲を決定する
'[I/O] utUI: ユーザーインターフェイス
'[RET] なし
'---------------------------------------------------------------------
Dim lngColumnsInSheet As Integer
Dim lngRowsInSheet As Integer
Dim lngNowShowingRows As Integer

    With utUI
        lngColumnsInSheet = .nColumnsInSheet
        lngRowsInSheet = .nRowsInSheet
        lngNowShowingRows = .nNowShowingItemCount

        With .oBookHScrollBar
            If (lngColumnsInSheet >= BOOKNUMCOLUMNS) Then
                .Value = 0
                .Enabled = False
            Else
                .Minimum = 0
                .Maximum = (BOOKNUMCOLUMNS - lngColumnsInSheet)
                .Enabled = True
            End If
        End With

        With .oBookVScrollBar
            If (lngRowsInSheet - BOOKFIXEDROWS >= lngNowShowingRows) Then
                .Value = 0
                .Enabled = False
            Else
                .Minimum = 0
                .Maximum = (lngNowShowingRows - lngRowsInSheet + BOOKFIXEDROWS)
                .Enabled = True
            End If
        End With
    End With
End Sub

Public Sub StartupUserInterface(ByRef utUI As tUserInterface, _
    ByVal picBook As PictureBox, ByVal picCanvas As PictureBox, _
    ByVal picCell As PictureBox, ByVal picIcons As PictureBox, _
    ByVal hsbBook As HScrollBar, ByVal vsbBook As VScrollBar, _
    ByVal stbInfo As System.Windows.Forms.StatusStrip)
'---------------------------------------------------------------------
'ユーザーインターフェイスのセットアップ
'[OUT] utUI      : ユーザーインターフェイス
'[ IN] picBook   : 家計簿を表示するメインのピクチャーボックス
'[ IN] picCanvas : 家計簿全体を保持する作業用のピクチャーボックス
'[ IN] picCell   : セルの内容を保持する作業用ピクチャーボックス
'[ IN] picIcons  : アイコンを保持したピクチャーボックス
'[ IN] hsbBook   : 表示範囲をコントロールする水平スクロールバー
'[ IN] vsbBook   : 表示範囲をコントロールする垂直スクロールバー
'[ IN] stbInfo   : 情報表示用のステータスバー
'[RET] なし
'---------------------------------------------------------------------

    With utUI
        .oBookPicture = picBook
        ' .oCanvasPicture = picCanvas
        ' .oCellPicture = picCell
        ' .oIconsPicture = picIcons
        .oBookHScrollBar = hsbBook
        .oBookVScrollBar = vsbBook
        .oInfoStatusBar = stbInfo
    End With
End Sub

Public Sub UpdateBook(ByRef utUI As tUserInterface,
        ByRef utBook As tAccountBook,
        ByVal lngYear As Integer, ByVal lngWeek As Integer)
'---------------------------------------------------------------------
'指定したピクチャーボックスに家計簿の内容を描画する
'[I/O] utUI    : ユーザーインターフェイス
'[ IN] utBook  : 家計簿データ
'[ IN] lngYear : 表示する西暦年
'[ IN] lngWeek : 表示する週
'[RET] なし
'---------------------------------------------------------------------
Dim i As Integer, X As Integer
Dim lngItemCount As Integer, lngRootItemCount As Integer
Dim lngBalanceCount As Integer, lngRootBalanceCount As Integer
Dim lngCurTop As Integer, lngInc As Integer
Dim lngMonth As Integer
Dim strTemp As String
Dim strText As String
Dim utDayInfo As tParsedDate
Dim colorText As Color = Color.Black

    '描画するデータ(年／週)を記録する
    With utUI
        If (lngYear < 0) Then lngYear = .nCurrentYear Else .nCurrentYear = lngYear
        If (lngWeek < 0) Then lngWeek = .nCurrentWeek Else .nCurrentWeek = lngWeek
    End With

    '家計簿オブジェクトの状態をチェックする
    If (IsAccountBookEnabled(utBook) = False) Then Exit Sub

    'データの個数をチェックする
    With utBook
        lngItemCount = BookItemGetRegisteredItemCount(.utBookItems)
        lngRootItemCount = BookItemGetRootItemCount(.utBookItems)
    End With

    With utUI
        .nNowShowingItemCount = 0
        ReDim .nNowShowingItems(0 To lngItemCount + lngBalanceCount - 1)
        ReDim .utNowShowingDates(0 To NUMDAYSPERWEEK - 1)

        'ターゲットに描かれている内容をクリアする
        Dim g As Graphics = Graphics.FromImage(.imgCanvas)
        g.Clear(Color.White)
        g.Dispose()
    End With

    '表示する最初の日付を取得して、何月分かを調べる
    GetDayFromIndex(utDayInfo, lngYear, (lngWeek * 7), -1)
    lngMonth = utDayInfo.nMonth

    'タイトル表示
    strTemp = WriteVariablesInString(utUI.sTableCaption, lngYear, lngWeek, lngMonth, 0)
    UserInterfaceDrawCell(utUI,
            0, 0, 0, 0, strTemp, ACCENTER, -1,
            Color.FromArgb(BOOKBGFIXEDROWSCOLOR),
            Color.FromArgb(BOOKLINECOLOR),
            colorText,
            2, 1)

    For X = 0 To 6
        GetDayFromIndex(utDayInfo, lngYear, (lngWeek * 7) + X, -1)
        strTemp = GetDayStringFromInfo(utDayInfo, False, True)
        utUI.utNowShowingDates(X) = utDayInfo
        UserInterfaceDrawCell(utUI,
                X + BOOKFIXEDCOLS, 0, 0, 0, strTemp, ACCENTER, -1, _
                Color.FromArgb(BOOKBGFIXEDROWSCOLOR),
                Color.FromArgb(BOOKLINECOLOR),
                colorText,
                1, 1)
    Next X

    '週計
    strTemp = gstrExtraColumnName(EXTRACOLUMN_WEEKTOTAL)
    strText = WriteVariablesInString(strTemp, lngYear, lngWeek, lngMonth, 0)
    UserInterfaceDrawCell(utUI,
            COLWEEKTOTAL + BOOKFIXEDCOLS, 0, 0, 0,
            strText, ACCENTER, -1,
            Color.FromArgb(BOOKBGFIXEDROWSCOLOR),
            Color.FromArgb(BOOKLINECOLOR),
            colorText,
            1, 1)

    '月計
    strTemp = gstrExtraColumnName(EXTRACOLUMN_MONTHTOTAL)
    strText = WriteVariablesInString(strTemp, lngYear, lngWeek, lngMonth, 0)
    UserInterfaceDrawCell(utUI,
            COLMONTHTOTAL + BOOKFIXEDCOLS, 0, 0, 0,
            strText, ACCENTER, -1,
            Color.FromArgb(BOOKBGFIXEDROWSCOLOR),
            Color.FromArgb(BOOKLINECOLOR),
            colorText,
            1, 1)

    '年計
    strTemp = gstrExtraColumnName(EXTRACOLUMN_YEARTOTAL)
    strText = WriteVariablesInString(strTemp, lngYear, lngWeek, lngMonth, 0)
    UserInterfaceDrawCell(utUI,
            COLYEARTOTAL + BOOKFIXEDCOLS, 0, 0, 0,
            strText, ACCENTER, -1,
            Color.FromArgb(BOOKBGFIXEDROWSCOLOR),
            Color.FromArgb(BOOKLINECOLOR),
            colorText,
            1, 1)

    '予算
    strTemp = gstrExtraColumnName(EXTRACOLUMN_BUDGETOFMONTH)
    strText = WriteVariablesInString(strTemp, lngYear, lngWeek, lngMonth, 0)
    UserInterfaceDrawCell(utUI,
            COLBUDGETOFMONTH + BOOKFIXEDCOLS, 0, 0, 0,
            strText, ACCENTER, -1,
            Color.FromArgb(BOOKBGFIXEDROWSCOLOR),
            Color.FromArgb(BOOKLINECOLOR),
            colorText,
            1, 1)

    '予算残高
    strTemp = gstrExtraColumnName(EXTRACOLUMN_BUDGETBALANCE)
    strText = WriteVariablesInString(strTemp, lngYear, lngWeek, lngMonth, 0)
    UserInterfaceDrawCell(utUI,
            COLBUDGETBALANCE + BOOKFIXEDCOLS, 0, 0, 0,
            strText, ACCENTER, -1,
            Color.FromArgb(BOOKBGFIXEDROWSCOLOR),
            Color.FromArgb(BOOKLINECOLOR),
            colorText,
            1, 1)

    lngCurTop = 1
    For i = 0 To lngRootItemCount - 1
        lngInc = UserInterfaceShowItem(utUI, utBook, _
            0, lngCurTop, i, lngYear, lngMonth, lngWeek)
        lngCurTop = lngCurTop + lngInc
    Next i

    '現金残高
    For i = 0 To lngRootBalanceCount - 1
        lngInc = UserInterfaceShowItem(utUI, utBook, _
            0, lngCurTop, i + MAXITEMS, lngYear, lngMonth, lngWeek)
        lngCurTop = lngCurTop + lngInc
    Next i
End Sub

'=========================================================================
'
'プライベートプロシージャ
'

Private Sub DrawSprite( _
        ByRef imgIcons As System.Drawing.Bitmap, _
        ByRef hdcDest As IntPtr, _
        ByVal destX As Integer, _
        ByVal destY As Integer, _
        ByVal srcX As Integer, _
        ByVal srcY As Integer, _
        Optional ByVal iconWidth As Integer = 16, _
        Optional ByVal iconHeight As Integer = 16)
''--------------------------------------------------------------------
''    スプライトを描画する。
''--------------------------------------------------------------------
Dim hdcIcons As IntPtr
Dim hOldObj As IntPtr
Dim iResult As Integer

    hdcIcons = CreateCompatibleDC(hdcDest)
    hOldObj = SelectObject(hdcIcons, imgIcons.GetHbitmap())

    iResult = BitBlt(hdcDest, destX, destY, iconWidth, iconHeight,
            hdcIcons, srcX, srcY + iconHeight, SRCAND)
    iResult = BitBlt(hdcDest, destX, destY, iconWidth, iconHeight,
            hdcIcons, srcX, srcY, SRCPAINT)

    SelectObject(hdcIcons, hOldObj)
    DeleteDC(hdcIcons)

End Sub

Private Sub UserInterfaceDrawCell(ByRef utUI As tUserInterface, _
    ByVal lngCol As Integer, ByVal lngRow As Integer, _
    ByVal lngLeftMargin As Integer, ByVal lngRightMargin As Integer, _
    ByVal strText As String, _
    ByVal lngArrangeCol As Integer, ByVal lngIcon As Integer, _
    ByVal lngBGColor As Color, _
    ByVal lngBorderColor As Color, _
    ByVal lngTextColor As Color, _
    Optional ByVal lngMultiCols As Integer = 1, _
    Optional ByVal lngMultiRows As Integer = 1)
'---------------------------------------------------------------------
'一つのセルを描画する
'[ IN] utUI          : ユーザーインターフェイスデータ
'[ IN] lngCol, lngRow: セルの位置
'[ IN] lngLeftMargin :
'[ IN] lngTopMargin  :
'[ IN] strText       : セルに表示する文字列
'[ IN] lngArrangeCol :
'[ IN] lngIcon       : 表示するアイコンの番号、なければ-1
'[ IN] lngMultiCols  :
'[ IN] lngMultiRows  :
'[ IN] lngBGColor    : セルの背景の色
'[ IN] lngBorderColor: セルの枠の色
'[ IN] lngTextColor  : テキストの色
'[RET] なし
'---------------------------------------------------------------------
Dim lngDestX As Integer, lngDestY As Integer, lngSrcX As Integer
Dim lngWidth As Integer, lngHeight As Integer
Dim lngTextAreaLeft As Integer, lngTextAreaWidth As Integer
Dim lngTextWidth As Integer
Dim hCellDC As IntPtr
Dim CurrentX As Integer, CurrentY As Integer
Dim grpCanvas As System.Drawing.Graphics
Dim grpCell As System.Drawing.Graphics
Dim rectSrc As System.Drawing.Rectangle

    If (lngMultiCols <= 0) Then lngMultiCols = 1
    If (lngMultiRows <= 0) Then lngMultiRows = 1

    With utUI
        lngWidth = .nCellWidth * lngMultiCols
        lngHeight = .nCellHeight * lngMultiRows
        If (lngIcon < 0) Then
            lngTextAreaLeft = lngLeftMargin + .nCharWidth
            lngTextAreaWidth = lngWidth - (lngLeftMargin + lngRightMargin) - .nCharWidth * 2
        Else
            lngTextAreaLeft = lngLeftMargin + .nCharWidth + 16
            lngTextAreaWidth = lngWidth - (lngLeftMargin + lngRightMargin + 16) - .nCharWidth * 2
        End If

        If .imgCell Is Nothing Then
            .imgCell = New System.Drawing.Bitmap(200, 100)
        End If
        grpCanvas = System.Drawing.Graphics.FromImage(.imgCanvas)

        grpCell = Graphics.FromImage(.imgCell)
        grpCell.FillRectangle(Brushes.White, grpCell.VisibleClipBounds)

        Dim brushBG As New SolidBrush(lngBGColor)
        grpCell.FillRectangle(brushBG, 0, 0, lngWidth, lngHeight)
        brushBG.Dispose()

        Dim p As New Pen(Color.Black, 1)
        grpCell.DrawRectangle(p, 0, 0, lngWidth, lngHeight)

        'アイコンを表示する
        If (lngIcon >= 0) Then
            hCellDC = grpCell.GetHdc()
            lngSrcX = lngIcon * 16
            lngDestY = (lngHeight - 16) \ 2

            DrawSprite(
                    .imgIcons, hCellDC, lngLeftMargin, lngDestY,
                    lngSrcX, 0, 16, 16)
            grpCell.ReleaseHdc(hCellDC)
        End If


        '文字を表示する
        With .oBookPicture
            lngTextWidth = grpCell.MeasureString(strText, .Font).Width

            If (lngArrangeCol = ACLEFT) Then
                CurrentX = lngTextAreaLeft
            ElseIf (lngArrangeCol = ACRIGHT) Then
                CurrentX = lngTextAreaLeft + (lngTextAreaWidth - lngTextWidth)
            Else
                CurrentX = lngTextAreaLeft + (lngTextAreaWidth - lngTextWidth) \ 2
            End If
            CurrentY = (lngHeight - utUI.nCharHeight) \ 2
            ' .ForeColor = lngTextColor
        End With
        grpCell.DrawString(
                strText, SystemFonts.DefaultFont, Brushes.Black,
                CurrentX, CurrentY)
        grpCell.Dispose()

        lngDestX = lngCol * utUI.nCellWidth
        lngDestY = lngRow * utUI.nCellHeight
        rectSrc = New System.Drawing.Rectangle(
                0, 0, lngWidth + 1, lngHeight + 1)
        grpCanvas.DrawImage(
                .imgCell, lngDestX, lngDestY,
                rectSrc, GraphicsUnit.Pixel)

        grpCanvas.Dispose()
    End With

End Sub

Private Sub UserInterfaceShowData(ByRef utUI As tUserInterface, _
    ByRef utBook As tAccountBook, ByVal lngDepth As Integer, _
    ByVal lngFixedColIcon As Integer, ByVal lngFixedColArrange As Integer, _
    ByVal lngBGFixedColsColor As Color, ByVal lngBGColor As Color, _
    ByVal lngTop As Integer, ByVal lngRootItem As Integer, _
    ByVal strItemName As String, _
    ByVal lngYear As Integer, ByVal lngMonth As Integer, _
    ByVal lngWeek As Integer)
'---------------------------------------------------------------------
'データを表示する
'[ IN] utUI                :
'[ IN] utBook              :
'[ IN] lngDepth            :
'[ IN] lngFixedColIcon     :
'[ IN] lngFixedColArrange  :
'[ IN] lngFixedColsBGColor :
'[ IN] lngBGColor          :
'[ IN] lngTop              :
'[ IN] lngRootItem         :
'[ IN] strItemName         :
'[ IN] lngYear             :
'[ IN] lngMonth            :
'[ IN] lngWeek             :
'[RET] なし
'[ACT]
'  ピクチャーボックスの指定位置に、
'家計簿の内容のlngRootItem で示されるノードのアイテムを描画する。
'---------------------------------------------------------------------
Dim X As Integer
Dim lngType As Integer
Dim lngYearIndex As Integer, lngDate As Integer, lngDayTotal As Integer
Dim lngWeekTotal As Integer, lngMonthTotal As Integer, lngYearTotal As Integer
Dim strText As String
Dim lngTextColor As Color, lngCellColor As Color
Dim utDate As tParsedDate

    'この項目以下の合計を表示する
    UserInterfaceDrawCell(utUI, _
            0, lngTop, lngDepth * 8, 0, strItemName,
            lngFixedColArrange, lngFixedColIcon,
            lngBGFixedColsColor,
            Color.FromArgb(BOOKLINECOLOR), Color.FromArgb(NORMALTEXTCOLOR),
            2, 1)

    With utBook
        lngYearIndex = lngYear - .nStartYear

        For X = 0 To 6
            lngDate = (lngWeek * NUMDAYSPERWEEK) + X

            If (IsDayBeforeStart(utBook, lngYear, lngDate)) Then
                '開始日より前
                lngCellColor = Color.FromArgb(BOOKBGREADONLYCELLSCOLOR)
                lngTextColor = Color.FromArgb(READONLYTEXTCOLOR)
                strText = ""
            Else
                GetDayFromIndex(utDate, lngYear, lngDate, -1)
                If (utDate.nYear <> lngYear) Then
                    '去年の残り、又は、来年へのはみ出し
                    lngCellColor = Color.FromArgb(BOOKBGREADONLYCELLSCOLOR)
                    lngTextColor = Color.FromArgb(READONLYTEXTCOLOR)
                Else
                    lngCellColor = lngBGColor
                    lngTextColor = Color.FromArgb(NORMALTEXTCOLOR)
                End If

                lngDayTotal = AnnualRecordGetItemDayTotal(.utAnnualRecords, lngRootItem, lngDate)
                If (lngDayTotal = 0) Then
                    strText = ""
                Else
                    strText = Format$(AnnualRecordGetItemDayTotal(.utAnnualRecords, lngRootItem, lngDate), "#,##0")
                End If
            End If

            UserInterfaceDrawCell(utUI, _
                    X + BOOKFIXEDCOLS, lngTop, 0, 0, strText, ACRIGHT, -1, _
                    lngCellColor, Color.FromArgb(BOOKLINECOLOR),
                    lngTextColor,
                    1, 1)
        Next X

        lngType = BookItemGetItemType(.utBookItems, lngRootItem)
        lngWeekTotal = AnnualRecordGetItemWeekTotal(.utAnnualRecords, lngRootItem, lngWeek)
        lngMonthTotal = AnnualRecordGetItemMonthTotal(.utAnnualRecords, lngRootItem, lngMonth)
        lngYearTotal = AnnualRecordGetItemYearTotal(.utAnnualRecords, lngRootItem, lngYearIndex)
    End With

    '週計
    If (lngType = ITEM_FLAG_BALANCE) Or (lngWeekTotal = 0) Then
        strText = ""
    Else
        strText = Format$(lngWeekTotal, "#,##0")
    End If
    UserInterfaceDrawCell(utUI, _
            COLWEEKTOTAL + BOOKFIXEDCOLS, lngTop, 0, 0,
            strText, ACRIGHT, -1, _
            Color.FromArgb(BOOKBGTOTALSCOLOR),
            Color.FromArgb(BOOKLINECOLOR),
            Color.FromArgb(NORMALTEXTCOLOR),
            1, 1)

    '月計
    If (lngType = ITEM_FLAG_BALANCE) Or (lngMonthTotal = 0) Then
        strText = ""
    Else
        strText = Format$(lngMonthTotal, "#,##0")
    End If
    UserInterfaceDrawCell(utUI, _
            COLMONTHTOTAL + BOOKFIXEDCOLS, lngTop, 0, 0,
            strText, ACRIGHT, -1,
            Color.FromArgb(BOOKBGTOTALSCOLOR),
            Color.FromArgb(BOOKLINECOLOR),
            Color.FromArgb(NORMALTEXTCOLOR),
            1, 1)

    '年計
    If (lngType = ITEM_FLAG_BALANCE) Or (lngYearTotal = 0) Then
        strText = ""
    Else
        strText = Format$(lngYearTotal, "#,##0")
    End If
    UserInterfaceDrawCell(utUI, _
            COLYEARTOTAL + BOOKFIXEDCOLS, lngTop, 0, 0,
            strText, ACRIGHT, -1, _
            Color.FromArgb(BOOKBGTOTALSCOLOR),
            Color.FromArgb(BOOKLINECOLOR),
            Color.FromArgb(NORMALTEXTCOLOR),
            1, 1)

    '予算
    strText = ""
    UserInterfaceDrawCell(utUI, _
            COLBUDGETOFMONTH + BOOKFIXEDCOLS, lngTop, 0, 0,
            strText, ACRIGHT, -1,
            Color.FromArgb(BOOKBGTOTALSCOLOR),
            Color.FromArgb(BOOKLINECOLOR),
            Color.FromArgb(NORMALTEXTCOLOR),
            1, 1)

    '予算残高
    strText = ""
    UserInterfaceDrawCell(utUI, _
            COLBUDGETBALANCE + BOOKFIXEDCOLS, lngTop, 0, 0,
            strText, ACRIGHT, -1,
            Color.FromArgb(BOOKBGTOTALSCOLOR),
            Color.FromArgb(BOOKLINECOLOR),
            Color.FromArgb(NORMALTEXTCOLOR),
            1, 1)

End Sub

Private Function UserInterfaceShowItem(ByRef utUI As tUserInterface, _
        ByRef utBook As tAccountBook, _
        ByVal lngDepth As Integer, ByVal lngTop As Integer,
        ByVal lngRootItem As Integer,
        ByVal lngYear As Integer, ByVal lngMonth As Integer,
        ByVal lngWeek As Integer) As Integer
'---------------------------------------------------------------------
'項目を表示する
'[ IN] utUI        :
'[ IN] utBook      :
'[ IN] lngDepth    :
'[ IN] lngTop      :
'[ IN] lngRootItem :
'[ IN] lngYear     :
'[ IN] lngMonth    :
'[ IN] lngWeek     :
'[RET] Integer
'  表示した項目の数
'[ACT]
'  ピクチャーボックスの指定位置に、
'家計簿の内容のlngRootItem で示されるノード以下のアイテムを描画する。
'---------------------------------------------------------------------
Dim i As Integer
Dim lngType As Integer, lngCount As Integer, lngSubItem As Integer
Dim lngInc As Integer, lngResult As Integer
Dim lngIcon As Integer
Dim lngColor As Color
Dim strName As String
Dim blnExpand As Boolean

    With utBook
        strName = BookItemGetItemName(.utBookItems, lngRootItem)
        lngType = BookItemGetItemType(.utBookItems, lngRootItem)
        blnExpand = BookItemGetItemExpanded(.utBookItems, lngRootItem)
        lngCount = BookItemGetSubItemCount(.utBookItems, lngRootItem)
    End With

    '表示する背景色を決定する
    If (lngDepth = 0) Then
        lngColor = Color.FromArgb(BOOKBGTOTALSCOLOR)
    ElseIf ((lngCount = 0) And (lngDepth >= 2)) Then
        lngColor = Color.FromArgb(BOOKBGLEAFSCOLOR)
    Else
        lngColor = Color.FromArgb(BOOKBGNORMALSCOLOR)
    End If

    '左端の列に表示するアイコンを決定する
    If (lngCount = 0) Then
        lngIcon = 0
    Else
        If (blnExpand = False) Then
            lngIcon = 1
        Else
            lngIcon = 2
        End If
    End If

    'この項目を表示する
    lngResult = 1
    If (lngType = ITEM_FLAG_BALANCE) Then
        '残高
        UserInterfaceShowData(utUI, utBook,
            lngDepth, lngIcon, ACRIGHT,
            Color.FromArgb(BOOKBGFIXEDROWSCOLOR),
            Color.FromArgb(BOOKBGTOTALSCOLOR),
            lngTop, lngRootItem, strName, lngYear, lngMonth, lngWeek)
    Else
        '通常の項目
        UserInterfaceShowData(utUI, utBook,
            lngDepth, lngIcon, ACLEFT,
            Color.FromArgb(BOOKBGFIXEDCOLSCOLOR), lngColor,
            lngTop, lngRootItem, strName, lngYear, lngMonth, lngWeek)
    End If

    With utUI
        .nNowShowingItems(.nNowShowingItemCount) = lngRootItem
        .nNowShowingItemCount = .nNowShowingItemCount + 1
    End With

    If (blnExpand) Then
        'この項目を展開し、サブアイテムも表示する
        lngTop = lngTop + 1
        For i = 0 To lngCount - 1
            lngSubItem = BookItemGetSubItemHandle(utBook.utBookItems, lngRootItem, i)
            lngInc = UserInterfaceShowItem(utUI, utBook, _
               lngDepth + 1, lngTop, lngSubItem, lngYear, lngMonth, lngWeek)
            lngTop = lngTop + lngInc
            lngResult = lngResult + lngInc
        Next i
    End If

    '表示した項目数を返す
    UserInterfaceShowItem = lngResult
End Function

End Module
