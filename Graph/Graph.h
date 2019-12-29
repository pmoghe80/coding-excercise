#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <queue>
#include <stack>

using namespace std;

class Graph {
   public:	
	Graph(int vrt): v(vrt) {
              adjList = new list<int> [v];
              e = 0; 	      
        }
	void DAddEdge (int v1, int v2); 
	void UNDAddEdge (int v1, int v2); 
        void DFS (int v);
	void DFSUtil(int v, bool *visited); 
	void DetectCycleDFS(int v, bool *visited, bool *pushed);
	void BFS (int v);
        void BFSUtil(int v, bool *visited); 	
	void DCycle();
	bool DCycleUtil(int i, vector<bool> &visited, int *parent); 
	void TopoSort();
	void TopoSortUtil(int k, bool *visited, stack<int> &st);
   private:
       int v;
       int e;
       list<int> *adjList; 
       queue<int> bfsq;
};       


