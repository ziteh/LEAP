namespace LEAP_ControlPanel
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox_R_State_Ready = new System.Windows.Forms.TextBox();
            this.textBox_R_State_Dircetion = new System.Windows.Forms.TextBox();
            this.textBox_R_State_Limit = new System.Windows.Forms.TextBox();
            this.textBox_R_State_AnglePOT = new System.Windows.Forms.TextBox();
            this.textBox_R_State_FrontFSR = new System.Windows.Forms.TextBox();
            this.textBox_R_State_BackFSR = new System.Windows.Forms.TextBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.groupBox_SerialPort = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.comboBox_SerialPort_COMPort = new System.Windows.Forms.ComboBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.comboBox_SerialPort_BaudRate = new System.Windows.Forms.ComboBox();
            this.comboBox_SerialPort_DataBits = new System.Windows.Forms.ComboBox();
            this.comboBox_SerialPort_StopBits = new System.Windows.Forms.ComboBox();
            this.comboBox_SerialPort_Parity = new System.Windows.Forms.ComboBox();
            this.comboBox_SerialPort_Handshaking = new System.Windows.Forms.ComboBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.groupBox_SerialPort.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(3, 63);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1066, 522);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.tableLayoutPanel2);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(1058, 496);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.label4, 0, 3);
            this.tableLayoutPanel2.Controls.Add(this.label5, 0, 4);
            this.tableLayoutPanel2.Controls.Add(this.label6, 0, 5);
            this.tableLayoutPanel2.Controls.Add(this.label3, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.label2, 0, 2);
            this.tableLayoutPanel2.Controls.Add(this.textBox_R_State_Ready, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.textBox_R_State_Dircetion, 1, 1);
            this.tableLayoutPanel2.Controls.Add(this.textBox_R_State_Limit, 1, 2);
            this.tableLayoutPanel2.Controls.Add(this.textBox_R_State_AnglePOT, 1, 3);
            this.tableLayoutPanel2.Controls.Add(this.textBox_R_State_FrontFSR, 1, 4);
            this.tableLayoutPanel2.Controls.Add(this.textBox_R_State_BackFSR, 1, 5);
            this.tableLayoutPanel2.Location = new System.Drawing.Point(181, 101);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 6;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(204, 257);
            this.tableLayoutPanel2.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Ready : ";
            // 
            // label4
            // 
            this.label4.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 141);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(66, 12);
            this.label4.TabIndex = 0;
            this.label4.Text = "Angle POT : ";
            // 
            // label5
            // 
            this.label5.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(3, 183);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(62, 12);
            this.label5.TabIndex = 0;
            this.label5.Text = "Front FSR : ";
            // 
            // label6
            // 
            this.label6.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(3, 227);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(61, 12);
            this.label6.TabIndex = 0;
            this.label6.Text = "Back FSR : ";
            // 
            // label3
            // 
            this.label3.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 57);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "Dircetion : ";
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 99);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "Limit : ";
            // 
            // textBox_R_State_Ready
            // 
            this.textBox_R_State_Ready.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_R_State_Ready.Location = new System.Drawing.Point(105, 10);
            this.textBox_R_State_Ready.Name = "textBox_R_State_Ready";
            this.textBox_R_State_Ready.ReadOnly = true;
            this.textBox_R_State_Ready.Size = new System.Drawing.Size(96, 22);
            this.textBox_R_State_Ready.TabIndex = 1;
            this.textBox_R_State_Ready.Text = "--";
            // 
            // textBox_R_State_Dircetion
            // 
            this.textBox_R_State_Dircetion.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_R_State_Dircetion.Location = new System.Drawing.Point(105, 52);
            this.textBox_R_State_Dircetion.Name = "textBox_R_State_Dircetion";
            this.textBox_R_State_Dircetion.ReadOnly = true;
            this.textBox_R_State_Dircetion.Size = new System.Drawing.Size(96, 22);
            this.textBox_R_State_Dircetion.TabIndex = 1;
            this.textBox_R_State_Dircetion.Text = "--";
            // 
            // textBox_R_State_Limit
            // 
            this.textBox_R_State_Limit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_R_State_Limit.Location = new System.Drawing.Point(105, 94);
            this.textBox_R_State_Limit.Name = "textBox_R_State_Limit";
            this.textBox_R_State_Limit.ReadOnly = true;
            this.textBox_R_State_Limit.Size = new System.Drawing.Size(96, 22);
            this.textBox_R_State_Limit.TabIndex = 1;
            this.textBox_R_State_Limit.Text = "--";
            // 
            // textBox_R_State_AnglePOT
            // 
            this.textBox_R_State_AnglePOT.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_R_State_AnglePOT.Location = new System.Drawing.Point(105, 136);
            this.textBox_R_State_AnglePOT.Name = "textBox_R_State_AnglePOT";
            this.textBox_R_State_AnglePOT.ReadOnly = true;
            this.textBox_R_State_AnglePOT.Size = new System.Drawing.Size(96, 22);
            this.textBox_R_State_AnglePOT.TabIndex = 1;
            this.textBox_R_State_AnglePOT.Text = "--";
            // 
            // textBox_R_State_FrontFSR
            // 
            this.textBox_R_State_FrontFSR.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_R_State_FrontFSR.Location = new System.Drawing.Point(105, 178);
            this.textBox_R_State_FrontFSR.Name = "textBox_R_State_FrontFSR";
            this.textBox_R_State_FrontFSR.ReadOnly = true;
            this.textBox_R_State_FrontFSR.Size = new System.Drawing.Size(96, 22);
            this.textBox_R_State_FrontFSR.TabIndex = 1;
            this.textBox_R_State_FrontFSR.Text = "--";
            // 
            // textBox_R_State_BackFSR
            // 
            this.textBox_R_State_BackFSR.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_R_State_BackFSR.Location = new System.Drawing.Point(105, 222);
            this.textBox_R_State_BackFSR.Name = "textBox_R_State_BackFSR";
            this.textBox_R_State_BackFSR.ReadOnly = true;
            this.textBox_R_State_BackFSR.Size = new System.Drawing.Size(96, 22);
            this.textBox_R_State_BackFSR.TabIndex = 1;
            this.textBox_R_State_BackFSR.Text = "--";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.groupBox_SerialPort);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(1058, 496);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // groupBox_SerialPort
            // 
            this.groupBox_SerialPort.Controls.Add(this.tableLayoutPanel3);
            this.groupBox_SerialPort.Location = new System.Drawing.Point(148, 51);
            this.groupBox_SerialPort.Name = "groupBox_SerialPort";
            this.groupBox_SerialPort.Size = new System.Drawing.Size(195, 258);
            this.groupBox_SerialPort.TabIndex = 0;
            this.groupBox_SerialPort.TabStop = false;
            this.groupBox_SerialPort.Text = "Serial Port";
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.label7, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.label8, 0, 1);
            this.tableLayoutPanel3.Controls.Add(this.label9, 0, 3);
            this.tableLayoutPanel3.Controls.Add(this.label10, 0, 2);
            this.tableLayoutPanel3.Controls.Add(this.label11, 0, 4);
            this.tableLayoutPanel3.Controls.Add(this.label12, 0, 5);
            this.tableLayoutPanel3.Controls.Add(this.comboBox_SerialPort_COMPort, 1, 0);
            this.tableLayoutPanel3.Controls.Add(this.comboBox_SerialPort_BaudRate, 1, 1);
            this.tableLayoutPanel3.Controls.Add(this.comboBox_SerialPort_DataBits, 1, 2);
            this.tableLayoutPanel3.Controls.Add(this.comboBox_SerialPort_StopBits, 1, 3);
            this.tableLayoutPanel3.Controls.Add(this.comboBox_SerialPort_Parity, 1, 4);
            this.tableLayoutPanel3.Controls.Add(this.comboBox_SerialPort_Handshaking, 1, 5);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 18);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 6;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(189, 237);
            this.tableLayoutPanel3.TabIndex = 0;
            // 
            // label7
            // 
            this.label7.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(29, 13);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(62, 12);
            this.label7.TabIndex = 0;
            this.label7.Text = "COM Port : ";
            // 
            // label8
            // 
            this.label8.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(28, 52);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(63, 12);
            this.label8.TabIndex = 0;
            this.label8.Text = "Baud Rate : ";
            // 
            // label9
            // 
            this.label9.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(37, 130);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(54, 12);
            this.label9.TabIndex = 0;
            this.label9.Text = "Stop bits : ";
            // 
            // label10
            // 
            this.label10.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(37, 91);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(54, 12);
            this.label10.TabIndex = 0;
            this.label10.Text = "Data bits : ";
            // 
            // label11
            // 
            this.label11.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(50, 169);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(41, 12);
            this.label11.TabIndex = 0;
            this.label11.Text = "Parity : ";
            // 
            // label12
            // 
            this.label12.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(16, 210);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(75, 12);
            this.label12.TabIndex = 0;
            this.label12.Text = "Handshaking : ";
            // 
            // comboBox_SerialPort_COMPort
            // 
            this.comboBox_SerialPort_COMPort.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBox_SerialPort_COMPort.FormattingEnabled = true;
            this.comboBox_SerialPort_COMPort.Location = new System.Drawing.Point(97, 9);
            this.comboBox_SerialPort_COMPort.Name = "comboBox_SerialPort_COMPort";
            this.comboBox_SerialPort_COMPort.Size = new System.Drawing.Size(89, 20);
            this.comboBox_SerialPort_COMPort.TabIndex = 1;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Controls.Add(this.tabControl1, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 60F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1072, 618);
            this.tableLayoutPanel1.TabIndex = 1;
            // 
            // comboBox_SerialPort_BaudRate
            // 
            this.comboBox_SerialPort_BaudRate.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBox_SerialPort_BaudRate.AutoCompleteCustomSource.AddRange(new string[] {
            "9600",
            "14400",
            "19200"});
            this.comboBox_SerialPort_BaudRate.FormattingEnabled = true;
            this.comboBox_SerialPort_BaudRate.Location = new System.Drawing.Point(97, 48);
            this.comboBox_SerialPort_BaudRate.Name = "comboBox_SerialPort_BaudRate";
            this.comboBox_SerialPort_BaudRate.Size = new System.Drawing.Size(89, 20);
            this.comboBox_SerialPort_BaudRate.TabIndex = 1;
            // 
            // comboBox_SerialPort_DataBits
            // 
            this.comboBox_SerialPort_DataBits.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBox_SerialPort_DataBits.FormattingEnabled = true;
            this.comboBox_SerialPort_DataBits.Items.AddRange(new object[] {
            "5",
            "6",
            "7",
            "8",
            "9"});
            this.comboBox_SerialPort_DataBits.Location = new System.Drawing.Point(97, 87);
            this.comboBox_SerialPort_DataBits.Name = "comboBox_SerialPort_DataBits";
            this.comboBox_SerialPort_DataBits.Size = new System.Drawing.Size(89, 20);
            this.comboBox_SerialPort_DataBits.TabIndex = 1;
            // 
            // comboBox_SerialPort_StopBits
            // 
            this.comboBox_SerialPort_StopBits.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBox_SerialPort_StopBits.FormattingEnabled = true;
            this.comboBox_SerialPort_StopBits.Items.AddRange(new object[] {
            "1",
            "1.5",
            "2"});
            this.comboBox_SerialPort_StopBits.Location = new System.Drawing.Point(97, 126);
            this.comboBox_SerialPort_StopBits.Name = "comboBox_SerialPort_StopBits";
            this.comboBox_SerialPort_StopBits.Size = new System.Drawing.Size(89, 20);
            this.comboBox_SerialPort_StopBits.TabIndex = 1;
            // 
            // comboBox_SerialPort_Parity
            // 
            this.comboBox_SerialPort_Parity.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBox_SerialPort_Parity.FormattingEnabled = true;
            this.comboBox_SerialPort_Parity.Items.AddRange(new object[] {
            "None"});
            this.comboBox_SerialPort_Parity.Location = new System.Drawing.Point(97, 165);
            this.comboBox_SerialPort_Parity.Name = "comboBox_SerialPort_Parity";
            this.comboBox_SerialPort_Parity.Size = new System.Drawing.Size(89, 20);
            this.comboBox_SerialPort_Parity.TabIndex = 1;
            // 
            // comboBox_SerialPort_Handshaking
            // 
            this.comboBox_SerialPort_Handshaking.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBox_SerialPort_Handshaking.FormattingEnabled = true;
            this.comboBox_SerialPort_Handshaking.Items.AddRange(new object[] {
            "None"});
            this.comboBox_SerialPort_Handshaking.Location = new System.Drawing.Point(97, 206);
            this.comboBox_SerialPort_Handshaking.Name = "comboBox_SerialPort_Handshaking";
            this.comboBox_SerialPort_Handshaking.Size = new System.Drawing.Size(89, 20);
            this.comboBox_SerialPort_Handshaking.TabIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1072, 618);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "Form1";
            this.Text = "L.E.A.P Control Pane";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.groupBox_SerialPort.ResumeLayout(false);
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel3.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox_R_State_Ready;
        private System.Windows.Forms.TextBox textBox_R_State_Dircetion;
        private System.Windows.Forms.TextBox textBox_R_State_Limit;
        private System.Windows.Forms.TextBox textBox_R_State_AnglePOT;
        private System.Windows.Forms.TextBox textBox_R_State_FrontFSR;
        private System.Windows.Forms.TextBox textBox_R_State_BackFSR;
        private System.Windows.Forms.GroupBox groupBox_SerialPort;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.ComboBox comboBox_SerialPort_COMPort;
        private System.Windows.Forms.ComboBox comboBox_SerialPort_BaudRate;
        private System.Windows.Forms.ComboBox comboBox_SerialPort_DataBits;
        private System.Windows.Forms.ComboBox comboBox_SerialPort_StopBits;
        private System.Windows.Forms.ComboBox comboBox_SerialPort_Parity;
        private System.Windows.Forms.ComboBox comboBox_SerialPort_Handshaking;
        private System.IO.Ports.SerialPort serialPort1;
    }
}

