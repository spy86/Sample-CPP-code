#include "stdafx.h"
#using <system.xml.dll>
#include<iostream>
#include<conio.h>

using namespace System;
using namespace System::Xml;
using namespace std;
void main()
{
    XmlReader ^reader;
	reader = XmlReader::Create("c:\\users\\user\\desktop\\config.xml");
   while (reader->Read()){
            switch (reader->NodeType)
            {
                case XmlNodeType::Comment:
                    Console::WriteLine(reader->Depth);
                    Console::WriteLine(reader->Value);
                    break;
                case XmlNodeType::Element:
                    Console::WriteLine(reader->Depth);
                    Console::WriteLine(reader->Name);
                    if (reader->HasAttributes)
                    {
                        while (reader->MoveToNextAttribute())
                        {
                            Console::WriteLine(reader->Depth);
                            Console::WriteLine(reader->Name);
                            Console::WriteLine(reader->Value);
                        }
                        reader->MoveToElement();
                    }
                    if (reader->IsEmptyElement)
                    {
                        Console::WriteLine(reader->Depth);
                        Console::WriteLine(reader->Name);
                    }
                    break;
                case XmlNodeType::EndElement:
                    Console::WriteLine(reader->Depth);
                    Console::WriteLine(reader->Name);
                    break;
                case XmlNodeType::Text:
                    Console::WriteLine(reader->Depth);
                    Console::WriteLine(reader->Value);
                    break;
                case XmlNodeType::XmlDeclaration:
                    Console::WriteLine(reader->Depth);
                    Console::WriteLine(reader->Name);

                    if (reader->HasAttributes)
                    {
                        while (reader->MoveToNextAttribute())
                        {
                            Console::WriteLine(reader->Depth);
                            Console::WriteLine(reader->Name);
                            Console::WriteLine(reader->Value);
                        }
                    }
                    reader->MoveToElement();
                    Console::WriteLine(reader->Depth);
                    Console::WriteLine(reader->Name);
                    break;
                case XmlNodeType::Whitespace:
                    break;
                default:
                    Console::WriteLine("blad");
                    Console::WriteLine(reader->Depth);
                    Console::WriteLine(reader->Name);
                    Console::WriteLine(reader->Value);

            }
        }
   getch();
}
