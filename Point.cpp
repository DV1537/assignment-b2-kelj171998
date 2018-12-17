#include "stdafx.h"
#include "Point.hpp"

Point::Point(double x, double y) {
	this->point.x = x;
	this->point.y = y;

	this->sizeOfVertices = 2;
	this->vertices = new double[this->sizeOfVertices];

	this->vertices[0] = this->point.x;
	this->vertices[1] = this->point.y;
}

Point::~Point() {

}

std::string Point::getType() const {
	return "Point";
}

double Point::area() {
	return 0.0;
}

double Point::circumference() {
	return 0.0;
}

Point::Vertex Point::position() {
	return this->point;
}

bool Point::isConvex() {
	return false;
}

double Point::distance(Shape* shape) {
	double distance = abs(sqrt(pow(this->position().x - shape->position().x, 2) + pow(this->position().y - shape->position().y, 2)));
	return distance;
}

Point& Point::operator=(const Point& copy) {

	if (this == &copy)
		return *this;

	this->point = copy.point;

	return *this;
}

Point::Vertex Point::getVertices() const {
	return this->point;
}