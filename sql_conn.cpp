#include "stdafx.h"

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Configuration;

void main()
{
SqlConnection^ connection = gcnew SqlConnection();

connection->ConnectionString = "SQLConnection";

try
{
connection->Open();
Console::WriteLine("Connected to SQL database!");
}

catch (SqlException ^e)
{
Console::WriteLine("No connection to the SQL database {0}",
e->Message);
}

finally
{
connection->Close();
Console::WriteLine("The connection to the SQL database has been closed ...");
}
}