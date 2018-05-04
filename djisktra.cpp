#include <iostream>

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
              adjList[i] = new Gnode(i+1);
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
         
         Gnode gn(v2);
         if (src_vrtx->next == NULL) {
             cout<<"Empty, Added Edge between vertex "<< v1 <<" and vertex "<< v2 <<endl;
             src_vrtx->next = &gn;
             return;
         }   
         gn.next = src_vrtx->next;
         src_vrtx->next = &gn;
         cout<<"Added Edge between vertex "<< v1 <<" and vertex "<< v2 <<endl;
         return;
    }

    void printGraphAttributes(void) {
      cout <<"Vertices: "<< num_vertex<<endl;
      cout<<"Edges: "<<num_edges<<endl;
      cout<<"Density: "<<gdensity<<endl;
    }
};

int main() {
   Graph g1(5, 6); //= new Graph;
   Graph g2(13, 5, .2); // = new Graph(13, 5, .2);  
   g1.printGraphAttributes();
   g2.printGraphAttributes();
   g1.addEdge(1,5);
   g1.addEdge(1,4);
   g1.addEdge(2,5);
   g1.addEdge(3,4);
   g1.addEdge(4,5);
   g1.addEdge(2,3);
   return 0;
}      
