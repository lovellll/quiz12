// quiz12.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <initializer_list>
#include <vector>



class Shape
{
public:
	enum ClassType
	{
		CIRCLE,
		TRIANGLE,
	};
	
	Shape()
	{
	}

	virtual std::ostream& print(std::ostream &out) const = 0;
	virtual ClassType getType() const  = 0;
	friend std::ostream& operator<<(std::ostream &out, Shape &shape)
	{
		return shape.print(out);
	}
	virtual ~Shape()
	{
	}
};

class Point
{
private:
	int m_x;
	int m_y;
	int m_z;
public:
	Point(int x, int y, int z):m_x(x),m_y(y),m_z(z)
	{
	}

	friend std::ostream& operator<<(std::ostream &out,const Point &point)
	{
		out << "Point(" << point.m_x << "," << point.m_y << "," << point.m_z << ")";
		return out;
	}
};

class Triangle :public Shape
{
	Point m_point1;
	Point m_point2;
	Point m_point3;
public:
	/*
	Triangle(const std::initializer_list<Point> &list)
	{
		int count = 0;
		for (const auto &element : list)
		{
			m_point[count] = element;
			++count;
		}
	}
	*/

	Triangle(Point &point1, Point &point2, Point &point3) :m_point1(point1), m_point2(point2), m_point3(point3)
	{
	}

	virtual ~Triangle()
	{
	}


	virtual ClassType getType() const override
	{
		return Shape::TRIANGLE;
	}

	virtual std::ostream& print(std::ostream &out) const override
	{
		out << "Triangle(" << m_point1 << ',' << m_point1 << ',' << m_point3 << ")\n";
		return out;
	}
};

class Circle :public Shape
{
	Point m_point;
	int m_radius;
public:
	Circle(Point center, int radius) :m_point(center), m_radius(radius)
	{
	}
	
	virtual ~Circle()
	{
	}

	int getRadius()
	{
		return m_radius;
	}

	virtual std::ostream& print(std::ostream &out) const override
	{
		out << "Circle(" << m_point << ',' << "radius " << m_radius << ")\n";
		return out;
	}

	virtual ClassType getType() const override
	{
		return Shape::CIRCLE;
	}
};

int getLargestRadius(std::vector<Shape*> v)
{
	int biggestRadius = 0;
	for (auto &element : v)
	{
		if(element->getType()==Shape::CIRCLE)
		{
			int elementRadius = dynamic_cast<Circle*>(element)->getRadius();
			if (elementRadius > biggestRadius)
				biggestRadius = elementRadius;
		}
	}
	return biggestRadius;
}



int main()
{
	std::vector<Shape*> v;
	v.push_back(new Circle(Point(1, 2, 3), 7));
	v.push_back(new Triangle(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9)));
	v.push_back(new Circle(Point(4, 5, 6), 3));

	// print each shape in vector v on its own line here
	for (auto &element : v)
	{
		std::cout<<*element;
	}

	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

	// delete each element in the vector here
	for (auto &element : v)
	{
		delete element;
	}

	for (auto &element : v)
	{
		std::cout << *element;
	}

}

