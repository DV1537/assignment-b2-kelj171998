// AssignmentA2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include <crtdbg.h>  
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include "Shape.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Triangle.hpp"
#include "Polygon.hpp"
#include "Figure.hpp"

enum ReadLine {
	first,
	second
};

struct Vertices {
	double* numArr;
	int sizeOfArr;

	Vertices() {
		this->numArr = nullptr;
		this->sizeOfArr = 0;
	}

	Vertices(double* numArr, int sizeOfArr) : numArr(numArr), sizeOfArr(sizeOfArr) {

	}
};

double* ReadFileAndStoreValues(std::string fileName, int& numOfElements, ReadLine readLine);
Shape* IdentifyShapeToCalcArea(double coordinates[], const int numOfElements);
std::ostream& operator<<(std::ostream& out, const Vertices& vertices);


Vertices* ReadFileAndStoreValues(const std::string& fileName, int& countLines);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int countLines = 0;
	Vertices* shapeVertices = ReadFileAndStoreValues("combo.txt", countLines);

	for (int i = 0; i < countLines; i++) {
		for (int j = 0; j < shapeVertices[i].sizeOfArr; j++) {
			std::cout << shapeVertices[i].numArr[j] << " ";
		}
		std::cout << '\n';
	}

	Figure figure;
	Shape** shapes = new Shape*[countLines];
	for (int i = 0; i < countLines; i++) {
		shapes[i] = IdentifyShapeToCalcArea(shapeVertices[i].numArr, shapeVertices[i].sizeOfArr);
		figure.addShape(shapes[i]);
	}

	std::cout << "\nThe two closest shapes: \n";
	const int numShapes = 2;
	for (int i = 0; i < numShapes; i++) {
		std::cout << figure.getClosest(shapes[0], numShapes)[i]->getType() << '\n';
	}

	for (int i = 0; i < countLines; i++) {
		delete shapes[i];
		delete shapeVertices[i].numArr;
	}

	delete[] shapeVertices;
	delete[] shapes;

	/*
	Vertices coordsForShape1;
	Vertices coordsForShape2;

	coordsForShape1.numArr = ReadFileAndStoreValues("combo.txt", coordsForShape1.sizeOfArr, ReadLine::first);
	Shape* shape1 = IdentifyShapeToCalcArea(coordsForShape1.numArr, coordsForShape1.sizeOfArr);
	
	coordsForShape2.numArr = ReadFileAndStoreValues("combo.txt", coordsForShape2.sizeOfArr, ReadLine::second);
	Shape* shape2 = IdentifyShapeToCalcArea(coordsForShape2.numArr, coordsForShape2.sizeOfArr);

	Shape* resultShapeArr = *shape1 + *shape2;
	Vertices resultVertices(resultShapeArr->getComboArray(), resultShapeArr->getSizeOfNewSize());
	
	Shape* resultShape = IdentifyShapeToCalcArea(resultShapeArr->getComboArray(), resultShapeArr->getSizeOfNewSize());
	std::cout << "Input: " << resultVertices;
	std::cout << "\tArea: " << resultShape->area() << std::endl;
	
	Figure fig;
	fig.addShape(shape1);
	fig.addShape(shape2);
	fig.addShape(resultShape);

	std::cout << "\nThe two closest shapes: \n";
	const int numShapes = 2;
	for (int i = 0; i < numShapes; i++) {
		std::cout << fig.getClosest(shape1, numShapes)[i]->getType() << '\n';
	}

	delete shape1;
	delete shape2;
	delete resultShape;
	delete[] coordsForShape1.numArr;
	delete[] coordsForShape2.numArr;
	*/
	getchar();
}

Shape* IdentifyShapeToCalcArea(double coordinates[], const int numOfElements) {
	Shape* shape = nullptr;

	/* These numbers are how many coordinates the file has
	* both x and y coordinates are counted.
	*/
	const int numOfCoordsForPoint = 2;
	const int numOfCoordsForLine = 4;
	const int numOfCoordsForTriangle = 6;

	if (numOfElements == numOfCoordsForPoint) {
		shape = new Point(coordinates[0], coordinates[1]);
	}
	else if (numOfElements == numOfCoordsForLine) {
		shape = new Line(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
	}
	else if (numOfElements == numOfCoordsForTriangle) {
		shape = new Triangle(coordinates[0], coordinates[1], coordinates[2], coordinates[3], coordinates[4], coordinates[5]);
	}
	else {
		shape = new Polygon(coordinates, numOfElements);
	}

	return shape;
}

double* ReadFileAndStoreValues(std::string fileName, int& numOfElements, ReadLine readLine) {
	std::ifstream file = std::ifstream(fileName);

	if (file.fail()) {
		std::cout << "Error: Couldn't open file!";
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	std::string line = "";
	getline(file, line);

	if (readLine == ReadLine::second) {
		line = "";
		getline(file, line);
	}

	std::string::size_type nextVal;
	unsigned int tmpCount = 0;
	unsigned int size = 1;
	double* coords = new double[size];
	for (unsigned int i = 0; i < line.length() && tmpCount < line.length(); i++) {
		coords[i] = std::stod(line.substr(tmpCount, line.length()), &nextVal);

		// Expand array
		double* tempArr = new double[size + 1];

		for (unsigned int i = 0; i < size; i++)
			tempArr[i] = coords[i];
		delete[] coords;
		coords = nullptr;
		coords = tempArr;

		size++;
		tmpCount += nextVal;
	}

	numOfElements = size - 1;

	return coords;
}

double* convertToArray(const std::string& line, int& numOfElements) {

	std::string::size_type nextVal;
	unsigned int tmpCount = 0;
	unsigned int size = 1;
	double* coords = new double[size];
	for (unsigned int i = 0; i < line.length() && tmpCount < line.length(); i++) {
		coords[i] = std::stod(line.substr(tmpCount, line.length()), &nextVal);

		// Expand array
		double* tempArr = new double[size + 1];

		for (unsigned int i = 0; i < size; i++)
			tempArr[i] = coords[i];
		delete[] coords;
		coords = nullptr;
		coords = tempArr;

		size++;
		tmpCount += nextVal;
	}

	numOfElements = size - 1;

	return coords;
}

Vertices* ReadFileAndStoreValues(const std::string& fileName, int& countLines) {
	std::ifstream file = std::ifstream(fileName);

	if (file.fail()) {
		std::cout << "Error: Couldn't open file!";
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	std::string line = "";
	while (getline(file, line)) {
		countLines++;
	}
	file.clear();
	file.seekg(0);

	line = "";
	std::string* contentOfLines = new std::string[countLines];
	int counter = 0;
	while (getline(file, line)) {
		std::cout << line << '\n';
		contentOfLines[counter] = line;
		counter++;
	}
	
	std::cout << "\nLines: " << countLines << '\n';

	Vertices* vertices = new Vertices[countLines];
	for (int i = 0; i < countLines; i++) {
		vertices[i].numArr = convertToArray(contentOfLines[i], vertices[i].sizeOfArr);
	}

	delete[] contentOfLines;
	return vertices;
}

std::ostream& operator<<(std::ostream& out, const Vertices& vertices) {
	const double MAX_DECIMALS = 1000.0;
	for (int i = 0; i < vertices.sizeOfArr; i++) {
		out << round(MAX_DECIMALS * vertices.numArr[i]) / MAX_DECIMALS << " ";
	}
	return out;
}