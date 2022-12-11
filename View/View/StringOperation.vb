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

Public Function GetFileExt(ByVal strFileName As String) As String
'---------------------------------------------------------------------
'ファイルの拡張子を取得する
'[ IN] strFileName: ファイル名
'[RET] String     : 拡張子
'[ACT]
'  返される結果は、先頭の "." を含まない。
'---------------------------------------------------------------------
Dim i As Integer

    i = Len(strFileName)
    For i = Len(strFileName) To 1 Step -1
        If Mid$(strFileName, i, 1) = "." Then
            'この "." の後ろを取り出す
            GetFileExt = Mid$(strFileName, i + 1)
            Exit Function
        End If
    Next i

    '. が見つからないので、このファイル名には拡張子がない
    GetFileExt = ""
End Function

Public Function GetDirFromPath(ByVal strPath As String) As String
'---------------------------------------------------------------------
'フルパスからディレクトリ名を取得する
'[ IN] strPath: フルパス
'[RET] String : ディレクトリ名
'[ACT]
'  ファイル名(フルパスの最も右の"\"から後ろ)を切り捨て、
'ディレクトリ名を取得する。
'  返される結果は、最後の "\" を含まない。
'---------------------------------------------------------------------
Dim i As Integer

    i = Len(strPath)
    For i = Len(strPath) To 1 Step -1
        If Mid$(strPath, i, 1) = "\" Then
            'この "\" の前までを取り出す
            GetDirFromPath = Left$(strPath, i - 1)
            Exit Function
        End If
    Next i

    '"\" が見つからないので、このフルパスはディレクトリ名を含んでいない
    GetDirFromPath = ""
End Function

Public Function GetFullPathName(ByVal strBaseDir As String,
        ByVal strRelativePath As String) As String
'---------------------------------------------------------------------
'strBaseDirを基準とした、相対パスから、フルパスを取得する
'[ IN] strBaseDir     : 基準となるディレクトリ名
'[ IN] strRelativePath: strBaseDirからの相対パス
'[RET] String         : フルパス
'[ACT]
'  strBaseDirからの相対パスをフルパスに変換する。
'---------------------------------------------------------------------
Dim lngPos As Integer
Dim strTemp As String
Dim strLeft As String

    strTemp = strRelativePath

    Do While Len(strRelativePath) > 0
        Application.DoEvents()
        lngPos = InStr(strRelativePath, "\")
        If (lngPos = 0) Then
            'ディレクトリ指定がもうないので、ファイル名を最後にくっつける
            strTemp = strTemp & "\" & strRelativePath
            strRelativePath = ""
        Else
            strLeft = Left$(strRelativePath, lngPos)
            strRelativePath = Mid$(strRelativePath, lngPos + 1)
            If (strLeft = ".\") Then
                '現在のディレクトリ
            ElseIf (strLeft = "..\") Then
               '親ディレクトリに移動
                strTemp = Wrapper.Common.FilePathUtils.removeDirFromPath(strTemp)
            Else
                '指定されたディレクトリに移動
                strTemp = strTemp & "\" & strLeft
            End If
        End If
    Loop

    GetFullPathName = strTemp
End Function

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
