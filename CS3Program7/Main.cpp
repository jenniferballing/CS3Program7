#include "GraphNode.h"
#include<fstream>
#include<queue>

void topoFunc(GraphNode arr[], int numNodes);
void depthFirst(GraphNode arr[], int numNodes);
string recursePrint(GraphNode arr[], int i);
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
string recursePrint(GraphNode arr[], int i)
{
	//Check for visited flag and check for end of the line
	vector <Dependents> temp = arr[i].getDepVec();
	int size = temp.size();
	if (arr[i].getVisited() == true) return "";
	else
	{
		arr[i].setVisited(true);
		return arr[i].getName() + " " + recursePrint( );
	}
}
