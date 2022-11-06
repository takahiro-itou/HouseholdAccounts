Option Explicit

Module BookSettings

'*****************************************************************************
' AccountBook
' BookSettings  モジュール
'
' 家計簿を管理する
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2006/09/23 - 2008/01/06
'*****************************************************************************

'=========================================================================
'
'パブリックプロシージャ
'

Public Function AllocBookItems(ByRef utBook As tAccountBook, _
    ByVal lngItemBufferSize As Integer) As Integer
'---------------------------------------------------------------------
'項目データ用バッファを確保する
'[I/O] utBook            : 家計簿データ
'[ IN] lngItemBufferSize : 確保する項目数
'[RET] Long
'  増えた部分の先頭のインデックス
'---------------------------------------------------------------------
Dim lngBufferSize As Integer
Dim lngStartYear As Integer, lngNumYears As Integer
Dim lngResult As Integer

    With utBook
        lngStartYear = .nStartYear
        lngNumYears = .nNumYears

        'バッファをリサイズし、増えた部分の先頭を記録しておく
        With .utBookItems
            lngResult = .nItemBufferSize
            lngBufferSize = (lngItemBufferSize + 15) And &H7FFFFFF0
            .nItemBufferSize = lngBufferSize

            ReDim .nFlags(0 To lngBufferSize - 1)
            ReDim .utItemEntries(0 To lngBufferSize - 1)
        End With

        ReallocAnnualRecordsBuffers(
                .utAnnualRecords, lngBufferSize, lngStartYear, lngNumYears)
    End With

    AllocBookItems = lngResult
End Function

Public Function BookItemAllocNewItem(ByRef utBook As tAccountBook) As Integer
'---------------------------------------------------------------------
'新しい項目用の領域を確保し、そのハンドルを返す
'[I/O] utBook: 家計簿データ
'[RET] Long
'  新しい項目用のハンドル
'---------------------------------------------------------------------
Dim i As Integer
Dim lngResult As Integer

    With utBook
        'バッファサイズと登録済み項目数を比較し、
        'バッファに空きがある場合は、
        '空きを探してそのバンドル(インデックス)を返す
        lngResult = -1
        With .utBookItems
            If (.nRegisteredItemCount < .nItemBufferSize) Then
                For i = .nRootItemCount To .nItemBufferSize - 1
                    If (.nFlags(i) = ITEM_FLAG_NOTUSED) Then
                        lngResult = i
                        Exit For
                    End If
                Next i
            End If
        End With
    End With

    If (lngResult >= 0) Then
        BookItemAllocNewItem = lngResult
        Exit Function
    End If

    'バッファをリサイズし、増えた部分の先頭を確保する
    BookItemAllocNewItem = AllocBookItems(utBook, lngResult)
End Function

Public Function InsertNewBookItem(ByRef utBook As tAccountBook,
        ByVal lngParentItemHandle As Integer, ByVal strName As String,
        ByVal lngFlags As Integer, ByVal lngStartDate As Integer,
        ByVal lngStartBalance As Integer) As Integer
'---------------------------------------------------------------------
'指定した項目に新しいサブ項目を追加する
'[I/O] utBookItems         : 項目一覧データ
'[I/O] utYearRecord        : 年間レコードデータ
'[ IN] lngParentItemHandle : 親項目のハンドル
'[ IN] strName             : 項目名
'[ IN] lngFlags            : 項目フラグ
'[ IN] lngStartDate        : 開始日
'[ IN] lngStartBalance     : 開始時金額
'[RET] Long
'  追加した項目のハンドル
'---------------------------------------------------------------------
Dim lngNewItemHandle As Integer

    '新しい項目用のインデックスを取得する
    lngNewItemHandle = BookItemAllocNewItem(utBook)

    With utBook.utBookItems
        'この項目に初期値を書き込む
        .nFlags(lngNewItemHandle) = lngFlags
        With .utItemEntries(lngNewItemHandle)
            .nParentHandle = lngParentItemHandle
            .sItemName = strName
            .nSubItemCount = 0
            .nStartDate = lngStartDate
            .nStartBalance = lngStartBalance
        End With

        .nRegisteredItemCount = .nRegisteredItemCount + 1

        '親項目の内容を更新する
        With .utItemEntries(lngParentItemHandle)
            ReDim Preserve .nSubItems(0 To .nSubItemCount)
            .nSubItems(.nSubItemCount) = lngNewItemHandle
            .nSubItemCount = .nSubItemCount + 1
        End With
    End With

    '追加した新しい項目のハンドルを返す
    InsertNewBookItem = lngNewItemHandle
End Function

End Module
