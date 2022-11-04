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
    ByVal lngCol As Long, ByVal lngRow As Long, _
    ByVal lngLeftMargin As Long, ByVal lngRightMargin As Long, _
    ByVal strText As String, _
    ByVal lngArrangeCol As Long, ByVal lngIcon As Long, _
    ByVal lngBGColor As Color, _
    ByVal lngBorderColor As Color, _
    ByVal lngTextColor As Color, _
    Optional ByVal lngMultiCols As Long = 1, _
    Optional ByVal lngMultiRows As Long = 1)
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
Dim lngDestX As Long, lngDestY As Long, lngSrcX As Long
Dim lngWidth As Long, lngHeight As Long
Dim lngTextAreaLeft As Long, lngTextAreaWidth As Long
Dim lngTextWidth As Long
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

End Module
