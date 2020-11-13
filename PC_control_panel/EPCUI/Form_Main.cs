using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;


namespace EPCUI
{
    public partial class FROM_EPCUI : Form
    {
        public Form ControlForm;

        /* Serial Port */
        private Boolean Connected = false;
        private SerialPort COMPort;
        private Int32 RxtotalLength, TxtotalLength = 0;
        delegate void Display(Byte[] buffer);

        public FROM_EPCUI()
        {   
            InitializeComponent();
            string[] AllPorts = SerialPort.GetPortNames();  // Get All COM Port
            CB_sp_COMPort.DataSource = AllPorts;

            CB_sp_COMPort.SelectedItem = AllPorts[0];

            // CSP
            CB_Csp_MotorID.Text = "0(R)";
            CB_Csp_Status.Text = "Keep";
            CB_Csp_Direction.Text = "Keep";
            NUD_Csp_Speed.Value = -1;

            // SP setting
            CB_sp_BaudRate.Text = "9600";
            CB_sp_DataBits.Text = "8";
            CB_sp_StopBits.Text = "1";
            CB_sp_Parity.Text = "None";
            CB_sp_Handshaking.Text = "None";

            // Monitor
            CB_TxEncode.SelectedItem = "ASCII";
            CB_RxEncode.SelectedItem = "ASCII";
            CB_RxEncodeSub.SelectedItem = "HEX";
        }

        int MotorSpeed = 0;         // Motor Speed in percent(%). >0:CW; <0:CCW; =0:non rotate.
        int FStoMS_Constant = 10;   // Force Sensor Value to Motor Speed convert constant.

        private void TB_ForceSensor_T_Scroll(object sender, EventArgs e)
        {
            MotorSpeed = FStoMS_Constant * (TB_ForceSensor_T.Value - TB_ForceSensor_C.Value );
            TB_MotorSpeed.Value = MotorSpeed;
        }

        private void TB_ForceSensor_C_Scroll(object sender, EventArgs e)
        {
            MotorSpeed = FStoMS_Constant * (TB_ForceSensor_T.Value - TB_ForceSensor_C.Value);
            TB_MotorSpeed.Value = MotorSpeed;
        }

        private void Panel1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = panel1.CreateGraphics();
            Pen pen = new Pen(Color.Blue, 2);

            g.DrawLine(pen, 10, 10, 100, 100);//在画板上画直线,起始坐标为(10,10),终点坐标为(100,100)
            g.DrawRectangle(pen, 10, 10, 90, 90);//在画板上画矩形,起始坐标为(10,10),宽为,高为
            g.DrawEllipse(pen, 10, 10, 90, 90);//在画板上画椭圆,起始坐标为(10,10),外接矩形的宽为,高为
        }

        private void BT_ShowForm_SerialSet_Click(object sender, EventArgs e)
        {
            // Show "Form_SerialPort_Setting"
            //ControlForm = new Form_SerialPort_Setting();
            //ControlForm.Show();
        }


/* Serial Port --------------------------------------------------------------------------------- */
        private void DisplayText(Byte[] Data)
        {
            TB_RxMessage.Text += RxEncodeSelect(CB_RxEncode.Text, Data, CH_RxCRLF.Checked);
            TB_RxMessageSub.Text += RxEncodeSelect(CB_RxEncodeSub.Text, Data, CH_RxCRLF.Checked);

            // automatically scroll to the end.
            if (CH_RxAutoScroll.Checked)
            {
                TB_RxMessage.SelectionStart = TB_RxMessage.Text.Length;
                TB_RxMessage.ScrollToCaret();

                TB_RxMessageSub.SelectionStart = TB_RxMessageSub.Text.Length;
                TB_RxMessageSub.ScrollToCaret();
            }

            // Count Rx-Data Bytes
            RxtotalLength += Data.Length;
            LAB_RxNum.Text = "Rx:  " + RxtotalLength.ToString() + " Bytes";
        }

