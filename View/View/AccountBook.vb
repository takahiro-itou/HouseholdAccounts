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
