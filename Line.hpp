#ifndef LINE_H
#define LINE_H
#include "Shape.hpp"

class Line : public Shape {
	Vertex startPoint;
	Vertex endPoint;

public:
	Line(double x1, double y1, double x2, double y2);
	virtual ~Line();

	std::string getType() const override;
	double area() override;
	double circumference() override;
	Vertex position() override;
	bool isConvex() override;
	double distance(Shape* shape) override;
	Line& operator=(const Line& copy);
};

#endif