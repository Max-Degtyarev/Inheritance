#define _USE_MATH_DEFINES
#include<iostream>
#include<math.h>
#include<Windows.h>
using namespace std;

#define delimiter "---------------------------------------------\n"


// enam (Enumeration - перечисление) - это набор
// целочисленных констант. Перечисление также является типом данных
namespace Geometry
{
	enum Color
	{

		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,

		console_default = 0x00000007,
		console_blue = 0x000099,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE,
		console_white = 0XFF

	};

	enum Defaults
	{
		min_start_x = 10,
		max_start_x = 800,
		min_start_y = 10,
		max_start_y = 500,
		min_line_width = 5,
		max_line_width = 20,

	};


	class Shape
	{
	protected:
		Color color;
		int start_x;
		int start_y;
		unsigned int line_width;

	public:
		Color get_color()const
		{
			return color;
		}

		int get_start_x()const
		{
			return start_x;
		}

		int get_start_y()const
		{
			return start_y;
		}

		unsigned int get_line_width()const
		{
			return line_width;
		}

		void set_start_x(int start_x)
		{
			if (start_x < Defaults::min_start_x)this->start_x = Defaults::min_start_x;
			else if (start_x > Defaults::max_start_x)this->start_x = Defaults::max_start_x;
			else this->start_x = start_x;
		}

		void set_start_y(int start_y)
		{
			if (start_y < Defaults::min_start_y)this->start_y = Defaults::min_start_y;
			else if (start_y > Defaults::max_start_y)this->start_y = Defaults::max_start_y;
			else this->start_y = start_y;
		}

		void set_line_width(unsigned int line_width)
		{
			if (line_width < Defaults::min_line_width)this->line_width = Defaults::min_line_width;
			else if (line_width > Defaults::max_line_width)this->line_width = Defaults::max_line_width;
			else this->line_width = line_width;
		}


		Shape(int start_x, int start_y, unsigned int line_width, Color color) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}

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

		Square(double side, int start_x, int start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color)
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
			cout << delimiter;
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

		Rectangle(double side_a, double side_b, int start_x, int start_y, unsigned int line_width, Color color)
			: Shape(start_x, start_y, line_width, color)
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
			// Грубо говоря, HDC это то на чем мы будем рисовать
			HDC hdc = GetDC(hwnd);
			//3) Создадим инструменты, которыми мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, line_width, color); // карандаш рисует контур
			// Для того чтобы применить заливку, нужна кисть:
			HBRUSH hBrush = CreateSolidBrush(color);
			//4) Создать карандаш недостаточно, его ещё нужно выбрать
			// и только тогда мы сможем им рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//5) Рисуем прямоугольник:
			::Rectangle(hdc, start_x, start_y, start_x + side_a, start_y + side_b);

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
			cout << delimiter;
		}
	};




	class Circle :public Shape
	{
		double radius;

	public:
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			if (radius >= 10 && radius <= 500)this->radius = radius;
			else if (radius < 10)this->radius = 10;
			else this->radius = 500;
		}

		Circle(double radius, int start_x, int start_y, unsigned int line_width, Color color)
			: Shape(start_x, start_y, line_width, color)
		{
			set_radius(radius);
		}

		~Circle() {}

		double get_area()const
		{
			return M_PI * pow(radius, 2);
		}

		double get_perimeter()const
		{
			return 2 * radius * M_PI;
		}

		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, start_x, start_y, start_x + radius * 2, start_y + radius * 2);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << radius << endl;
			Shape::info();
		}
	};



}




void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::console_blue);
	Geometry::Square square(5, 50, 10, 5, Geometry::Color::console_red);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадарат: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();
	
	Geometry::Rectangle rect(500, 300, 500, 100, 5, Geometry::Color::green);
	rect.info();

	Geometry::Circle circle(150, 850, 250, 15, Geometry::Color::yellow);
	circle.info();




}