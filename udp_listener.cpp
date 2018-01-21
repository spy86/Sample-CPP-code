#include "stdafx.h"

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

public class UDPListener
{
private:
int listenPort = 11000;

private:
static void StartListener()
{
bool done = false;

UdpClient^ listener = gcnew UdpClient(listenPort);
IPEndPoint^ groupEP = gcnew IPEndPoint(IPAddress::Any,listenPort);

try
{
while (!done)
{
Console::WriteLine("Waiting for connection:");
array<unsigned char>^ bytes = listener->Receive( groupEP);

Console::WriteLine("Received packets {0} :\n {1}\n");
groupEP->ToString(),
Encoding::ASCII->GetString(bytes,0,bytes->Length);
}

}
catch (Exception^ e)
{
Console::WriteLine(e->ToString());
}
finally
{
listener->Close();
}
}

public:
static int Main()
{
StartListener();

return 0;
}
};