#include "GraphNode.h"
#include<fstream>
#include<queue>
#include <algorithm>

void topoFunc(GraphNode arr[], int numNodes);
void depthFirst(GraphNode arr[], int numNodes);
void recursePrint(GraphNode arr[], int i);
void dijkstras(GraphNode arr[], int numNodes);
bool mySort(Dependents a, Dependents b); 
void clearQ(queue<Dependents> &q);
void prims(GraphNode arr[], int numNodes);

int main()
{
	//set up file i/o
	fstream fin;
	fin.open("prog7.txt");
	int numNodes, numEdges, weight;
	char firstLetter, secondLetter;
	fin >> numNodes >> numEdges;

	//Read info from file and store info in array
	GraphNode arr[100];
	while (!fin.eof())
	{

		fin >> firstLetter >> secondLetter >> weight;
		int firstIndex = firstLetter - 'A';
		int secondIndex = secondLetter - 'A';
		
		//create first node
		if (arr[firstIndex].getName() == ' ')
		{
			GraphNode firstNode(firstLetter);
			Dependents newDep(secondLetter, weight);
			firstNode.addDependents(newDep);
			arr[firstIndex] = firstNode;
		}
		else
		{
			Dependents newDep(secondLetter, weight);
			arr[firstIndex].addDependents(newDep);
		}
		
		
		//create second node
		if (arr[secondIndex].getName() == ' ')
		{
			GraphNode secondNode(secondLetter);
			secondNode.setDependent(true);
			arr[secondIndex] = secondNode;
		}
		else
		{
			arr[secondIndex].setDependent(true);
		}		
	}

	//Part 1 Topographical Ordering
	topoFunc(arr, numNodes);

	//Part 2 Depth First Traversal
	depthFirst(arr, numNodes);

	//Part 3 Dijkstra's Algorithm
	dijkstras(arr, numNodes);

	//Part 4 Prim's Algorithm
	prims(arr, numNodes);

	return 0;
}

