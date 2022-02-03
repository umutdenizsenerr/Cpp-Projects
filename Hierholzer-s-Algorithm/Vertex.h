#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#ifndef VERTEX_H
#define VERTEX_H


class Vertex {

public:
	int ID;
	vector<int> outDegreeIDs;
	int outDegree;
	int inDegree;
	Vertex(int ID);


	};
#endif

Vertex::Vertex(int _ID){
	this->ID = _ID;
	this->outDegreeIDs;
	this->outDegree=0;
	this->inDegree=0;
}
