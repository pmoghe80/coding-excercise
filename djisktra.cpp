/*************************************************************************************************************
 * Implement undirected graph using either adjacency list or matrix (comment on choice)

 * Write set of constructors for declaring and initializing graph

 *  Write a function to produce randomly generated set of edges with positive distances

 * Random graph function should have edge density as parameter, 
 * graph with density 0.1 would have 10% of random edges picked with random distance range. 
 * This function should run through all possible edges (i,j) and place the edge in the graph 
 * if a random probability calculation is less than the density. 

 * Compute for a set of randomly generated graphs an average shortest path.
 
 RANDOM EDGE SELECTION ALGORITHM
  1) Loop through all the vertices
  2) For each vertex go through all the other vertex in a nested loop 
  3) For each pair of vertices generate a random number between 0...100 (rand()%100)
  4) If the generated number is less than "density*100" add this edge
  5) If more then skip this edge
*************************************************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>

#define MAX_PQ 10

using namespace std;

template <typename T>
class PriorityQueue {
   private:
      vector <T> pqueue;
      int pqsz;
  public:
     /*inline*/ int ParentIndx(int x) { return x/2;}
     /*inline*/ int LChildIndx(int x) { return 2*x; }
     /*inline*/ int RChildIndx(int x) { return 2*x + 1;}
     T ExtractMax();
     void ShiftUp (int x); 
     void ShiftDown (int x);
     void ChangePriority(T * x, int *wt, int prio);
     void pqadd(T item); 
     void pqremove(T item);  
     T ExtractMin();
     void Swap(T it1, T it2);
};

template <class T>
void PriorityQueue<T>::Swap(T it1, T it2) {
    T tmp = it1;
    it1 = it2;
    it2 = tmp;
}

template <class T>
void PriorityQueue<T>::ShiftUp(int x) {
    while (x >= 1 && pqueue[x] < pqueue[ParentIndx(x)]) {
         Swap(pqueue[x], pqueue[ParentIndx(x)]);
         x = ParentIndx(x);  
    }
}

template <class T>
void PriorityQueue<T>::ShiftDown(int x) {
   int maxindx = x;
   if (pqueue[maxindx] > pqueue[LChildIndx(x)]) {
      maxindx = LChildIndx(x);
   }

   if (pqueue[maxindx] > pqueue[RChildIndx(x)]) {
      maxindx = RChildIndx(x);
   }

   if (x != maxindx) {
      Swap(pqueue[x], pqueue[maxindx]);
   }
   ShiftDown(maxindx);           
}

template <class T>
void PriorityQueue<T>::pqadd(T item) {
     if (pqsz >= MAX_PQ) {
        cout << "Queue Full" << endl;
        return;
     }
     pqsz = pqsz + 1;
     pqueue[pqsz] = item;
     ShiftUp(pqsz); 
}

template <class T>
void PriorityQueue<T>::pqremove(T item) {
     int i;

     for (i=0; i<= pqsz; i++) {
         if (pqueue[i] == item) {
             break;
         }
     }

     if ( i > pqsz) { 
        cout << "Object not found in PQ" << endl;
        return;
     } else if (i == pqsz) {
        pqsz--;
     } else {
         T tmp = pqueue[i];
         pqueue[i] = pqueue[pqsz];
         pqsz--;
         ShiftDown(i);
     }
     return;
}    
      
     
template <class T>
T PriorityQueue<T>::ExtractMin() {
    T result = pqueue[1];
    pqueue[1] = pqueue[pqsz--];
    ShiftDown(1);
    return result;
}

template <class T>
void PriorityQueue<T>::ChangePriority(T * x, int *cur_pri, int prio) {
     if (*cur_pri == prio) {
         return;
     }

     int i;
     for (i=0; i<= pqsz; i++) {
         if (pqueue[i] == x) {
             break;
         }
     }
     //assert(i <= pqsz);
     int tmp = *cur_pri;
     *cur_pri = prio;
     if (tmp > prio) {
         ShiftUp(i);
     } else {
         ShiftDown(i);
     }
} 
  

class Gnode {
  public:
   int vertex;
   bool visited;
   int weight;

   Gnode (int vertex) {
       this->vertex = vertex;
       //this->next = NULL;
       visited = false;
   } 
};

class Edge {
    public:
        Gnode *src;
        Gnode *dst;
        Edge *next;
        int weight; 
        void  EdgeInit (Gnode *src, Gnode *dst, int wt, Edge *next = NULL) {
            this->src = src;
            this->dst = dst;
            this->next = next;
            weight = wt;
        }
   
        bool operator >(const Edge &ed) {
            if (weight > ed.weight) {
                return true;
            } else {
                return false;
            }
        }    

