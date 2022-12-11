Option Explicit

Module StringOperation

'*****************************************************************************
' Libary
' Stringモジュール
'
' 文字列を操作する関数群
'
' Copyright (c) Itou Takahiro, All rights reserved.
' This file is written in 2004/08/18 - 2007/12/31
'*****************************************************************************

Public Function GetRelativePath(ByVal strPath As String,
        ByVal strBaseDir As String) As String
'---------------------------------------------------------------------
'フルパスから、strBaseDirを基準とした、相対パスを取得する
'[ IN] strPath   : フルパス
'[ IN] strBaseDir: 基準となるディレクトリ名
'[RET] String    : 相対パス
'[ACT]
'  フルパスstrPathを、strBaseDirからの相対パスに変換する。
'---------------------------------------------------------------------
Dim lngPos As Integer
Dim strTemp As String
Dim strBaseTemp As String
Dim strNameTemp As String

    If strBaseDir = "" Then
        GetRelativePath = strPath
    End If

    strTemp = ""

    lngPos = 0
    Do While lngPos = 0
        strBaseTemp = LCase$(strBaseDir)
        strNameTemp = LCase$(strPath)
        lngPos = InStr(strNameTemp, strBaseTemp)
        If lngPos = 0 Then
            strBaseDir = Wrapper.Common.FilePathUtils.removeDirFromPath(strBaseDir)
            strTemp = strTemp & "..\"
        Else
            strTemp = strTemp & Mid$(strPath, Len(strBaseDir) + 2)
        End If
    Loop

    GetRelativePath = strTemp
End Function

End Module
