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

Public Function ReadAnnualRecords(
        ByRef utRecord As Wrapper.AnnualRecords,
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

Public Function RecountAnnualRecords(
        ByRef utRecord As Wrapper.AnnualRecords,
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
            If ((lngItemFlags(i) And Wrapper.ItemFlag.ITEM_FLAG_TYPEMASK) = Wrapper.ItemFlag.ITEM_FLAG_BALANCE) Then
                .utItemDetailCounts(i).nDayTotal(0) = .utItemAnnualCounts(i).nStartValues(lngYear)
            End If
        Next i

        lngStartDayIndex = Wrapper.ManagedDate.getWeekday(lngYear, 1, 1)
        lngEndDayIndex = Wrapper.ManagedDate.getDayInYear(lngYear, 12, 31) + lngStartDayIndex

        '全てのレシートを集計する
        For lngDate = 0 To lngNumDays - 1
            'バッファをクリアする
            For i = 0 To lngItemBufferSize - 1
                If ((lngItemFlags(i) And Wrapper.ItemFlag.ITEM_FLAG_TYPEMASK) = Wrapper.ItemFlag.ITEM_FLAG_BALANCE) Then
                Else
                    .utItemDetailCounts(i).nDayTotal(lngDate) = 0
                End If
            Next i
        Next lngDate
    End With

    RecountAnnualRecords = True
End Function

Public Function WriteAnnualRecords(
        ByRef utRecord As Wrapper.AnnualRecords,
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
Dim utTemp() As Wrapper.BookItemAnnualCounts

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
