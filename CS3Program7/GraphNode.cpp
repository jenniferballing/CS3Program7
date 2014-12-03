#include "GraphNode.h"

Dependents::Dependents()
{
	name = ' ';
	edgeWeight = 0;
}

Dependents::Dependents(char n, int e)
{
	name = n;
	edgeWeight = e;
}
char Dependents::getName()
{
	return name;
}
int Dependents::getEdge()
{
	return edgeWeight;
}
string Dependents::getPath()
{
	return path;
}
void Dependents::setName(char n)
{
	name = n;
}
void Dependents::setEdge(int e)
{
	edgeWeight = e;
}
void Dependents::setPath(string s)
{
	path = s;
}

GraphNode::GraphNode()
{
	name = ' ';
	visited = false;
	isDependent = false;
	depVec.clear();
	nDist = 0;
}

GraphNode::GraphNode(char n)
{
	name = n;
	visited = false;
	isDependent = false;
	depVec.clear();
	nDist = 0;
}

void GraphNode::setName(char n)
{
	name = n;
}
void GraphNode::setVisited(bool v)
{
	visited = v;
}
void GraphNode::setDependent(bool d)
{
	isDependent = d;
}
void GraphNode::addDependents(Dependents d)
{
	depVec.push_back(d);
}
void GraphNode::setNDist(int n)
{
	nDist = n;
}

char GraphNode::getName()
{
	return name;
}
bool GraphNode::getVisited()
{
	return visited;
}
bool GraphNode::getDependent()
{
	return isDependent;
}
vector<Dependents> GraphNode::getDepVec()
{
	return depVec;
}
int GraphNode::getNDist()
{
	return nDist;
}

GraphNode::~GraphNode()
{
}
