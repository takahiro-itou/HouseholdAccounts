Option Explicit

Module AnnualRecord

'*****************************************************************************
' AccountBook
' AnnualRecord  モジュール
'
' 家計簿の一年分のデータを管理する
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2006/09/23 - 2008/01/09
'*****************************************************************************

Public Function AnnualRecordGetItemDayTotal( _
    ByRef utRecord As tAnnualRecords, _
    ByVal lngItemIndex As Integer, ByVal lngDate As Integer) As Integer
'---------------------------------------------------------------------
'項目の１日の合計金額を返す
'[ IN] utRecord    : 年間レコード
'[ IN] lngItemIndex: 項目インデックス
'[ IN] lngDate     : 日付
'[RET] Long
'  １日の合計金額
'---------------------------------------------------------------------
Dim lngTotal As Integer

    With utRecord
        lngTotal = .utItemDetailCounts(lngItemIndex).nDayTotal(lngDate)
    End With
    AnnualRecordGetItemDayTotal = lngTotal
End Function

Public Function AnnualRecordGetItemMonthTotal( _
    ByRef utRecord As tAnnualRecords, _
    ByVal lngItemIndex As Integer, ByVal lngMonth As Integer) As Integer
'---------------------------------------------------------------------
'項目の１ヶ月の合計金額を返す
'[ IN] utRecord    : 年間レコード
'[ IN] lngItemIndex: 項目インデックス
'[ IN] lngMonth    : 月
'[RET] Long
'  １ヶ月の合計金額
'---------------------------------------------------------------------
Dim lngTotal As Integer

    With utRecord
        If (lngItemIndex < MAXITEMS) Then
            lngTotal = .utItemDetailCounts(lngItemIndex).nMonthTotal(lngMonth)
        Else
            lngTotal = 0
        End If
    End With
    AnnualRecordGetItemMonthTotal = lngTotal
End Function

Public Function AnnualRecordGetItemWeekTotal( _
    ByRef utRecord As tAnnualRecords, _
    ByVal lngItemIndex As Integer, ByVal lngWeek As Integer) As Integer
'---------------------------------------------------------------------
'項目の１週間の合計金額を返す
'[ IN] utRecord    : 年間レコード
'[ IN] lngItemIndex: 項目インデックス
'[ IN] lngWeek     : 週
'[RET] Long
'  １週間の合計金額
'---------------------------------------------------------------------
Dim lngTotal As Integer

    With utRecord
        If (lngItemIndex < MAXITEMS) Then
            lngTotal = .utItemDetailCounts(lngItemIndex).nWeekTotal(lngWeek)
        Else
            lngTotal = 0
        End If
    End With
    AnnualRecordGetItemWeekTotal = lngTotal
End Function

Public Function AnnualRecordGetItemYearTotal( _
    ByRef utRecord As tAnnualRecords, _
    ByVal lngItemIndex As Integer, ByVal lngYearIndex As Integer) As Integer
'---------------------------------------------------------------------
'項目の１年間の合計金額を返す
'[ IN] utRecord    : 年間レコード
'[ IN] lngItemIndex: 項目インデックス
'[ IN] lngYear     : 西暦年
'[RET] Long
'  １年間の合計金額
'---------------------------------------------------------------------
Dim lngTotal As Integer

    With utRecord
        lngTotal = .utItemAnnualCounts(lngItemIndex).nYearTotal(lngYearIndex)
    End With
    AnnualRecordGetItemYearTotal = lngTotal
End Function

End Module