        private void BTN_Connect_Click(object sender, EventArgs e)
        {
            System.IO.Ports.Parity COMParity = Parity.None;
            System.IO.Ports.StopBits COMStopBits = StopBits.One;

            switch (CB_sp_Parity.Text)
            {
                case "None":
                    COMParity = Parity.None;
                    break;
                case "Even":
                    COMParity = Parity.Even;
                    break;
                case "Odd":
                    COMParity = Parity.Odd;
                    break;
                case "Mark":
                    COMParity = Parity.Mark;
                    break;
                case "Space":
                    COMParity = Parity.Space;
                    break;
                default:
                    COMParity = Parity.None;
                    break;
            }

            switch (CB_sp_StopBits.Text)
            {
                case "1.5":
                    COMStopBits = StopBits.OnePointFive;
                    break;
                case "2":
                    COMStopBits = StopBits.Two;
                    break;
                case "None":
                    COMStopBits = StopBits.None;
                    break;
                default:
                    COMStopBits = StopBits.One;
                    break;
            }

            // Set COM  Port
            COMPort = new SerialPort(CB_sp_COMPort.Text,
                                    int.Parse(CB_sp_BaudRate.Text),
                                    COMParity,
                                    int.Parse(CB_sp_DataBits.Text),
                                    COMStopBits);
            COMPort.DataReceived += new SerialDataReceivedEventHandler(COMPort_DataReceived);

            if (!Connected && !COMPort.IsOpen)
            {
                try
                {
                    COMPort.Close();
                    COMPort.Open();
                    BTN_Send.Enabled = true;
                    //GB_COMPortConfig.Enabled = false;
                    Connected = true;
                }
                catch (Exception EX) // error
                {
                    MessageBox.Show("Error !!\nCon't open COM port");
                }
            }
            else
            {
                COMPort.Close();

                LAB_StaConnect.Text = "Disconnecting";
                while (COMPort.IsOpen)
                {
                }
                Thread.Sleep(1000);
//                BTN_Send.Enabled = false;
                //GB_COMPortConfig.Enabled = true;
                Connected = false;
            }
            UpdateCOMPortStatus();
        }

        private void COMPort_DataReceived(Object sender, SerialDataReceivedEventArgs e)
        {
            Byte[] buffer = new Byte[1024];
            Int32 length = (sender as SerialPort).Read(buffer, 0, buffer.Length);
            Array.Resize(ref buffer, length);
            Display d = new Display(DisplayText);
            this.Invoke(d, new Object[] { buffer });
        }

        private string RxEncodeSelect(string Encode, byte[] Text, Boolean LF_eq_CRLF)
        {
            string RTText = "";

            switch (Encode)
            {
                case "ASCII":
                    if (LF_eq_CRLF)   // CR=LF
                        RTText += ConvertHex((BitConverter.ToString(Text).Replace("-", "")).Replace("0A", "0D0A")); // 0A:LF ; 0D:CR
                    else
                        RTText += ConvertHex(BitConverter.ToString(Text).Replace("-", ""));
                    break;

                case "HEX":
                    RTText += BitConverter.ToString(Text);
                    break;

                case "BIN":
                    RTText += BitConverter.ToString(Text);
                    break;

                case "STM32 Instruction":
                    break;

                default:
                    break;
            }

            return RTText;
        }

        private void UpdateCOMPortStatus()
        {
            string sParity = "N";
            string sHandshaking = "N";

            if (Connected)
            {
                BTN_Connect.Text = "Disconnect";
                LAB_StaConnect.Text = "Connected";
            }
            else
            {
                BTN_Connect.Text = "Connect";
                LAB_StaConnect.Text = "Disconnected";
            }

            switch (CB_sp_Parity.Text)
            {
                case "None":
                    sParity = "N";
                    break;
                case "Even":
                    sParity = "E";
                    break;
                case "Odd":
                    sParity = "O";
                    break;
                case "Mark":
                    sParity = "M";
                    break;
                case "Space":
                    sParity = "S";
                    break;
                default:
                    sParity = "?";
                    break;
            }

            LAB_COMPortConfig.Text =    CB_sp_COMPort.Text + " " +
                                        CB_sp_BaudRate.Text + ", " +
                                        sParity + "-" +
                                        CB_sp_DataBits.Text + "-" +
                                        CB_sp_StopBits.Text + ", " +
                                        sHandshaking;
        }

