#include<iostream>
#include<Windows.h>
using namespace std;

// enam (Enumeration - перечисление) - это набор
// целочисленных констант. Перечисление также является типом данных
namespace Geometry
{
	enum Color
	{

		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,

		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE,
		console_white = 0XFF

	};


	class Shape
	{
	protected:
		Color color;

	public:
		Color get_color()const
		{
			return color;
		}
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			cout << typeid(*this).name() << endl;
			draw();
		}
	};

	class Square : public Shape
	{
		double side;

	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side <= 0)side = 10;
			this->side = side;
		}

		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {}

		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //В переменную hConsole сохраняем стандартный вывод текущего окна консоли
			SetConsoleTextAttribute(hConsole, get_color());// Для стандартного вывода текущего окна задаем текст цвета и фона
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны квадрата: " << get_side() << endl;
			Shape::info();

		}

	};

	class Rectangle :public Shape
	{
		double side_a, side_b;

	public:
		double get_side_a()const
		{
			return side_a;
		}
		double get_side_b()const
		{
			return side_b;
		}
		void set_side_a(double side_a)
		{
			if (side_a <= 0)side_a = 20;
			this->side_a = side_a;
		}
		void set_side_b(double side_b)
		{
			if (side_b <= 0)side_b = 10;
			this->side_b = side_b;
		}

		Rectangle(double side_a, double side_b, Color color) : Shape(color)
		{
			set_side_a(side_a);
			set_side_b(side_b);
		}
		~Rectangle() {}

		double get_area()const
		{
			return side_a * side_b;
		}
		double get_perimeter()const
		{
			return (side_a + side_b) * 2;
		}
		void draw()const
		{
			//1) Получаем окно консоли
			// HWND - Handler to Window (обработчик окна консоли)
			HWND hwnd = GetConsoleWindow();
			//2) Для того чтобы рисовать нужно создать контекст устройства
			//HDC - Handler to Device Context
			// Грубо говоря, HDC это то на чем мы будеи рисовать
			HDC hdc = GetDC(hwnd);
			//3) Создадим инструменты, которыми мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, 10, color); // карандаш рисует контур
			// Для того чтобы применить заливку, нужна кисть:
			HBRUSH hBrush = CreateSolidBrush(color);
			//4) Создать карандаш недостаточно, его ещё нужно выбрать
			// и только тогда мы сможем им рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//5) Рисуем прямоугольник:
			::Rectangle(hdc, 100, 100, 300, 200);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона А: " << side_a << endl;
			cout << "Сторона B: " << side_b << endl;
			Shape::info();
		}
	};
}




void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::console_blue);
	Geometry::Square square(5, Geometry::Color::console_red);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадарат: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();
	Geometry::Rectangle rect(50, 30, Geometry::Color::green);
	rect.info();





}