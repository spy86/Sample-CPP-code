#include "stdafx.h"
#include

using namespace System;
using namespace System::Threading;
using namespace System::Diagnostics;
using namespace System::Diagnostics::Tracing;
ref class IsThreadPool
{
public:

static void ThreadMethod()
{
Console::WriteLine( "ThreadOne, executing ThreadMethod, "
"is {0}from the thread pool.", Thread::CurrentThread->IsThreadPoolThread ? (String^)"" : "not " );
}

static void WorkMethod( Object^ stateInfo )
{
Console::WriteLine( "ThreadTwo, executing WorkMethod, "
"is {0}from the thread pool.", Thread::CurrentThread->IsThreadPoolThread ? (String^)"" : "not " );

dynamic_cast(stateInfo)->Set();
}

};

int main()
{

AutoResetEvent^ autoevent = gcnew AutoResetEvent(false);
Thread^ regularThread = gcnew Thread(gcnew ThreadStart(&IsThreadPool::ThreadMethod));
regularThread->Start();
ThreadPool::QueueUserWorkItem(gcnew WaitCallback(&IsThreadPool::WorkMethod),autoevent);

regularThread->Join();
autoevent->WaitOne();
getch();
}