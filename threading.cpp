#include "stdafx.h"

using namespace System;
using namespace System::Threading;

public ref class Thread_Examlpe {

public: static void ThreadProc()
{

for (int i = 0; i < 10; i++)
{
Console::WriteLine("Test_Program");
Console::WriteLine(i); Thread::Sleep(0);
}
}
};

int main()
{

Console::WriteLine("Start_Thread");

Thread^ oThread = gcnew Thread( gcnew ThreadStart(
&Thread_Examlpe::ThreadProc ) );
oThread->Start();

for (int i = 0; i < 4; i++)
{

Console::WriteLine("Main_Thread..do_something");
Thread::Sleep(0);
}

Console::WriteLine( "Main_Thread_to_wait_until_ThreadProc_ends." );
oThread->Join();
Console::WriteLine( "Main_Thread:_ThreadProc.Join_has returned." );
Console::ReadLine();

return 0;
}