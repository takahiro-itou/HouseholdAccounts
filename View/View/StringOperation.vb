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

Public Function DeleteExtFromPath(ByVal strPath As String) As String
'---------------------------------------------------------------------
'フルパスから、拡張子のみを除いた部分を取得する
'[ IN] strPath: フルパス
'[RET] String : 拡張子を除いた部分
'[ACT]
'  フルパスから、拡張子のみを取り除く。
'  返される結果には、ディレクトリ名が含まれる。
'---------------------------------------------------------------------
Dim i As Integer

    i = Len(strPath)
    For i = Len(strPath) To 1 Step -1
        If Mid$(strPath, i, 1) = "." Then
            'この "." の前までを取り出す
            DeleteExtFromPath = Left$(strPath, i - 1)
            Exit Function
        End If
    Next i

    '"." が見つからないので、このフルパスには拡張子がない
    DeleteExtFromPath = strPath
End Function

Public Function DeleteDirFromPath(ByVal strPath As String) As String
'---------------------------------------------------------------------
'フルパスから、ディレクトリ名を除いた部分を取得する
'[ IN] strPath: フルパス
'[RET] String : ディレクトリ名を除いた部分
'[ACT]
'  フルパスから、ディレクトリ名を取り除く。
'  返される結果には、拡張子も含むが、
'ディレクトリの区切りを示す "\" は含まない。
'---------------------------------------------------------------------
Dim i As Integer

    i = Len(strPath)
    For i = Len(strPath) To 1 Step -1
        If Mid$(strPath, i, 1) = "\" Then
            'この ".\" の後ろを取り出す
            DeleteDirFromPath = Mid$(strPath, i + 1)
            Exit Function
        End If
    Next i

    '"\" が見つからないので、このフルパスはディレクトリ名を含んでいない
    DeleteDirFromPath = strPath
End Function

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

Public Function ReplaceConstant(ByVal strText As String, _
    ByRef strConstName() As String, ByRef strConstValue() As String) As String
'---------------------------------------------------------------------
'文字列中の定数名に値を代入して返す
'[ IN] strText      : 文字列
'[ IN] strConstName : 定数名のリスト
'[ IN] strConstValue: 定数に代入する値のリスト
'[RET] String       : 代入結果
'[ACT]
'  strText 中に、strConstNameと一致する部分が現れるごとに
'strConstValue の対応する値で書き換える。
'---------------------------------------------------------------------
Dim i As Integer
Dim lngPos As Integer
Dim strTemp As String
Dim strName As String
Dim strValue As String

    strTemp = strText
    For i = LBound(strConstName) To UBound(strConstName)
        '定数名と値
        strName = strConstName(i)

        If i > UBound(strConstValue) Then
            strValue = ""
        ElseIf IsNumeric(strConstValue(i)) Then
            strValue = Trim$(Str$(strConstValue(i)))
        Else
            strValue = strConstValue(i)
        End If

        'すべて置換する
        Do While True
            lngPos = InStr(strTemp, strName)
            If (lngPos = 0) Or (Len(strTemp) = 0) Then Exit Do
            If (lngPos = 1) Then
                strTemp = strValue & Mid$(strTemp, 1 + Len(strName))
            Else
                strTemp = Left$(strTemp, lngPos - 1) & strValue & Mid$(strTemp, lngPos + Len(strName))
            End If
        Loop
    Next i

    '置換した文字列を返す
    ReplaceConstant = strTemp
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
