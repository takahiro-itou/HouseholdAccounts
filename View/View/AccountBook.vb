Option Explicit

Module AccountBook

'*****************************************************************************
' AccountBook
' AccountBook モジュール
'
' 家計簿を管理する
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2006/09/23 - 2008/01/09
'*****************************************************************************

Public gutTempBook As tAccountBook

Public Function AccountBookUpdateItemHandleInYearRecord(
        ByRef lpBookItems As tBookItems,
        ByRef lpNewIndex() As Integer,
        ByRef utYearRecord As tAnnualRecords) As Integer
'---------------------------------------------------------------------
'家計簿の項目を並べ替えにあわせて、
'指定された年のデータの、項目毎の集計データを並べなおし、
'さらに全レシートの項目番号を設定しなおす。
'lpBookItems 内の項目データは既に並べたなおした後の状態になっている必要がある
'---------------------------------------------------------------------
Dim i As Integer, lngNew As Integer, lngBufferSize As Integer
Dim j As Integer, lngFlags As Integer, lngCount As Integer
Dim lngDay As Integer
'Dim utAnnualCounts() As tBookItemAnnualCounts
Dim utDetailCounts() As tBookItemDetailCounts

    lngBufferSize = lpBookItems.nItemBufferSize

    With utYearRecord
        '項目毎の集計データを更新する
'        utAnnualCounts() = .utItemAnnualCounts()
        utDetailCounts = .utItemDetailCounts
        For i = 0 To lngBufferSize - 1
'            .utItemAnnualCounts(lngNew) = utAnnualCounts(i)
            .utItemDetailCounts(lngNew) = utDetailCounts(i)
        Next i

        'レシートの項目番号を設定しなおす
        For lngDay = 0 To MAXDAYS - 1
        With .utDayRecords(lngDay)
            For i = 0 To .nNumReceipt - 1
            With .utReceipts(i)
                lngFlags = .nFlags
                lngCount = .nNumGoods
                If (lngFlags <> RECEIPT_FLAG_NOTUSED) Then
                    For j = 0 To lngCount - 1
                    With .utGoods(j)
                        lngNew = lpNewIndex(.nItemType)
                        .nItemType = lngNew
                        .nRootItemType = BookItemGetRootItemHandle(lpBookItems, lngNew)
                    End With
                    Next j
                End If
            End With
            Next i
        End With
        Next lngDay
    End With

    AccountBookUpdateItemHandleInYearRecord = 0
End Function

Public Function AddDataToItemTotal(ByRef utBook As tAccountBook,
        ByVal lngYearIndex As Integer, ByVal lngDayIndex As Integer,
        ByVal lngItemIndex As Integer, ByVal lngValue As Integer) As Boolean
'---------------------------------------------------------------------
'---------------------------------------------------------------------
Dim lngFlags() As Integer
Dim lngParentHandle As Integer
Dim lngYear As Integer, lngWeek As Integer, lngMonth As Integer
Dim utDate As tParsedDate
Dim blnAddToParent As Boolean, blnAddToRoot As Boolean

    blnAddToParent = True
    blnAddToRoot = True

    '項目フラグを取り出しておく
    With utBook
        lngYear = .nStartYear + lngYearIndex
        With .utBookItems
            lngFlags = .nFlags
        End With
    End With

    '日付から、週と月を計算しておく
    GetDayFromIndex(utDate, lngYear, lngDayIndex, -1)
    With utDate
        lngWeek = .nWeek
        lngMonth = .nMonth
        lngYear = .nYear
    End With

    With utBook.utAnnualRecords
        Do While (lngItemIndex >= 0)
            lngParentHandle = utBook.utBookItems.utItemEntries(lngItemIndex).nParentHandle

            If (lngFlags(lngItemIndex) And ITEM_FLAG_NOCOUNT_PARENT) Then
                blnAddToParent = False
                blnAddToRoot = False
            End If
            If (lngFlags(lngItemIndex) And ITEM_FLAG_NOCOUNT_ROOT) Then
                blnAddToRoot = False
            End If

            If (lngParentHandle = -1) And (blnAddToRoot = False) Then Exit Do

            With .utItemDetailCounts(lngItemIndex)
                .nDayTotal(lngDayIndex) = .nDayTotal(lngDayIndex) + lngValue
                .nWeekTotal(lngWeek) = .nWeekTotal(lngWeek) + lngValue
                .nMonthTotal(lngMonth) = .nMonthTotal(lngMonth) + lngValue
            End With
            With .utItemAnnualCounts(lngItemIndex)
                .nYearTotal(lngYearIndex) = .nYearTotal(lngYearIndex) + lngValue
            End With

            If ((blnAddToParent = False) Or (lngParentHandle = -1)) Then Exit Do
            lngItemIndex = lngParentHandle
        Loop
    End With

    AddDataToItemTotal = blnAddToRoot
End Function

Public Function IsAccountBookEnabled(ByRef utBook As tAccountBook) As Boolean
'---------------------------------------------------------------------
'家計簿データが有効なデータかどうか判断する
'[ IN] utBook : 家計簿データ
'[RET] Boolean
'  有効ならTrue, 無効なら False
'[ACT]
'  初期化されていない状態などは無効なデータである。
'  新規作成、ロードなどを行って、家計簿の処理ができる状態に
'移行していれば有効なデータである。
'---------------------------------------------------------------------
    IsAccountBookEnabled = utBook.bEnabled
End Function

Public Function IsDayBeforeStart(ByRef utBook As tAccountBook, _
    ByVal lngYear As Integer, ByVal lngDayIndex As Integer) As Boolean
'---------------------------------------------------------------------
'指定した日付が、家計簿の開始日より前かどうか調べる
'[ IN] utBook      : 家計簿データ
'[ IN] lngYear     : 西暦年
'[ IN] lngDayIndex : 元日からの日数(オフセット付)
'[RET] Boolean
'  開始日より前ならTrue, そうでなければ False
'---------------------------------------------------------------------
Dim blnResult As Boolean

    With utBook
        If (CompareDates(lngYear, lngDayIndex, .nStartYear, .nStartDayIndex) < 0) Then
            blnResult = True
        Else
            blnResult = False
        End If
    End With
    IsDayBeforeStart = blnResult
End Function

End Module
