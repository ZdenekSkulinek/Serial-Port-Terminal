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

#pragma once
#using <mscorlib.dll>
#include <process.h>

#define NEWEST_AT_TOP true
#define MAX_LINES_HISTORY 500
#define MAX_LINE_SIZE  32768

namespace serialTerminal {

	enum ESerialLineType
	{
		LINE_IN=1,
		LINE_OUT=2,
		LINE_SYSTEM=3
	};

	public ref class SerialLine
	{
	public:
		enum ESerialLineType	m_Type;
		System::String^			m_String;
	};


	public ref class SerialDataSource
	{
		protected:
			int		m_LinesCount;
			int     m_MaxLines;
			bool	m_NewestAtTop;
			System::Collections::Generic::List<SerialLine^> m_Lines;

			System::String^ m_PortName;
			System::IO::Ports::SerialPort^ m_Port;
		public:
			delegate void RefreshDelegate(System::String^ text);
		protected:
			RefreshDelegate^ m_Delegate;
			System::Threading::Mutex^  m_Mutex;
			System::Threading::Thread^ m_ReadThread;
			void SerialReadThread();
		public:
			SerialDataSource(System::String^ portname, RefreshDelegate^ customdelegate);
			System::String^ Open();
			void Close();
			void AddText(enum ESerialLineType type, System::String^ text);
			void Send(System::String^ text);
			virtual ~SerialDataSource();

			System::String^ GetPortName(){return m_PortName;};
			System::String^ GetBaudrate();
			System::String^ GetDatabits();
			System::String^ GetParity();
			System::String^ GetStopbits();
			System::String^ GetFlowcontrol();
			System::String^ Setup(System::String^ baudrate, System::String^ databits, System::String^ parity, System::String^ stopbits, System::String^flowcontrol);

			int RtfStrLen(System::String^ line);
			int RtfStrCpy(char* dest, System::String^ src);
			System::String^ CreateRtf();
	};
}