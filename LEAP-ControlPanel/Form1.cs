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

        private void SerialPortSetup()
        {
            Parity serialPortParity;
            switch (comboBox_SerialPort_Parity.Text)
            {
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
                case "None":
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
        }

        private void button_SerialPort_Connect_Click(object sender, EventArgs e)
        {
            SerialPortSetup();

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
            string data = serialPort1.ReadLine();
            //MessageBox.Show(data);
        }
    }
}
