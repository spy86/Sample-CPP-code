#include "database.h"

#include "stdafx.h"

using namespace System;
using namespace System::Data;
using namespace System::Data::OleDb;
using namespace System::Data::SqlClient;

ref struct MyEventHandler
{
static void StateChange(Object^ sender, StateChangeEventArgs^ e)
{
Console::WriteLine(e->CurrentState.ToString());
}
};

void main()
{
OleDbConnection^ myOleDbConnection = nullptr;
SqlConnection^ mySqlConnection = nullptr;
OleDbConnectionStringBuilder^ connectionBuilder = gcnew OleDbConnectionStringBuilder();
connectionBuilder->Provider = "Microsoft.Jet.OLEDB.4.0";
connectionBuilder->DataSource = "music.mdb";

myOleDbConnection = gcnew OleDbConnection(connectionBuilder->ToString());
myOleDbConnection->Open();
SqlConnectionStringBuilder^ connectionBuilder2 =gcnew SqlConnectionStringBuilder();
connectionBuilder2->DataSource = "localhost";
connectionBuilder2->InitialCatalog = "ultramax";
connectionBuilder2->UserID = "sa";
connectionBuilder2->Password = "";

mySqlConnection = gcnew SqlConnection(connectionBuilder2->ToString());
mySqlConnection->StateChange += gcnew StateChangeEventHandler(MyEventHandler::StateChange);

mySqlConnection->Open();

Console::WriteLine("Database: {0}", mySqlConnection->Database);
Console::WriteLine("DataSource: {0}", mySqlConnection->DataSource);
Console::WriteLine("ServerVersion: {0}",mySqlConnection->ServerVersion);
Console::WriteLine("Workstation ID: {0}",mySqlConnection->WorkstationId);
myOleDbConnection->Close();
mySqlConnection->Close();
}