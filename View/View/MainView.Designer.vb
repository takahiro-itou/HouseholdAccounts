<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class MainView
    Inherits System.Windows.Forms.Form

    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    Private components As System.ComponentModel.IContainer

    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(MainView))

        Me.mnuMain = New System.Windows.Forms.MenuStrip()
        Me.mnuFile = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileNew = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileOpen = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileSep1 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuFileSave = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileSaveAs = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileSep2 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuFileExit = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuEdit = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuEditMove = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuView = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuViewToolBar = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuViewStatusBar = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuOptions = New System.Windows.Forms.ToolStripMenuItem()

        Me.dlgFont = New System.Windows.Forms.FontDialog()
        Me.dlgOpen = New System.Windows.Forms.OpenFileDialog()
        Me.dlgSave = New System.Windows.Forms.SaveFileDialog()
        Me.tlbMain = New System.Windows.Forms.ToolStrip()
        Me.stbMain = New System.Windows.Forms.StatusStrip()

        Me.pnlView = New System.Windows.Forms.Panel()
        Me.splContainer = New System.Windows.Forms.SplitContainer()
        Me.dgvTotal = New System.Windows.Forms.DataGridView()
        Me.dgvBalance = New System.Windows.Forms.DataGridView()
        Me.picBook = New System.Windows.Forms.PictureBox()

        Me.mnuMain.SuspendLayout()
        Me.pnlView.SuspendLayout()
        CType(Me.splContainer, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.splContainer.Panel1.SuspendLayout()
        Me.splContainer.Panel2.SuspendLayout()
        Me.splContainer.SuspendLayout()
        CType(Me.dgvTotal, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.dgvBalance, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.picBook, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()

        '
        'mnuMain
        '
        resources.ApplyResources(Me.mnuMain, "mnuMain")
        Me.mnuMain.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuFile, Me.mnuEdit, Me.mnuView, Me.mnuOptions})
        Me.mnuMain.Name = "mnuMain"
        '
        'mnuFile
        '
        resources.ApplyResources(Me.mnuFile, "mnuFile")
        Me.mnuFile.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuFileNew, Me.mnuFileOpen, Me.mnuFileSep1, Me.mnuFileSave, Me.mnuFileSaveAs, Me.mnuFileSep2, Me.mnuFileExit})
        Me.mnuFile.Name = "mnuFile"
        '
        'mnuFileNew
        '
        resources.ApplyResources(Me.mnuFileNew, "mnuFileNew")
        Me.mnuFileNew.Name = "mnuFileNew"
        '
        'mnuFileOpen
        '
        resources.ApplyResources(Me.mnuFileOpen, "mnuFileOpen")
        Me.mnuFileOpen.Name = "mnuFileOpen"
        '
        'mnuFileSep1
        '
        resources.ApplyResources(Me.mnuFileSep1, "mnuFileSep1")
        Me.mnuFileSep1.Name = "mnuFileSep1"
        '
        'mnuFileSave
        '
        resources.ApplyResources(Me.mnuFileSave, "mnuFileSave")
        Me.mnuFileSave.Name = "mnuFileSave"
        '
        'mnuFileSaveAs
        '
        resources.ApplyResources(Me.mnuFileSaveAs, "mnuFileSaveAs")
        Me.mnuFileSaveAs.Name = "mnuFileSaveAs"
        '
        'mnuFileSep2
        '
        resources.ApplyResources(Me.mnuFileSep2, "mnuFileSep2")
        Me.mnuFileSep2.Name = "mnuFileSep2"
        '
        'mnuFileExit
        '
        resources.ApplyResources(Me.mnuFileExit, "mnuFileExit")
        Me.mnuFileExit.Name = "mnuFileExit"
        '
        'mnuEdit
        '
        resources.ApplyResources(Me.mnuEdit, "mnuEdit")
        Me.mnuEdit.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuEditMove})
        Me.mnuEdit.Name = "mnuEdit"
        '
        'mnuEditMove
        '
        resources.ApplyResources(Me.mnuEditMove, "mnuEditMove")
        Me.mnuEditMove.Name = "mnuEditMove"
        '
        'mnuView
        '
        resources.ApplyResources(Me.mnuView, "mnuView")
        Me.mnuView.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuViewToolBar, Me.mnuViewStatusBar})
        Me.mnuView.Name = "mnuView"
        '
        'mnuViewToolBar
        '
        resources.ApplyResources(Me.mnuViewToolBar, "mnuViewToolBar")
        Me.mnuViewToolBar.Name = "mnuViewToolBar"
        '
        'mnuViewStatusBar
        '
        resources.ApplyResources(Me.mnuViewStatusBar, "mnuViewStatusBar")
        Me.mnuViewStatusBar.Name = "mnuViewStatusBar"
        '
        'mnuOptions
        '
        resources.ApplyResources(Me.mnuOptions, "mnuOptions")
        Me.mnuOptions.Name = "mnuOptions"

        '
        'dlgOpen
        '
        Me.dlgOpen.FileName = "OpenFileDialog1"
        resources.ApplyResources(Me.dlgOpen, "dlgOpen")
        '
        'dlgSave
        '
        resources.ApplyResources(Me.dlgSave, "dlgSave")

        '
        'tlbMain
        '
        resources.ApplyResources(Me.tlbMain, "tlbMain")
        Me.tlbMain.ImageScalingSize = New System.Drawing.Size(32, 32)
        Me.tlbMain.Name = "tlbMain"
        '
        'stbMain
        '
        resources.ApplyResources(Me.stbMain, "stbMain")
        Me.stbMain.Name = "stbMain"

        '
        'pnlView
        '
        resources.ApplyResources(Me.pnlView, "pnlView")
        Me.pnlView.Controls.Add(Me.splContainer)
        Me.pnlView.Name = "pnlView"
        Me.pnlView.Visible = False

        '
        'splContainer
        '
        resources.ApplyResources(Me.splContainer, "splContainer")
        Me.splContainer.Name = "splContainer"
        '
        'splContainer.Panel1
        '
        resources.ApplyResources(Me.splContainer.Panel1, "splContainer.Panel1")
        Me.splContainer.Panel1.Controls.Add(Me.dgvTotal)
        '
        'splContainer.Panel2
        '
        resources.ApplyResources(Me.splContainer.Panel2, "splContainer.Panel2")
        Me.splContainer.Panel2.Controls.Add(Me.dgvBalance)

        '
        'dgvTotal
        '
        resources.ApplyResources(Me.dgvTotal, "dgvTotal")
        Me.dgvTotal.AllowUserToAddRows = False
        Me.dgvTotal.AllowUserToDeleteRows = False
        Me.dgvTotal.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.DisableResizing
        Me.dgvTotal.EditMode = System.Windows.Forms.DataGridViewEditMode.EditOnEnter
        Me.dgvTotal.MultiSelect = False
        Me.dgvTotal.Name = "dgvTotal"
        Me.dgvTotal.ReadOnly = True
        Me.dgvTotal.RowHeadersVisible = False
        Me.dgvTotal.RowTemplate.Height = 25
        Me.dgvTotal.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect

        '
        'dgvBalance
        '
        resources.ApplyResources(Me.dgvBalance, "dgvBalance")
        Me.dgvBalance.AllowUserToAddRows = False
        Me.dgvBalance.AllowUserToResizeRows = False
        Me.dgvBalance.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.DisableResizing
        Me.dgvBalance.MultiSelect = False
        Me.dgvBalance.Name = "dgvBalance"
        Me.dgvBalance.ReadOnly = True
        Me.dgvBalance.RowHeadersVisible = False
        Me.dgvBalance.RowTemplate.Height = 25
        Me.dgvBalance.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect

        '
        'picBook
        '
        resources.ApplyResources(Me.picBook, "picBook")
        Me.picBook.Name = "picBook"
        Me.picBook.BackColor = System.Drawing.SystemColors.Window
        Me.picBook.TabStop = False

        '
        'MainView
        '
        resources.ApplyResources(Me, "$this")
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None
        ' Me.Controls.Add(Me.pnlView)
        Me.Controls.Add(Me.picBook)
        Me.Controls.Add(Me.stbMain)
        Me.Controls.Add(Me.tlbMain)
        Me.Controls.Add(Me.mnuMain)
        Me.MainMenuStrip = Me.mnuMain
        Me.Name = "MainView"

        Me.mnuMain.ResumeLayout(False)
        Me.mnuMain.PerformLayout()
        Me.pnlView.ResumeLayout(False)
        Me.splContainer.Panel1.ResumeLayout(False)
        Me.splContainer.Panel2.ResumeLayout(False)
        CType(Me.splContainer, System.ComponentModel.ISupportInitialize).EndInit()
        Me.splContainer.ResumeLayout(False)
        CType(Me.dgvTotal, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.dgvBalance, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.picBook, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents dgvTotal As DataGridView
    Friend WithEvents dgvBalance As DataGridView
    Friend WithEvents dlgFont As FontDialog
    Friend WithEvents dlgOpen As OpenFileDialog
    Friend WithEvents dlgSave As SaveFileDialog

    Friend WithEvents picBook As PictureBox
    Friend WithEvents pnlView As Panel
    Friend WithEvents splContainer As SplitContainer
    Friend WithEvents stbMain As StatusStrip
    Friend WithEvents tlbMain As ToolStrip

    Friend WithEvents mnuMain As MenuStrip
    Friend WithEvents mnuFile As ToolStripMenuItem
    Friend WithEvents mnuFileNew As ToolStripMenuItem
    Friend WithEvents mnuFileOpen As ToolStripMenuItem
    Friend WithEvents mnuFileSep1 As ToolStripSeparator
    Friend WithEvents mnuFileSave As ToolStripMenuItem
    Friend WithEvents mnuFileSaveAs As ToolStripMenuItem
    Friend WithEvents mnuFileSep2 As ToolStripSeparator
    Friend WithEvents mnuFileExit As ToolStripMenuItem
    Friend WithEvents mnuEdit As ToolStripMenuItem
    Friend WithEvents mnuEditMove As ToolStripMenuItem
    Friend WithEvents mnuView As ToolStripMenuItem
    Friend WithEvents mnuViewToolBar As ToolStripMenuItem
    Friend WithEvents mnuViewStatusBar As ToolStripMenuItem
    Friend WithEvents mnuOptions As ToolStripMenuItem

End Class
