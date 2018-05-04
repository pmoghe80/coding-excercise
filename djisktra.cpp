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

using namespace std;

class Gnode {
  public:
   int vertex;
   Gnode *next;
   Gnode (int vertex) {
       this->vertex = vertex;
       this->next = NULL;
   } 
};

class Graph {

  public:
    Gnode **adjList;
    const int num_vertex;
    const int num_edges;
    const float gdensity;

    //Constructor with default arguments and intializing const attributes
    Graph (int vertex = 0, int edges = 0, float density = .1): num_vertex(vertex), num_edges(edges), gdensity(density) {
          adjList =  new  Gnode * [num_vertex];
          for (int i=0; i < num_vertex; i++) {
              adjList[i] = new Gnode(i);
          }
    }

    void addEdge (int v1, int v2) {
         Gnode *src_vrtx = adjList[v1];
         if (!src_vrtx) {
            cout<<"Invalid source vertex index"<<endl;
            return;
         } else if (v2 > num_vertex) {
            cout<<"Invalid dest vertex"<<endl;
            return;
         }      
         
         Gnode * gn = new Gnode(v2);
         if (src_vrtx->next == NULL) {
             //cout<<"Empty, Added Edge between vertex "<< v1 <<" and vertex "<< v2 <<endl;
             src_vrtx->next = gn;
             gn->next = NULL; 
             return;
         }   
         gn->next = src_vrtx->next;
         src_vrtx->next = gn;
         //cout<<"Added Edge between vertex "<< v1 <<" and vertex "<< v2 <<endl;
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
                  addEdge(i,j);
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
           Gnode *n = adjList[i];
           while (n) {
              cout << n->vertex+1 <<" ";
              n = n->next;
           }
           cout << endl;
       }
    }
};

int main() {
   Graph g1(5, 6); //= new Graph;
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
