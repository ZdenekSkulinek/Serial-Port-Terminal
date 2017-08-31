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
#include "SerialDataSource.h"

namespace serialTerminal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SerialSettingsForm
	/// </summary>
	public ref class SerialSettingsForm : public System::Windows::Forms::Form
	{
		SerialDataSource^ PortData;
	public:
		SerialSettingsForm(SerialDataSource^ port)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			PortData=port;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SerialSettingsForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ComboBox^  comboBox_BaudRate;
	private: System::Windows::Forms::ComboBox^  comboBox_DataBits;
	private: System::Windows::Forms::ComboBox^  comboBox_Parity;
	private: System::Windows::Forms::ComboBox^  comboBox_StopBits;
	private: System::Windows::Forms::ComboBox^  comboBox_FlowControl;
	private: System::Windows::Forms::Button^  OKButton;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->comboBox_BaudRate = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_DataBits = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_Parity = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_StopBits = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_FlowControl = (gcnew System::Windows::Forms::ComboBox());
			this->OKButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Baud Rate";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 40);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(50, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Data Bits";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 68);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(33, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Parity";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 96);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(49, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Stop Bits";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(12, 124);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(65, 13);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Flow Control";
			// 
			// comboBox_BaudRate
			// 
			this->comboBox_BaudRate->FormattingEnabled = true;
			this->comboBox_BaudRate->Items->AddRange(gcnew cli::array< System::Object^  >(15) {L"110", L"300", L"600", L"1200", L"2400", 
				L"4800", L"9600", L"14440", L"19200", L"38400", L"57600", L"115200", L"230400", L"460800", L"921600"});
			this->comboBox_BaudRate->Location = System::Drawing::Point(93, 12);
			this->comboBox_BaudRate->Name = L"comboBox_BaudRate";
			this->comboBox_BaudRate->Size = System::Drawing::Size(121, 21);
			this->comboBox_BaudRate->TabIndex = 5;
			// 
			// comboBox_DataBits
			// 
			this->comboBox_DataBits->FormattingEnabled = true;
			this->comboBox_DataBits->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"7", L"8"});
			this->comboBox_DataBits->Location = System::Drawing::Point(93, 37);
			this->comboBox_DataBits->Name = L"comboBox_DataBits";
			this->comboBox_DataBits->Size = System::Drawing::Size(121, 21);
			this->comboBox_DataBits->TabIndex = 6;
			// 
			// comboBox_Parity
			// 
			this->comboBox_Parity->FormattingEnabled = true;
			this->comboBox_Parity->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"None", L"Even", L"Odd", L"Mark", L"Space"});
			this->comboBox_Parity->Location = System::Drawing::Point(93, 65);
			this->comboBox_Parity->Name = L"comboBox_Parity";
			this->comboBox_Parity->Size = System::Drawing::Size(121, 21);
			this->comboBox_Parity->TabIndex = 7;
			// 
			// comboBox_StopBits
			// 
			this->comboBox_StopBits->FormattingEnabled = true;
			this->comboBox_StopBits->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"One", L"Two", L"OnePointFive"});
			this->comboBox_StopBits->Location = System::Drawing::Point(93, 93);
			this->comboBox_StopBits->Name = L"comboBox_StopBits";
			this->comboBox_StopBits->Size = System::Drawing::Size(121, 21);
			this->comboBox_StopBits->TabIndex = 8;
			// 
			// comboBox_FlowControl
			// 
			this->comboBox_FlowControl->FormattingEnabled = true;
			this->comboBox_FlowControl->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"None", L"XOnXOff", L"RequestToSend", 
				L"RequestToSendXOnXOff"});
			this->comboBox_FlowControl->Location = System::Drawing::Point(93, 121);
			this->comboBox_FlowControl->Name = L"comboBox_FlowControl";
			this->comboBox_FlowControl->Size = System::Drawing::Size(121, 21);
			this->comboBox_FlowControl->TabIndex = 9;
			// 
			// OKButton
			// 
			this->OKButton->Location = System::Drawing::Point(217, 153);
			this->OKButton->Name = L"OKButton";
			this->OKButton->Size = System::Drawing::Size(75, 23);
			this->OKButton->TabIndex = 10;
			this->OKButton->Text = L"OK";
			this->OKButton->UseVisualStyleBackColor = true;
			this->OKButton->Click += gcnew System::EventHandler(this, &SerialSettingsForm::OKButton_Click);
			// 
			// SerialSettingsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(303, 182);
			this->Controls->Add(this->OKButton);
			this->Controls->Add(this->comboBox_FlowControl);
			this->Controls->Add(this->comboBox_StopBits);
			this->Controls->Add(this->comboBox_Parity);
			this->Controls->Add(this->comboBox_DataBits);
			this->Controls->Add(this->comboBox_BaudRate);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"SerialSettingsForm";
			this->Text = L"SerialSettingsForm";
			this->Load += gcnew System::EventHandler(this, &SerialSettingsForm::SerialSettingsForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SerialSettingsForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 String^ name=String::Concat(gcnew String("Setting for "),PortData->GetPortName());
				 this->Text = name;

				 comboBox_BaudRate->SelectedItem=PortData->GetBaudrate();
				 comboBox_DataBits->SelectedItem=PortData->GetDatabits();
				 comboBox_Parity->SelectedItem=PortData->GetParity();
				 comboBox_StopBits->SelectedItem=PortData->GetStopbits();
				 comboBox_FlowControl->SelectedItem=PortData->GetFlowcontrol();
			 }
private: System::Void OKButton_Click(System::Object^  sender, System::EventArgs^  e) {
				String^ rv=PortData->Setup(
					comboBox_BaudRate->SelectedItem->ToString(),
					comboBox_DataBits->SelectedItem->ToString(),
					comboBox_Parity->SelectedItem->ToString(),
					comboBox_StopBits->SelectedItem->ToString(),
					comboBox_FlowControl->SelectedItem->ToString());
				if(!rv) Close();
				else 
					{
						MessageBox::Show(rv,"Port Setting Error", MessageBoxButtons::OK,MessageBoxIcon::Exclamation);
						comboBox_BaudRate->SelectedItem=PortData->GetBaudrate();
						comboBox_DataBits->SelectedItem=PortData->GetDatabits();
						comboBox_Parity->SelectedItem=PortData->GetParity();
						comboBox_StopBits->SelectedItem=PortData->GetStopbits();
						comboBox_FlowControl->SelectedItem=PortData->GetFlowcontrol();
					}


		 }
};
}
