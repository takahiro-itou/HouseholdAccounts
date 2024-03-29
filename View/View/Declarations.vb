﻿Option Explicit

Module Declarations

'*****************************************************************************
' AccountBook
' Declarations  モジュール
'
' 変数、定数、ユーザー定義型を定義する
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2006/09/23 - 2008/01/05
'*****************************************************************************

'*****************************************************************************
'
'レシートデータ用フラグ
'

Public Const RECEIPT_FLAG_TYPEMASK As Integer = &HFF&
Public Const RECEIPT_FLAG_NOTUSED As Integer = 0
Public Const RECEIPT_FLAG_USED As Integer = 1

'*****************************************************************************
'
'各データの最大個数
'

Public Const DAY_START As Integer = 6
Public Const MAXITEMS As Integer = 65536       '家計簿に記録できる最大項目数
Public Const MAXBALANCES As Integer = 256      '家計簿に登録できる最大口座数

Public Const MAXDAYS As Integer = 378          '１年分の家計簿に記録する最大日数
Public Const MAXWEEKS As Integer = 54          '１年分の家計簿に記録する最大週数
Public Const MAXMONTH As Integer = 12          '１年分の家計簿に記録する最大月数

'*****************************************************************************
'
'表示関係
'

Public Const ACCENTER As Integer = 0
Public Const ACLEFT As Integer = 1
Public Const ACRIGHT As Integer = 2

'行や列の見出しなど
Public Const NUMDAYSPERWEEK As Integer = 7

Public Const NUMBEROFEXTRACOLUMNS As Integer = 5
Public Const EXTRACOLUMN_WEEKTOTAL As Integer = 0
Public Const EXTRACOLUMN_MONTHTOTAL As Integer = 1
Public Const EXTRACOLUMN_YEARTOTAL As Integer = 2
Public Const EXTRACOLUMN_BUDGETOFMONTH As Integer = 3
Public Const EXTRACOLUMN_BUDGETBALANCE As Integer = 4
Public gstrExtraColumnName() As String

Public Const BOOKFIXEDCOLS As Integer = 2
Public Const BOOKFIXEDROWS As Integer = 1

'色
'Private Const BOOKLINECOLOR As Integer = &HC8D0D4
Public Const BOOKLINECOLOR As Integer = &H0

Public Const BOOKBGFIXEDCOLSCOLOR As Integer = &HBAF0FE
Public Const BOOKBGFIXEDROWSCOLOR As Integer = &H67A6FE
Public Const BOOKBGREADONLYCELLSCOLOR As Integer = &HF0F0F0
Public Const BOOKBGLEAFSCOLOR As Integer = &HFFFFFF
Public Const BOOKBGNORMALSCOLOR As Integer = &HD0E4FF
Public Const BOOKBGTOTALSCOLOR As Integer = &HBAFFCC
Public Const BOOKSELECTEDCOLOR As Integer = &HFF

Public Const NORMALTEXTCOLOR As Integer = &H0
Public Const READONLYTEXTCOLOR As Integer = &H808080

'列番号
Public Const COLWEEKTOTAL As Integer = NUMDAYSPERWEEK + EXTRACOLUMN_WEEKTOTAL
Public Const COLMONTHTOTAL As Integer = NUMDAYSPERWEEK + EXTRACOLUMN_MONTHTOTAL
Public Const COLYEARTOTAL As Integer = NUMDAYSPERWEEK + EXTRACOLUMN_YEARTOTAL
Public Const COLBUDGETOFMONTH As Integer = NUMDAYSPERWEEK + EXTRACOLUMN_BUDGETOFMONTH
Public Const COLBUDGETBALANCE As Integer = NUMDAYSPERWEEK + EXTRACOLUMN_BUDGETBALANCE

Public Const STARTOFEXTRACOL As Integer = NUMDAYSPERWEEK
Public Const BOOKNUMCOLUMNS As Integer = BOOKFIXEDCOLS + COLBUDGETBALANCE + 1

'*****************************************************************************
'
'表に関する情報
'

'*****************************************************************************
'
'表示設定
'

Public Structure tUserInterface
    '家計簿の表を表示する領域
    Public oBookPicture As PictureBox

    Public grpBook As System.Drawing.Graphics
    Public imgCanvas As System.Drawing.Bitmap
    Public imgCell As System.Drawing.Bitmap
    Public imgIcons As System.Drawing.Bitmap

    Public nLeftMargin As Integer
    Public nTopMargin As Integer
    Public nBookWidth As Integer
    Public nBookHeight As integer

    Public canvasWidth As Integer
    Public canvasHeight As Integer

    Public nCellWidth As Integer
    Public nCellHeight As Integer
    Public nColumnsInSheet As Integer
    Public nRowsInSheet As Integer

    Public nCharWidth As Integer                          '固定フォントで一文字当たりの幅
    Public nCharHeight As Integer                         '固定フォントで一文字あたりの高さ

    '現在画面に表示している内容
    Public nCurrentYear As Integer
    Public nCurrentWeek As Integer
    Public sTableCaption As String                     'テーブルキャプション
    Public nNowShowingItemCount As Integer                '現在画面に表示している項目数
    Public nNowShowingItems() As Integer                  '現在画面に表示している項目
    Public utNowShowingDates() As Wrapper.ParsedDate    '現在画面に表示している列項目(日付)

    'スクロール範囲と位置
    Public oBookHScrollBar As HScrollBar
    Public oBookVScrollBar As VScrollBar
    Public nMaxHScrollBar As Integer
    Public nMaxVScrollBar As Integer
    Public nLeftCol As Integer
    Public nTopRow As Integer

    'ステータスバー
    Public oInfoStatusBar As System.Windows.Forms.StatusStrip

    'マウス
    Public nCurrentMouseX As Integer
    Public nCurrentMouseY As Integer
End Structure

Public Structure tBookView
    Public utAccountBook As Wrapper.AccountBook
    Public utUserInterface As tUserInterface
    Public oBookForm As Form

    Public nNumWeeks As Integer

    '家計簿の状態
    Public bBackupedBookFile As Boolean        'ファイルを一度バックアップしたか
    Public sCurrentBookFile As String          '現在使用中の家計簿ファイル
    Public bModifyCurrentBook As Boolean       '現在の家計簿ファイルを更新したか

    'ウィンドウキャプション
    Public sWindowCaption As String
    Public sNoNameCaption As String
    Public sModifyCaption As String

    'ツールバー、ステータスバー
    Public bShowStatusBar As Boolean
    Public bShowToolBar As Boolean
End Structure

End Module
