#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


template<typename S, typename T> struct hash<pair<S, T>>
{
	inline size_t operator()(const pair<S, T> & v) const
	{
		size_t seed = 0;
		::hash_combine(seed, v.first);
		::hash_combine(seed, v.second);
		return seed;
	}
};


vector<vector<bool>> BuildEdgeGraph(vector<vector<bool>> inputGraph)
{
	int edgeCount = 0;
	unordered_map<pair<int,int>,int> myHash;

	//  Find every edge in the original graph
	for(int row = 0; row < inputGraph.size(); row++)
	{
		for(int col = 0; col < inputGraph[row].size(); col++)
		{
			if (inputGraph[row][col] == true && myHash.find(pair<int,int>(row,col)) == myHash.end())
			{
				myHash[pair<int,int>(row,col)] = edgeCount;
				myHash[pair<int,int>(col,row)] = edgeCount;
				edgeCount++;
			}
		}
	}

	//  Make new matrix with new dimensions
	vector<vector<bool>> newGraph(edgeCount,vector<bool>(edgeCount,false));

	//  Fill new matrix
	for(int row = 0; row < inputGraph.size(); row++)
	{
		for(int col = 0; col < inputGraph[row].size(); col++)
		{
			if (inputGraph[row][col] == true) //  If current value is an edge, check all values in current row
			{
				int currentHash = myHash[pair<int,int>(row,col)];
				for(int edgeCol = 0; edgeCol < inputGraph[row].size(); edgeCol++)
				{
					if(inputGraph[row][edgeCol] == true && edgeCol != col) //  If it's an edge, add a new edge to the new graph
					{
						int incedentHash = myHash[pair<int,int>(row,edgeCol)];
						newGraph[currentHash][incedentHash] = true;
						newGraph[incedentHash][currentHash] = true;
					}
				}
			}
		}
	}

	return newGraph;
}

int main()
{
	string fileName;
	cout << "File: ";
	cin >> fileName;

	ifstream inputFile(fileName);
	vector<vector<bool>> myGraph;

	while(inputFile.eof() == false)
	{
		string line;
		getline(inputFile,line);
		vector<bool> myVec;
		for(int cha = 0; cha < line.length(); cha++)
		{
			if(line[cha] == '0') myVec.push_back(false);
			else if(line[cha] == '1') myVec.push_back(true);
		}
		myGraph.push_back(myVec);
	}

	for(int i = 0; i < 5; i++)
	{
		cout << endl << to_string(myGraph.size());
		myGraph = BuildEdgeGraph(myGraph);
	}
	

	/*for(int i = 0; i < myGraph.size(); i++)
	{
		for(int j = 0; j < myGraph[i].size(); j++)
		{
			if(myGraph[i][j]) cout << "1 ";
			else cout << "0 ";
		}
		cout << endl;
	}

	vector<vector<bool>> newGraph = BuildEdgeGraph(myGraph);

	for(int i = 0; i < newGraph.size(); i++)
	{
		for(int j = 0; j < newGraph[i].size(); j++)
		{
			if(newGraph[i][j]) cout << "1 ";
			else cout << "0 ";
		}
		cout << endl;
	}*/


	char boop;
	cin >> boop;

}