        bool operator <(const Edge &ed) {
            if (weight < ed.weight) {
                return true;
            } else {
                return false;
            }
        }

        bool operator >=(const Edge &ed) {
            if (weight >= ed.weight) {
                return true;
            } else {
                return false;
            }
        }

        bool operator <=(const Edge &ed) {
            if (weight <= ed.weight) {
                return true;
            } else {
                return false;
            }
        }
};   

class Graph {

  public:
    Edge **adjList;
    Gnode ** nodeTable;
    const int num_vertex;
    const int num_edges;
    const float gdensity;

    //Constructor with default arguments and intializing const attributes
    Graph (int vertex = 0, int edges = 0, float density = .1): num_vertex(vertex), num_edges(edges), gdensity(density) {
          adjList =  new  Edge * [num_vertex];
          nodeTable = new Gnode * [num_vertex];
          for (int i=0; i < num_vertex; i++) {
              adjList[i] = NULL;
              nodeTable[i] = new Gnode(i);
          }
    }

    int V(void) {
       return num_vertex;
    } 
    
    int E() {
       return num_edges;
    }
    
    bool adjacent (int x, int y) {
         Gnode *src_vrtx = nodeTable[x];
         if (!src_vrtx) {
             cout << "Invalid source vertex " << x << endl;
             return false;
         }
         Edge *edg = adjList[x]; 
         if (!edg) {
            cout << "No edges from source vertex " << x << endl;
            return false;
         }

         while (edg && edg->dst->vertex != y) {
               edg = edg->next;
         }
    
         if (!edg) {
            cout << "Edge " << x << "-->" << y << " not found"<< endl;
            return false;
         } else {
            return true;
         }
    }    

    void add (int v1, int v2, int wt) {
         addEdge(v1,v2, wt);
    }
               
    void addEdge (int v1, int v2, int wt) {
         Gnode *src_vrtx = nodeTable[v1];
         if (!src_vrtx) {
            cout<<"Invalid source vertex index"<<endl;
            return;
         } else if (v2 > num_vertex) {
            cout<<"Invalid dest vertex"<<endl;
            return;
         }      
         
         Gnode * gn = nodeTable[v2];
         Edge *edg = new Edge;
         if (!adjList[v1]) {
             adjList[v1] = edg;
             edg->EdgeInit(src_vrtx, gn, wt, adjList[v1]->next); 
             return;   
         }    
         edg->EdgeInit(src_vrtx, gn, wt, adjList[v1]->next); 
         adjList[v1]->next = edg;
         return;
    }

    void buildRandomGraph(void) {
        for (int i=0; i<num_vertex; i++) {
           for (int j=0; j<num_vertex; j++) {
               if (i==j) {
                  continue;
               } 
               int is_edge = (rand()%100) < (gdensity*100);
               if (is_edge) {
                  int wt = rand()%15;
                  addEdge(i,j, wt);
               } 
           }
        }
    }     

    
    void printGraphAttributes(void) {
      cout <<"Vertices: "<< num_vertex<<endl;
      cout<<"Edges: "<<num_edges<<endl;
      cout<<"Density: "<<gdensity<<endl;
    }

    void printGraph() {
       for (int i=0; i<num_vertex; i++) {
           Edge *n = adjList[i];
           while (n) {
              cout << n->src->vertex+1 <<" ";
              n = n->next;
           }
           cout << endl;
       }
    }

    //Edge * getEdge
};

class ShortestPath: public Graph {
    private:
       int cost;
       PriorityQueue<Gnode *> pq;
       vector<Edge *> path;
    public:
       void Path(int u, int v);
};

void ShortestPath::Path (int u, int v) {
      Gnode *src = nodeTable[u];
      Gnode *dst = nodeTable[v];
      
      src->weight = 0;
      Edge * src_edg = adjList[u];
      
      Edge * tmp_edg = src_edg;
      path.push_back(src_edg);
      while (tmp_edg) {
          if (tmp_edg->dst) 
          tmp_edg->dst->weight = src_edg->weight + src->weight;
          pq.pqadd(tmp_edg->dst);

      }    
}

int main() {
   Graph g1(15, 6); //= new Graph;
   Graph g2(13, 5, .2); // = new Graph(13, 5, .2);  
   cout << "Building g1 graph"<<endl;
   g1.buildRandomGraph();
   g1.printGraphAttributes();
   g1.printGraph();
   cout << endl <<endl;
   cout << "Building g2 graph"<<endl;
   g2.printGraphAttributes();
   g2.buildRandomGraph();
   g2.printGraph();
   /*g1.addEdge(1,5);
   g1.addEdge(1,4);
   g1.addEdge(2,5);
   g1.addEdge(3,4);
   g1.addEdge(4,5);
   g1.addEdge(2,3);*/
   return 0;
}      
