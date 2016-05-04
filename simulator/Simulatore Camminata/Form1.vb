Imports System.Threading
Imports System.IO.Ports.SerialPort

Public Class Form1

    Dim a, b As Double
    Dim xd1, xd2, yd1, yd2, xd3, yd3, xd4, yd4, xd5, yd5 As Double
    Dim diagn1, diagn2, diagn3, diagn4, diagn5, diagn6 As Double
    Dim FemoreX(3), FemoreY(3), TibiaX(3), TibiaY(3), piedeX(3), piedeY(3), discriminante(3) As Double
    Dim angInizFemore, angInizTibia, angFemore(3), angTibia(3), errX(3), errY(3), AltezzaTerra As Double
    Dim piedeSopraX(3), FemoreSopraX(3), TibiaSopraX(3), FemoreSopraY(3), TibiaSopraY(3), piedeSopraY(3) As Double
    Dim angFinalFemore, angFinalTibia, posxMaxAvanti, posxMaxIndietro, posxMinAvanti, posxMinIndietro, angMaxCurva As Double
    Dim LunghezzaGamba, LunghezzaTibia, LunghezzaFemore, piedeBasso, curvatura, lungBacino, largBacino As Double
    Dim counterSend As Integer = 0



    Dim BarX, BarY, raggioTibia(3), raggioFemore(3), angoloCurva(3), faseCurva(3), angRotaz(3) As Double
    Dim posizione(3) As String

    Dim bprint, bPrint1, bPrima, bAlzo(3), bGiaAlzato(3) As Boolean

    Dim correzione, constX1, constY1, constK, varX As Double
    Dim constA, constB, constC, sporgGinocchio, velocAvanzamento, lunghPasso, pesoSuGamba As Double
    Dim cicliRitardoAlzo, cicliFatti, candidatoAlzo, candidatoAlzoCurva, contaAlzi, contaAlzati As Integer
    Dim bCandidabile, bPiedeAlzato, bPrimoPasso, bCurva As Boolean
    Public TPen As New System.Drawing.Pen(System.Drawing.Color.Black, 1)
    Public Fase(3), spess As Integer, color As Color
    Public lavGraphics As System.Drawing.Graphics

    Public Sub Picline(X1 As Long, Y1 As Long, X2 As Long, Y2 As Long)
        TPen.Width = spess
        TPen.Color = Color.Blue
        lavGraphics.DrawLine(TPen, X1, Y1, X2, Y2)

    End Sub
    Public Sub Picline(X1 As Long, Y1 As Long, X2 As Long, Y2 As Long, Colore As Color)

        TPen.Width = spess
        TPen.Color = Colore
        lavGraphics.DrawLine(TPen, X1, Y1, X2, Y2)

    End Sub
    Public Sub PicEllisse(Xcentro As Double, Ycentro As Double, larghezza As Double, altezza As Double)
        Dim Rect As New Rectangle
        Rect.X = Xcentro - larghezza / 2
        Rect.Y = Ycentro - altezza / 2
        Rect.Width = larghezza
        Rect.Height = altezza
        TPen.Width = spess
        'TPen.Color = Color.Blue
        lavGraphics.DrawEllipse(TPen, Rect)
    End Sub
    Private Sub txtPeso_TextChanged(sender As Object, e As EventArgs) Handles txtPeso.TextChanged
        If LunghezzaGamba > 0 Then ResetRobot()
    End Sub
    Private Sub trktimer_Scroll(sender As Object, e As EventArgs) Handles trkTimer.Scroll
        If trkTimer.Value = 0 Then trkTimer.Value = 1
        lblTimer.Text = "Timer ms/tick " & Str(trkTimer.Value)
    End Sub


    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        ResetRobot()
        Timer1.Enabled = False
    End Sub
    Private Sub chkForma_CheckedChanged(sender As Object, e As EventArgs) Handles chkForma.CheckedChanged

        If bPrima = True Then ResetRobot()
        bprima = True
    End Sub
    Private Sub trkLunghezza_Scroll(sender As Object, e As EventArgs) Handles trkLunghezza.Scroll

        btnSopra.Left = btnFianco.Left
        picFianco.Refresh()
        lblLunghezza.Text = "Lung bacino cm " & Str(trkLunghezza.Value)
        ResetRobot()
    End Sub

    Private Sub trkLarghezza_Scroll(sender As Object, e As EventArgs) Handles trkLarghezza.Scroll

        picSopra.Refresh()
        lblLarghezza.Text = "Larg bacino cm " & Str(trkLarghezza.Value)
        ResetRobot()
    End Sub
    Private Sub trkPasso_Scroll(sender As Object, e As EventArgs) Handles trkPasso.Scroll
        lblPasso.Text = "Sporg. ginocchio cm " & Str(trkPasso.Value)

        ResetRobot()
    End Sub
    Private Sub trkVelalzo_Scroll(sender As Object, e As EventArgs) Handles trkVelAlzo.Scroll
        lblVelocita.Text = "Incr.passo cm/tick " & Str(trkVelAlzo.Value)
        ResetRobot()
    End Sub
    Private Sub trkSpinta_Scroll(sender As Object, e As EventArgs) Handles trkSpinta.Scroll
        lblSpinta.Text = "Velocità cm/tick " & Str(trkSpinta.Value)
        ResetRobot()
    End Sub
    Private Sub trkRapporto_Scroll(sender As Object, e As EventArgs) Handles trkFermore.Scroll
        lblRapporto.Text = "Lungh Femore cm " & Str(trkFermore.Value)
        ResetRobot()
    End Sub
    Private Sub trktibia_Scroll(sender As Object, e As EventArgs) Handles trktibia.Scroll
        lblTibia.Text = "Lungh Tibia cm " & Str(trktibia.Value)
        ResetRobot()
    End Sub
    Private Sub trkRitardoAlzo_Scroll(sender As Object, e As EventArgs) Handles trkRitardoAlzo.Scroll
        lblRitardoAlzo.Text = "Ritardo Alzata " & Str(trkRitardoAlzo.Value)
        ResetRobot()
    End Sub
    Private Sub trkCurva_Scroll(sender As Object, e As EventArgs) Handles trkCurva.Scroll
        curvatura = trkCurva.Value - 180
        lblCurva.Text = "Curva gradi " & Str(curvatura)
        curvatura = curvatura * Math.PI / 180
        PreparaCurva()
    End Sub
    Private Sub lblCurva_doubleclick(sender As Object, e As EventArgs) Handles lblCurva.DoubleClick
        trkCurva.Value = 180
        curvatura = trkCurva.Value - 180
        lblCurva.Text = "Curva gradi " & Str(curvatura)
        curvatura = curvatura * Math.PI / 180
    End Sub
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

        WindowState = FormWindowState.Maximized
        btnSopra.Visible = False
        Left = 0
        Top = 0
        picFianco.Left = 20
        picFianco.Top = 20
        picFianco.Height = Me.Height / 2 - 50
        picFianco.Width = Width / 2
        picSopra.Left = picFianco.Left
        picSopra.Top = picFianco.Top + picFianco.Height + 20
        picSopra.Width = picFianco.Width
        picSopra.Height = picFianco.Height
        btnBaricentro1.Top = picSopra.Top + picSopra.Height / 2
        btnBaricentro1.Left = picSopra.Left + picSopra.Width / 2 + 10
        btnBaricentro1.BackColor = Color.Black
        btnBaricentro.Top = picSopra.Top + picSopra.Height / 2
        btnBaricentro.Left = picSopra.Left + picSopra.Width / 2
        btnBaricentro.BackColor = Color.Black
        btnBaricentro.Focus()
        btnstart.Left = picFianco.Left + picFianco.Width + 30
        btnstart.Top = picFianco.Top
        btnReset.Left = btnstart.Left + btnstart.Width + 20
        btnReset.Top = btnstart.Top
        lblGamba.Top = btnstart.Top + 10
        lblGamba.Left = btnReset.Left + btnReset.Width + 5
        txtGamba.Top = lblGamba.Top
        txtGamba.Left = lblGamba.Left + lblGamba.Width
        lblDiscriminante.Top = lblGamba.Top
        lblDiscriminante.Left = lblGamba.Left + lblGamba.Width + 20
        txtDiscriminante.Top = lblDiscriminante.Top
        txtDiscriminante.Left = lblDiscriminante.Left + lblDiscriminante.Width
        lblCom.Top = txtDiscriminante.Top
        lblCom.Left = lblDiscriminante.Left + lblDiscriminante.Width + 50
        txtCom.Top = lblCom.Top
        txtCom.Left = lblCom.Left + lblCom.Width

        chkForma.Top = lblDiscriminante.Top
        chkForma.Left = txtCom.Left + txtCom.Width + 30
        trkVelAlzo.Left = btnstart.Left
        trkPasso.Left = trkVelAlzo.Left
        trkSpinta.Left = trkVelAlzo.Left
        trkLunghezza.Left = trkVelAlzo.Left
        trkLarghezza.Left = trkVelAlzo.Left
        trkFermore.Left = trkVelAlzo.Left
        trktibia.Left = trkVelAlzo.Left
        trktibia.Top = trkFermore.Top + trkFermore.Height + 10
        trkRitardoAlzo.Left = trkVelAlzo.Left
        trkRitardoAlzo.Top = trktibia.Top + trktibia.Height + 10
        lblRitardoAlzo.Top = trkRitardoAlzo.Top
        lblRitardoAlzo.Left = trkRitardoAlzo.Left + trkRitardoAlzo.Width + 5
        trkTimer.Left = trkVelAlzo.Left
        trkTimer.Top = trkRitardoAlzo.Top + trkRitardoAlzo.Height + 10
        trkCurva.Left = trkTimer.Left
        trkCurva.Top = trkTimer.Top + trkTimer.Height + 10
        lblCurva.Top = trkCurva.Top
        lblCurva.Left = trkCurva.Left + trkCurva.Width + 5
        curvatura = trkCurva.Value - 180
        lblCurva.Text = "Curva gradi " & Str(curvatura)
        lblVelocita.Left = trkVelAlzo.Left + trkVelAlzo.Width + 10
        lblTimer.Top = trkTimer.Top
        lblTimer.Left = trkTimer.Left + trkTimer.Width + 5
        lblPasso.Left = lblVelocita.Left
        lblSpinta.Left = lblVelocita.Left
        lblLunghezza.Left = lblVelocita.Left
        lblLarghezza.Left = lblVelocita.Left
        lblRapporto.Left = lblVelocita.Left
        lblTibia.Left = lblVelocita.Left
        lblTibia.Top = trktibia.Top
        lblCoppia.Top = trkSpinta.Top
        lblCoppia.Left = lblSpinta.Left + lblSpinta.Width + 50
        txtCoppia.Top = lblCoppia.Top
        txtCoppia.Left = lblCoppia.Left + lblCoppia.Width
        lblPeso.Top = lblCoppia.Top
        lblPeso.Left = lblCoppia.Left + lblCoppia.Width + 40
        txtPeso.Top = lblPeso.Top
        txtPeso.Left = lblPeso.Left + lblPeso.Width

        btnFianco.Top = picFianco.Top + 20
        btnFianco.Height = 20

        btnSopra.Left = btnFianco.Left

        LunghezzaGamba = picFianco.Height - (btnFianco.Top + btnFianco.Height - picFianco.Top)
        lblLarghezza.Text = "Larg bacino cm" & Str(trkLarghezza.Value)
        lblLunghezza.Text = "Lung bacino cm " & Str(trkLunghezza.Value)
        lblPasso.Text = "Sporg. ginocchio cm " & Str(trkPasso.Value)
        lblVelocita.Text = "Incr.passo cm/tick" & Str(trkVelAlzo.Value)
        lblSpinta.Text = "Velocità cm/tick " & Str(trkSpinta.Value)
        lblRapporto.Text = "Lungh Femore cm " & Str(trkFermore.Value)
        lblTibia.Text = "Lungh Tibia cm " & Str(trktibia.Value)
        lblRitardoAlzo.Text = "Ritardo Alzata " & Str(trkRitardoAlzo.Value)
        lblTimer.Text = "Timer ms/tick " & Str(trkTimer.Value)
        posizione(0) = "avanti"
        posizione(1) = "avanti"
        posizione(2) = "dietro"
        posizione(3) = "dietro"
    End Sub
    Private Sub btnstart_Click(sender As Object, e As EventArgs) Handles btnstart.Click
        If btnstart.Text = "Start" Then

            btnstart.Text = "Stop"
            StartAnimazione()
        Else
            btnstart.Text = "Start"
            StopAnimazione()
        End If

    End Sub
    Private Sub btnReset_Click(sender As Object, e As EventArgs) Handles btnReset.Click
        ResetRobot()
    End Sub
    Sub ResetRobot()
        Dim i As Int16
        picFianco.Refresh()
        picSopra.Refresh()
        For i = 0 To 3
            ResetGamba(i)
            DisegnaGamba(i)
        Next
    End Sub
    Function PiuIndietro(r As Short, s As Short, t As Short) As Short
        Dim p(3) As Double
        p(0) = piedeX(0) - FemoreX(0)
        p(1) = piedeX(1) - FemoreX(1)
        p(2) = piedeX(2) - FemoreX(2)
        p(3) = piedeX(3) - FemoreX(3)
        If p(r) <= p(s) And p(r) <= p(t) Then
            PiuIndietro = r
        ElseIf p(t) <= p(r) And p(t) <= p(s) Then
            PiuIndietro = t
        ElseIf p(s) <= p(r) And p(s) <= p(t) Then
            PiuIndietro = s
        End If
        Return PiuIndietro
    End Function
    Function EntroBaricentro(g As Short) As Double
        Dim fuoriBaricentro As Double
        EntroBaricentro = 0
        BarX = picSopra.Left + picSopra.Width / 2

        If posizione(g) = "avanti" Then
            BarX = BarX - 60
        Else
            BarX = BarX + 60
        End If
        btnBaricentro.Left = BarX
        If g = 0 Then
            fuoriBaricentro = BarX - (TibiaX(1) - TibiaX(3)) / 2
            If fuoriBaricentro > 0 Then
                EntroBaricentro = fuoriBaricentro
            End If
        ElseIf g = 1 Then
            fuoriBaricentro = BarX - (TibiaX(0) - TibiaX(2)) / 2
            If fuoriBaricentro > 0 Then
                EntroBaricentro = fuoriBaricentro
            End If
        ElseIf g = 2 Then
            fuoriBaricentro = BarX - (TibiaX(1) - TibiaX(3)) / 2
            If fuoriBaricentro < 0 Then
                EntroBaricentro = fuoriBaricentro
            End If
        ElseIf g = 3 Then
            fuoriBaricentro = BarX - (TibiaX(0) - TibiaX(2)) / 2
            If fuoriBaricentro < 0 Then
                EntroBaricentro = fuoriBaricentro
            End If
        End If

    End Function
    Sub ResetGamba(g As Short)
        Dim spostamentoPasso As Double

        btnSopra.Visible = False
        LunghezzaTibia = LunghezzaGamba * trktibia.Value / (trktibia.Value + trkFermore.Value)
        LunghezzaFemore = LunghezzaGamba * trkFermore.Value / (trktibia.Value + trkFermore.Value)
        sporgGinocchio = LunghezzaGamba * trkPasso.Value / (trktibia.Value + trkFermore.Value)
        pesoSuGamba = Val(txtPeso.Text) / 3000
        txtCoppia.Text = " " & Str((pesoSuGamba * trkPasso.Value))
        velocAvanzamento = LunghezzaGamba * trkSpinta.Value / (trktibia.Value + trkFermore.Value)
        lunghPasso = LunghezzaGamba * trkVelAlzo.Value / (trktibia.Value + trkFermore.Value)
        lungBacino = LunghezzaGamba * trkLunghezza.Value / (trktibia.Value + trkFermore.Value)
        largBacino = LunghezzaGamba * trkLarghezza.Value / (trktibia.Value + trkFermore.Value)
        btnFianco.Width = lungBacino
        btnFianco.Left = picFianco.Left + (picFianco.Width - lungBacino) / 2
        btnSopra.Left = btnFianco.Left
        btnSopra.Width = lungBacino
        btnSopra.Height = largBacino
        btnSopra.Top = picSopra.Top + (picSopra.Height - btnSopra.Height) / 2
        angInizFemore = +Math.Asin(sporgGinocchio / LunghezzaFemore)
        angInizTibia = -Math.Asin(sporgGinocchio / LunghezzaTibia)

        btnFianco.Top = picFianco.Top + 20 + LunghezzaFemore * (1 - Math.Cos(angInizFemore)) + LunghezzaTibia * (1 - Math.Cos(angInizTibia))
        FemoreY(g) = btnFianco.Top + btnFianco.Height - 20
        TibiaY(g) = FemoreY(g) + LunghezzaFemore * Math.Cos(angInizFemore)
        piedeY(g) = TibiaY(g) + LunghezzaTibia * Math.Cos(-angInizTibia) - 4
        If posizione(g) = "avanti" Then
            FemoreX(g) = btnFianco.Left + lungBacino - picFianco.Left - 10
            TibiaX(g) = FemoreX(g) + sporgGinocchio
            piedeX(g) = FemoreX(g)
            piedeBasso = piedeX(g) - lungBacino
        Else
            FemoreX(g) = btnFianco.Left - picFianco.Left + 10
            If chkForma.Checked = True Then
                TibiaX(g) = FemoreX(g) + sporgGinocchio
            Else
                TibiaX(g) = FemoreX(g) - sporgGinocchio
            End If
            piedeX(g) = FemoreX(g)
            piedeBasso = piedeX(g)
        End If
        'LunghezzaFemore = Math.Sqrt((TibiaX(g) - FemoreX(g)) ^ 2 + (TibiaY(g) - FemoreY(g)) ^ 2)
        ' LunghezzaTibia = Math.Sqrt((piedeX(g) - TibiaX(g)) ^ 2 + (piedeY(g) - TibiaY(g)) ^ 2)
        AltezzaTerra = LunghezzaTibia * Math.Cos(angInizTibia) + LunghezzaFemore * Math.Cos(angInizFemore)
        spostamentoPasso = sporgGinocchio * 0.8
        posxMaxAvanti = btnFianco.Left + lungBacino + spostamentoPasso
        posxMaxIndietro = btnFianco.Left + spostamentoPasso
        posxMinAvanti = btnFianco.Left + lungBacino - spostamentoPasso
        posxMinIndietro = btnFianco.Left - spostamentoPasso

        If g = 0 Or g = 3 Then
            piedeSopraY(g) = btnSopra.Top - picSopra.Top
            FemoreSopraY(g) = btnSopra.Top - picSopra.Top
            TibiaSopraY(g) = btnSopra.Top - picSopra.Top
        Else
            piedeSopraY(g) = btnSopra.Top - picSopra.Top + largBacino
            FemoreSopraY(g) = btnSopra.Top - picSopra.Top + largBacino
            TibiaSopraY(g) = btnSopra.Top - picSopra.Top + largBacino
        End If


        Fase(0) = 2
        Fase(1) = 2
        Fase(2) = 2
        Fase(3) = 1
        btnBaricentro.Left = picSopra.Left + picSopra.Width / 2 - 30
        angFemore(g) = angInizFemore
        angTibia(g) = angInizTibia
        errX(g) = 0
        errY(g) = 0
        color = Color.Coral
        cicliRitardoAlzo = trkRitardoAlzo.Value
    End Sub



    Sub PreparaCurva()

        ResetRobot()
        angMaxCurva = Math.Atan((largBacino / 2 + sporgGinocchio) / (lungBacino / 2)) - Math.Atan((largBacino / 2) / (lungBacino / 2))
        diagn1 = Int(10000 * (Math.Tan(angMaxCurva + Math.Atan((largBacino / 2) / (lungBacino / 2))) * (lungBacino / 2) - largBacino / 2) / sporgGinocchio) / 10000

        If curvatura <> 0 Then
            bCurva = True

            For i = 0 To 3
                TrovaPosizioni(i, AltezzaTerra, 0)

                angoloCurva(i) = curvatura
                faseCurva(i) = 1
                Fase(i) = 0
            Next
        End If
        candidatoAlzoCurva = 0
        contaAlzi = 0
    End Sub
    Sub EseguiCurva(g As Short)

        piedeSopraX(g) = piedeX(g)

        If faseCurva(g) = 1 Then

            If Math.Abs(angoloCurva(g)) > angMaxCurva Then
                angRotaz(g) = Math.Asin(Int((10000 * (Math.Tan(angMaxCurva + Math.Atan((largBacino / 2) / (lungBacino / 2))) * (lungBacino / 2) - largBacino / 2)) / sporgGinocchio) / 10000)
                diagn2 = angRotaz(g) * 180 / Math.PI
                diagn3 = angMaxCurva * 180 / Math.PI
                diagn4 = angoloCurva(g) * 180 / Math.PI
                If angoloCurva(g) > 0 Then
                    angoloCurva(g) = angoloCurva(g) - angMaxCurva
                Else
                    angoloCurva(g) = angoloCurva(g) + angMaxCurva
                    angRotaz(g) = -angRotaz(g)
                End If
                diagn4 = angoloCurva(g) * 180 / Math.PI
            Else
                angRotaz(g) = Math.Asin(Int((10000 * (Math.Tan(angoloCurva(g) + Math.Atan((largBacino / 2) / (lungBacino / 2))) * (lungBacino / 2) - largBacino / 2)) / sporgGinocchio) / 10000)
                'angolo = Math.Asin(((Math.Tan(angoloCurva(g) + Math.Atan((largBacino / 2) / (lungBacino / 2))) * (lungBacino / 2) - largBacino / 2)) / sporgGinocchio)
                diagn1 = angRotaz(g) * 180 / Math.PI
                diagn2 = angoloCurva(g) * 180 / Math.PI
                angoloCurva(g) = 0

            End If

            lblCurva.Text = "Curva gradi " & Str(angoloCurva(g) * 180 / Math.PI)
            If posizione(g) = "avanti" Then
                Svolta(g, angRotaz(g))
            Else
                Svolta(g, -angRotaz(g))
            End If
            faseCurva(g) = 2
        ElseIf faseCurva(g) = 2 Then
            If g = candidatoAlzoCurva Then
                bAlzo(g) = True
                faseCurva(g) = 3
                contaAlzati = contaAlzati + 1
                TrovaPosizioni(g, AltezzaTerra - 20, 0)
                Ritorna(g)
            End If

        ElseIf faseCurva(g) = 3 Then

            TrovaPosizioni(g, AltezzaTerra, 0)
            Ritorna(g)
            If g < 3 Then
                candidatoAlzoCurva = candidatoAlzoCurva + 1
                faseCurva(g) = 4
            Else
                candidatoAlzoCurva = 0
                If contaAlzati >= 4 And g = 3 Then
                    contaAlzati = 0
                    If angoloCurva(g) <> 0 Then
                        For i = 0 To 3
                            faseCurva(i) = 1
                        Next
                    Else
                        bCurva = False
                        trkCurva.Value = 180
                        'trkPasso.Value = sporgGinocchio / 2
                        For i = 0 To 3
                            faseCurva(i) = 0
                            Fase(0) = 1
                            Fase(1) = 2
                            Fase(2) = 2
                            Fase(3) = 2
                            candidatoAlzo = 0
                            If i = 0 Or i = 3 Then
                                TibiaSopraY(i) = btnSopra.Top - picSopra.Top
                            Else
                                TibiaSopraY(i) = btnSopra.Top - picSopra.Top + largBacino
                            End If
                        Next
                    End If
                    a = faseCurva(3)
                End If
            End If



        ElseIf faseCurva(g) = 4 Then




        End If


    End Sub
    Sub Svolta(g As Short, angolo As Double)


        diagn1 = TibiaSopraY(g)
        If posizione(g) = "avanti" Then
            TibiaX(g) = FemoreX(g) + sporgGinocchio * Math.Cos(angolo)
        Else
            If chkForma.Checked = True Then
                TibiaX(g) = FemoreX(g) + sporgGinocchio * Math.Cos(angolo)
            Else
                TibiaX(g) = FemoreX(g) - sporgGinocchio * Math.Cos(angolo)
            End If
        End If
        If g = 0 Or g = 3 Then
            TibiaSopraY(g) = btnSopra.Top - picSopra.Top + sporgGinocchio * Math.Sin(angolo)
        Else
            TibiaSopraY(g) = btnSopra.Top - picSopra.Top + largBacino + sporgGinocchio * Math.Sin(angolo)
        End If

        diagn2 = TibiaSopraY(g)
        diagn3 = angolo * 180 / Math.PI
    End Sub
    Sub Ritorna(g As Short)
        If posizione(g) = "avanti" Then
            TibiaX(g) = FemoreX(g) + sporgGinocchio
        Else
            If chkForma.Checked = True Then
                TibiaX(g) = FemoreX(g) + sporgGinocchio
            Else
                TibiaX(g) = FemoreX(g) - sporgGinocchio
            End If
        End If

        If g = 0 Or g = 3 Then
            TibiaSopraY(g) = btnSopra.Top - picSopra.Top
        Else
            TibiaSopraY(g) = btnSopra.Top - picSopra.Top + largBacino
        End If
        diagn2 = TibiaSopraY(g)
    End Sub

    Sub AggiornaGamba(g As Short)
        Dim passo As Double

        diagn1 = errX(g)
        btnSopra.Visible = False

        If Int(cicliFatti / 4) >= cicliRitardoAlzo And bCandidabile = True Then
            cicliRitardoAlzo = trkRitardoAlzo.Value
            If g = candidatoAlzo Then
                diagn1 = EntroBaricentro(g)
                If (posizione(g) = "avanti" And piedeX(g) <= posxMinAvanti) Or (posizione(g) = "dietro" And piedeX(g) <= posxMinIndietro) Then
                    Fase(g) = 1
                    cicliFatti = 0
                    bCandidabile = False
                End If
            End If
        End If
        cicliFatti = cicliFatti + 1
        If Fase(g) = 1 Then
            bCandidabile = False
            passo = lunghPasso
            If (posizione(g) = "avanti" And piedeX(g) + lunghPasso >= posxMaxAvanti) Or (posizione(g) = "dietro" And piedeX(g) + lunghPasso >= posxMaxIndietro) Then
                If posizione(g) = "avanti" Then
                    passo = posxMaxAvanti - piedeX(g)
                Else
                    passo = posxMaxIndietro - piedeX(g)
                End If

                bCandidabile = True
                If bGiaAlzato(g) = True Then
                    TrovaPosizioni(g, AltezzaTerra, -passo)
                    bGiaAlzato(g) = False
                    Fase(g) = 2
                Else
                    TrovaPosizioni(g, AltezzaTerra - 15, -passo)
                    bGiaAlzato(g) = True
                End If
                'Debug.Print("a " & Str(g) & " " & Str(passo) & " " & Str(bGiaAlzato(g)))
            Else
                TrovaPosizioni(g, AltezzaTerra - 15, -passo)
                bGiaAlzato(g) = True
                ' Debug.Print("b " & Str(g) & " " & Str(passo) & " " & Str(bGiaAlzato(g)))
            End If
            If g = 0 Then
                candidatoAlzo = 2 'PiuIndietro(1, 2, 3) '3 '
            ElseIf g = 1 Then
                candidatoAlzo = 3 'PiuIndietro(0, 2, 3) '2 '
            ElseIf g = 2 Then
                candidatoAlzo = 1 'PiuIndietro(0, 1, 3) '0 '
            ElseIf g = 3 Then
                candidatoAlzo = 0 'PiuIndietro(0, 1, 2) '1 '
            End If

            a = 0


        ElseIf Fase(g) = 2 Then

            TrovaPosizioni(g, AltezzaTerra, velocAvanzamento)


        End If
        If piedeX(g) <> 0 Then piedeSopraX(g) = piedeX(g)
    End Sub
    Sub TrovaPosizioni(g As Short, altezzaTerra As Double, spinta As Double)

        xd1 = TibiaX(g)
        yd1 = TibiaY(g)
        'x^2+y^2=R^2
        '(x-x1)^2+(y-y1)^2=R1^2
        'con x1=distanza(piedeX-FemoreX), y1=altezzaterra, R= lunghezzaFemore, R1=lunghezzaTibia
        'x=(-b+-V(b^2-4ac))/2a
        'con x=coord x della tibia
        piedeX(g) = piedeX(g) - spinta
        constX1 = piedeX(g) - FemoreX(g)
        constY1 = altezzaTerra
        constK = (LunghezzaFemore ^ 2 - LunghezzaTibia ^ 2 + constX1 ^ 2 + constY1 ^ 2) / (2 * constY1)
        constA = 1 + (constX1 / constY1) ^ 2
        constB = -2 * constK * constX1 / constY1
        constC = constK ^ 2 - LunghezzaFemore ^ 2
        discriminante(g) = (constB ^ 2 - 4 * constA * constC)
        If discriminante(g) < 0 Then
            txtGamba.Text = Str(g)
            txtDiscriminante.Text = Str(Int(discriminante(g)))
            Application.DoEvents()
            StopAnimazione()
            Exit Sub
        End If
        If posizione(g) = "avanti" Or chkForma.Checked = True Then
            varX = ((-constB + Math.Sqrt(discriminante(g))) / (2 * constA))
        Else
            varX = ((-constB - Math.Sqrt(discriminante(g))) / (2 * constA))
        End If
        TibiaX(g) = varX + FemoreX(g)
        TibiaY(g) = constK - (constX1 / constY1) * varX
        xd2 = TibiaX(g)
        yd2 = TibiaY(g)
        If errX(g) = 0 Then
            errX(g) = xd1 - xd2
            errY(g) = yd1 - yd2
        End If
        'errX(0) = errX(1)
        angFemore(g) = Math.Asin((TibiaX(g) - FemoreX(g)) / LunghezzaFemore)
        angTibia(g) = Math.Asin((piedeX(g) - TibiaX(g)) / LunghezzaTibia)

        TibiaX(g) = FemoreX(g) + LunghezzaFemore * Math.Sin(angFemore(g))
        TibiaY(g) = FemoreY(g) + LunghezzaFemore * Math.Cos(angFemore(g))
        piedeX(g) = TibiaX(g) + LunghezzaTibia * Math.Sin(angTibia(g))
        piedeY(g) = TibiaY(g) + LunghezzaTibia * Math.Cos(angTibia(g)) - 4

    End Sub
    Sub DisegnaGamba(g As Short)
        Dim lTib As Double
        lTib = Math.Sqrt((piedeX(g) - TibiaX(g)) ^ 2 + (piedeY(g) - TibiaY(g)) ^ 2)
        bprint = True
        bPrint1 = True
        diagn6 = diagn6 + 1
        'If g <> 0 Then Exit Sub
        lavGraphics = picFianco.CreateGraphics
        spess = 1
        TPen.Color = Color.Black
        PicEllisse(FemoreX(g), FemoreY(g), 2 * LunghezzaFemore, 2 * LunghezzaFemore)
        PicEllisse(piedeX(g), piedeY(g), 2 * lTib, 2 * lTib)
        ' PicEllisse(piedeX(g), piedeY(g), 2 * LunghezzaTibia, 2 * LunghezzaTibia)
        spess = 4
        If g = 0 Or g = 3 Then
            color = Color.Bisque
        Else
            color = Color.Coral
        End If
        Picline(FemoreX(g), FemoreY(g), TibiaX(g), TibiaY(g), color)
        Picline(TibiaX(g), TibiaY(g), piedeX(g), piedeY(g), color)

        TPen.Color = Color.Red
        PicEllisse(FemoreX(g), FemoreY(g), 5, 5)
        PicEllisse(TibiaX(g), TibiaY(g), 5, 5)
        TPen.Color = Color.Blue
        PicEllisse(piedeX(g), piedeY(g), 5, 5)

        lavGraphics = picSopra.CreateGraphics
        spess = 2
        color = Color.Red
        Picline(btnSopra.Left - picSopra.Left, btnSopra.Top - picSopra.Top, btnSopra.Left + btnSopra.Width - picSopra.Left, btnSopra.Top - picSopra.Top, color)
        Picline(btnSopra.Left - picSopra.Left, btnSopra.Top + largBacino - picSopra.Top, btnSopra.Left + btnSopra.Width - picSopra.Left, btnSopra.Top - picSopra.Top + largBacino, color)
        Picline(btnSopra.Left - picSopra.Left, btnSopra.Top - picSopra.Top, btnSopra.Left - picSopra.Left, btnSopra.Top + largBacino - picSopra.Top, color)
        Picline(btnSopra.Left + btnSopra.Width - picSopra.Left, btnSopra.Top - picSopra.Top, btnSopra.Left + btnSopra.Width - picSopra.Left, btnSopra.Top + largBacino - picSopra.Top, color)

        spess = 4
        TPen.Color = Color.Blue
        PicEllisse(piedeX(g), piedeSopraY(g), 5, 5)
        spess = 3
        TPen.Color = Color.Green
        PicEllisse(FemoreX(g), FemoreSopraY(g), 3, 3)
        TPen.Color = Color.Red
        PicEllisse(TibiaX(g), TibiaSopraY(g), 3, 3)
        spess = 2
        color = Color.Yellow
        Picline(FemoreX(g), FemoreSopraY(g), TibiaX(g), TibiaSopraY(g), color)
        color = Color.Azure
        Picline(TibiaX(g), TibiaSopraY(g), piedeX(g), piedeSopraY(g), color)
        color = Color.Black
        spess = 1
        bprint = True
        For i = 0 To 3
            If piedeSopraX(i) = 0 Or piedeSopraY(i) = 0 Then
                bPrint = False
            End If
        Next

        If bAlzo(g) = True Then
            'bAlzo(g) = False
            ' If g = 0 Then
            ' candidatoAlzoCurva = 1
            'ElseIf g = 1 Then
            ' candidatoAlzoCurva = 2
            'ElseIf g = 2 Then
            '  candidatoAlzoCurva = 3
            'ElseIf g = 3 Then
            '   candidatoAlzoCurva = 0
            'End If
        End If

        If bPiedeAlzato = True Then

            If Fase(g) = 1 Or bAlzo(g) = True Then

                If g = 0 Then
                    Picline(piedeSopraX(1), piedeSopraY(1), piedeSopraX(2), piedeSopraY(2), color)
                    Picline(piedeSopraX(2), piedeSopraY(2), piedeSopraX(3), piedeSopraY(3), color)
                    Picline(piedeSopraX(3), piedeSopraY(3), piedeSopraX(1), piedeSopraY(1), color)
                ElseIf g = 1 Then
                    Picline(piedeSopraX(0), piedeSopraY(0), piedeSopraX(2), piedeSopraY(2), color)
                    Picline(piedeSopraX(2), piedeSopraY(2), piedeSopraX(3), piedeSopraY(3), color)
                    Picline(piedeSopraX(3), piedeSopraY(3), piedeSopraX(0), piedeSopraY(0), color)
                ElseIf g = 2 Then
                    Picline(piedeSopraX(0), piedeSopraY(0), piedeSopraX(1), piedeSopraY(1), color)
                    Picline(piedeSopraX(1), piedeSopraY(1), piedeSopraX(3), piedeSopraY(3), color)
                    Picline(piedeSopraX(3), piedeSopraY(3), piedeSopraX(0), piedeSopraY(0), color)
                ElseIf g = 3 Then
                    Picline(piedeSopraX(0), piedeSopraY(0), piedeSopraX(1), piedeSopraY(1), color)
                    Picline(piedeSopraX(1), piedeSopraY(1), piedeSopraX(2), piedeSopraY(2), color)
                    Picline(piedeSopraX(2), piedeSopraY(2), piedeSopraX(0), piedeSopraY(0), color)
                End If
            End If



        Else


            Picline(piedeSopraX(0), piedeSopraY(0), piedeSopraX(1), piedeSopraY(1), color)
            Picline(piedeSopraX(1), piedeSopraY(1), piedeSopraX(2), piedeSopraY(2), color)
            Picline(piedeSopraX(2), piedeSopraY(2), piedeSopraX(3), piedeSopraY(3), color)
            Picline(piedeSopraX(3), piedeSopraY(3), piedeSopraX(0), piedeSopraY(0), color)
        End If

    End Sub

    Sub StopAnimazione()
        tmrCamminata.Enabled = False
    End Sub
    Sub StartAnimazione()

        tmrCamminata.Interval = trkTimer.Value '500
        tmrCamminata.Enabled = True
    End Sub

    Private Sub tmrCamminata_Tick(sender As Object, e As EventArgs) Handles tmrCamminata.Tick
        Dim i As Int16

        tmrCamminata.Interval = trkTimer.Value
        If bCurva = False Then
            For i = 0 To 3
                AggiornaGamba(i)
                txtGamba.Text = Str(i)
                txtDiscriminante.Text = Str(Int(discriminante(i)))
            Next
        Else
            For i = 0 To 3
                EseguiCurva(i)
            Next
        End If
        'Application.DoEvents()
        ' Dim stopwatch As Stopwatch = Stopwatch.StartNew
        ' Thread.Sleep(1)
        'Stopwatch.Stop()
        bPiedeAlzato = False

        For i = 0 To 3

            If Fase(i) = 1 Then
                bPiedeAlzato = True

            End If

            diagn1 = faseCurva(2)
        Next

        picFianco.Refresh()
        picSopra.Refresh()
        For i = 0 To 3
            If discriminante(i) >= 0 Then
                DisegnaGamba(i)
            Else
                txtGamba.Text = Str(i)
                txtDiscriminante.Text = Str(Int(discriminante(i)))
                Application.DoEvents()
                StopAnimazione()
                Exit Sub
            End If

        Next i
        InviaDatiRobot()
    End Sub
    Sub InviaDatiRobot()
        Dim datiInChiaro As String = Trim(Str(counterSend)) & ":"
        Dim dati As String = Trim(Str(counterSend)) & ":"
        For i = 0 To 3
            dati &= Replace(Hex(tmrCamminata.Interval).PadLeft(3), " ", "0") & cmServo(angFemore(i)) & cmServo(angTibia(i)) & cmServo(angRotaz(i))
            datiInChiaro &= Str(tmrCamminata.Interval) & Str(Int(100 * angFemore(i) * 180 / Math.PI) / 100) & Str(Int(100 * angTibia(i) * 180 / Math.PI) / 100) & Str(Int(100 * angRotaz(i) * 180 / Math.PI) / 100)
        Next
        dati &= "!"
        If txtCom.Text <> "0" And Not dati = String.Empty Then
            SendSerialData(dati)
        End If
        Debug.Print(dati)
        Debug.Print(datiInChiaro)
    End Sub
    Sub SendSerialData(ByVal data As String)

        ' Send strings to a serial port.
        Using com1 As IO.Ports.SerialPort =
            My.Computer.Ports.OpenSerialPort("COM" & txtCom.Text, 9600, System.IO.Ports.Parity.None, 8, 1)
            com1.Write(data)
            If counterSend = 4 Then
                counterSend = 0
            Else
                counterSend = counterSend + 1
            End If
            com1.Close()
        End Using
    End Sub

    Public Function cmServo(ByVal angle As Double) As String
        Return Hex(Math.Round(((angle * (180 / Math.PI)) + 90) * 1400 / 180) + 800)
    End Function
    Sub SendSerialData1(ByVal data As String)

        ' Send strings to a serial port.
        Using com1 As IO.Ports.SerialPort =
            My.Computer.Ports.OpenSerialPort("COM" & txtCom.Text, 9600, System.IO.Ports.Parity.None, 8)
            com1.Write(data)
            If counterSend = 4 Then
                counterSend = 0
            Else
                counterSend = counterSend + 1
            End If
            com1.Close()
        End Using
    End Sub

    Public Function cmServo1(ByVal angle As Double) As String
        Return Hex(Math.Round(((angle * 180 / Math.PI) * 1400 / 180) + 800))
    End Function

End Class

