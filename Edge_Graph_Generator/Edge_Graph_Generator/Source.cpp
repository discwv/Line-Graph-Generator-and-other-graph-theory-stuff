#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

#define PAIR(x,y) pair<int, int> (x,y)

vector<vector<bool>> BuildEdgeGraph(vector<vector<bool>> inputGraph)
{
	int edgeCount = 0;
	unordered_map<pair<int,int>,int> myHash;

	//  Find every edge in the original graph
	for(int row = 0; row < inputGraph.size(); row++)
	{
		for(int col = 0; col < inputGraph[row].size(); col++)
		{
			if (inputGraph[row][col] == true && myHash.find(PAIR(row,col)) == myHash.end)
			{
				myHash[PAIR(row,col)] = edgeCount;
				myHash[PAIR(col,row)] = edgeCount;
				edgeCount++;
			}
		}
	}

	//  Make new matrix with new dimensions
	vector<vector<bool>> newGraph(edgeCount,vector<bool>(edgeCount,false));
	
	//  Fill new matrix
	for(int row = 0; row < inputGraph.size(); row++)
	{
		for(int col = row; col < inputGraph[row].size(); col++)
		{
			if (inputGraph[row][col] == true) //  If current value is an edge, check all values in current row
			{
				int currentHash = myHash[PAIR(row,col)];
				for(int edgeCol = 0; edgeCol < inputGraph[row].size(); edgeCol++)
				{
					if(inputGraph[row][edgeCol] == true && edgeCol != col) //  If it's an edge, add a new edge to the new graph
					{
						int incedentHash = myHash[PAIR(row,edgeCol)];
						newGraph[currentHash][incedentHash] = true;
						newGraph[incedentHash][currentHash] = true;
					}
				}
			}
		}
	}

	return newGraph;
}
