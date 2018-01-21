#include "stdafx.h"

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

void main()
{
	UdpClient^ sock = gcnew UdpClient(9050);
	Console::WriteLine("Ready to broadcasts");

	sock->JoinMulticastGroup(IPAddress::Parse("127.0.0.1"),50);
	IPEndPoint^ iep = gcnew IPEndPoint(IPAddress::Any, 0);
	array<System::Byte>^ data = sock->Receive;
	String^ stringData = Encoding::ASCII->GetString(data, 0, data->Length);
	Console::WriteLine("received: {0}  from: {1}", stringData, iep->ToString());
	sock->Close();
}
