#include "Graph.h"

void Graph::UNDAddEdge (int v1, int v2) {
	adjList[v1].insert(adjList[v1].begin(), v2);
	adjList[v2].insert(adjList[v2].begin(), v1);
	e++;
}

void Graph::DAddEdge (int v1, int v2) {
	adjList[v1].insert(adjList[v1].begin(), v2);
	e++;
}

/*To detect cycle in directed Graph*/
void Graph::DetectCycleDFS (int v, bool *visited, bool *pushed)  {
	if (pushed[v]) {
		cout << "There is a cycle at " << v << endl;
		return;
	}
        //pushed[v] = true;
        visited[v] = true;
	list<int>::iterator it = adjList[v].begin();
	while (it != adjList[v].end()) {
		if (!visited[*it]) {
		    DetectCycleDFS(*it, visited, pushed);
		} else if (visited[*it] && pushed[*it]) {
		    cout << "There is a cycle at " << *it << endl;
		}

		it++;
	}
        pushed[v] = true;	
}


void Graph::DFSUtil (int v, bool *visited) {
	if (visited[v])  {
		return;
	}	
	visited[v] = true;
	list<int>::iterator it = adjList[v].begin();
	cout << v << " " ;
	while (it != adjList[v].end()) {
		if (!visited[*it]) {
		       DFSUtil(*it, visited);
		} 
                it++;
        }		
}

void Graph::DFS (int v) {
	bool *visited = new bool(this->v);
	bool *pushed = new bool(this->v);
	int i=0;

	while (i < this->v) {
		pushed[i]    = false;
		visited[i++] = false;
	}

        for (int j=0; j < this->v; j++) {
	    if (!visited[j]) {
	        //DFSUtil(j, visited);
		DetectCycleDFS(j, visited, pushed);
	    }
	}
        cout << endl;	
}


void Graph::BFSUtil (int v, bool *visited) {
	bfsq.push(v);
	visited[v] = true;
	while (!bfsq.empty()) {
		int itm = bfsq.front();
                bfsq.pop();
		cout << itm << " " ;
		list<int>::iterator it = adjList[itm].begin();
		while (it != adjList[itm].end()) {
			if (!visited[*it]) {
	                        visited[*it] = true;
				bfsq.push(*it);
			}
			it++;
		}
	}	
}		

void Graph::BFS (int v) {
	bool *visited = new bool(this->v);
	int i = 0;

        while (i < this->v) {
	      visited[i++] = false;
        }

        BFSUtil(0, visited);	
	cout<<endl;
}	

/*To Detect Cycle in UnDirected Graph*/
bool Graph::DCycleUtil (int i, vector<bool> &visited, int *parent) {
    visited[i] = true;
    list<int>::iterator it = adjList[i].begin();  
    while (it != adjList[i].end()) {
	   if (!visited[*it]) {
		  if (DCycleUtil(*it, visited, &i)) {
			  return true;
	          }  
           } else if (*it != *parent) {
                cout << "Loop Found at Adj Node " << *it << " for Node " << i<<endl;
		return true;
           }
           it++;
    }	   
}

void Graph::DCycle() {
    vector<bool> visited(this->v, false);
    int i = 0;

    while (i < this->v) {
        if (!visited[i]) {
            if (DCycleUtil(i, visited, NULL)) {
		    return;
            }		    
        }
	i++;
    }	    
    
}

void Graph::TopoSortUtil (int k, bool *visited, stack<int> &st) {
    int i = 0;
    list<int>::iterator it = adjList[k].begin();
    visited[k] = true;
    while (it != adjList[k].end()) {
	    if (!visited[*it]) {
                TopoSortUtil(*it, visited, st);
            }
	    it++;
    }	    
    st.push(k); 
}

void Graph::TopoSort () {
   int i=0;
   bool visited[v];
   stack<int> topoStack;
   while (i < v) {
	 visited[i++] = false;
   }

   for (i=0; i < v; i++) {
       if (!visited[i]) {
          TopoSortUtil(i, visited, topoStack);
       }
   }
   while (!topoStack.empty()) {
       int m = topoStack.top();
       topoStack.pop();
       printf("%d ", m);       
   }
   printf("\n");   
}

int main() {
	Graph g(6);
	//g.UNDAddEdge(0,1);
	//g.UNDAddEdge(1,2);
	//g.UNDAddEdge(0,2);
	//g.UNDAddEdge(2,3);
	//g.UNDAddEdge(3,4);
	//g.AddEdge(3, 1);
	/*g.AddEdge(4,6);
	g.AddEdge(5,7);
	g.AddEdge(6,8);
	g.AddEdge(7,9);
	g.AddEdge(8,9);
	g.AddEdge(9,10);
	g.AddEdge(10,0);*/
	//g.DFS(0);
	//g.BFS(0);
	//g.DCycle();
        g.DAddEdge(0, 5);
        g.DAddEdge(5, 2);
        g.DAddEdge(2, 3);
        g.DAddEdge(3, 1);
        g.DAddEdge(4,0);	
        g.DAddEdge(4,1);	
        g.TopoSort();
	return(0);
}	

  	 
		 
