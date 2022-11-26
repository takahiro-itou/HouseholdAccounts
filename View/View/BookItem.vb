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

Public Function BookItemGetItemFlags(
        ByRef utBookItems As Wrapper.BookItems,
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

Public Function BookItemGetParentItemHandle(
        ByRef utBookItems As Wrapper.BookItems,
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

Public Function BookItemGetSubItemHandle(
        ByRef utBookItems As Wrapper.BookItems,
        ByVal lngItemIndex As Integer,
        ByVal lngSubItemIndex As Integer) As Integer
'---------------------------------------------------------------------
'項目が持つサブ項目のハンドルを返す
'[ IN] utBookItems     : 項目一覧データ
'[ IN] lngItemIndex    : 項目番号
'[ IN] lngSubItemIndex : サブ項目の番号
'[RET] Long
'---------------------------------------------------------------------
Dim lngSubItemHandle As Integer

    lngSubItemHandle = utBookItems.utItemEntries(lngItemIndex).nSubItems(lngSubItemIndex)
    BookItemGetSubItemHandle = lngSubItemHandle
End Function

Public Function BookItemRelocateItems(
        ByRef utBookItems As Wrapper.BookItems,
        ByRef lpNewIndex() As Integer) As Integer
'---------------------------------------------------------------------
'家計簿の項目を並べなおす
'i 番目の項目を、lpNewIndex(i) で指定される位置に移動し、
'それにあわせて、子ノードのnParentHandle を更新する
'[I/O] utBookItems   : 項目一覧データ
'[ IN] lngNewIndex() :
'[RET] Long
'          失敗すれば、負の整数
'          成功すれば、+1
'[ACT]
'  この関数を呼び出して、項目を並べ替えた場合は、
'年間項目データも更新すること
'---------------------------------------------------------------------
Dim lngItemBufferSize As Integer
Dim i As Integer, lngNew As Integer
Dim j As Integer, lngCount As Integer, lngChildHandle As Integer
Dim lngFlags() As Integer
Dim lngSubItems() As Integer, lngCheck() As Integer
Dim utItems() As Wrapper.BookItemEntry

    lngItemBufferSize = utBookItems.nItemBufferSize

    '並び替える前に、並び替えのデータを検査する
    ReDim lngCheck(0 To lngItemBufferSize - 1)
    For i = 0 To lngItemBufferSize - 1
        lngCheck(i) = 0
    Next i
    For i = 0 To lngItemBufferSize - 1
        lngNew = lpNewIndex(i)
        lngCheck(lngNew) = lngCheck(lngNew) + 1
    Next i
    For i = 0 To lngItemBufferSize - 1
        If (lngCheck(i) <> 1) Then
            MessageBox.Show("エラー：項目の並び替えができません。" & vbCrLf & "指示された並び替えは、重複または不足があります。")
            BookItemRelocateItems = -1
            Exit Function
        End If
    Next i

    With utBookItems
        '配列のバックアップコピーをとる
        lngFlags = .nFlags.Clone
        utItems = .utItemEntries.Clone

        '項目データを設定する
        For i = 0 To lngItemBufferSize - 1
            lngNew = lpNewIndex(i)
            .nFlags(lngNew) = lngFlags(i)
            .utItemEntries(lngNew) = utItems(i)

            '子ノードを書き換える
            With .utItemEntries(lngNew)
                lngCount = .nSubItemCount
                lngSubItems = .nSubItems.Clone
            End With

            For j = 0 To lngCount - 1
                lngChildHandle = lngSubItems(j)
                .utItemEntries(lngChildHandle).nParentHandle = lngNew
            Next j
        Next i
    End With

    '完了
    BookItemRelocateItems = 1
End Function

End Module
