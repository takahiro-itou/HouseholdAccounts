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

Public Sub ChangeCellSize(ByRef utUI As tUserInterface, _
    ByRef utBook As tAccountBook, _
    ByVal lngNewWidth As Long, ByVal lngNewHeight As Long)
'---------------------------------------------------------------------
'セルの幅と高さを変更する
'[I/O] utUI        : ユーザーインターフェイス
'[ IN] utBook      : 家計簿データ
'[ IN] lngNewWidth : セルの幅
'[ IN] lngNewHeight: セルの高さ
'[RET] なし
'---------------------------------------------------------------------
Dim lngCount As Long
Dim lngCellWidth As Long, lngCellHeight As Long

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
        With .oCellPicture
            .Width = lngCellWidth * 4
            .Height = lngCellHeight * 4
        End With

        With .oCanvasPicture
            .Width = (lngCellWidth * (BOOKNUMCOLUMNS + 1) + 16) * glngTwipsPerPixelX
            .Height = (lngCellHeight * (lngCount + BOOKFIXEDROWS + 1)) * glngTwipsPerPixelY
        End With
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
        .oCanvasPicture = Nothing
        .oCellPicture = Nothing
        .oIconsPicture = Nothing
        .oBookHScrollBar = Nothing
        .oBookVScrollBar = Nothing
    End With

End Sub

Public Sub SetScrollRange(ByRef utUI As tUserInterface)
'---------------------------------------------------------------------
'スクロールの範囲を決定する
'[I/O] utUI: ユーザーインターフェイス
'[RET] なし
'---------------------------------------------------------------------
Dim lngColumnsInSheet As Long
Dim lngRowsInSheet As Long
Dim lngNowShowingRows As Long

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
Dim grpCell As System.Drawing.graphics
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
        With .oCellPicture
            lngTextWidth = grpCell.MeasureString(strText, .Font).Width

            If (lngArrangeCol = ACLEFT) Then
                CurrentX = lngTextAreaLeft
            ElseIf (lngArrangeCol = ACRIGHT) Then
                CurrentX = lngTextAreaLeft + (lngTextAreaWidth - lngTextWidth)
            Else
                CurrentX = lngTextAreaLeft + (lngTextAreaWidth - lngTextWidth) \ 2
            End If
            CurrentY = (lngHeight - utUI.nCharHeight) \ 2
            .ForeColor = lngTextColor
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
Dim i As Integer, X As Integer
Dim lngDestY As Integer
Dim lngType As Integer
Dim lngYearIndex As Integer, lngDate As Integer, lngDayTotal As Integer
Dim lngWeekTotal As Integer, lngMonthTotal As Integer, lngYearTotal As Integer
Dim strText As String
Dim lngTopMargin As Integer
Dim lngSrcDC As IntPtr, lngBltResult As Integer
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

End Module
