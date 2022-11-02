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

Private Sub UserInterfaceDrawCell(ByRef utUI As tUserInterface, _
    ByVal lngCol As Long, ByVal lngRow As Long, _
    ByVal lngLeftMargin As Long, ByVal lngRightMargin As Long, _
    ByVal strText As String, _
    ByVal lngArrangeCol As Long, ByVal lngIcon As Long, _
    Optional ByVal lngMultiCols As Long = 1, Optional ByVal lngMultiRows As Long = 1, _
    Optional ByVal lngBGColor As OLE_COLOR = &HFFFFFF, _
    Optional ByVal lngBorderColor As OLE_COLOR = &H0&, _
    Optional ByVal lngTextColor As OLE_COLOR = &H0&)
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
Dim hCellPictureDC As Long, lngResult As Long

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

        .oCellPicture.Cls
        .oCellPicture.Line (0, 0)-(lngWidth, lngHeight), lngBGColor, BF
        .oCellPicture.Line (0, 0)-(lngWidth, lngHeight), lngBorderColor, B
        hCellPictureDC = .oCellPicture.hDC

        'アイコンを表示する
        If (lngIcon >= 0) Then
            lngSrcX = lngIcon * 16
            lngDestY = (lngHeight - 16) \ 2

            lngResult = BitBlt(hCellPictureDC, lngLeftMargin, lngDestY, 16, 16, .oIconsPicture.hDC, lngSrcX, 16, SRCAND)
            lngResult = BitBlt(hCellPictureDC, lngLeftMargin, lngDestY, 16, 16, .oIconsPicture.hDC, lngSrcX, 0, SRCPAINT)
        End If

        '文字を表示する
        With .oCellPicture
            lngTextWidth = .TextWidth(strText)
            If (lngArrangeCol = ACLEFT) Then
                .CurrentX = lngTextAreaLeft
            ElseIf (lngArrangeCol = ACRIGHT) Then
                .CurrentX = lngTextAreaLeft + (lngTextAreaWidth - lngTextWidth)
            Else
                .CurrentX = lngTextAreaLeft + (lngTextAreaWidth - lngTextWidth) \ 2
            End If
            .CurrentY = (lngHeight - utUI.nCharHeight) \ 2
            .ForeColor = lngTextColor
        End With
        .oCellPicture.Print strText

        lngDestX = lngCol * utUI.nCellWidth
        lngDestY = lngRow * utUI.nCellHeight
        lngResult = BitBlt(.oCanvasPicture.hDC, lngDestX, lngDestY, lngWidth + 1, lngHeight + 1, hCellPictureDC, 0, 0, SRCCOPY)
    End With
End Sub

End Module
