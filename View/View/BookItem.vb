Option Explicit

Module BookItem

'*****************************************************************************
' AccountBook
' BookItem  モジュール
'
' 家計簿のデータ項目を管理する
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2006/09/23 - 2008/01/06
'*****************************************************************************

Public Function BookItemGetItemType(ByRef utBookItems As tBookItems, _
    ByVal lngItemIndex As Integer) As Integer
'---------------------------------------------------------------------
'項目の種類を返す
'[ IN] utBookItems : 項目一覧データ
'[ IN] lngItemIndex: 項目番号
'[RET] Long
'---------------------------------------------------------------------
Dim lngType As Integer
Dim lngParentHandle As Integer

    With utBookItems
        Do While (lngItemIndex >= 0)
            lngType = (.nFlags(lngItemIndex) And ITEM_FLAG_TYPEMASK)
            lngParentHandle = .utItemEntries(lngItemIndex).nParentHandle

            If (lngType = ITEM_FLAG_INHERIT) Then
                lngItemIndex = lngParentHandle
            Else
                Exit Do
            End If
        Loop
    End With

    BookItemGetItemType = lngType
End Function

Public Function BookItemGetRegisteredItemCount(ByRef utBookItems As tBookItems) As Long
'---------------------------------------------------------------------
'使用済みの項目数を返す
'[ IN] utBookItems : 項目一覧データ
'[RET] Long
'---------------------------------------------------------------------
    BookItemGetRegisteredItemCount = utBookItems.nRegisteredItemCount
End Function

End Module
