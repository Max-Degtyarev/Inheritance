#include<iostream>
#include<ctime>
using std::cout;
using std::endl;
using namespace std;

#define UPPER_LEFT_ANGLE (char)218
#define UPPER_RIGHT_ANGLE (char)191
#define DOWN_LEFT_ANGLE (char)192
#define DOWN_RIGHT_ANGLE (char)217
#define HORIZONTAL_LINE (char)196 << (char)196
#define VERTICAL_LINE (char)179




//class Vehicle
//{
//	int speed;
//public:
//	virtual void move() = 0;
//	//Абстрактрый класс
//};
//
//class GroundVehicle :public Vehicle
//{
//
//};
//
//class Car :public GroundVehicle
//{
//
//public:
//	void move()
//	{
//		cout << "Машина едет на четырех колесах" << endl;
//	}
//	// Конкретный класс
//};
//
//class Bike :public GroundVehicle
//{
//
//public:
//	void move()
//	{
//		cout << "Мотоцикл едет на двух колесах" << endl;
//	}
//};
//
//class AirVehicle :public Vehicle
//{
//	int height;
//public:
//	virtual void take_off() = 0;
//
//};
//
//class Helicopter :public AirVehicle
//{
//public:
//	void move()
//	{
//		cout << "Вертолет летит на винте" << endl;
//	}
//	void take_off()
//	{
//		cout << "Вертикальный взлет" << endl;
//	}
//
//};



class Shape
{

public:
	virtual void print() = 0;

};



class Quadrilateral : public Shape
{


};


class Square :public Quadrilateral
{
	int side;

public:

	int area(int side)
	{
		return side * side;
	}
	
	int perimetr(int side)
	{
		return side * 4;
	}

	void print()
	{
		cout << "\n---------------------------------------------\n" << endl << "Квадрат" << endl;
		srand(time(NULL));
		int side = rand() % 15 + 1;
		cout << "Длина стороны = " << side << endl;
		cout << "Площадь = " << area(side) << endl;
		cout << "Периметр = " << perimetr(side) << endl;
		setlocale(LC_ALL, "C");
		
		for (int i = 0; i <= side; i++)
		{
			for (int j = 0; j <= side; j++)
			{
				if (i == 0 && j == 0)cout << UPPER_LEFT_ANGLE;
				else if (i == 0 && j == side)cout << UPPER_RIGHT_ANGLE;
				else if (i == side && j == 0)cout << DOWN_LEFT_ANGLE;
				else if (i == side && j == side)cout << DOWN_RIGHT_ANGLE;
				else if (i == 0 || i == side)cout << HORIZONTAL_LINE;
				else if (j == 0 || j == side)cout << VERTICAL_LINE;
				else cout << (i % 2 == j % 2 ? "  " : "  ");
				
			}
			cout << endl;

		}
		setlocale(LC_ALL, "");

	}

};


class Rectangle :public Quadrilateral
{
	int length;
	int width;

public:


	int area(int length, int width)
	{
		return length * width;

	}

	int perimetr(int length, int width)
	{
		return (length + width) * 2;
	}


	void print()
	{
		cout << "\n---------------------------------------------\n" << endl << "Прямоугольник" << endl;
		srand(time(NULL));
		int length = rand() % 20 + 1;
		int width = rand() % 10 + 1;
		cout << "Площадь = " << area(length, width) << endl;
		cout << "Периметр = " << perimetr(length, width) << endl;
		setlocale(LC_ALL, "C");

		for (int i = 0; i <= width; i++)
		{
			for (int j = 0; j <= length; j++)
			{
				if (i == 0 && j == 0)cout << UPPER_LEFT_ANGLE;
				else if (i == 0 && j == length)cout << UPPER_RIGHT_ANGLE;
				else if (i == width && j == 0)cout << DOWN_LEFT_ANGLE;
				else if (i == width && j == length)cout << DOWN_RIGHT_ANGLE;
				else if (i == 0 || i == width)cout << HORIZONTAL_LINE;
				else if (j == 0 || j == length)cout << VERTICAL_LINE;
				else cout << (i % 2 == j % 2 ? "  " : "  ");

			}
			cout << endl;

		}
		setlocale(LC_ALL, "");


	}


};





class Circle:public Shape
{
	int area;

public:

	double radius(int area)
	{
		double p = 3.14;
		return sqrt(area / p);
	}



	void print()
	{
		cout << "\n---------------------------------------------\n";
		srand(time(NULL));
		int area = rand() % 15 + 1;
		cout << "Площадь = " << area << endl;
		cout << "Радиус = " << radius(area) << endl;
		for (int i = 0; i < area; i++)
		{
			for (int j = i; j < area; j++)cout << "  ";
			cout << "*";
			for (int j = 0; j < i * 2; j++)cout << "  ";
			cout << "*";
			cout << endl;
			
		}
		for (int i = 0; i < area; i++)
		{
			for (int j = 0; j <= i; j++)cout << "  ";
			cout << "*";
			for (int j = 0; j < (area - 1 - i) * 2; j++)cout << "  ";
			cout << "*";
			cout << endl;
			
		}



	}


};


class Triangle : public Shape
{
	int side;
	int height;

public:

	int get_height()const
	{
		cout << height;
		return height;
	}

	void set_height(int side)
	{
		height = (side * sqrt(3)) / 2;

	}


	int perimetr(int side)
	{
		return side * 3;

	}

	int area(int side, int height)
	{
		return (side * height) / 2;

	}
	



	void print()
	{
		cout << "\n---------------------------------------------\n" << "Треугольник" << endl;
		srand(time(NULL));
		int side = rand() % 15 + 1;
		cout << "Высота = "; 
		set_height(side);
		get_height();
		cout << endl;
		cout << "Площадь = " << area(side, height) << endl;
		cout << "Периметр = " << perimetr(side) << endl;
		for (int i = 0; i < side; i++)
		{
			for (int j = i; j < side; j++)cout << "  ";
			cout << "*";
			for (int j = 0; j < i * 2; j++)cout << "  ";
			cout << "*";
			cout << endl;

		}
		for (int i = 0; i < side * 2; i++)
		{
			cout << "* ";
			
		}
		cout << "*";

	}




};






Shape* ShapeFactory()
{
	srand(time(NULL));
	int a = rand() % 4 + 1;
	if (a == 1)return new Square;
	else if (a == 2)return new Circle;
	else if (a == 3)return new Rectangle;
	else if (a == 4)return new Triangle;

}



//#define VEHICLE

void main()
{
	setlocale(LC_ALL, "");
#ifdef VEHICLE
	Car bmw;
	Bike hd;
	bmw.move();
	hd.move();

	Helicopter apache;
	apache.take_off();
	apache.move();
#endif // VEHICLE

	
	
	Shape* group[4];


	bool unique;
	for (int i = 0; i < 4; i++)
	{
		do
		{
			group[i] = ShapeFactory();
			unique = true;
			for (int j = 0; j < i; j++)
			{
				if (typeid(*group[i]).name() == typeid(*group[j]).name())
				{
					unique = false;
					break;
				}
			}
		} while (!unique);


	}


	for (int i = 0; i < 4; i++)
	{
		group[i]->print();

	}

	for (int i = 0; i < 4; i++)
	{
		delete group[i];
	}





	//Square ty;
	//ty.print();

	//cout << "-----------------------------------\n";

	//Circle a;
	//a.print();

	//cout << "-----------------------------------\n";

	//Rectangle g;
	//g.print();













}