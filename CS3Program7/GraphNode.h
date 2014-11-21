#ifndef GRAPHNODE_H
#define GRAPHNODE_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Dependents
{
	char name;
	int edgeWeight;
public:
	Dependents();
	Dependents(char, int);
	char getName();
	int getEdge();
	void setName(char);
	void setEdge(int);
};
class GraphNode
{
	char name;
	bool visited;
	bool isDependent;
	vector < Dependents > depVec;
	int nDist;
public:
	GraphNode();
	GraphNode(char);
	void setName( char);
	void setVisited(bool);
	void setDependent(bool);
	void addDependents(Dependents);
	void setNDist(int);

	char getName();
	bool getVisited();
	bool getDependent();
	vector<Dependents> getDepVec();
	int getNDist();

	~GraphNode();
};

#endif;