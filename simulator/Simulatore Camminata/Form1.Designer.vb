<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.picFianco = New System.Windows.Forms.PictureBox()
        Me.picSopra = New System.Windows.Forms.PictureBox()
        Me.tmrCamminata = New System.Windows.Forms.Timer(Me.components)
        Me.trkVelAlzo = New System.Windows.Forms.TrackBar()
        Me.trkPasso = New System.Windows.Forms.TrackBar()
        Me.lblVelocita = New System.Windows.Forms.Label()
        Me.lblPasso = New System.Windows.Forms.Label()
        Me.trkSpinta = New System.Windows.Forms.TrackBar()
        Me.lblSpinta = New System.Windows.Forms.Label()
        Me.btnstart = New System.Windows.Forms.Button()
        Me.trkLunghezza = New System.Windows.Forms.TrackBar()
        Me.trkLarghezza = New System.Windows.Forms.TrackBar()
        Me.lblLunghezza = New System.Windows.Forms.Label()
        Me.lblLarghezza = New System.Windows.Forms.Label()
        Me.btnReset = New System.Windows.Forms.Button()
        Me.trkFermore = New System.Windows.Forms.TrackBar()
        Me.lblRapporto = New System.Windows.Forms.Label()
        Me.btnFianco = New System.Windows.Forms.Button()
        Me.btnSopra = New System.Windows.Forms.Button()
        Me.btnBaricentro = New System.Windows.Forms.Button()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.trkTimer = New System.Windows.Forms.TrackBar()
        Me.lblTimer = New System.Windows.Forms.Label()
        Me.trkRitardoAlzo = New System.Windows.Forms.TrackBar()
        Me.lblRitardoAlzo = New System.Windows.Forms.Label()
        Me.lblGamba = New System.Windows.Forms.Label()
        Me.lblDiscriminante = New System.Windows.Forms.Label()
        Me.txtGamba = New System.Windows.Forms.TextBox()
        Me.txtDiscriminante = New System.Windows.Forms.TextBox()
        Me.btnBaricentro1 = New System.Windows.Forms.Button()
        Me.chkForma = New System.Windows.Forms.CheckBox()
        Me.trkCurva = New System.Windows.Forms.TrackBar()
        Me.lblCurva = New System.Windows.Forms.Label()
        Me.trktibia = New System.Windows.Forms.TrackBar()
        Me.lblTibia = New System.Windows.Forms.Label()
        Me.lblCoppia = New System.Windows.Forms.Label()
        Me.txtCoppia = New System.Windows.Forms.TextBox()
        Me.lblPeso = New System.Windows.Forms.Label()
        Me.txtPeso = New System.Windows.Forms.TextBox()
        Me.lblCom = New System.Windows.Forms.Label()
        Me.txtCom = New System.Windows.Forms.TextBox()
        CType(Me.picFianco, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.picSopra, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trkVelAlzo, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trkPasso, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trkSpinta, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trkLunghezza, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trkLarghezza, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trkFermore, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trkTimer, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trkRitardoAlzo, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trkCurva, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trktibia, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'picFianco
        '
        Me.picFianco.BackColor = System.Drawing.SystemColors.ControlLight
        Me.picFianco.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.picFianco.Location = New System.Drawing.Point(28, 22)
        Me.picFianco.Name = "picFianco"
        Me.picFianco.Size = New System.Drawing.Size(305, 130)
        Me.picFianco.TabIndex = 0
        Me.picFianco.TabStop = False
        '
        'picSopra
        '
        Me.picSopra.BackColor = System.Drawing.SystemColors.ControlLight
        Me.picSopra.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.picSopra.Location = New System.Drawing.Point(28, 198)
        Me.picSopra.Name = "picSopra"
        Me.picSopra.Size = New System.Drawing.Size(305, 113)
        Me.picSopra.TabIndex = 1
        Me.picSopra.TabStop = False
        '
        'tmrCamminata
        '
        '
        'trkVelAlzo
        '
        Me.trkVelAlzo.BackColor = System.Drawing.SystemColors.InactiveBorder
        Me.trkVelAlzo.Location = New System.Drawing.Point(648, 75)
        Me.trkVelAlzo.Maximum = 100
        Me.trkVelAlzo.Name = "trkVelAlzo"
        Me.trkVelAlzo.Size = New System.Drawing.Size(162, 56)
        Me.trkVelAlzo.TabIndex = 2
        Me.trkVelAlzo.Value = 15
        '
        'trkPasso
        '
        Me.trkPasso.BackColor = System.Drawing.SystemColors.InactiveBorder
        Me.trkPasso.Location = New System.Drawing.Point(651, 198)
        Me.trkPasso.Maximum = 50
        Me.trkPasso.Name = "trkPasso"
        Me.trkPasso.Size = New System.Drawing.Size(162, 56)
        Me.trkPasso.TabIndex = 3
        Me.trkPasso.Value = 15
        '
        'lblVelocita
        '
        Me.lblVelocita.AutoSize = True
        Me.lblVelocita.Location = New System.Drawing.Point(816, 75)
        Me.lblVelocita.Name = "lblVelocita"
        Me.lblVelocita.Size = New System.Drawing.Size(91, 17)
        Me.lblVelocita.TabIndex = 4
        Me.lblVelocita.Text = "Velocita' alzo"
        '
        'lblPasso
        '
        Me.lblPasso.AutoSize = True
        Me.lblPasso.Location = New System.Drawing.Point(819, 198)
        Me.lblPasso.Name = "lblPasso"
        Me.lblPasso.Size = New System.Drawing.Size(47, 17)
        Me.lblPasso.TabIndex = 5
        Me.lblPasso.Text = "Passo"
        '
        'trkSpinta
        '
        Me.trkSpinta.BackColor = System.Drawing.SystemColors.InactiveBorder
        Me.trkSpinta.Location = New System.Drawing.Point(651, 137)
        Me.trkSpinta.Maximum = 20
        Me.trkSpinta.Name = "trkSpinta"
        Me.trkSpinta.Size = New System.Drawing.Size(162, 56)
        Me.trkSpinta.TabIndex = 6
        Me.trkSpinta.Value = 5
        '
        'lblSpinta
        '
        Me.lblSpinta.AutoSize = True
        Me.lblSpinta.Location = New System.Drawing.Point(819, 137)
        Me.lblSpinta.Name = "lblSpinta"
        Me.lblSpinta.Size = New System.Drawing.Size(85, 17)
        Me.lblSpinta.TabIndex = 7
        Me.lblSpinta.Text = "Veloc spinta"
        '
        'btnstart
        '
        Me.btnstart.Location = New System.Drawing.Point(648, 22)
        Me.btnstart.Name = "btnstart"
        Me.btnstart.Size = New System.Drawing.Size(71, 34)
        Me.btnstart.TabIndex = 8
        Me.btnstart.Text = "Start"
        Me.btnstart.UseVisualStyleBackColor = True
        '
        'trkLunghezza
        '
        Me.trkLunghezza.BackColor = System.Drawing.SystemColors.InactiveBorder
        Me.trkLunghezza.Location = New System.Drawing.Point(648, 261)
        Me.trkLunghezza.Maximum = 100
        Me.trkLunghezza.Name = "trkLunghezza"
        Me.trkLunghezza.Size = New System.Drawing.Size(162, 56)
        Me.trkLunghezza.TabIndex = 9
        Me.trkLunghezza.Value = 60
        '
        'trkLarghezza
        '
        Me.trkLarghezza.BackColor = System.Drawing.SystemColors.InactiveBorder
        Me.trkLarghezza.Location = New System.Drawing.Point(648, 323)
        Me.trkLarghezza.Maximum = 100
        Me.trkLarghezza.Name = "trkLarghezza"
        Me.trkLarghezza.Size = New System.Drawing.Size(162, 56)
        Me.trkLarghezza.TabIndex = 10
        Me.trkLarghezza.Value = 40
        '
        'lblLunghezza
        '
        Me.lblLunghezza.AutoSize = True
        Me.lblLunghezza.Location = New System.Drawing.Point(816, 261)
        Me.lblLunghezza.Name = "lblLunghezza"
        Me.lblLunghezza.Size = New System.Drawing.Size(78, 17)
        Me.lblLunghezza.TabIndex = 11
        Me.lblLunghezza.Text = "Lunghezza"
        '
        'lblLarghezza
        '
        Me.lblLarghezza.AutoSize = True
        Me.lblLarghezza.Location = New System.Drawing.Point(816, 323)
        Me.lblLarghezza.Name = "lblLarghezza"
        Me.lblLarghezza.Size = New System.Drawing.Size(75, 17)
        Me.lblLarghezza.TabIndex = 12
        Me.lblLarghezza.Text = "Larghezza"
        '
        'btnReset
        '
        Me.btnReset.Location = New System.Drawing.Point(725, 22)
        Me.btnReset.Name = "btnReset"
        Me.btnReset.Size = New System.Drawing.Size(74, 34)
        Me.btnReset.TabIndex = 13
        Me.btnReset.Text = "Reset"
        Me.btnReset.UseVisualStyleBackColor = True
        '
        'trkFermore
        '
        Me.trkFermore.BackColor = System.Drawing.SystemColors.InactiveBorder
        Me.trkFermore.Location = New System.Drawing.Point(648, 385)
        Me.trkFermore.Maximum = 100
        Me.trkFermore.Name = "trkFermore"
        Me.trkFermore.Size = New System.Drawing.Size(162, 56)
        Me.trkFermore.TabIndex = 14
        Me.trkFermore.Value = 38
        '
        'lblRapporto
        '
        Me.lblRapporto.AutoSize = True
        Me.lblRapporto.Location = New System.Drawing.Point(816, 385)
        Me.lblRapporto.Name = "lblRapporto"
        Me.lblRapporto.Size = New System.Drawing.Size(100, 17)
        Me.lblRapporto.TabIndex = 15
        Me.lblRapporto.Text = "Lungh Femore"
        '
        'btnFianco
        '
        Me.btnFianco.Location = New System.Drawing.Point(47, 33)
        Me.btnFianco.Name = "btnFianco"
        Me.btnFianco.Size = New System.Drawing.Size(266, 13)
        Me.btnFianco.TabIndex = 16
        Me.btnFianco.UseVisualStyleBackColor = True
        '
        'btnSopra
        '
        Me.btnSopra.Location = New System.Drawing.Point(37, 224)
        Me.btnSopra.Name = "btnSopra"
        Me.btnSopra.Size = New System.Drawing.Size(266, 31)
        Me.btnSopra.TabIndex = 17
        Me.btnSopra.UseVisualStyleBackColor = True
        '
        'btnBaricentro
        '
        Me.btnBaricentro.Location = New System.Drawing.Point(430, 236)
        Me.btnBaricentro.Name = "btnBaricentro"
        Me.btnBaricentro.Size = New System.Drawing.Size(5, 5)
        Me.btnBaricentro.TabIndex = 18
        Me.btnBaricentro.UseVisualStyleBackColor = True
        '
        'Timer1
        '
        Me.Timer1.Enabled = True
        Me.Timer1.Interval = 50
        '
        'trkTimer
        '
        Me.trkTimer.BackColor = System.Drawing.SystemColors.InactiveBorder
        Me.trkTimer.Location = New System.Drawing.Point(395, 159)
        Me.trkTimer.Maximum = 2000
        Me.trkTimer.Name = "trkTimer"
        Me.trkTimer.Size = New System.Drawing.Size(162, 56)
        Me.trkTimer.TabIndex = 19
        Me.trkTimer.Value = 1000
        '
        'lblTimer
        '
        Me.lblTimer.AutoSize = True
        Me.lblTimer.Location = New System.Drawing.Point(415, 216)
        Me.lblTimer.Name = "lblTimer"
        Me.lblTimer.Size = New System.Drawing.Size(44, 17)
        Me.lblTimer.TabIndex = 20
        Me.lblTimer.Text = "Timer"
        '
        'trkRitardoAlzo
        '
        Me.trkRitardoAlzo.BackColor = System.Drawing.SystemColors.InactiveBorder
        Me.trkRitardoAlzo.Location = New System.Drawing.Point(395, 75)
        Me.trkRitardoAlzo.Name = "trkRitardoAlzo"
        Me.trkRitardoAlzo.Size = New System.Drawing.Size(162, 56)
        Me.trkRitardoAlzo.TabIndex = 21
        '
        'lblRitardoAlzo
        '
        Me.lblRitardoAlzo.AutoSize = True
        Me.lblRitardoAlzo.Location = New System.Drawing.Point(563, 99)
        Me.lblRitardoAlzo.Name = "lblRitardoAlzo"
        Me.lblRitardoAlzo.Size = New System.Drawing.Size(97, 17)
        Me.lblRitardoAlzo.TabIndex = 22
        Me.lblRitardoAlzo.Text = "Ritardo Alzata"
        '
        'lblGamba
        '
        Me.lblGamba.AutoSize = True
        Me.lblGamba.Location = New System.Drawing.Point(816, 29)
        Me.lblGamba.Name = "lblGamba"
        Me.lblGamba.Size = New System.Drawing.Size(58, 17)
        Me.lblGamba.TabIndex = 23
        Me.lblGamba.Text = "Gamba:"
        '
        'lblDiscriminante
        '
        Me.lblDiscriminante.AutoSize = True
        Me.lblDiscriminante.Location = New System.Drawing.Point(884, 29)
        Me.lblDiscriminante.Name = "lblDiscriminante"
        Me.lblDiscriminante.Size = New System.Drawing.Size(58, 17)
        Me.lblDiscriminante.TabIndex = 24
        Me.lblDiscriminante.Text = "Discrim:"
        '
        'txtGamba
        '
        Me.txtGamba.Location = New System.Drawing.Point(465, 261)
        Me.txtGamba.Name = "txtGamba"
        Me.txtGamba.Size = New System.Drawing.Size(21, 22)
        Me.txtGamba.TabIndex = 25
        '
        'txtDiscriminante
        '
        Me.txtDiscriminante.Location = New System.Drawing.Point(395, 261)
        Me.txtDiscriminante.Name = "txtDiscriminante"
        Me.txtDiscriminante.Size = New System.Drawing.Size(51, 22)
        Me.txtDiscriminante.TabIndex = 26
        '
        'btnBaricentro1
        '
        Me.btnBaricentro1.Location = New System.Drawing.Point(465, 236)
        Me.btnBaricentro1.Name = "btnBaricentro1"
        Me.btnBaricentro1.Size = New System.Drawing.Size(5, 5)
        Me.btnBaricentro1.TabIndex = 27
        Me.btnBaricentro1.UseVisualStyleBackColor = True
        '
        'chkForma
        '
        Me.chkForma.AutoSize = True
        Me.chkForma.Location = New System.Drawing.Point(408, 28)
        Me.chkForma.Name = "chkForma"
        Me.chkForma.Size = New System.Drawing.Size(74, 21)
        Me.chkForma.TabIndex = 28
        Me.chkForma.Text = "Forma "
        Me.chkForma.UseVisualStyleBackColor = True
        '
        'trkCurva
        '
        Me.trkCurva.BackColor = System.Drawing.SystemColors.InactiveBorder
        Me.trkCurva.Location = New System.Drawing.Point(395, 302)
        Me.trkCurva.Maximum = 360
        Me.trkCurva.Name = "trkCurva"
        Me.trkCurva.Size = New System.Drawing.Size(162, 56)
        Me.trkCurva.TabIndex = 29
        Me.trkCurva.Value = 180
        '
        'lblCurva
        '
        Me.lblCurva.AutoSize = True
        Me.lblCurva.Location = New System.Drawing.Point(548, 323)
        Me.lblCurva.Name = "lblCurva"
        Me.lblCurva.Size = New System.Drawing.Size(198, 17)
        Me.lblCurva.TabIndex = 30
        Me.lblCurva.Text = "Curvatura                                "
        '
        'trktibia
        '
        Me.trktibia.BackColor = System.Drawing.SystemColors.InactiveBorder
        Me.trktibia.Location = New System.Drawing.Point(395, 364)
        Me.trktibia.Maximum = 100
        Me.trktibia.Name = "trktibia"
        Me.trktibia.Size = New System.Drawing.Size(162, 56)
        Me.trktibia.TabIndex = 31
        Me.trktibia.Value = 40
        '
        'lblTibia
        '
        Me.lblTibia.AutoSize = True
        Me.lblTibia.Location = New System.Drawing.Point(548, 382)
        Me.lblTibia.Name = "lblTibia"
        Me.lblTibia.Size = New System.Drawing.Size(83, 17)
        Me.lblTibia.TabIndex = 32
        Me.lblTibia.Text = "Lungh Tibia"
        '
        'lblCoppia
        '
        Me.lblCoppia.AutoSize = True
        Me.lblCoppia.Location = New System.Drawing.Point(995, 32)
        Me.lblCoppia.Name = "lblCoppia"
        Me.lblCoppia.Size = New System.Drawing.Size(113, 17)
        Me.lblCoppia.TabIndex = 33
        Me.lblCoppia.Text = "Coppia richiesta:"
        '
        'txtCoppia
        '
        Me.txtCoppia.Location = New System.Drawing.Point(506, 261)
        Me.txtCoppia.Name = "txtCoppia"
        Me.txtCoppia.Size = New System.Drawing.Size(36, 22)
        Me.txtCoppia.TabIndex = 34
        '
        'lblPeso
        '
        Me.lblPeso.AutoSize = True
        Me.lblPeso.Location = New System.Drawing.Point(948, 33)
        Me.lblPeso.Name = "lblPeso"
        Me.lblPeso.Size = New System.Drawing.Size(25, 17)
        Me.lblPeso.TabIndex = 35
        Me.lblPeso.Text = "gr:"
        '
        'txtPeso
        '
        Me.txtPeso.Location = New System.Drawing.Point(566, 261)
        Me.txtPeso.Name = "txtPeso"
        Me.txtPeso.Size = New System.Drawing.Size(34, 22)
        Me.txtPeso.TabIndex = 36
        Me.txtPeso.Text = "3000"
        '
        'lblCom
        '
        Me.lblCom.AutoSize = True
        Me.lblCom.Location = New System.Drawing.Point(948, 89)
        Me.lblCom.Name = "lblCom"
        Me.lblCom.Size = New System.Drawing.Size(34, 17)
        Me.lblCom.TabIndex = 37
        Me.lblCom.Text = "com"
        '
        'txtCom
        '
        Me.txtCom.Location = New System.Drawing.Point(610, 256)
        Me.txtCom.Name = "txtCom"
        Me.txtCom.Size = New System.Drawing.Size(21, 22)
        Me.txtCom.TabIndex = 38
        Me.txtCom.Text = "0"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(1157, 421)
        Me.Controls.Add(Me.txtCom)
        Me.Controls.Add(Me.lblCom)
        Me.Controls.Add(Me.txtPeso)
        Me.Controls.Add(Me.lblPeso)
        Me.Controls.Add(Me.txtCoppia)
        Me.Controls.Add(Me.lblCoppia)
        Me.Controls.Add(Me.lblTibia)
        Me.Controls.Add(Me.trktibia)
        Me.Controls.Add(Me.lblCurva)
        Me.Controls.Add(Me.trkCurva)
        Me.Controls.Add(Me.chkForma)
        Me.Controls.Add(Me.btnBaricentro1)
        Me.Controls.Add(Me.txtDiscriminante)
        Me.Controls.Add(Me.txtGamba)
        Me.Controls.Add(Me.lblDiscriminante)
        Me.Controls.Add(Me.lblGamba)
        Me.Controls.Add(Me.lblRitardoAlzo)
        Me.Controls.Add(Me.trkRitardoAlzo)
        Me.Controls.Add(Me.lblTimer)
        Me.Controls.Add(Me.trkTimer)
        Me.Controls.Add(Me.btnBaricentro)
        Me.Controls.Add(Me.btnSopra)
        Me.Controls.Add(Me.btnFianco)
        Me.Controls.Add(Me.lblRapporto)
        Me.Controls.Add(Me.trkFermore)
        Me.Controls.Add(Me.btnReset)
        Me.Controls.Add(Me.lblLarghezza)
        Me.Controls.Add(Me.lblLunghezza)
        Me.Controls.Add(Me.trkLarghezza)
        Me.Controls.Add(Me.trkLunghezza)
        Me.Controls.Add(Me.btnstart)
        Me.Controls.Add(Me.lblSpinta)
        Me.Controls.Add(Me.trkSpinta)
        Me.Controls.Add(Me.lblPasso)
        Me.Controls.Add(Me.lblVelocita)
        Me.Controls.Add(Me.trkPasso)
        Me.Controls.Add(Me.trkVelAlzo)
        Me.Controls.Add(Me.picSopra)
        Me.Controls.Add(Me.picFianco)
        Me.Name = "Form1"
        Me.Text = "Simulatore Camminata "
        CType(Me.picFianco, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.picSopra, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trkVelAlzo, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trkPasso, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trkSpinta, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trkLunghezza, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trkLarghezza, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trkFermore, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trkTimer, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trkRitardoAlzo, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trkCurva, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trktibia, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents picFianco As PictureBox
    Friend WithEvents picSopra As PictureBox
    Friend WithEvents tmrCamminata As Timer
    Friend WithEvents trkVelAlzo As TrackBar
    Friend WithEvents trkPasso As TrackBar
    Friend WithEvents lblVelocita As Label
    Friend WithEvents lblPasso As Label
    Friend WithEvents trkSpinta As TrackBar
    Friend WithEvents lblSpinta As Label
    Friend WithEvents btnstart As Button
    Friend WithEvents trkLunghezza As TrackBar
    Friend WithEvents trkLarghezza As TrackBar
    Friend WithEvents lblLunghezza As Label
    Friend WithEvents lblLarghezza As Label
    Friend WithEvents btnReset As Button
    Friend WithEvents trkFermore As TrackBar
    Friend WithEvents lblRapporto As Label
    Friend WithEvents btnFianco As Button
    Friend WithEvents btnSopra As Button
    Friend WithEvents btnBaricentro As Button
    Friend WithEvents Timer1 As Timer
    Friend WithEvents trkTimer As TrackBar
    Friend WithEvents lblTimer As Label
    Friend WithEvents trkRitardoAlzo As TrackBar
    Friend WithEvents lblRitardoAlzo As Label
    Friend WithEvents lblGamba As Label
    Friend WithEvents lblDiscriminante As Label
    Friend WithEvents txtGamba As TextBox
    Friend WithEvents txtDiscriminante As TextBox
    Friend WithEvents btnBaricentro1 As Button
    Friend WithEvents chkForma As CheckBox
    Friend WithEvents trkCurva As TrackBar
    Friend WithEvents lblCurva As Label
    Friend WithEvents trktibia As TrackBar
    Friend WithEvents lblTibia As Label
    Friend WithEvents lblCoppia As Label
    Friend WithEvents txtCoppia As TextBox
    Friend WithEvents lblPeso As Label
    Friend WithEvents txtPeso As TextBox
    Friend WithEvents lblCom As Label
    Friend WithEvents txtCom As TextBox
End Class
