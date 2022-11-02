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

Public Function BookItemGetRegisteredItemCount(ByRef utBookItems As tBookItems) As Long
'---------------------------------------------------------------------
'使用済みの項目数を返す
'[ IN] utBookItems : 項目一覧データ
'[RET] Long
'---------------------------------------------------------------------
    BookItemGetRegisteredItemCount = utBookItems.nRegisteredItemCount
End Function

End Module
