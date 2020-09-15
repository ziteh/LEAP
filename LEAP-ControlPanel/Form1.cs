using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LEAP_ControlPanel
{
    public partial class Form1 : Form
    {
        private delegate void Display(Byte[] buffer);

        public Form1()
        {
            InitializeComponent();
            SerialPortInit();
        }

        private void SerialPortInit()
        {
            // Get all COM Port name.
            string[] allPortName = SerialPort.GetPortNames();
            if (allPortName.Length > 0)
            {
                comboBox_SerialPort_COMPort.DataSource = allPortName;
                comboBox_SerialPort_COMPort.Text = allPortName[0];
            }
            else
            {
                comboBox_SerialPort_COMPort.Text = "Can't find any device";
            }

            comboBox_SerialPort_BaudRate.Text = "9600";
            comboBox_SerialPort_DataBits.Text = "8";
            comboBox_SerialPort_StopBits.Text = "1";
            comboBox_SerialPort_Parity.Text = "None";
            comboBox_SerialPort_Handshaking.Text = "None";
        }

        private void button_SerialPort_Connect_Click(object sender, EventArgs e)
        {
            Parity serialPortParity;
            switch (comboBox_SerialPort_Parity.Text)
            {
                case "None":
                    serialPortParity = Parity.None;
                    break;
                case "Even":
                    serialPortParity = Parity.Even;
                    break;
                case "Odd":
                    serialPortParity = Parity.Odd;
                    break;
                case "Mark":
                    serialPortParity = Parity.Mark;
                    break;
                case "Space":
                    serialPortParity = Parity.Space;
                    break;
                default:
                    serialPortParity = Parity.None;
                    break;
            }

            StopBits serialPortStopBits;
            switch (comboBox_SerialPort_StopBits.Text)
            {
                case "1.5":
                    serialPortStopBits = StopBits.OnePointFive;
                    break;
                case "2":
                    serialPortStopBits = StopBits.Two;
                    break;
                case "None":
                    serialPortStopBits = StopBits.None;
                    break;
                case "1":
                default:
                    serialPortStopBits = StopBits.One;
                    break;
            }

            serialPort1 = new SerialPort(comboBox_SerialPort_COMPort.Text,
                                        Convert.ToInt32(comboBox_SerialPort_BaudRate.Text),
                                        serialPortParity,
                                        Convert.ToInt32(comboBox_SerialPort_DataBits.Text),
                                        serialPortStopBits);
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(SerialPort_DataReceived);

            if (!serialPort1.IsOpen)
            {
                try
                {
                    //serialPort1.Close();
                    serialPort1.Open();
                    while (!serialPort1.IsOpen)
                    {
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Can't open serial port.\r\n" + ex.Message,
                                    "Error!",
                                    MessageBoxButtons.OK,
                                    MessageBoxIcon.Error);
                }
            }
            else
            {
                serialPort1.Close();
                while (serialPort1.IsOpen)
                {
                }
            }
        }

        private void SerialPort_DataReceived(Object sender, SerialDataReceivedEventArgs e)
        {
            Byte[] buffer = new Byte[1024];
            Int32 length = (sender as SerialPort).Read(buffer, 0, buffer.Length);
            Array.Resize(ref buffer, length);
            Display d = new Display(DisplayText);
            this.Invoke(d, new Object[] { buffer });
        }

        private void DisplayText(Byte[] data)
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
    }
}
