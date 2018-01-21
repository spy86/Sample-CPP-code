#include"stdafx.h"
#include<conio.h>

using namespace System;
using namespace System::Threading;
using namespace System::Text;

const int numIterations = 1;
const int numThreads = 3;

ref class Test
{
public:

static Mutex^ mut = gcnew Mutex;
static void MyThreadProc()
{
for ( int i = 0; i < numIterations; i++ )
{
UseResource();

}
}

public:

static Mutex^ mut1 = gcnew Mutex;
static void MyThreadProc1()

{

for (int j = 0; j < numIterations; j++)
{

UseResource();

}

}

private:

static void UseResource()
{
mut->WaitOne();
Console::WriteLine( "{0} has entered protected the area", Thread::CurrentThread->Name );
Thread::Sleep( 500 );
Console::WriteLine( "{0} is leaving protected the area\r\n", Thread::CurrentThread->Name );
mut->ReleaseMutex();

mut1->WaitOne();
Console::WriteLine("{0} has entered protected area", Thread::CurrentThread->Name);
Thread::Sleep(500);
Console::WriteLine("{0} is leaving protected area \r\n",Thread::CurrentThread->Name);
mut1->ReleaseMutex();

}

};

int main()
{

for ( int i = 0; i < numThreads; i++ )
{
Thread^ myThread = gcnew Thread( gcnew ThreadStart( Test::MyThreadProc ) );
myThread->Name = String::Format( "Thread {0}", i + 1 );
myThread->Start();

}

for (int j = 0; j < numThreads; j++)
{
Thread^ myThread1 = gcnew Thread (gcnew ThreadStart(Test::MyThreadProc1));
myThread1->Name = String::Format("Thread {0}", j + 1);
myThread1->Start();
}
getch();
}