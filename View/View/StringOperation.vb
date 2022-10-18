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

Public Function ByteToString(ByRef lpBuffer() As Byte, _
    ByVal lngStart As Long, ByVal lngEnd As Long, _
    Optional ByVal blnNullTerm As Boolean = True) As String
'---------------------------------------------------------------------
'バイト列を文字列に変換する
'[ IN] bytBuffer(): バイト列
'[ IN] lngStart   : 変換を開始する位置(配列のインデックス)
'[ IN] lngEnd     : 変換を終了する位置(配列のインデックス)
'[ IN] blnNullTerm: TrueならNull文字を終端とする
'[RET] String     : 変換結果
'[ACT]
'  lngStartからlngEnd までの範囲を
'(システムで使用している文字コードで)文字列に変換する。
'---------------------------------------------------------------------
Dim i As Long
Dim lpTemp() As Byte
Dim strText As String

    '指定された範囲を文字列に変換する
    ReDim lpTemp(lngEnd - lngStart + 1)
    For i = lngStart To lngEnd
        lpTemp(i - lngStart) = lpBuffer(i)
    Next i
    strText = System.Text.Encoding.GetEncoding("utf8").GetString(lpTemp)

    'NULL終端文字で文字列を切る
    If blnNullTerm Then
        i = InStr(strText, vbNullChar)
        If (i > 0) Then
            strText = Left$(strText, i - 1)
        End If
    End If

    '変換結果を返す
    ByteToString = strText
End Function

End Module
