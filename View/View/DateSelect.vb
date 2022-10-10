''************************************************************************
''                                                                      ''
''                  ---  Household Accounts View.  ---                  ''
''                                                                      ''
''          Copyright (C), 2017-2022, Takahiro Itou                     ''
''          All Rights Reserved.                                        ''
''                                                                      ''
''          License: (See COPYING and LICENSE files)                    ''
''          GNU Affero General Public License (AGPL) version 3,         ''
''          or (at your option) any later version.                      ''
''                                                                      ''
''************************************************************************

Public Class DateSelect

Private m_selectedDate As System.DateTime

''========================================================================
Public Function getSelectedDate() As System.DateTime
''--------------------------------------------------------------------
''    選択した日付を取得する。
''--------------------------------------------------------------------
    getSelectedDate = m_selectedDate
End Function

''========================================================================
Public Sub selectDate(ByVal valDate As System.DateTime)
''--------------------------------------------------------------------
''    指定した日付を選択する。
''--------------------------------------------------------------------
    mncDate.SelectionStart = valDate
End Sub

''========================================================================
Private Sub btnOK_Click(sender As Object, e As EventArgs) _
    Handles btnOK.Click
''--------------------------------------------------------------------
''    「OK」ボタンのクリックイベントハンドラ。
''--------------------------------------------------------------------
    Me.m_selectedDate = mncDate.SelectionStart
End Sub

''========================================================================
Private Sub mncDate_DateChanged(sender As Object, e As DateRangeEventArgs) _
    Handles mncDate.DateChanged
''--------------------------------------------------------------------
''    カレンダーの日付クリックイベントハンドラ。
''--------------------------------------------------------------------
    Me.m_selectedDate = mncDate.SelectionStart
End Sub

End Class
