#define _CRT_SECURE_NO_WARNINGS
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
		purple = 0x00BB00BB,
		light_blue = 0x00BBBB00,

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
		max_start_x = 1500,
		min_start_y = 10,
		max_start_y = 2000,
		min_line_width = 4,
		max_line_width = 20,
		min_line_length = 10,
		max_line_length = 500,

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
			cout << delimiter;
		}
	};


//#define DZ

#ifdef DZ

	class Triangle :public Shape
	{

	protected:

		Triangle(int start_x, int start_y, unsigned int line_width, Color color)
			: Shape(start_x, start_y, line_width, color) {}

	};


	class Equilateral_triangle :public Triangle
	{

		double side;


	public:

		double get_side()const
		{
			return side;
		}

		void set_side(double side)
		{
			if (side >= 20 && side <= 300)this->side = side;
			else if (side < 20)this->side = 20;
			else this->side = 300;
		}


		Equilateral_triangle(double side, int start_x, int start_y, unsigned int line_width, Color color)
			: Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);

		}

		double get_area()const
		{
			double pp = (side + side + side) / 2;
			return sqrt(pp * (pp - side) * (pp - side) * (pp - side));

		}

		double get_perimeter()const
		{
			return side + side + side;
		}


		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, green);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT points[3] = { {start_x, start_y}, {start_x - side, start_y + side}, {start_x + side, start_y + side} };
			::Polygon(hdc, points, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}


		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона треугольника: " << side << endl;
			Shape::info();
			cout << delimiter;
		}

	};

	class Right_triangle :public Triangle
	{
		int leg_1;
		int leg_2;


	public:

		int get_leg_1()const
		{
			return leg_1;
		}
		int get_leg_2()const
		{
			return leg_2;
		}

		void set_leg_1(int leg_1)
		{
			if (leg_1 >= 20 && leg_1 <= 150)this->leg_1 = leg_1;
			else if (leg_1 < 20)this->leg_1 = 20;
			else this->leg_1 = 150;
		}
		void set_leg_2(int leg_2)
		{
			if (leg_2 >= 10 && leg_2 <= 100)this->leg_2 = leg_2;
			else if (leg_2 < 10)this->leg_2 = 10;
			else this->leg_2 = 100;
		}


		Right_triangle(int leg_1, int leg_2, int start_x, int start_y, unsigned int line_width, Color color)
			: Triangle(start_x, start_y, line_width, color)
		{
			set_leg_1(leg_1);
			set_leg_2(leg_2);

		}

		double get_area()const
		{
			//int hypotenuse = sqrt((leg_1 * leg_1) + (leg_2 * leg_2)); // Вопрос
			//double pp = (leg_1 + leg_2 + hypotenuse) / 2;
			//return sqrt(pp * (pp - leg_1) * (pp - leg_2) * (pp - hypotenuse)); 
			return (leg_1 * leg_2) / 2;

		}

		double get_perimeter()const
		{
			int hypotenuse = sqrt((leg_1 * leg_1) + (leg_2 * leg_2));
			return leg_1 + leg_2 + hypotenuse;
		}


		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, purple);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT points[3] = { {start_x, start_y}, {start_x, start_y + leg_1}, {start_x + leg_2, start_y + leg_1} };
			::Polygon(hdc, points, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}


		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона треугольника 1: " << leg_1 << endl;
			cout << "Сторона треугольника 2: " << leg_2 << endl;
			Shape::info();
			cout << delimiter;
		}

	};



	class Obtuse_triangle : Triangle
	{
		int leg_1;
		int leg_2;
		//int hypotenuse;

	public:

		int get_leg_1()const
		{
			return leg_1;
		}
		int get_leg_2()const
		{
			return leg_2;
		}

		void set_leg_1(int leg_1)
		{
			if (leg_1 >= 20 && leg_1 <= 100)this->leg_1 = leg_1;
			else if (leg_1 < 20)this->leg_1 = 20;
			else this->leg_1 = 100;
		}
		void set_leg_2(int leg_2)
		{
			if (leg_2 < leg_1)this->leg_2 = leg_1 + 50;
			else if (leg_2 >= 10 && leg_2 <= 150)this->leg_2 = leg_2;
			else if (leg_2 < 10)this->leg_2 = 10;
			else this->leg_2 = 150;
		}


		Obtuse_triangle(int leg_1, int leg_2, int start_x, int start_y, unsigned int line_width, Color color)
			: Triangle(start_x, start_y, line_width, color)
		{
			set_leg_1(leg_1);
			set_leg_2(leg_2);
			//hypotenuse = sqrt((leg_1 * leg_1) + (leg_2 * leg_2)); // Вопрос

		}
		double get_hypotenuse()const
		{
			return sqrt((leg_1 * leg_1) + (leg_2 * leg_2)); // Вопрос
		}


		double get_area()const
		{
			double pp = (leg_1 + leg_2 + get_hypotenuse() / 2);
			return sqrt(pp * (pp - leg_1) * (pp - leg_2) * (pp - get_hypotenuse()));

		}

		double get_perimeter()const
		{
			//int hypotenuse = sqrt((leg_1 * leg_1) + (leg_2 * leg_2));
			return leg_1 + leg_2 + get_hypotenuse();
		}


		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, yellow);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT points[3] = { {start_x, start_y}, {start_x + leg_1, start_y + leg_1}, {start_x + leg_1 + leg_2, start_y + leg_1} };
			::Polygon(hdc, points, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}


		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона треугольника 1: " << leg_1 << endl;
			cout << "Сторона треугольника 2: " << leg_2 << endl;
			Shape::info();
			cout << delimiter;
		}


	};


	class Isoscelec_triangle :public Triangle
	{
		int side;
		int ground;


	public:

		int get_side()const
		{
			return side;
		}
		int get_ground()const
		{
			return ground;
		}

		void set_side(int side)
		{
			if (side >= 20 && side <= 400)this->side = side;
			else if (side < 20)this->side = 20;
			else this->side = 150;
		}
		void set_ground(int ground)
		{
			if (ground >= 10 && ground <= 200)this->ground = ground;
			else if (ground < 10)this->ground = 10;
			else this->ground = 100;
		}


		Isoscelec_triangle(int side, int ground, int start_x, int start_y, unsigned int line_width, Color color)
			: Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);
			set_ground(ground);

		}


		double get_area()const
		{
			return (ground / 4) * sqrt((4 * (side * side)) - (ground * ground));

		}

		double get_perimeter()const
		{
			return 2 * side + ground;
		}


		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, green);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT points[3] = { {start_x, start_y}, {start_x - ground / 2, start_y + side}, {start_x + ground / 2, start_y + side} };
			::Polygon(hdc, points, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона треугольника : " << side << endl;
			cout << "Основание треугольника : " << ground << endl;
			Shape::info();
			cout << delimiter;
		}

	};

