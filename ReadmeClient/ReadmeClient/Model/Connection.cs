using System;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;

namespace Readme.Model
{

    public class Connection : IConnection
    {
        private IPAddress _host;
        private IPEndPoint _hostep;
        private Socket _socket;


        public Connection()
        {
            string fileName = "c.dll";
            string path = Path.Combine(Environment.CurrentDirectory, @"Data\", fileName);

            /*_host = IPAddress.Parse("api.github.com");
            _hostep = new IPEndPoint(_host, 8080);
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);*/
        }

        public bool AskForReadme()
        {
            return DoSomethingInC(1) == 1 ? true : false;
        }

        [DllImport("D:\\VU\\4 pusmetis\\KompTinklai\\2UZD\\Readme\\Readme\\ConnectionDLL\\c.dll", EntryPoint = "DoSomethingInC")]
        public static extern int DoSomethingInC(int test);
    }
}