        private void BT_Csp_Send_Click(object sender, EventArgs e)
        {
            byte HeadData = 0xF1;
            byte CtrlData = 0x0F;

            switch (CB_Csp_MotorID.Text)
            {
                case "0(R)":
                    HeadData = 0x21;
                    break;
                case "1(L)":
                    HeadData = 0x29;
                    break;
                default:
                    break;
            }

            switch(CB_Csp_Status.Text)
            {
                case "Disable":
                    CtrlData = 0x03;
                    break;
                case "Enable":
                    CtrlData = 0x07;
                    break;
                case "Toggle":
                    CtrlData = 0x0B;
                    break;
                case "Keep":
                    CtrlData = 0x0F;
                    break;
                default:
                    break;
            }

            switch (CB_Csp_Direction.Text)
            {
                case "CW":
                    CtrlData &= 0xFC;
                    break;
                case "CCW":
                    CtrlData &= 0xFD;
                    break;
                case "Toggle":
                    CtrlData &= 0xFE;
                    break;
                case "Keep":
                    CtrlData &= 0xFF;
                    break;
                default:
                    break;
            }
            TB_Csp_SendHistory.Text += "ID:" + CB_Csp_MotorID.Text +
                                        "  STS:" + CB_Csp_Status.Text +
                                        "  DIR:" + CB_Csp_Direction.Text +
                                        "  SPD:" + NUD_Csp_Speed.Value +
                                        "\r\n";
            // automatically scroll to the end.
            TB_Csp_SendHistory.SelectionStart = TB_Csp_SendHistory.Text.Length;
            TB_Csp_SendHistory.ScrollToCaret();

            //COMPort.Write(new byte[] { HeadData, CtrlData }, 0, 2);

            if (NUD_Csp_Speed.Value != -1)
            {
                byte SpdData = 0x80;
                SpdData += Decimal.ToByte(NUD_Csp_Speed.Value);
                //COMPort.Write(new byte[] { HeadData, SpdData }, 0, 2);
            }

            //textBox1.Text = Convert.ToString(SpdData);

        }

        private void BTN_Send_Click(object sender, EventArgs e)
        {
            string TxData = null;
            byte[] ASCIIbyte = null;
            string HEXstr = null;

            switch (CB_TxEncode.Text)
            {
                case "ASCII":
                    if (TB_TxMessage.Text.IndexOf("\\n") != -1)
                    {
                        if (TB_TxMessage.Text.IndexOf("\\\\n") != -1)
                            TxData = TB_TxMessage.Text;
                        else
                        {
                            ASCIIbyte = Encoding.ASCII.GetBytes(TB_TxMessage.Text);                 // ASCII(Strinng) -> ASCII(byte)
                            HEXstr = BitConverter.ToString(ASCIIbyte);                              // ASCII(byte) -> HEX(string)
                            TxData = ConvertHex((HEXstr.Replace("-", "")).Replace("5C6E", "0A"));   // HEX(string)replace -> ASCII(string); 5C: \; 6E:n ;0A:LF
                        }
                    }
                    else
                        TxData = TB_TxMessage.Text;
                    break;

                case "HEX":
                    TxData = ConvertHex(TB_TxMessage.Text.Replace("-", ""));
                    break;

                case "BIN":
                    break;

                case "STM32 Instruction":
                    break;

                default:
                    break;
            }

            COMPort.Write(TxData);

            // Auto NewLine
            if (CH_TxAutoNewLine.Checked)
                TB_TxMessageHistory.Text += TxData + "\r\n";
            else
                TB_TxMessageHistory.Text += TxData;

            // Auto Scroll to end
            TB_TxMessageHistory.SelectionStart = TB_TxMessageHistory.Text.Length;
            TB_TxMessageHistory.ScrollToCaret();

            // Count Tx-Data Bytes
            TxtotalLength += Encoding.ASCII.GetBytes(TxData).Length;
            LAB_TxNum.Text = "Tx:  " + TxtotalLength.ToString() + " Bytes";
        }

        private void BTN_ClrRx_Click(object sender, EventArgs e)
        {
            TB_RxMessage.Clear();
            TB_RxMessageSub.Clear();
        }

        private void BTN_ClrTx_Click(object sender, EventArgs e)
        {
            TB_TxMessageHistory.Clear();
            TB_TxMessage.Clear();
        }