#endif // DZ


	class Triangle :public Shape
	{

	public:
		Triangle(int start_x, int start_y, unsigned int line_width, Color color):
			Shape(start_x, start_y, line_width, color){}
		
		~Triangle(){}
		virtual double get_height()const = 0;

	};


	class EquilateralTriangle :public Triangle
	{
		double side;

	public:

		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < Defaults::min_line_length)this->side = Defaults::min_line_length;
			else if (side > Defaults::max_line_length)this->side = Defaults::max_line_length;
			else this->side = side;
		}

		EquilateralTriangle(double side, int start_x, int start_y, unsigned int line_width, Color color) :
			Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~EquilateralTriangle(){}

		double get_height()const
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));

		}

		double get_area()const
		{
			return side * get_height() / 2;
		}

		double get_perimeter()const
		{
			return side * 3;
		}

		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertices[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};

			::Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
			
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона треугольника: " << side << endl;
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();

		}


	};

	class IsoscelesTriangle :public Triangle
	{
		double base;
		double side;
	public:

		double get_base()const
		{
			return base;
		}

		double get_side()const
		{
			return side;
		}

		void set_base(double base)
		{
			if (base < Defaults::min_line_length)base = Defaults::min_line_length;
			else if (base > Defaults::max_line_length)base = Defaults::max_line_length;
			//if (base >= side * 2)base /= 2;
			this->base = base;

		}
		void set_side(double side)
		{
			if (side < Defaults::min_line_length)side = Defaults::min_line_length;
			else if (side > Defaults::max_line_length)side = Defaults::max_line_length;
			if (side * 2 <= base)side = base;
			this->side = side;
		}
		
		IsoscelesTriangle& operator()(double base, double side)
		{
			if (base >= side * 2)base = side;
			set_base(base);
			set_side(side);
			return *this;
		}

		IsoscelesTriangle(double base, double side, int start_x, int start_y, unsigned int line_width, Color color) :
			Triangle(start_x, start_y, line_width, color)
		{
			operator()(base, side);

		}
		~IsoscelesTriangle() {}

		double get_height()const
		{
			return sqrt(pow(side, 2) - pow(base / 2, 2));
		}

		double get_area()const
		{
			return base * get_height() / 2;
		}

		double get_perimeter()const
		{
			return base + side * 2;
		}

		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertices[] =
			{
				{start_x, start_y + side},
				{start_x + base, start_y + side},
				{start_x + base / 2, start_y + side - get_height()}
			};

			::Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Основание треугольника: " << base << endl;
			cout << "Сторона треугольника: " << side << endl;
			cout << "Высота треугольника: " << get_height() << endl;
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
	
	Geometry::Rectangle rect(150, 100, 500, 220, 5, Geometry::Color::green);
	rect.info();

	Geometry::Circle circle(50, 500, 350, 5, Geometry::Color::yellow);
	circle.info();


	/*Geometry::Equilateral_triangle triangle(100, 600, 480, 1, Geometry::Color::purple);
	triangle.info();
	
	Geometry::Right_triangle triangle_2(130, 100, 600, 600, 1, Geometry::Color::light_blue);
	triangle_2.info();

	Geometry::Obtuse_triangle triangle_3(90, 80, 600, 750, 1, Geometry::Color::green);
	triangle_3.info();

	Geometry::Isoscelec_triangle triangle_4(400, 100, 1000, 500, 3, Geometry::Color::blue);
	triangle_4.info();*/
	

	Geometry::EquilateralTriangle qtri(100, 400, 400, 5, Geometry::Color::green);
	qtri.info();

	Geometry::IsoscelesTriangle itri(100, 200, 600, 500, 5, Geometry::Color::yellow);
	itri.info();




}