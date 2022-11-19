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

Public Function AnnualRecordGetItemDayTotal(
        ByRef utRecord As tAnnualRecords,
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

Public Function AnnualRecordGetItemMonthTotal(
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

Public Function AnnualRecordGetItemWeekTotal(
        ByRef utRecord As tAnnualRecords,
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

Public Function AnnualRecordGetItemYearTotal(
        ByRef utRecord As tAnnualRecords,
        ByVal lngItemIndex As Integer,
        ByVal lngYearIndex As Integer) As Integer
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

Public Function ReadAnnualRecords(ByRef utRecord As tAnnualRecords,
        ByVal lngFileNumber As Integer,
        ByVal lngItemBufferSize As Integer) As Integer
'---------------------------------------------------------------------
'ファイルから、一年分のレコードを読み込む
'[I/O] utRecord          : 年間レコード
'[ IN] lngFileNumber     : ファイル番号
'[ IN] lngItemBufferSize : 項目バッファのサイズ
'[RET] Long
'  読み込んだバイト数
'[ACT]
'  ファイルは予め開いて先頭位置にシークした状態でファイル番号を渡す
'---------------------------------------------------------------------
Dim lngStartPos As Integer, lngEndPos As Integer

    lngStartPos = Seek(lngFileNumber) - 1

    lngEndPos = Seek(lngFileNumber) - 1
    ReadAnnualRecords = (lngEndPos - lngStartPos)
End Function

Public Function ReallocAnnualRecordsBuffers(
        ByRef utRecord As tAnnualRecords,
        ByVal lngItemBufferSize As Integer,
        ByVal lngStartYear As Integer,
        ByVal lngNumYears As Integer) As Boolean
'---------------------------------------------------------------------
'年間レコード用のバッファを確保しなおす
'[I/O] utRecord          : 年間レコード
'[ IN] lngItemBufferSize : 項目バッファのサイズ
'[ IN] lngStartYear      : 開始西暦年
'[ IN] lngNumYears       : 年数
'[RET] Boolean
'  成功したらTrue, 失敗したら False
'---------------------------------------------------------------------
Dim i As Integer

    With utRecord
        If (lngItemBufferSize < 0) Then lngItemBufferSize = .nItemBufferSize

        'If (lngItemBufferSize < 0) Then lngItemBufferSize = .nItemBufferSize

        ReDim Preserve .utItemAnnualCounts(0 To lngItemBufferSize - 1)
        ReDim Preserve .utItemDetailCounts(0 To lngItemBufferSize - 1)
        .nItemBufferSize = lngItemBufferSize

        If (lngNumYears > 0) Then
            For i = 0 To lngItemBufferSize - 1
                With .utItemAnnualCounts(i)
                    ReDim Preserve .nStartValues(0 To lngNumYears - 1)
                    ReDim Preserve .nEndValues(0 To lngNumYears - 1)
                    ReDim Preserve .nYearTotal(0 To lngNumYears - 1)
                End With
            Next i
        End If

        For i = 0 To lngItemBufferSize - 1
            With .utItemDetailCounts(i)
                ReDim Preserve .nDayTotal(MAXDAYS - 1)
                ReDim Preserve .nWeekTotal(MAXWEEKS - 1)
                ReDim Preserve .nMonthTotal(MAXMONTH)
            End With
        Next i
    End With

    ReallocAnnualRecordsBuffers = True
End Function

Public Function RecountAnnualRecords(ByRef utRecord As tAnnualRecords,
        ByRef lngItemFlags() As Integer, ByVal lngItemBufferSize As Integer,
        ByVal lngYear As Integer, ByVal lngNumDays As Integer) As Boolean
'---------------------------------------------------------------------
'年間レコードを再集計する
'[I/O] utRecord          : 年間レコード
'[ IN] lngItemFlags()    : 各項目のフラグ
'[ IN] lngItemBufferSize : 項目バッファのサイズ
'[RET] Boolean
'  成功したらTrue, 何かエラーがあれば False
'---------------------------------------------------------------------
Dim i As Integer
Dim lngDate As Integer, lngStartDayIndex As Integer, lngEndDayIndex As Integer

    '初期値を書き込む
    With utRecord
        For i = 0 To lngItemBufferSize - 1
            If ((lngItemFlags(i) And ITEM_FLAG_TYPEMASK) = ITEM_FLAG_BALANCE) Then
                .utItemDetailCounts(i).nDayTotal(0) = .utItemAnnualCounts(i).nStartValues(lngYear)
            End If
        Next i

        lngStartDayIndex = GetWeekday(lngYear, 1, 1)
        lngEndDayIndex = GetDayInYear(lngYear, 12, 31) + lngStartDayIndex

        '全てのレシートを集計する
        For lngDate = 0 To lngNumDays - 1
            'バッファをクリアする
            For i = 0 To lngItemBufferSize - 1
                If ((lngItemFlags(i) And ITEM_FLAG_TYPEMASK) = ITEM_FLAG_BALANCE) Then
                Else
                    .utItemDetailCounts(i).nDayTotal(lngDate) = 0
                End If
            Next i
        Next lngDate
    End With

    RecountAnnualRecords = True
End Function

Public Function WriteAnnualRecords(ByRef utRecord As tAnnualRecords,
        ByVal lngFileNumber As Integer,
        ByVal lngItemBufferSize As Integer) As Integer
'---------------------------------------------------------------------
'ファイルに、一年分のレコードを書き込む
'[ IN] utRecord          : 年間レコード
'[ IN] lngFileNumber     : ファイル番号
'[ IN] lngItemBufferSize : 項目バッファのサイズ
'[RET] Long
'  書き込んだバイト数
'[ACT]
'  ファイルは予め開いて先頭位置にシークした状態でファイル番号を渡す
'---------------------------------------------------------------------
Dim lngReserved As Integer
Dim lngStartPos As Integer, lngEndPos As Integer
Dim utTemp() As tBookItemAnnualCounts

    lngStartPos = Seek(lngFileNumber) - 1
    With utRecord
        '記録する年を書き込む
        lngReserved = 0
        FilePut(lngFileNumber, lngReserved, lngStartPos + 1)

        '項目数を書き込む
        FilePut(lngFileNumber, lngItemBufferSize)

        '8Bytes予約
        lngReserved = 0
        FilePut(lngFileNumber, lngReserved)
        FilePut(lngFileNumber, lngReserved)

        '項目毎の年間集計データを書き込む
        utTemp = .utItemAnnualCounts.Clone
        ReDim Preserve utTemp(0 To lngItemBufferSize - 1)
        FilePut(lngFileNumber, utTemp)
    End With

    '書き込んだバイト数を返す
    lngEndPos = Seek(lngFileNumber) - 1
    WriteAnnualRecords = (lngEndPos - lngStartPos)
End Function

End Module
