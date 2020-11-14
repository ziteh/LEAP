using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

// Bluetooth
using InTheHand.Net;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;

namespace LEAP_ControlPanel
{
    class Bluetooth
    {
        public  void Main(string[] args)
        {
            BluetoothRadio bluetoothRadio = BluetoothRadio.PrimaryRadio;
            if (bluetoothRadio == null)
            {
                MessageBox.Show("沒有找到本機藍牙設備!");
            }
            else
            {
                Bluetooth p = new Bluetooth();
                p.localAdapterInfo(bluetoothRadio);
                p.openDoor();
            }
        }

        /**
         * 連接目標藍牙設備發送開門指令
         * **/
        public void openDoor()
        {
            BluetoothClient cli = new BluetoothClient();
            BluetoothAddress addr = null;
            BluetoothEndPoint ep = null;
            try
            {
                // [注意2]：要注意MAC地址中字節的對應關係，直接來看順序是相反的，例如
                // 如下對應的MAC地址爲 98:d3:31:90:60:26
                addr = new BluetoothAddress(new byte[] { 0x26, 0x60, 0x90, 0x31, 0xd3, 0x98 });
                ep = new BluetoothEndPoint(addr, BluetoothService.SerialPort);
                cli.Connect(ep); // 連接藍牙
                if (cli.Connected)
                {
                    Stream peerStream = cli.GetStream();
                    peerStream.WriteByte(0xBB); // 發送開門指令
                }
            }
            catch (SocketException e)
            {
                MessageBox.Show(e.Message);
            }
            finally
            {
                if (cli != null)
                {
                    // [注意3]：要延遲一定時間(例如1000毫秒)
                    //避免因連接後又迅速斷開而導致藍牙進入異常(傻逼)狀態
                    Thread.Sleep(1000);
                    cli.Close();
                }
            }
        }

        /**
         * 
         * 顯示本地藍牙的信息
         * 
         * **/
        public void localAdapterInfo(BluetoothRadio bluetoothRadio)
        {
            MessageBox.Show("ClassOfDevice: " + bluetoothRadio.ClassOfDevice);
            MessageBox.Show("HardwareStatus: " + bluetoothRadio.HardwareStatus);
            MessageBox.Show("HciRevision: " + bluetoothRadio.HciRevision);
            MessageBox.Show("HciVersion: " + bluetoothRadio.HciVersion);
            MessageBox.Show("LmpSubversion: " + bluetoothRadio.LmpSubversion);
            MessageBox.Show("LmpVersion: " + bluetoothRadio.LmpVersion);
            MessageBox.Show("LocalAddress: " + bluetoothRadio.LocalAddress);
            MessageBox.Show("Manufacturer: " + bluetoothRadio.Manufacturer);
            MessageBox.Show("Mode: " + bluetoothRadio.Mode);
            MessageBox.Show("Name: " + bluetoothRadio.Name);
            MessageBox.Show("Remote:" + bluetoothRadio.Remote);
            MessageBox.Show("SoftwareManufacturer: " + bluetoothRadio.SoftwareManufacturer);
            MessageBox.Show("StackFactory: " + bluetoothRadio.StackFactory);
        }
    }
}