void topoFunc(GraphNode arr[], int numNodes)
{
	queue <GraphNode> list;
	vector <char> topo;
	int index = 0;

	//put non dependent nodes into list
	for (int i = 0; i < numNodes; i++)
	{
		if (arr[i].getDependent() == false) list.push(arr[i]);
	}

	//when there is no topo ordering
	if (list.size() < 1)cout << "Topological ordering does not exist for this graph.";
	
	//when there is topo ordering
	else
	{
		while (list.size() >0)
		{
			GraphNode node = list.front();
			//add to final list
			//check if its already there
			int count = 0;
			for (int i = 0; i < topo.size(); i++)
			{
				if(topo[i]==node.getName()) count ++;
			}
			if (count == 0)	topo.push_back( node.getName());
			
			//get dependents and add to list
			vector<Dependents> temp = arr[(node.getName() - 'A')].getDepVec();
			
			while(temp.size()>0)
			{
				GraphNode tempNode(temp.back().getName());
				if (arr[(temp.back().getName() - 'A')].getVisited() == false)
				{
					list.push(tempNode);
					arr[(temp.back().getName() - 'A')].setVisited(true);
				}
				temp.pop_back();
			}
			list.pop();
		}
		int size = topo.size();
		cout << "Topological Ordering: " << endl;
		for (int i = 0; i < size; i++)
		{
			cout << i << ": " << topo[i] << endl;
		}
	}
}
void depthFirst(GraphNode arr[], int numNodes)
{
	cout << "Depth first traversal: " << endl;
	//reset all visited flags to false
	for (int k = 0; k < numNodes; k++)
	{
		arr[k].setVisited(false);
	}

	//Find non dependent nodes and store in array
	GraphNode noDepArr[50];
	int index = 0;
	for (int i = 0; i < numNodes; i++)
	{
		if (arr[i].getDependent() == false)
		{
			noDepArr[index] = arr[i];
			recursePrint(arr, i);
			index++;
		}
	}
}
void recursePrint(GraphNode arr[], int i)
{
	//Check visited flag
	if (arr[i].getVisited() == true) return;

	//set visited flag and create dependents list
	arr[i].setVisited(true);
	cout << arr[i].getName() << " " << endl;

	//store indices of all dependents
	vector<Dependents> tempDep = arr[i].getDepVec();
	int size = tempDep.size();
	queue <int> intQ;
	for (int i = 0; i < size; i++)
	{
		intQ.push(tempDep[i].getName() - 'A');
	}

	//NULL= 0 need to fix array to be vector//
	while (intQ.size() > 0)
	{
		recursePrint(arr, intQ.front());
		intQ.pop();
	}
}
void dijkstras(GraphNode arr[], int numNodes)
{
	cout << "All Nodes, Shortest Path, using Dijkstra's Algorithm: " << endl;
	//make q
	queue<Dependents> q;	
	

	//loop through each letter
	int charNum = 0;
	while (charNum < numNodes-1)
	{
		clearQ(q);
		//store dependents 	//get the dependents of n
		vector<Dependents> tempV = arr[13].getDepVec();
		Dependents parent('N', 0);
		parent.setPath("N");
		
		char desiredChar = charNum + 'A';

		//print char path
		cout << "N:";
		cout << desiredChar;
		cout << " path is ";
		bool found = false;
		int totalCost = 0;
		while (!found)
		{		
			//loop through all letters and add any that have desired as a dependent to tempV before sort.
			int num = 0;
			while (num<numNodes)
			{				
				vector<Dependents> nDep = arr[num].getDepVec();
				int nSize = nDep.size();
				for (int i = 0; i < nSize; i++)
				{
					if (nDep.back().getName() == parent.getName())
					{
						
						Dependents newDep(arr[num].getName(), nDep.back().getEdge());
						tempV.push_back(newDep);
						nDep.pop_back();
					}
				}
				num++;
			}

			//increase the edge weight of each dependent
			int vSize = tempV.size();
			vector <Dependents> vec;
			for (int i = 0; i < vSize; i++)
			{
				Dependents node = tempV.back();
				node.setEdge(node.getEdge() + parent.getEdge());
				vec.push_back(node);
				tempV.pop_back();
			} 
			tempV = vec;

			//sort vector (backwards)
			sort(tempV.begin(), tempV.end(), mySort);

			//put dependents into the queue according to edgeweight
			int size = tempV.size();
			for (int i = 0; i < size; i++)
			{
				char name = tempV.back().getName();
				int cost = tempV.back().getEdge() + parent.getEdge();
				tempV.back().setPath(parent.getPath() + "->"+ name);
				q.push(tempV.back());
				tempV.pop_back();
			}

			//pull the first one off and enqueu its dependents with new edgewights in order of new edgeweight
			Dependents front = q.front();
			q.pop();

			//check for desired char
			if (front.getName() == desiredChar)
			{
				cout << front.getPath() << " Total Cost " <<front.getEdge()<<endl;
				found = true;
			}
			parent = front;
			int newIndex = front.getName() - 'A';
			tempV = arr[newIndex].getDepVec();
		}
		charNum++;
	}
}
void prims(GraphNode arr[], int numNodes)
{
	//make q
	queue<Dependents> q;


	//loop through each letter
	int charNum = 0, total = 0;
	Dependents front;
	while (charNum < numNodes - 1)
	{
		clearQ(q);
		//store dependents 	//get the dependents of n
		vector<Dependents> tempV = arr[13].getDepVec();
		Dependents parent('N', 0);
		parent.setPath("N");

		char desiredChar = charNum + 'A';
		bool found = false;
		int totalCost = 0;
		while (!found)
		{
			//loop through all letters and add any that have desired as a dependent to tempV before sort.
			int num = 0;
			while (num<numNodes)
			{
				vector<Dependents> nDep = arr[num].getDepVec();
				int nSize = nDep.size();
				for (int i = 0; i < nSize; i++)
				{
					if (nDep.back().getName() == parent.getName())
					{

						Dependents newDep(arr[num].getName(), nDep.back().getEdge());
						tempV.push_back(newDep);
						nDep.pop_back();
					}
				}
				num++;
			}

			//increase the edge weight of each dependent
			int vSize = tempV.size();
			vector <Dependents> vec;
			for (int i = 0; i < vSize; i++)
			{
				Dependents node = tempV.back();
				node.setEdge(node.getEdge() + parent.getEdge());
				vec.push_back(node);
				tempV.pop_back();
			}
			tempV = vec;

			//sort vector (backwards)
			sort(tempV.begin(), tempV.end(), mySort);

			//put dependents into the queue according to edgeweight
			int size = tempV.size();
			for (int i = 0; i < size; i++)
			{
				char name = tempV.back().getName();
				int cost = tempV.back().getEdge() + parent.getEdge();
				tempV.back().setPath(parent.getPath() + "->" + name);
				q.push(tempV.back());
				tempV.pop_back();
			}

			//pull the first one off and enqueu its dependents with new edgewights in order of new edgeweight
			front = q.front();
			q.pop();

			//check for desired char
			if (front.getName() == desiredChar)
			{
				total += front.getEdge();
				found = true;
			}
			parent = front;
			int newIndex = front.getName() - 'A';
			tempV = arr[newIndex].getDepVec();
		}
		charNum++;
	}
	cout << "Prims Algorithm: Min Spanning Tree: " << front.getEdge() << endl;
	
}

bool mySort(Dependents a, Dependents b) 
{
	return (a.getEdge() > b.getEdge());
}

void clearQ(queue<Dependents> &q)
{
	queue <Dependents> empty;
	swap(q, empty);
}