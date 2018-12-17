#include "stdafx.h"
#include "Figure.hpp"

Figure::Figure() : capacity(GROWTH_STEP), size(0) {
	this->groupOfShapes = new Shape*[capacity];
}

Figure::~Figure() {
	delete[] groupOfShapes;
}

void Figure::addShape(Shape* shape) {
	if (size + 1 > capacity) {
		capacity += GROWTH_STEP;
		Shape** tempArr = new Shape*[capacity];
		for (unsigned int i = 0; i < size; i++) {
			tempArr[i] = groupOfShapes[i];
		}
		delete[] groupOfShapes;
		groupOfShapes = tempArr;
	}

	this->groupOfShapes[size] = shape;
	this->size++;
}

Shape* Figure::getShape(int index) const {
	return groupOfShapes[index];
}

Figure::Rectangle Figure::getBoundingBox() const {

	int totalSize = 0;
	unsigned int row = 0;
	int col = 0;

	// Calculate the total size
	for (row = 0; row < size; row++) {
		for (col = 0; col < groupOfShapes[row]->getSizeOfVertices(); col++) {
			totalSize++;
		}
	}

	// Put all coordinates in an array
	double* coordsAll = new double[totalSize];
	int index = 0;
	for (unsigned int row = 0; row < size; row++) {
		for (int col = 0; col < groupOfShapes[row]->getSizeOfVertices(); col++) {
			coordsAll[index] = groupOfShapes[row]->getVerticesArray()[col];
			index++;
		}
	}

	// Sort out x and y coordinates
	const int halfSize = totalSize / 2;
	double* coordsX = new double[halfSize];
	double* coordsY = new double[halfSize];

	int indexEvenX = 0;
	int indexOddY = 0;
	for (int i = 0; i < halfSize; i++) {
		indexEvenX = 2 * i;
		indexOddY = 2 * i + 1;

		coordsX[i] = coordsAll[indexEvenX];
		coordsY[i] = coordsAll[indexOddY];
	}

	sortArray(coordsX, halfSize);
	sortArray(coordsY, halfSize);

	Rectangle minRect(coordsX[0], coordsY[0], coordsX[halfSize - 1], coordsY[halfSize - 1]);

	delete[] coordsAll;
	delete[] coordsX;
	delete[] coordsY;

	return minRect;
}

template <typename T>
void Figure::sortArray(T* coords, const int size) const {

	for (int i = 0; i < size - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < size; j++) {
			if (coords[j] < coords[minIndex])
				minIndex = j;
		}
		
		T temp = coords[minIndex];
		coords[minIndex] = coords[i];
		coords[i] = temp;
	}
}

template <typename T>
void Figure::swap(T& objFirst, T& objSecond) {
	T temp = objFirst; 
	objFirst = objSecond;
	objSecond = temp;
}

void Figure::sortByDistance(Shape* shapes[], double distances[], const int size) {
	if (size == 1)
		return;

	for (int i = 0; i < size - 1; i++) {
		int next = i + 1;
		if (distances[i] > distances[next]) {
			swap(i, next);
			swap(distances[i], distances[next]);
			swap(shapes[i], shapes[next]);
		}
	}

	sortByDistance(shapes, distances, size - 1);
}

Shape** Figure::getClosest(Shape* location, int numOfShapes) {

	double* distances = new double[size];
	for (unsigned int i = 0; i < size; i++) {
		distances[i] = this->groupOfShapes[i]->distance(location);
	}

	sortByDistance(groupOfShapes, distances, size);
	for (unsigned int i = 0; i < size - 1 && static_cast<unsigned int>(numOfShapes) < size; i++) {
		for (unsigned int j = 0; j < size; j++)
			groupOfShapes[i] = groupOfShapes[i + 1];
	}

	delete[] distances;
	return groupOfShapes;
}

int Figure::getSize() const {
	return size;
}