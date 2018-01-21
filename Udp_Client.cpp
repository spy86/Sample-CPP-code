#include "stdafx.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text; 

namespace Jarloo::Listener
{
	internal class Program
	{
		private static void Main(string[] args)
		{
			UdpClient client = new UdpClient();
			client.ExclusiveAddressUse = false;
			IPEndPoint localEp = new IPEndPoint(IPAddress.Any, 2222);
			client.Client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
			client.ExclusiveAddressUse = false;
			client.Client.Bind(localEp);
			IPAddress multicastaddress = IPAddress.Parse("127.0.0.1");
			client.JoinMulticastGroup(multicastaddress);
			Console.WriteLine("Listening this will never quit so you will need to ctrl-c it");            

			while (true)
			{
				Byte[] data = client.Receive(ref localEp);
				string strData = Encoding.Unicode.GetString(data);
				Console.WriteLine(strData);
			}
		}
	}
}