        private void BTN_Connect_Click_1(object sender, EventArgs e)
        {
            System.IO.Ports.Parity COMParity = Parity.None;
            System.IO.Ports.StopBits COMStopBits = StopBits.One;

            switch (CB_sp_Parity.Text)
            {
                case "None":
                    COMParity = Parity.None;
                    break;
                case "Even":
                    COMParity = Parity.Even;
                    break;
                case "Odd":
                    COMParity = Parity.Odd;
                    break;
                case "Mark":
                    COMParity = Parity.Mark;
                    break;
                case "Space":
                    COMParity = Parity.Space;
                    break;
                default:
                    COMParity = Parity.None;
                    break;
            }

            switch (CB_sp_StopBits.Text)
            {
                case "1.5":
                    COMStopBits = StopBits.OnePointFive;
                    break;
                case "2":
                    COMStopBits = StopBits.Two;
                    break;
                case "None":
                    COMStopBits = StopBits.None;
                    break;
                default:
                    COMStopBits = StopBits.One;
                    break;
            }

            // Set COM  Port
            COMPort = new SerialPort(CB_sp_COMPort.Text,
                                        int.Parse(CB_sp_BaudRate.Text),
                                        COMParity,
                                        int.Parse(CB_sp_DataBits.Text),
                                        COMStopBits);
            COMPort.DataReceived += new SerialDataReceivedEventHandler(COMPort_DataReceived);

            if (!Connected && !COMPort.IsOpen)
            {
                try
                {
                    COMPort.Close();
                    COMPort.Open();
                    BTN_Send.Enabled = true;
                    GB_COMPortConfig.Enabled = false;
                    Connected = true;
                }
                catch (Exception EX) // error
                {
                    MessageBox.Show("Error !!\nCon't open COM port");
                }
            }
            else
            {
                COMPort.Close();

                LAB_StaConnect.Text = "Disconnecting";
                while (COMPort.IsOpen)
                {
                }
                Thread.Sleep(1000);
                //                BTN_Send.Enabled = false;
                GB_COMPortConfig.Enabled = true;
                Connected = false;
            }
            UpdateCOMPortStatus();
        }

        private void BTN_Send_Click_1(object sender, EventArgs e)
        {
            string TxData = null;
            byte[] ASCIIbyte = null;
            string HEXstr = null;

            switch (CB_TxEncode.Text)
            {
                case "ASCII":
                    if (TB_TxMessage.Text.IndexOf("\\n") != -1)
                    {
                        if (TB_TxMessage.Text.IndexOf("\\\\n") != -1)
                            TxData = TB_TxMessage.Text;
                        else
                        {
                            ASCIIbyte = Encoding.ASCII.GetBytes(TB_TxMessage.Text);                 // ASCII(Strinng) -> ASCII(byte)
                            HEXstr = BitConverter.ToString(ASCIIbyte);                              // ASCII(byte) -> HEX(string)
                            TxData = ConvertHex((HEXstr.Replace("-", "")).Replace("5C6E", "0A"));   // HEX(string)replace -> ASCII(string); 5C: \; 6E:n ;0A:LF
                        }
                    }
                    else
                        TxData = TB_TxMessage.Text;
                    break;

                case "HEX":
                    TxData = ConvertHex(TB_TxMessage.Text.Replace("-", ""));
                    break;

                case "BIN":
                    break;

                case "STM32 Instruction":
                    break;

                default:
                    break;
            }

            COMPort.Write(TxData);

            // Auto NewLine
            if (CH_TxAutoNewLine.Checked)
                TB_TxMessageHistory.Text += TxData + "\r\n";
            else
                TB_TxMessageHistory.Text += TxData;

            // Auto Scroll to end
            TB_TxMessageHistory.SelectionStart = TB_TxMessageHistory.Text.Length;
            TB_TxMessageHistory.ScrollToCaret();

            // Count Tx-Data Bytes
            TxtotalLength += Encoding.ASCII.GetBytes(TxData).Length;
            LAB_TxNum.Text = "Tx:  " + TxtotalLength.ToString() + " Bytes";
        }
    }

        public static string ConvertHex(String hexString) // Convert HEX(string) to ASCII(string)
        {
            try
            {
                string ascii = string.Empty;

                for (int i = 0; i < hexString.Length; i += 2)
                {
                    String hs = string.Empty;

                    hs = hexString.Substring(i, 2);
                    uint decval = System.Convert.ToUInt32(hs, 16);
                    char character = System.Convert.ToChar(decval);
                    ascii += character;

                }

                return ascii;
            }
            catch (Exception ex) { Console.WriteLine(ex.Message); }

            return string.Empty;
        }

    }
}
