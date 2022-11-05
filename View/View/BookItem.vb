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

Public Sub BookItemExpandItem(ByRef utBookItems As tBookItems, _
    ByVal lngItemIndex As Integer, ByVal blnExpanded As Boolean)
'---------------------------------------------------------------------
'指定した項目を展開したり、閉じたりする
'[I/O] utBookItems : 項目一覧データ
'[ IN] lngItemIndex: 項目番号
'[ IN] blnExpanded : 展開、または折畳
'          True  = サブ項目も表示する
'          False = この項目まで表示して、サブ項目は表示しない
'[RET] なし
'---------------------------------------------------------------------

    With utBookItems
        If (blnExpanded) Then
            .nFlags(lngItemIndex) = (.nFlags(lngItemIndex) Or ITEM_FLAG_EXPANDED)
        Else
            .nFlags(lngItemIndex) = (.nFlags(lngItemIndex) And (Not ITEM_FLAG_EXPANDED))
        End If
    End With
End Sub

Public Function BookItemGetItemBufferSize(ByRef utBookItems As tBookItems)
'---------------------------------------------------------------------
'項目用のバッファのサイズを得る
'[ IN] utBookItems : 項目一覧データ
'[RET] Long
'  項目用バッファのサイズ
'---------------------------------------------------------------------
    BookItemGetItemBufferSize = utBookItems.nItemBufferSize
End Function

Public Function BookItemGetItemExpanded(ByRef utBookItems As tBookItems, _
    ByVal lngItemIndex As Integer) As Boolean
'---------------------------------------------------------------------
'指定した項目が、展開されているかを返す
'[ IN] utBookItems : 項目一覧データ
'[ IN] lngItemIndex: 項目番号
'[RET] Boolean
'  True  = サブ項目も表示する
'  False = この項目まで表示して、サブ項目は表示しない
'---------------------------------------------------------------------
Dim lngFlags As Integer

    lngFlags = utBookItems.nFlags(lngItemIndex)
    BookItemGetItemExpanded = (lngFlags And ITEM_FLAG_EXPANDED)
End Function

Public Function BookItemGetItemFlags(ByRef utBookItems As tBookItems, _
    ByVal lngItemIndex As Integer) As Long
'---------------------------------------------------------------------
'項目のフラグを得る
'[ IN] utBookItems : 項目一覧データ
'[ IN] lngItemIndex: 項目番号
'[RET] Long
'---------------------------------------------------------------------
Dim lngFlags As Integer

    lngFlags = utBookItems.nFlags(lngItemIndex)
    BookItemGetItemFlags = lngFlags
End Function

Public Function BookItemGetItemName(ByRef utBookItems As tBookItems, _
    ByVal lngItemIndex As Integer) As String
'---------------------------------------------------------------------
'項目の名前を得る
'[ IN] utBookItems : 項目一覧データ
'[ IN] lngItemIndex: 項目番号
'[RET] String
'---------------------------------------------------------------------
Dim strName As String

    strName = utBookItems.utItemEntries(lngItemIndex).sItemName
    BookItemGetItemName = strName
End Function

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

Public Function BookItemGetParentItemHandle(ByRef utBookItems As tBookItems, _
    ByVal lngItemIndex As Integer) As Integer
'---------------------------------------------------------------------
'項目の親項目のハンドルを返す
'[ IN] utBookItems : 項目一覧データ
'[ IN] lngItemIndex: 項目番号
'[RET] Long
'---------------------------------------------------------------------
Dim lngParentHandle As Integer

    lngParentHandle = utBookItems.utItemEntries(lngItemIndex).nParentHandle
    BookItemGetParentItemHandle = lngParentHandle
End Function

Public Function BookItemGetRegisteredItemCount(ByRef utBookItems As tBookItems) As Integer
'---------------------------------------------------------------------
'使用済みの項目数を返す
'[ IN] utBookItems : 項目一覧データ
'[RET] Long
'---------------------------------------------------------------------
    BookItemGetRegisteredItemCount = utBookItems.nRegisteredItemCount
End Function

End Module
