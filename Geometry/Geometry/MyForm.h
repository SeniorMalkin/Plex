#pragma once
#include "TChart.h"
#include <msclr\marshal_cppstd.h>
#include <iterator>
#include <iostream>
namespace Geometry {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		TChart* pFirst;
		TChart* buf;
		TRoot *p1, *p2;
		int x1 ,x2,y1 , y2,x3,y3,x4,y4;
		int count_point;
		std::vector<TPoint*>* lst;
		bool click;
		bool move;
		bool line;
		SolidBrush^ br;
		SolidBrush^ eraser_br;
		Pen^ pn;
		Pen^ eraser_pn;
		Brush^ bru;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button4;

			 Graphics ^gr;
	public:
		MyForm(void)
		{
			InitializeComponent();
			br = gcnew SolidBrush(Color::Black);
			pn = gcnew Pen(Color::Violet);
			eraser_br = gcnew SolidBrush(Color::White);
			eraser_pn = gcnew Pen(Color::White);
			bru  = gcnew System::Drawing::Drawing2D::HatchBrush(System::Drawing::Drawing2D::HatchStyle::Divot, Color::DarkRed, Color::BlueViolet);
			pn->Brush = bru;
			pn->Width = 3;
			eraser_pn->Width = 3;
			lst = new std::vector<TPoint*>;
			p1 = new TPoint(-1000, -1000);
			p2 = new TPoint(-100, -100);
			pFirst = new TChart();
			pFirst->SetBegin(p1);
			pFirst->SetEnd(p2);
			pFirst->Unvisible();
			
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			delete br;
			delete pn;
			delete eraser_br;
			delete eraser_pn;
			delete bru;
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button4 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Location = System::Drawing::Point(12, 35);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(565, 393);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Harlow Solid Italic", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(110, 126);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 26);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Show";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(110, 328);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 31);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Open";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(64, 44);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(71, 28);
			this->checkBox1->TabIndex = 3;
			this->checkBox1->Text = L"Move";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->button4);
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->checkBox2);
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Harlow Solid Italic", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(601, 35);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 375);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Settings";
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Harlow Solid Italic", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(6, 126);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(85, 26);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Hide";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(17, 308);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(48, 24);
			this->label1->TabIndex = 5;
			this->label1->Text = L"File:";
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(60, 78);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(90, 28);
			this->checkBox2->TabIndex = 4;
			this->checkBox2->Text = L"Remove";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(110, 292);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 30);
			this->button4->TabIndex = 7;
			this->button4->Text = L"Save";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(813, 465);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		gr = pictureBox1->CreateGraphics();
	}
	private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		x1 = x2 = e->X;
		y1 = y2 = e->Y;
		if (checkBox2->Checked)
		{
			buf = pFirst->FindLine(gr, x1, y1);
			line = true;
		}
		if ((checkBox1->Checked) && (pFirst->Find(x1, y1)))
		{
			TPoint* p;
			if (pFirst->first)
			{
				p = dynamic_cast<TPoint*>((pFirst->GetRes())->GetBegin());
			}
			else
			{
				p = dynamic_cast<TPoint*>((pFirst->GetRes())->GetEnd());
			}
			x4=x3=x1 = p->GetX();
			y4=y3=y1 = p->GetY();
			*lst = pFirst->FindFriends(gr, x1, y1);
			count_point = lst->size();
			gr->DrawEllipse(pn, p->GetX() - 8, p->GetY() - 8, 16, 16);
			move = true;
			gr->FillEllipse(eraser_br, System::Drawing::Rectangle::Rectangle(x1 - 4, y1 - 4, 8, 8));
			gr->DrawEllipse(eraser_pn, x1 - 8, y1 - 8, 16, 16);
		}
		else
		click = true;
		
	}
	private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		Brush^ mybr = gcnew SolidBrush(Color::BlueViolet);
		Brush^ mybr1 = gcnew SolidBrush(Color::White);
		if (click)
		{
			gr->DrawLine(Pens::White, x1, y1, x2, y2);
			x2 = e->X;
			y2 = e->Y;
			gr->DrawLine(Pens::Black , x1, y1, x2, y2);
		}
		if (move)
		{
			x1 = e->X;
			y1 = e->Y;
			for(int i=0;i<(lst->size());i++)
			{
				x2 = (*lst)[i]->GetX();
				y2 = (*lst)[i]->GetY();
				gr->DrawLine(Pens::White, x3, y3, x2, y2);
				gr->DrawLine(Pens::Black, x1, y1, x2, y2);
			}
			gr->FillEllipse(mybr1, System::Drawing::Rectangle::Rectangle(x3 - 6, y3 - 6, 12, 12));
			gr->FillEllipse(mybr, System::Drawing::Rectangle::Rectangle(x1 - 6, y1 - 6, 12, 12));
			x3 = x1;
			y3 = y1;
			pFirst->Show(gr);
			
		}
		
	}
	private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		click = false;
		TPoint* p1, *p2,*p3;
		TChart* buf;
		bool bbuf;
		bool start, finish;
		if (move)
		{
			pFirst->Bias(gr, x1, y1,x4,y4);
			gr->Clear(pictureBox1->BackColor);
			
			gr->FillEllipse(br, System::Drawing::Rectangle::Rectangle(x1 - 4, y1- 4, 8, 8));
			gr->DrawEllipse(pn, x1 - 8, y1 - 8, 16, 16);
			move = false;
		}
		else
			if(!line)
		{
			if (pFirst == NULL)
			{
				p1 = new TPoint(x1, y1);
				p2 = new TPoint(x2, y2);
				pFirst = new TChart();
				pFirst->SetBegin(p1);
				pFirst->SetEnd(p2);
				
			}
			else
			{
				start = pFirst->Find(x1, y1);
				if (start)
				{
					if (pFirst->first)
					{
						p1 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetBegin());
					}
					else
					{
						p1 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetEnd());
					}
				}
				finish = pFirst->Find(x2, y2);

				if (start && finish)
				{
					gr->DrawLine(Pens::White, x1, y1, x2, y2);
					//p1 = new TPoint(x1, y1);
					if (pFirst->first)
					{
						p2 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetBegin());
					}
					else
					{
						p2 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetEnd());
					}
					gr->DrawLine(Pens::Black, p1->GetX(), p1->GetY(), p2->GetX(), p2->GetY());
					TChart* tmp = new TChart();
					tmp->SetBegin(p1);
					tmp->SetEnd(p2);
					if (pFirst->first)
						(pFirst->GetRes())->SetBegin(tmp);
					else
						(pFirst->GetRes())->SetEnd(tmp);

				}
				else
				{
					if (start)
					{
						p2 = new TPoint(x2, y2);
						gr->DrawLine(Pens::White, x1, y1, x2, y2);
						if (pFirst->first)
						{
							p1 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetBegin());
							gr->DrawLine(Pens::Black, p1->GetX(), p1->GetY(), p2->GetX(), p2->GetY());
						}
						else
						{
							p1 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetEnd());
							gr->DrawLine(Pens::Black, p1->GetX(), p1->GetY(), p2->GetX(), p2->GetY());
						}
						TChart* tmp = new TChart();
						tmp->SetBegin(p2);
						tmp->SetEnd(p1);
						if (pFirst->first)
							(pFirst->GetRes())->SetBegin(tmp);
						else
							(pFirst->GetRes())->SetEnd(tmp);

					}
					else
					{
						if (finish)
						{
							p2 = new TPoint(x1, y1);
							gr->DrawLine(Pens::White, x1, y1, x2, y2);
							if (pFirst->first)
							{
								p1 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetBegin());
								gr->DrawLine(Pens::Black, p1->GetX(), p1->GetY(), p2->GetX(), p2->GetY());
							}
							else
							{
								p1 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetEnd());
								gr->DrawLine(Pens::Black, p1->GetX(), p1->GetY(), p2->GetX(), p2->GetY());
							}
							TChart* tmp = new TChart();
							tmp->SetBegin(p2);
							tmp->SetEnd(p1);
							if (pFirst->first)
								(pFirst->GetRes())->SetBegin(tmp);
							else
								(pFirst->GetRes())->SetEnd(tmp);

						}
						else
						{
							pFirst->Find(-1000,-1000);
							p2 = new TPoint(x1, y1);
							gr->DrawLine(Pens::White, x1, y1, x2, y2);
							if (pFirst->first)
							{
								p1 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetBegin());
								//gr->DrawLine(Pens::Black, p1->GetX(), p1->GetY(), p2->GetX(), p2->GetY());
							}
							else
							{
								p1 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetEnd());
								//gr->DrawLine(Pens::Black, p1->GetX(), p1->GetY(), p2->GetX(), p2->GetY());
							}
							TChart* tmp = new TChart();
							tmp->SetBegin(p2);
							tmp->SetEnd(p1);
							if (pFirst->first)
								(pFirst->GetRes())->SetBegin(tmp);
							else
								(pFirst->GetRes())->SetEnd(tmp);

							

							pFirst->Find(x1, y1);
							p3 = new TPoint(x2, y2);
							//gr->DrawLine(Pens::White, x1, y1, x2, y2);
							if (pFirst->first)
							{
								p1 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetBegin());
								gr->DrawLine(Pens::Black, p1->GetX(), p1->GetY(), p2->GetX(), p2->GetY());
							}
							else
							{
								p1 = dynamic_cast<TPoint*>((pFirst->GetRes())->GetEnd());
								gr->DrawLine(Pens::Black, p1->GetX(), p1->GetY(), p2->GetX(), p2->GetY());
							}
							TChart* tmp1 = new TChart();
							tmp1->SetBegin(p3);
							tmp1->SetEnd(p1);
							if (pFirst->first)
								(pFirst->GetRes())->SetBegin(tmp1);
							else
								(pFirst->GetRes())->SetEnd(tmp1);
						}
					}

				}
				if (p1 != nullptr && p2 != nullptr)
				{
					gr->FillEllipse(br, System::Drawing::Rectangle::Rectangle(p1->GetX() - 4, p1->GetY() - 4, 8, 8));
					gr->FillEllipse(br, System::Drawing::Rectangle::Rectangle(p2->GetX() - 4, p2->GetY() - 4, 8, 8));
				}
			}
		}
		pFirst->Show(gr);
		start = pFirst->Find(x1, y1);
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		line = false;
		checkBox2->Checked = false;
		//pFirst->CheckStruct();
		gr->Clear(pictureBox1->BackColor);
		pFirst->Show(gr);
	}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	
	openFileDialog1->Filter = "TXT | *.txt";
	std::string str;
	int size;
	int i=0;
	//IntPtr ip = Marshal::StringToHGlobalAnsi(openFileDialog1->FileName);
	msclr::interop::marshal_context ^ context = gcnew msclr::interop::marshal_context();
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		std::ifstream file(msclr::interop::marshal_as<std::string>(openFileDialog1->FileName));
		if (file.good())
		size = std::distance(std::istream_iterator<std::string>(file), (std::istream_iterator<std::string>()))/6;
		file.clear();
		file.seekg(0, std::ios::beg);
		Record* rec = new Record[size];
		while ( i < size)
		{ 
			std::getline(file, str);
			rec[i].num = atoi(str.c_str());
			std::getline(file, str);
			rec[i].xB = atoi(str.c_str());
			std::getline(file, str);
			rec[i].yB = atoi(str.c_str());
			std::getline(file, str);
			rec[i].xE = atoi(str.c_str());
			std::getline(file, str);
			rec[i].yE = atoi(str.c_str());
			std::getline(file, str);
			rec[i].visible= atoi(str.c_str());
			i++;
		}
		file.close();


		Record temp;
		for ( i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (rec[j].num > rec[j + 1].num) {
					// меняем элементы местами
					temp = rec[j];
					rec[j] = rec[j + 1];
					rec[j + 1] = temp;
				}
			}
		}
		delete pFirst;
		pFirst = NULL;
		i = 0;
		while (i < size)
		{
			gr->Clear(Color::White);
			MouseEventArgs^ marg = gcnew MouseEventArgs(System::Windows::Forms::MouseButtons::Left, 1, rec[i].xB, rec[i].yB, 0);
			x1 = rec[i].xB;
			y1 = rec[i].yB;
			x2 = rec[i].xE;
			y2 = rec[i].yE;
			this->pictureBox1_MouseUp(sender, marg);
			if (!rec[i].visible)
				pFirst->GetRes()->Unvisible();
			delete marg;
			i++;

		}
		
	}
	//gr->Clear(Color::White);
	//pFirst->Show(gr);
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	gr->Clear(Color::White);
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	line = false;
	checkBox2->Checked = false;
	pFirst->CheckStruct();
}
};
}
