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
        .nBookWidth = .oBookPicture.ScaleWidth - .nLeftMargin * 2
        .nBookHeight = .oBookPicture.ScaleHeight - .nTopMargin * 2

        '一画面にどれだけ入るか計算する
        .nColumnsInSheet = .nBookWidth \ .nCellWidth
        .nRowsInSheet = .nBookHeight \ .nCellHeight

        'ピクチャボックスのサイズを変更する
        With .oCellPicture
            .Width = lngCellWidth * glngTwipsPerPixelX * 4
            .Height = lngCellHeight * glngTwipsPerPixelY * 4
        End With

        With .oCanvasPicture
            .Width = (lngCellWidth * (BOOKNUMCOLUMNS + 1) + 16) * glngTwipsPerPixelX
            .Height = (lngCellHeight * (lngCount + BOOKFIXEDROWS + 1)) * glngTwipsPerPixelY
        End With
    End With

    'スクロールバーの範囲を設定する
    SetScrollRange(utUI)
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
                .Min = 0
                .Max = (BOOKNUMCOLUMNS - lngColumnsInSheet)
                .Enabled = True
            End If
        End With

        With .oBookVScrollBar
            If (lngRowsInSheet - BOOKFIXEDROWS >= lngNowShowingRows) Then
                .Value = 0
                .Enabled = False
            Else
                .Min = 0
                .Max = (lngNowShowingRows - lngRowsInSheet + BOOKFIXEDROWS)
                .Enabled = True
            End If
        End With
    End With
End Sub

End Module
