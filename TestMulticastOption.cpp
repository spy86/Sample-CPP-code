#include "stdafx.h"

#using <System.dll>

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

public ref class TestMulticastOption
{
private:
   static IPAddress^ mcastAddress;
   static int mcastPort;
   static Socket^ mcastSocket;
   static MulticastOption^ mcastOption;

   static void MulticastOptionProperties()
   {
      Console::WriteLine( "multicast group: {0}", mcastOption->Group );
      Console::WriteLine( "multicast address: {0}", mcastOption->LocalAddress );

   }

   static void StartMulticast()
   {
      try
      {
         mcastSocket = gcnew Socket( AddressFamily::InterNetwork,SocketType::Dgram,ProtocolType::Udp );
         Console::Write( "enter the local IP address: " );
         IPAddress^ localIPAddr = IPAddress::Parse( Console::ReadLine() );

         EndPoint^ localEP = dynamic_cast<EndPoint^>(gcnew IPEndPoint( localIPAddr,mcastPort ));
         mcastSocket->Bind( localEP );

         mcastOption = gcnew MulticastOption( mcastAddress,localIPAddr );
         mcastSocket->SetSocketOption( SocketOptionLevel::IP, SocketOptionName::AddMembership, mcastOption );

      }
      catch ( Exception^ e )
      {
         Console::WriteLine( e );
      }

   }

   static void ReceiveBrodcastMessages()
   {
      bool done = false;
      array<Byte>^bytes = gcnew array<Byte>(100);
      IPEndPoint^ groupEP = gcnew IPEndPoint( mcastAddress,mcastPort );
      EndPoint^ remoteEP = dynamic_cast<EndPoint^>(gcnew IPEndPoint( IPAddress::Any,0 ));
      try
      {
         while (  !done )
         {
            Console::WriteLine( "waiting for the packages ......." );
            Console::WriteLine( "CTRL+C i DEAD ...." );
            mcastSocket->ReceiveFrom( bytes, remoteEP );
            Console::WriteLine( "received  {0} :\n {1}\n", groupEP, Encoding::ASCII->GetString( bytes, 0, bytes->Length ) );
         }
         mcastSocket->Close();
      }
      catch ( Exception^ e )
      {
         Console::WriteLine( e );
      }

   }

public:
   static void Main()
   {

      mcastAddress = IPAddress::Parse( "244.244.244.244" );
      mcastPort = 12345;

      StartMulticast();

      MulticastOptionProperties();

      ReceiveBrodcastMessages();
   }

};

int main()
{
   TestMulticastOption::Main();
}
