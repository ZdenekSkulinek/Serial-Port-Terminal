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
#include "SerialSettingsForm.h"
#include "SerialDataSource.h"

namespace serialTerminal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SerialForm
	/// </summary>
	public ref class SerialForm : public System::Windows::Forms::Form
	{
		
	public:
		
		delegate void SetTextDelegate(String^ text);

		SerialForm(System::String^ portname)
		{
			portName=portname;

			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	private: System::Windows::Forms::TextBox^  textBox;
	public: 

	public: 
	private: System::Windows::Forms::Button^  SendButton;



	public: 



	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		SerialDataSource^ PortData;

		~SerialForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  outBox;
	
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		protected: 
		System::String^ portName;
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->outBox = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox = (gcnew System::Windows::Forms::TextBox());
			this->SendButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// outBox
			// 
			this->outBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->outBox->BackColor = System::Drawing::SystemColors::Control;
			this->outBox->Location = System::Drawing::Point(0, 0);
			this->outBox->Name = L"outBox";
			this->outBox->ReadOnly = true;
			this->outBox->Size = System::Drawing::Size(283, 103);
			this->outBox->TabIndex = 1;
			this->outBox->TabStop = false;
			this->outBox->Text = L"";
			// 
			// textBox
			// 
			this->textBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox->Location = System::Drawing::Point(0, 109);
			this->textBox->Multiline = true;
			this->textBox->Name = L"textBox";
			this->textBox->Size = System::Drawing::Size(193, 58);
			this->textBox->TabIndex = 1;
			this->textBox->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &SerialForm::textBox_KeyUp);
			// 
			// SendButton
			// 
			this->SendButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->SendButton->Location = System::Drawing::Point(199, 109);
			this->SendButton->Name = L"SendButton";
			this->SendButton->Size = System::Drawing::Size(84, 53);
			this->SendButton->TabIndex = 2;
			this->SendButton->Text = L"Send";
			this->SendButton->UseVisualStyleBackColor = true;
			this->SendButton->Click += gcnew System::EventHandler(this, &SerialForm::SendButton_Click);
			// 
			// SerialForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 162);
			this->Controls->Add(this->SendButton);
			this->Controls->Add(this->textBox);
			this->Controls->Add(this->outBox);
			this->MinimumSize = System::Drawing::Size(300, 200);
			this->Name = L"SerialForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &SerialForm::SerialForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &SerialForm::SerialForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	public: System::String^ GetPortName(){
				return portName;
			}
			/*
	public: void SetText(String^ text)
        {
			static int invokescnt=0;
            // InvokeRequired required compares the thread ID of the 
            // calling thread to the thread ID of the creating thread. 
            // If these threads are different, it returns true. 
            if (this->outBox->InvokeRequired)
            {
				//invokescnt++;
                SetTextDelegate^ d = 
                    gcnew SetTextDelegate(this, &SerialForm::SetText);
                this->Invoke(d, gcnew array<Object^> { text });
            }
            else
            {
				//invokescnt--;
				//if(invokescnt<0) invokescnt=0;
                this->outBox->Rtf = text;
            }
        }*/
	public: void SetText(String^ text)
        {
            // InvokeRequired required compares the thread ID of the 
            // calling thread to the thread ID of the creating thread. 
            // If these threads are different, it returns true. 
            //if (this->outBox->InvokeRequired)
            {
                SetTextDelegate^ d = 
                    gcnew SetTextDelegate(this, &SerialForm::SetText2);
                this->Invoke(d, gcnew array<Object^> { text });
            }

        }
		protected: void SetText2(String^ text)
        {
                if(PortData && this) this->outBox->Rtf = text;
        }
	public: System::Void OnSettings() {
			 
				 SerialSettingsForm^ sf=gcnew SerialSettingsForm(PortData);
				 sf->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &SerialForm::SerialSettingsForm_Closed);
				 sf->Show();
			 }
	
private: void SerialSettingsForm_Closed(System::Object^ sender,System::ComponentModel::CancelEventArgs^ e)
			{

			}
	private: System::Void SerialForm_Load(System::Object^  sender, System::EventArgs^  e) {
				this->Name = this->portName;
				this->Text = this->portName;

				PortData= gcnew SerialDataSource(portName, gcnew SerialDataSource::RefreshDelegate(this,&SerialForm::SetText));
				String^ rv=PortData->Open();

				if(rv)
				{
					 MessageBox::Show(rv,"Port Opening Error", MessageBoxButtons::OK,MessageBoxIcon::Exclamation);
					 Close();
				}
			 }
	private: System::Void SerialForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 PortData->Close();
				 PortData=nullptr;
			 }

private: System::Void textBox_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {

			 if ( e->Control && e->KeyCode == Keys::Enter )
			 {
				 if(textBox->Text->Length<=2) {textBox->Text=gcnew String("");return;}
				PortData->Send(textBox->Text->Remove(textBox->Text->Length-2));
				textBox->Text=gcnew String("");
			 }
		 }
private: System::Void SendButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(textBox->Text->Length==0) return;
			 PortData->Send(textBox->Text);
			 textBox->Text=gcnew String("");
			 textBox->Focus();
		 }
};
}
