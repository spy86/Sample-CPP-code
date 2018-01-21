
#include "stdafx.h"
using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;
using namespace System::Text;

ref class TcpServer
{
public:
void ProcessThread(Object ^clientObj);
};

void TcpServer::ProcessThread(Object ^clientObj)
{
Socket^ client = (Socket^)clientObj;
IPEndPoint^ clientEP = (IPEndPoint^)client->RemoteEndPoint;

Console::WriteLine(clientEP->Address);
Console::WriteLine(clientEP->Port);

array<unsigned char>^ msg = Encoding::ASCII->GetBytes("success ...");
client->Send(msg);

int rcv;
while (true)
{
msg = gcnew array<unsigned char>(1024);

if ((rcv = client->Receive(msg)) == 0)
break;

Console::WriteLine(clientEP->Port);
Console::WriteLine(Encoding::ASCII->GetString(msg, 0, rcv));

client->Send(msg, rcv, SocketFlags::None);
}
client->Close();
Console::WriteLine(clientEP->Address);
Console::WriteLine(clientEP->Port);
}

void main()
{
TcpServer^ server = gcnew TcpServer();

TcpListener^ socket = gcnew TcpListener(IPAddress::Any, 12345);
socket->Start();

while(true)
{
Console::WriteLine("Waiting for a connection ....");
Socket^ client = socket->AcceptSocket();

Thread ^thr = gcnew Thread(
gcnew ParameterizedThreadStart(server, &TcpServer::ProcessThread));
thr->Start(client);
}
}
