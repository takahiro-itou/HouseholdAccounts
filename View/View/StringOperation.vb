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
Dim i As Long, cnvlastIndex As Long
Dim c As Byte
Dim lpTemp() As Byte
Dim strText As String

    '指定された範囲を文字列に変換する
    cnvLastIndex = lngEnd - lngStart + 1
    ReDim lpTemp(cnvLastIndex)
    For i = 0 To cnvLastIndex
        c = lpBuffer(i + lngStart)
        If (blnNullTerm) And (c = 0) And (i > 0) Then
            ReDim Preserve lpTemp(i - 1)
            Exit For
        End If
        lpTemp(i) = c
    Next i
    strText = System.Text.Encoding.GetEncoding("utf8").GetString(lpTemp)

    '変換結果を返す
    ByteToString = strText
End Function

Public Function StringToByte(ByVal strText As String, _
    ByRef lpBuf() As Byte, ByVal lngStart As Long, ByVal lngEnd As Long, _
    Optional ByVal blnAllocBuffer As Boolean = False) As Long
'---------------------------------------------------------------------
'文字列をバイト列に変換する
'[ IN] strText       : 文字列
'[OUT] lpBuf()       : 変換結果を格納するバッファ
'[ IN] lngStart      : 格納を開始する位置(配列のインデックス)
'[ IN] lngEnd        : 格納を終了する位置(配列のインデックス)
'[ IN] blnAllocBuffer: Trueならバッファの確保を関数内で行う
'[RET] Long          : 変換後のサイズをバイト単位で返す
'[ACT]
'  余ったバイトは、0で埋められる。
'---------------------------------------------------------------------
Dim i As Long
Dim lpTemp() As Byte
Dim lngTempStart As Long
Dim lngSize As Long

    lpTemp = System.Text.Encoding.GetEncoding("utf8").GetBytes(strText)
    lngTempStart = LBound(lpTemp)
    lngSize = UBound(lpTemp) - lngTempStart + 1

    If blnAllocBuffer Then
        ReDim Preserve lpBuf(lngEnd)
    End If

    If (lngEnd - lngStart + 1) < lngSize Then
        lngSize = lngEnd - lngStart + 1
    End If

    For i = lngStart To lngEnd
        lpBuf(i) = 0
    Next i

    For i = 0 To lngSize - 1
        lpBuf(lngStart + i) = lpTemp(lngTempStart + i)
    Next i

    StringToByte = lngSize

End Function

End Module
