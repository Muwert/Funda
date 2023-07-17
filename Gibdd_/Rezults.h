#pragma once
#include "Hash_Table.h"
#include<fstream>
#include <msclr\marshal_cppstd.h>
#include "Rezult_add.h"
#include "Otladka.h"

namespace Gibdd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Rezults
	/// </summary>

	std::vector <Rezult*> record_rezults = std::vector <Rezult*> (0);
	/// 
	public ref class Rezults : public System::Windows::Forms::Form
	{
	public:
		Rezults(void)
		{
			InitializeComponent();

		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Rezults()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::TextBox^ textBox2;

	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label4;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Button^ button11;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::TextBox^ textBox4;
	public protected: System::Windows::Forms::DateTimePicker^ dateTimePicker1;
	private:

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label3;
	public protected: System::Windows::Forms::DateTimePicker^ dateTimePicker2;
	private:
	private: System::Windows::Forms::TextBox^ textBox1;
	public protected:
	private: System::Windows::Forms::Button^ button12;


	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		/// 
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Rezults::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker2 = (gcnew System::Windows::Forms::DateTimePicker());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::Window;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(12, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(302, 29);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Справочник \"Результаты\"";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(803, 75);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(252, 29);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Поиск по дате сдачи:";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(660, 177);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(395, 34);
			this->textBox2->TabIndex = 7;
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox3->Location = System::Drawing::Point(660, 250);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(395, 34);
			this->textBox3->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(664, 218);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(391, 29);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Поиск по номеру удостоверения:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(655, 292);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(400, 29);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Поиск по длительности экзамена:";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Azure;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(1061, 101);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(36, 36);
			this->button1->TabIndex = 12;
			this->button1->Text = L"v";
			this->button1->UseVisualStyleBackColor = false;
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Azure;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(1061, 175);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(36, 36);
			this->button2->TabIndex = 13;
			this->button2->Text = L"v";
			this->button2->UseVisualStyleBackColor = false;
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::Azure;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(1061, 248);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(36, 36);
			this->button3->TabIndex = 14;
			this->button3->Text = L"v";
			this->button3->UseVisualStyleBackColor = false;
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::Azure;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(1061, 321);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(36, 36);
			this->button4->TabIndex = 15;
			this->button4->Text = L"v";
			this->button4->UseVisualStyleBackColor = false;
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::Azure;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button5->Location = System::Drawing::Point(847, 537);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(122, 36);
			this->button5->TabIndex = 16;
			this->button5->Text = L"Добавить";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &Rezults::button5_Click);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::Azure;
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button6->Location = System::Drawing::Point(975, 537);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(122, 36);
			this->button6->TabIndex = 17;
			this->button6->Text = L"Удалить";
			this->button6->UseVisualStyleBackColor = false;
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::Color::Azure;
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button7->Location = System::Drawing::Point(975, 603);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(122, 36);
			this->button7->TabIndex = 19;
			this->button7->Text = L"Экспорт";
			this->button7->UseVisualStyleBackColor = false;
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::Color::Azure;
			this->button8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button8->Location = System::Drawing::Point(847, 603);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(122, 36);
			this->button8->TabIndex = 18;
			this->button8->Text = L"Импорт";
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &Rezults::button8_Click);
			// 
			// button9
			// 
			this->button9->BackColor = System::Drawing::Color::Azure;
			this->button9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button9->Location = System::Drawing::Point(719, 576);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(122, 63);
			this->button9->TabIndex = 20;
			this->button9->Text = L"Окно отладки";
			this->button9->UseVisualStyleBackColor = false;
			this->button9->Click += gcnew System::EventHandler(this, &Rezults::button9_Click);
			// 
			// button10
			// 
			this->button10->BackColor = System::Drawing::Color::Azure;
			this->button10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button10->Location = System::Drawing::Point(145, 655);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(122, 36);
			this->button10->TabIndex = 22;
			this->button10->Text = L"Кандидаты";
			this->button10->UseVisualStyleBackColor = false;
			// 
			// button11
			// 
			this->button11->BackColor = System::Drawing::Color::Azure;
			this->button11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button11->Location = System::Drawing::Point(17, 655);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(122, 36);
			this->button11->TabIndex = 21;
			this->button11->Text = L"Инспекторы";
			this->button11->UseVisualStyleBackColor = false;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->richTextBox1->Location = System::Drawing::Point(17, 71);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(620, 566);
			this->richTextBox1->TabIndex = 23;
			this->richTextBox1->Text = L"";
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox4->Location = System::Drawing::Point(660, 324);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(395, 34);
			this->textBox4->TabIndex = 24;
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Location = System::Drawing::Point(660, 107);
			this->dateTimePicker1->MaxDate = System::DateTime(2023, 12, 31, 0, 0, 0, 0);
			this->dateTimePicker1->MinDate = System::DateTime(2013, 1, 1, 0, 0, 0, 0);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(395, 22);
			this->dateTimePicker1->TabIndex = 25;
			this->dateTimePicker1->Value = System::DateTime(2013, 1, 1, 0, 0, 0, 0);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(732, 145);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(323, 29);
			this->label6->TabIndex = 26;
			this->label6->Text = L"Поиск по номеру паспорта:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(803, 366);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(252, 58);
			this->label3->TabIndex = 27;
			this->label3->Text = L"Поиск по дате сдачи \r\nи номеру паспорта:";
			// 
			// dateTimePicker2
			// 
			this->dateTimePicker2->Location = System::Drawing::Point(660, 427);
			this->dateTimePicker2->MaxDate = System::DateTime(2023, 12, 31, 0, 0, 0, 0);
			this->dateTimePicker2->MinDate = System::DateTime(2013, 1, 1, 0, 0, 0, 0);
			this->dateTimePicker2->Name = L"dateTimePicker2";
			this->dateTimePicker2->Size = System::Drawing::Size(395, 22);
			this->dateTimePicker2->TabIndex = 28;
			this->dateTimePicker2->Value = System::DateTime(2013, 1, 1, 0, 0, 0, 0);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(660, 461);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(395, 34);
			this->textBox1->TabIndex = 29;
			// 
			// button12
			// 
			this->button12->BackColor = System::Drawing::Color::Azure;
			this->button12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button12->Location = System::Drawing::Point(1061, 459);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(36, 36);
			this->button12->TabIndex = 30;
			this->button12->Text = L"v";
			this->button12->UseVisualStyleBackColor = false;
			// 
			// Rezults
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightSteelBlue;
			this->ClientSize = System::Drawing::Size(1121, 709);
			this->Controls->Add(this->button12);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->dateTimePicker2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->dateTimePicker1);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button11);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Rezults";
			this->Text = L"Результаты";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*richTextBox1->Clear();
	auto f = System::IO::File::OpenText("Rezults.txt");
	auto s = f->ReadToEnd();
	richTextBox1->Text = s + "\n";
	f->Close();*/

	int k = 2;
	richTextBox1->Clear();
	auto reader = System::IO::File::OpenText("Rezults.txt");
	int size = 0;
	while (!reader->EndOfStream) 
	{
		auto str = reader->ReadLine();
		auto _list = str->Split('.');
		richTextBox1->AppendText(str);
		_list = str->Split('.');
		richTextBox1->AppendText(str);
		_list = str->Split(' ');
		richTextBox1->AppendText(str);
		_list = str->Split(' ');
		richTextBox1->AppendText(str);
		_list = str->Split(' ');
		richTextBox1->AppendText(str);
		_list = str->Split(':');
		richTextBox1->AppendText(str);
		_list = str->Split(' ');
		richTextBox1->AppendText(str);
	 Rezult* el = new Rezult();

		Hash_Table Table_rezults(15);
		Table_rezults.Add(*el, k);
		/*msclr::interop::marshal_context context;
		el->color = context.marshal_as<std::string>(_list[3]);
		el->label = context.marshal_as<std::string>(_list[1]);
		el->model = context.marshal_as<std::string>(_list[2]);
		el->plate = context.marshal_as<std::string>(_list[0]);
		el->num = size;*//*

		Add(el->label, size, TreeBrand);
		Add(el->color, size, TreeColor);
		Add(el->model, size, TreeModal);*/
		//Hashtable.Add(*el);



		record_rezults.push_back(el);

		richTextBox1->AppendText("\n");
		++size;
	}
	reader->Close();
}


private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Rezult_add^ _add = gcnew Rezult_add();
	_add->ShowDialog();
}
private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Otladka^ f = gcnew Otladka();
	f->ShowDialog();
}

};
}


