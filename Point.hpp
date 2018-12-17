#ifndef POINT_H
#define POINT_H
#include "Shape.hpp"

class Point : public Shape {
	Vertex point;

public: 
	Point(double x, double y);
	virtual ~Point();

	std::string getType() const override;
	double area() override;
	double circumference() override;
	Vertex position() override;
	bool isConvex() override;
	double distance(Shape* shape) override;
	Vertex getVertices() const;
	Point& operator=(const Point& copy);
};

#endif