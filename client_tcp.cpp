#include "stdafx.h"

using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;

void main() {

TcpClient^ server;
StreamWriter^ writer;
StreamReader^ reader;
String^ msg;

server= gcnew TcpClient("127.0.0.1", 25201);
writer=gcnew StreamWriter(server->GetStream());
reader=gcnew StreamReader(server->GetStream());

msg="";
writer->WriteLine(msg);
writer->Flush();
msg = reader->ReadLine();

Console::WriteLine(msg);
Console::WriteLine("close connection");
server->Close();

}