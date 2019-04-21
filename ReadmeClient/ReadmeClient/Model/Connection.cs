using System;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;

namespace Readme.Model
{

    public class Connection : IConnection
    {
        private Socket _socket;


        public Connection()
        {
            //******************************
            //connect to server in localhost
            var hostEntry = Dns.GetHostEntry("localhost");

            //later : try not foreach but single
            foreach (var address in hostEntry.AddressList)
            {
                if (address.AddressFamily != AddressFamily.InterNetwork)
                    continue;

                var ipe = new IPEndPoint(address, 5050);
                var tempSocket = new Socket(ipe.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                tempSocket.Connect(new IPEndPoint(address, 5050));

                if (tempSocket.Connected)
                {
                    _socket = tempSocket;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }

        public bool AskForReadme(string language, string project)
        {
            string request = GetRequest(language, project);
            Byte[] bytesSent = Encoding.ASCII.GetBytes(request);
            Byte[] bytesReceived = new Byte[256];
            string page = "";
            
            // Here goes all the work

            _socket.Send(bytesSent, bytesSent.Length, 0);

            // Receive server answer
            // Success scenario : json from github api about repo info
            int bytes = 0;

                // The following will block until the page is transmitted.
            do
            {
               bytes = _socket.Receive(bytesReceived, bytesReceived.Length, 0);
               page = page + Encoding.ASCII.GetString(bytesReceived, 0, bytes);
            }
            while (bytes > 0);


            return true;
        }

            
        private string GetRequest(string language, string project)
        {
            var request = "GET /search/";
            if (!string.IsNullOrWhiteSpace(project))
                request += $"repositories?q={project}+";

            if (string.IsNullOrWhiteSpace(language))
                request += $"language:{language}";

            request += "&sort=stars&order=desc HTTP/1.1\r\n" +
                "Host: api.github.com\r\n" +
                "Content-Length: 100\r\n" +
                "Content-Type: application/json\r\n";

            return request;
        }
    }
}
