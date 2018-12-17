#ifndef POLYGON_H
#define POLYGON_H
#include "Shape.hpp"

class Polygon : public Shape {
	double* coordinates;
	double* tempCoords;
	int numOfElements;
	static const int addTwoPoints = 2;

public:
	Polygon(double* coordinates);
	Polygon(double* coordinates, const int numOfCoordinates);
	virtual ~Polygon();

	std::string getType() const override;
	double area() override;
	double circumference() override;
	Vertex position() override;
	bool isConvex() override;
	double distance(Shape* shape) override;

	bool IsLineIntersection(Vertex startPoint1, Vertex endPoint1, Vertex startPoint2, Vertex endPoint2);
	bool FoundIntersection(Vertex coordinates[], const int size);
	Polygon& operator=(const Polygon& otherPolygon);
	Polygon& operator+(double coordinates[addTwoPoints]);
};

#endif
