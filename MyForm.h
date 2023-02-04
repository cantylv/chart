#pragma once

#include <ctime>
#include <chrono>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <Windows.h>

#define TIME_X 250


namespace Learning {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace System::Threading;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		// поток для построения графика
		Thread^ DrawThread;
		// поток для кнопки stop/continue
		Thread^ StopThread;
		// поток для генерации в label случайного числа
		Thread^ GenerateThread;
		bool cancel_draw = false;
		// таймер, который помогает отсчитать единицу масштаба по оси Х (н-р, 1 сек)
		int timer = 0;
		// время рисования графика
		double time_draw = 0;
		// для правильной работы кнопок
		bool was_stopped = false;
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart;
	private: System::Windows::Forms::Button^ draw;
	private: System::Windows::Forms::Button^ stop;
	private: System::Windows::Forms::Button^ clear;
	private: System::Windows::Forms::Label^ label;
	private: System::Windows::Forms::Button^ button;
	protected:




	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->draw = (gcnew System::Windows::Forms::Button());
			this->stop = (gcnew System::Windows::Forms::Button());
			this->clear = (gcnew System::Windows::Forms::Button());
			this->label = (gcnew System::Windows::Forms::Label());
			this->button = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart))->BeginInit();
			this->SuspendLayout();
			// 
			// chart
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart->ChartAreas->Add(chartArea1);
			this->chart->Dock = System::Windows::Forms::DockStyle::Fill;
			legend1->Name = L"Legend1";
			legend1->Title = L"Графики функций";
			this->chart->Legends->Add(legend1);
			this->chart->Location = System::Drawing::Point(0, 0);
			this->chart->Name = L"chart";
			series1->BorderWidth = 3;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Legend = L"Legend1";
			series1->LegendText = L"n(t), об/мин";
			series1->Name = L"Series1";
			series2->BorderWidth = 3;
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Legend = L"Legend1";
			series2->LegendText = L"u(t), об/мин";
			series2->Name = L"Series2";
			this->chart->Series->Add(series1);
			this->chart->Series->Add(series2);
			this->chart->Size = System::Drawing::Size(2317, 1276);
			this->chart->TabIndex = 0;
			this->chart->Text = L"chart1";
			// 
			// draw
			// 
			this->draw->Location = System::Drawing::Point(50, 236);
			this->draw->Name = L"draw";
			this->draw->Size = System::Drawing::Size(168, 67);
			this->draw->TabIndex = 1;
			this->draw->Text = L"Draw";
			this->draw->UseVisualStyleBackColor = true;
			this->draw->Click += gcnew System::EventHandler(this, &MyForm::draw_Click);
			// 
			// stop
			// 
			this->stop->Enabled = false;
			this->stop->Location = System::Drawing::Point(50, 331);
			this->stop->Name = L"stop";
			this->stop->Size = System::Drawing::Size(163, 61);
			this->stop->TabIndex = 2;
			this->stop->Text = L"Stop";
			this->stop->UseVisualStyleBackColor = true;
			this->stop->Click += gcnew System::EventHandler(this, &MyForm::stop_Click);
			// 
			// clear
			// 
			this->clear->Enabled = false;
			this->clear->Location = System::Drawing::Point(50, 416);
			this->clear->Name = L"clear";
			this->clear->Size = System::Drawing::Size(163, 64);
			this->clear->TabIndex = 3;
			this->clear->Text = L"Clear";
			this->clear->UseVisualStyleBackColor = true;
			this->clear->Click += gcnew System::EventHandler(this, &MyForm::clear_Click);
			// 
			// label
			// 
			this->label->AutoSize = true;
			this->label->Location = System::Drawing::Point(66, 110);
			this->label->Name = L"label";
			this->label->Size = System::Drawing::Size(48, 25);
			this->label->TabIndex = 4;
			this->label->Text = L"500";
			// 
			// button
			// 
			this->button->Location = System::Drawing::Point(50, 555);
			this->button->Name = L"button";
			this->button->Size = System::Drawing::Size(163, 65);
			this->button->TabIndex = 5;
			this->button->Text = L"Generate";
			this->button->UseVisualStyleBackColor = true;
			this->button->Click += gcnew System::EventHandler(this, &MyForm::button_Click);
			// 
			// dateTimePicker1
			// 
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(2317, 1276);
			this->Controls->Add(this->button);
			this->Controls->Add(this->label);
			this->Controls->Add(this->clear);
			this->Controls->Add(this->stop);
			this->Controls->Add(this->draw);
			this->Controls->Add(this->chart);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	// Реализация графика 01.02.2023

	private: System::Void draw_Click(System::Object^ sender, System::EventArgs^ e)
	{
		DrawThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::Go1));
		DrawThread->Start();
		
	}	
	public: void Go1()
	{
		// скорей всего, сюда мы допишем обновление фрейма графика, чтобы он не превращался в сплошную фигуру 
		MyForm::draw->BeginInvoke(gcnew InvokeSetEnabledToDraw(this, &MyForm::SetEnabledToDraw), false);
		MyForm::stop->BeginInvoke(gcnew InvokeSetEnabledToStop(this, &MyForm::SetEnabledToStop), true);
		MyForm::clear->BeginInvoke(gcnew InvokeSetEnabledToClear(this, &MyForm::SetEnabledToClear), true);
		
		while (!cancel_draw)
		{
			MyForm::chart->BeginInvoke(gcnew DrawChart(this, &MyForm::Draw), time_draw);
			Sleep(TIME_X);
			time_draw += (double)TIME_X/1000;
		}
	}
	delegate void DrawChart(double tik);

	public: void Draw(double tik)
	{
		chart->Series[0]->Points->AddXY(tik, Convert::ToDouble(MyForm::label->Text));
	}

	private: System::Void stop_Click(System::Object^ sender, System::EventArgs^ e)
	{
		StopThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::Go2));
		StopThread->Start();
	}
	
	public: void Go2()
	{
		was_stopped = true;
		cancel_draw = !cancel_draw;
		stop->Text = cancel_draw ? "Continue" : "Stop";
		if (!cancel_draw)
		{
			DrawThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::Go1));
			DrawThread->Start();
		}
	}

	private: System::Void clear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		chart->Series[0]->Points->Clear();
		stop->Text = "Stop";
		if(was_stopped)
		{
			draw->Enabled = true;
			stop->Enabled = false;
			clear->Enabled = false;
			was_stopped = false;
		}
		else
		{
			draw->Enabled = false;
			stop->Enabled = true;
			clear->Enabled = true;
		}
		cancel_draw = false;
		time_draw = 0;
	}


	// отвечает за генерацию случайных чисел в элементе MyForm::label
	private: System::Void button_Click(System::Object^ sender, System::EventArgs^ e)
	{
		GenerateThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::Go3));
		GenerateThread->Start();
	}
	public: void Go3()
	{
		srand(time(NULL));
		while (true)
		{
			MyForm::label->BeginInvoke(gcnew SetTextIntoLabel(this, &MyForm::change_Text), rand()%1000+100);
			Sleep(1);
		}
	}
	delegate void SetTextIntoLabel(int num);
	public: void change_Text(int num)
	{
		System::String^ text;
		text = gcnew System::String(to_string(num).c_str());
		MyForm::label->Text = text;
	}
	

	
	//////////////////////////////////////////////////////
	delegate void InvokeSetEnabledToDraw(bool enabled);
	public: void SetEnabledToDraw(bool enabled)
	{
		MyForm::draw->Enabled = enabled;

	}

	delegate void InvokeSetEnabledToStop(bool enabled);
	public: void SetEnabledToStop(bool enabled)
	{
		MyForm::stop->Enabled = enabled;

	}

	delegate void InvokeSetEnabledToClear(bool enabled);
	public: void SetEnabledToClear(bool enabled)
	{
		MyForm::clear->Enabled = enabled;

	}
		  private: System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
		  {
			  try
			  {
				  DrawThread->Abort();
				  StopThread->Abort();
				  GenerateThread->Abort();
			  }
			  catch (...) {}
		  }

	};
}
