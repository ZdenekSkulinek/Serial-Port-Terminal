/* Serial port terminal
*
* This program demonstrates usage of Serial port converter
* under MS Windows 10. 
*
* Copyright (C) 2013 Zdenìk Skulínek
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "StdAfx.h" 
#include "SerialDataSource.h"
#include <string.h>
#include <malloc.h>
#include <process.h>


const char* RtfEpilog="\\cf0\\lang1033\\f1\\par}";
const char* RtfProlog="{\\rtf1\\ansi\\ansicpg1250\\deff0\\deflang1029{\\fonttbl{\\f0\\fnil\\fcharset238 Calibri;}{\\f1\\fnil\\fcharset0 Calibri;}}\n\
{\\colortbl ;\\red255\\green0\\blue0;\\red0\\green176\\blue80;\\red75\\green172\\blue198;}\n\
{\\*\\generator Msftedit 5.41.21.2510;}\\viewkind4\\uc1\\pard\\sa200\\sl240\\slmult1\\cf1\\f0\\fs22\n";

namespace serialTerminal{

	SerialDataSource::SerialDataSource(System::String^ portname, RefreshDelegate^ customdelegate)
	{
		m_LinesCount=0;
		m_MaxLines=MAX_LINES_HISTORY;
		m_NewestAtTop=NEWEST_AT_TOP;
		m_PortName=portname;
		m_Delegate=customdelegate;
		m_Port=nullptr;
		m_Mutex=gcnew System::Threading::Mutex();
	}


	System::String^ SerialDataSource::Open()
	{
		System::String^retval=nullptr;

		try{
			
			m_Port=gcnew System::IO::Ports::SerialPort(m_PortName);
			System::Threading::ThreadStart^ myThreadDelegate = gcnew System::Threading::ThreadStart(this, &serialTerminal::SerialDataSource::SerialReadThread);
			m_ReadThread = gcnew System::Threading::Thread(myThreadDelegate);
			m_Port->ReadTimeout=500;
			m_Port->Open();
		}
		catch(System::Exception^ e){
			retval= e->Message;
		}
		if(!retval) 
			{
				AddText(LINE_SYSTEM,gcnew System::String("Port opened."));
				m_ReadThread->Start();
			}
		return retval;
	}


	void SerialDataSource::Close()
	{		
		AddText(LINE_SYSTEM,gcnew System::String("Port closed."));
		m_ReadThread=nullptr;
		if(m_Port) m_Port->Close();
		m_Port=nullptr;
		
	}



	void SerialDataSource::Send(System::String^ text)
	{
		if(m_Port)
		{
			System::String^ ex=nullptr;
			try
			{
				m_Port->Write(text);
				m_Port->Write(gcnew System::String("\x08"));
			}
			catch(System::Exception^ e) {
				ex=e->Message;
			};
			if(ex) AddText(LINE_SYSTEM,ex);
			else AddText(LINE_OUT,text);
		}
	}


	void SerialDataSource::SerialReadThread()
	{
		char Buffer[MAX_LINE_SIZE+1];
		int pos=0;
		System::String^ ex=nullptr;

		while(m_Port)
		{
			int c=-1;
			try{
				c=m_Port->ReadChar();
			}
			catch (System::TimeoutException ^ e) { 
			}
			catch(System::Exception^ e) {
				ex=e->Message;
			};
			if(c==-1) continue;
			if(ex) {
				AddText(LINE_SYSTEM,ex);
				ex=nullptr;
				continue;
			}
			
			if(c==8)
				{
					if(pos==0) continue;
					Buffer[pos]=0;
					AddText(LINE_IN,gcnew System::String(Buffer));
					pos=0;
					continue;
				}
			Buffer[pos]=c;
			pos++;
			if(pos>=MAX_LINE_SIZE)
				{
					Buffer[pos]=0;
					AddText(LINE_IN,gcnew System::String(Buffer));
					pos=0;
				}
		}
	}


	int SerialDataSource::RtfStrLen(System::String^ line)
	{
		int len=0;
		for(int i=0;i<line->Length;i++)
			switch(line[i])
			{
			case '{':len+=2;break;
			case '}':len+=2;break;
			case '\\':len+=2;break;
			case '\n':len+=6;break;
			default:len++;
			}
		return len;
	}


	int SerialDataSource::RtfStrCpy(char* dest, System::String^ src)
	{
		char* str=dest;
		for(int i=0;i<src->Length;i++)
			switch(src[i])
			{
			case '{':*str='\\';str++;*str='{';str++;break;
			case '}':*str='\\';str++;*str='}';str++;break;
			case '\\':*str='\\';str++;*str='\\';str++;break;
			case '\n':strcpy(str, "\\line ");str+=6;break;
			default:*str=(char)src[i];str++;
			}
		return str-dest;
	}

	System::String^ SerialDataSource::CreateRtf()
	{
		int chrlen=0;
		for each (SerialLine^ ln in m_Lines)
		{
			chrlen+=RtfStrLen(ln->m_String);
		}
		chrlen+=strlen(RtfProlog)+m_LinesCount*(5/*\cfX */+5/*\par\n */)+strlen(RtfEpilog)+1/*zero*/;
		char *sdata=(char*)malloc(chrlen);
		if(sdata)
		{
			char* ptr=sdata;
			strcpy(ptr,RtfProlog);
			ptr+=strlen(RtfProlog);
			for each (SerialLine^ ln in m_Lines)
			{
				switch(ln->m_Type)
				{
				case LINE_IN:strcpy(ptr,"\\cf1 ");ptr+=5;break;
				case LINE_OUT:strcpy(ptr,"\\cf2 ");ptr+=5;break;
				case LINE_SYSTEM:strcpy(ptr,"\\cf3 ");ptr+=5;break;
				}
				ptr+=RtfStrCpy(ptr, ln->m_String);
				strcpy(ptr,"\\par\n");
				ptr+=5;
			}
			strcpy(ptr,RtfEpilog);
			ptr+=strlen(RtfEpilog);
			*ptr=0;
		}
		System::String^ retval=gcnew System::String(sdata);
		if(sdata) free(sdata);
		return retval;
	}


	void SerialDataSource::AddText(enum ESerialLineType type, System::String^ text)
	{
		SerialLine^ ln=gcnew SerialLine();
		ln->m_Type=type;
		ln->m_String=text;
		System::String^ rtfdoc;


		m_Mutex->WaitOne();
		if(m_NewestAtTop)
		{
			if(m_LinesCount>=m_MaxLines)
			{
				m_LinesCount--;
				m_Lines.RemoveAt(m_LinesCount);
			}
			m_Lines.Insert(0,ln);
			m_LinesCount++;
		}
		else{
			if(m_LinesCount>=m_MaxLines)
			{
				m_LinesCount--;
				m_Lines.RemoveAt(0);
			}
			m_Lines.Add(ln);
			m_LinesCount++;
		}
		rtfdoc=CreateRtf();
		m_Mutex->ReleaseMutex();

		m_Delegate->Invoke(rtfdoc);
	}


	SerialDataSource::~SerialDataSource()
	{
		m_Mutex=nullptr;
		if(m_Port) m_Port->Close();
	}

	System::String^ SerialDataSource::GetBaudrate()
	{
		return System::Convert::ToString(m_Port->BaudRate);
	}


	System::String^ SerialDataSource::GetDatabits()
	{
		return System::Convert::ToString(m_Port->DataBits);
	}


	System::String^ SerialDataSource::GetParity()
	{
		return m_Port->Parity.ToString();
	}


	System::String^ SerialDataSource::GetStopbits()
	{
		return m_Port->StopBits.ToString();
	}


	System::String^ SerialDataSource::GetFlowcontrol()
	{
		return m_Port->Handshake.ToString();
	}


	System::String^ SerialDataSource::Setup(System::String^ baudrate, System::String^ databits, System::String^ parity, System::String^ stopbits, System::String^ flowcontrol)
	{
		System::String^ retval=nullptr;
		char* prop=nullptr;

		int orig_br=m_Port->BaudRate;
		int orig_db=m_Port->DataBits;
		System::IO::Ports::Parity orig_p=m_Port->Parity;
		System::IO::Ports::StopBits orig_sb=m_Port->StopBits;
		System::IO::Ports::Handshake orig_h=m_Port->Handshake;

		try{
			prop="Baudrate: ";
			m_Port->BaudRate=System::Int32::Parse(baudrate);
			prop="Data Bits: ";
			m_Port->DataBits=System::Int32::Parse(databits);
			prop="Parity: ";
			m_Port->Parity=(System::IO::Ports::Parity)System::Enum::Parse(System::IO::Ports::Parity::typeid, parity);
			prop="Stop Bits: ";
			m_Port->StopBits=(System::IO::Ports::StopBits)System::Enum::Parse(System::IO::Ports::StopBits::typeid, stopbits);
			prop="Flow Control: ";
			m_Port->Handshake=(System::IO::Ports::Handshake)System::Enum::Parse(System::IO::Ports::Handshake::typeid, flowcontrol);
		}
		catch(System::Exception^ e){
			retval= System::String::Concat(gcnew System::String(prop),e->Message);
		}

		if(retval)
		{
			try{
				m_Port->BaudRate=orig_br;
				m_Port->DataBits=orig_db;
				m_Port->Parity=orig_p;
				m_Port->StopBits=orig_sb;
				m_Port->Handshake=orig_h;
			}
			catch(System::Exception^ e){
				retval= gcnew System::String("Sorry.. Internal Error. I can't return to valid state.");
			}
		};
		if(!retval)
		{
			System::String^ s=System::String::Format("Port set to {0} baud, {1} data bits, parity {2}, {3} stop bits and flow control {4}",baudrate, databits, parity, stopbits, flowcontrol);
			AddText(LINE_SYSTEM,s);
		}
		return retval;
	}
}
