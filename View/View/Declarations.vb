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
'項目用フラグ
'

Public Const ITEM_FLAG_TYPEMASK As Long = &HFF&
Public Const ITEM_FLAG_NOTUSED As Long = 0          '未使用
Public Const ITEM_FLAG_INHERIT As Long = 1          '親の設定を継承
Public Const ITEM_FLAG_BALANCE As Long = 9          '残高表示
Public Const ITEM_FLAG_INCOME As Long = 17          '収入
Public Const ITEM_FLAG_OUTLAY As Long = 18          '支出
Public Const ITEM_FLAG_BANK As Long = 25            '銀行口座
Public Const ITEM_FLAG_BANK_WITHDRAW As Long = 26   '口座引出
Public Const ITEM_FLAG_BANK_DEPOSIT As Long = 27    '口座入金
Public Const ITEM_FLAG_BANK_TRANSFER As Long = 28   '口座振替

Public Const ITEM_FLAG_EXPANDED As Long = &H100&

Public Const ITEM_FLAG_NOCOUNT_PARENT As Long = &H10000
Public Const ITEM_FLAG_NOCOUNT_ROOT As Long = &H20000
Public Const ITEM_FLAG_HIDDEN As Long = &H10000000
Public Const ITEM_FLAG_UNERASABLE As Long = &H20000000
Public Const ITEM_FLAG_READONLY As Long = &H40000000

'*****************************************************************************
'
'レシートデータ用フラグ
'

Public Const RECEIPT_FLAG_TYPEMASK As Long = &HFF&
Public Const RECEIPT_FLAG_NOTUSED As Long = 0
Public Const RECEIPT_FLAG_USED As Long = 1

'*****************************************************************************
'
'各データの最大個数
'

Public Const DAY_START As Long = 6
Public Const MAXITEMS As Long = 65536       '家計簿に記録できる最大項目数
Public Const MAXBALANCES As Long = 256      '家計簿に登録できる最大口座数

Public Const MAXDAYS As Long = 378          '１年分の家計簿に記録する最大日数
Public Const MAXWEEKS As Long = 54          '１年分の家計簿に記録する最大週数
Public Const MAXMONTH As Long = 12          '１年分の家計簿に記録する最大月数

'*****************************************************************************
'
'表示関係
'

Public Const ACCENTER As Long = 0
Public Const ACLEFT As Long = 1
Public Const ACRIGHT As Long = 2

'行や列の見出しなど
Public Const NUMDAYSPERWEEK As Long = 7

Public Const NUMBEROFEXTRACOLUMNS As Long = 5
Public Const EXTRACOLUMN_WEEKTOTAL As Long = 0
Public Const EXTRACOLUMN_MONTHTOTAL As Long = 1
Public Const EXTRACOLUMN_YEARTOTAL As Long = 2
Public Const EXTRACOLUMN_BUDGETOFMONTH As Long = 3
Public Const EXTRACOLUMN_BUDGETBALANCE As Long = 4
Public gstrExtraColumnName() As String

Public Const BOOKFIXEDCOLS As Long = 2
Public Const BOOKFIXEDROWS As Long = 1

'色
'Private Const BOOKLINECOLOR As Long = &HC8D0D4
Public Const BOOKLINECOLOR As Long = &H0&

Public Const BOOKBGFIXEDCOLSCOLOR As Long = &HBAF0FE
Public Const BOOKBGFIXEDROWSCOLOR As Long = &H67A6FE
Public Const BOOKBGREADONLYCELLSCOLOR As Long = &HF0F0F0
Public Const BOOKBGLEAFSCOLOR As Long = &HFFFFFF
Public Const BOOKBGNORMALSCOLOR As Long = &HD0E4FF
Public Const BOOKBGTOTALSCOLOR As Long = &HBAFFCC
Public Const BOOKSELECTEDCOLOR As Long = &HFF&

Public Const NORMALTEXTCOLOR As Long = &H0&
Public Const READONLYTEXTCOLOR As Long = &H808080

'列番号
Public Const COLWEEKTOTAL As Long = NUMDAYSPERWEEK + EXTRACOLUMN_WEEKTOTAL
Public Const COLMONTHTOTAL As Long = NUMDAYSPERWEEK + EXTRACOLUMN_MONTHTOTAL
Public Const COLYEARTOTAL As Long = NUMDAYSPERWEEK + EXTRACOLUMN_YEARTOTAL
Public Const COLBUDGETOFMONTH As Long = NUMDAYSPERWEEK + EXTRACOLUMN_BUDGETOFMONTH
Public Const COLBUDGETBALANCE As Long = NUMDAYSPERWEEK + EXTRACOLUMN_BUDGETBALANCE

Public Const STARTOFEXTRACOL As Long = NUMDAYSPERWEEK
Public Const BOOKNUMCOLUMNS As Long = BOOKFIXEDCOLS + COLBUDGETBALANCE + 1

'*****************************************************************************
'
'家計簿内の各項目、口座(現金残高を含む)
'

'データ項目
Public Structure tBookItemEntry
    Public nParentHandle As Long               '親項目のハンドル
    Public nItemNameID As Long                 '項目名のID(文字列テーブル内のインデックス)
    Public sItemName As String                 '項目名
    Public nSubItemCount As Long               'サブ項目数
    Public nSubItems() As Long                 'サブ項目のハンドル(インデックス)
    Public nStartDate As Long                  '開始年月日(残高の項目のみ)
    Public nStartBalance As Long               '開始時の残高(残高の項目のみ)
End Structure

'項目一覧
Public Structure tBookItems
    Public nItemBufferSize As Long                 '項目用バッファサイズ
    Public nRegisteredItemCount As Long            '登録済み項目数
    Public nRootItemCount As Long                  'ルートになる項目の数
    Public nFlags() As Long                        '項目のフラグ
    Public utItemEntries() As tBookItemEntry       '項目データ
    Public nInnerTaxItemHandle As Long             '「内税」項目のハンドル
    Public nOuterTaxItemHandle As Long             '「外税」項目のハンドル
End Structure

'*****************************************************************************
'
'集計されたデータの情報
'

'項目毎の年間集計
Public Structure tBookItemAnnualCounts
    Public nStartValues() As Long                  '開始時の数値
    Public nEndValues() As Long                    '終了時の数値
    Public nYearTotal() As Long                    '各年の合計金額
End Structure

'項目毎の詳細集計結果
Public Structure tBookItemDetailCounts
    '日週月毎の集計、一年間の合計金額
    Public nDayTotal() As Long     '日毎の合計金額：378 日
    Public nWeekTotal() As Long   '週毎の合計金額：54週
    Public nMonthTotal() As Long      '月毎の合計金額：12ヶ月
End Structure

End Module
