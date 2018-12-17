#ifndef SHAPE_H
#define SHAPE_H

#include "stdafx.h"
#include <string>

class Shape {
private: 
	double* combineCoords;

protected: 
	int newSize;
	double* vertices;
	int sizeOfVertices;

	struct Vertex {
		double x;
		double y;
	};

	enum Area {
		NO_AREA = -1
	};

public:

	struct ComboArray {
		double* vertices;
		int sizeOfVertices;
	};

	Shape() {}
	virtual ~Shape() {
		delete[] vertices;
		delete[] combineCoords;
	}

	virtual std::string getType() const = 0;
	virtual double area() = 0;
	virtual double circumference() = 0;
	virtual Vertex position() = 0;
	virtual bool isConvex() = 0;
	virtual double distance(Shape* shape) = 0;
	
	virtual Shape* operator+(Shape& otherShape) {
		this->newSize = this->sizeOfVertices + otherShape.sizeOfVertices;
		combineCoords = new double[newSize] { 0.0 };

		int nextNum = 0;
		for (nextNum; nextNum < sizeOfVertices; nextNum++) {
			combineCoords[nextNum] = vertices[nextNum];
		}

		for (int i = 0; i < newSize && nextNum < newSize; i++) {
			combineCoords[nextNum++] = otherShape.vertices[i];
		}

		ComboArray combinedPoints;
		combinedPoints.vertices = combineCoords;
		combinedPoints.sizeOfVertices = newSize;

		return this;
	};

	int getSizeOfVertices() const {
		return this->sizeOfVertices;
	}

	int getSizeOfNewSize() const {
		return this->newSize;
	}

	double* getComboArray() const {
		return this->combineCoords;
	}

	double* getVerticesArray() const {
		return this->vertices;
	}
};

#endif