#include "stdafx.h" 

using namespace System;
using namespace System::Threading; 

ref class PrintTasks
{
public: static bool runFlag = true; 

public:
void PrintDigit(Object^ name) {
    while (runFlag) {
        Console::WriteLine((String^)name);
    }
} 

void PrintLetter(Object^ name) {
    while (runFlag) {
        Console::WriteLine((String^)name);
    }
} 

void PrintSlashes(Object^ name) {
    while (runFlag) {
        Console::WriteLine("/");
        Console::WriteLine("\\");
    }
}
}; 

int main(array<System::String ^> ^args)
{
PrintTasks ^tasks = gcnew PrintTasks();
array<Thread^> ^threads = gcnew array<Thread^>(37); 

for (int d=0; d<10; d++) {
    threads[d] = gcnew Thread ( gcnew ParameterizedThreadStart( tasks, &PrintTasks::PrintDigit ) );
    threads[d]->Start(d.ToString());
} 

for (wchar_t d='A'; d<='Z'; d++) {
    threads[10+d-'A'] = gcnew Thread ( gcnew ParameterizedThreadStart( tasks, &PrintTasks::PrintLetter ) );
    threads[10+d-'A']->Start(d.ToString());
} 

threads[36] = gcnew Thread ( gcnew ParameterizedThreadStart( tasks, &PrintTasks::PrintSlashes ) );
threads[36]->Start(""); 

Thread::Sleep(1000);
PrintTasks::runFlag=false; 

for (int i=0; i<37; i++) threads[i]->Abort(); 

return 0;
}