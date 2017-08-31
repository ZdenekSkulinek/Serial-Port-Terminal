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
#include "SerialForm.h"

namespace serialTerminal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	int windowsCount;

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			windowsCount = 0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  windowToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem1;
	private: System::ComponentModel::IContainer^  components;

	
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->windowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
				this->windowToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->MdiWindowListItem = this->windowToolStripMenuItem;
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(452, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->newToolStripMenuItem, 
				this->optionToolStripMenuItem, this->exitToolStripMenuItem1});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"&File";
			this->fileToolStripMenuItem->DropDownOpening += gcnew System::EventHandler(this, &Form1::fileToolStripMenuItem_DropDownOpening);
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->newToolStripMenuItem->Text = L"&New";
			//this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::newToolStripMenuItem_Click);
			// 
			// optionToolStripMenuItem
			// 
			this->optionToolStripMenuItem->Enabled = false;
			this->optionToolStripMenuItem->Name = L"optionToolStripMenuItem";
			this->optionToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->optionToolStripMenuItem->Text = L"&Options";
			this->optionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::optionToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem1
			// 
			this->exitToolStripMenuItem1->Name = L"exitToolStripMenuItem1";
			this->exitToolStripMenuItem1->Size = System::Drawing::Size(152, 22);
			this->exitToolStripMenuItem1->Text = L"&Exit";
			this->exitToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem1_Click);
			// 
			// windowToolStripMenuItem
			// 
			this->windowToolStripMenuItem->Name = L"windowToolStripMenuItem";
			this->windowToolStripMenuItem->Size = System::Drawing::Size(63, 20);
			this->windowToolStripMenuItem->Text = L"&Window";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(452, 520);
			this->Controls->Add(this->menuStrip1);
			this->IsMdiContainer = true;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Serial Port terminal";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 
				 System::Windows::Forms::ToolStripMenuItem^  mi=dynamic_cast<System::Windows::Forms::ToolStripMenuItem^> (sender);
				 SerialForm^ sf=gcnew SerialForm(mi->Name);
				 sf->MdiParent=this;
				 sf->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::SerialForm_Closed);
				 windowsCount += 1;
				 this->optionToolStripMenuItem->Enabled = true;
				 sf->Show();
			 }

		

		private: void SerialForm_Closed(System::Object^ sender,System::ComponentModel::CancelEventArgs^ e)
			{
			windowsCount -= 1;
			if(windowsCount==0) this->optionToolStripMenuItem->Enabled = false;
			}

private: System::Void exitToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
				Application::Exit(); 
		 }
private: System::Void optionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			  SerialForm^ sf=static_cast<serialTerminal::SerialForm^>(this->ActiveMdiChild);
			  if(sf) sf->OnSettings();
		 }
private: System::Void fileToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e) {
		
			array<String^>^ serialPorts = nullptr;
			try
				{
				// Get a list of serial port names.
				serialPorts = System::IO::Ports::SerialPort::GetPortNames();
				}
			catch (Win32Exception^ ex)
				{
				Console::WriteLine(ex->Message);
				}

			this->newToolStripMenuItem->Enabled=false;
			this->newToolStripMenuItem->DropDownItems->Clear();
			if(!serialPorts || serialPorts->Length==0)
			{	
				return;
			}


			cli::array< System::Windows::Forms::ToolStripItem^  >^ miarr=gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(serialPorts->Length);
			int miarrIndex=0;
			SerialForm^ sf;//=static_cast<serialTerminal::SerialForm^>(this->ActiveMdiChild);
			for(int i=0;i<serialPorts->Length;i++)
			{
				int found=0;
				for ( int x = 0; x < this->MdiChildren->Length; x++ )
				{
					sf = dynamic_cast<serialTerminal::SerialForm^>(this->MdiChildren[ x ]);
					if(sf->GetPortName()->CompareTo(serialPorts[i])==0) 
						{
							found++;
							break;
						}
				}
				if(found) continue;
				System::Windows::Forms::ToolStripMenuItem^  mi=(gcnew System::Windows::Forms::ToolStripMenuItem());
				mi->Name = serialPorts[i];
				mi->Size = System::Drawing::Size(152, 22);
				mi->Text = serialPorts[i];
				mi->Click += gcnew System::EventHandler(this, &Form1::newToolStripMenuItem_Click);
				miarr[miarrIndex]=mi;
				miarrIndex++;
			}

			if(miarrIndex==0) return;
			cli::array< System::Windows::Forms::ToolStripItem^  >^ miarr2=gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(miarrIndex);
			System::Array::Copy(miarr, miarr2,miarrIndex);

			
			this->newToolStripMenuItem->Enabled=true;
			this->newToolStripMenuItem->DropDownItems->AddRange(miarr2);
			

		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

