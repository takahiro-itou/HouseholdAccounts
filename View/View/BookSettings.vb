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
Dim i As Integer
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

End Module
