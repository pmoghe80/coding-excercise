#include <iostream>

using namespace std;

class Vertex {
    private:
      int label;
      int visited;
    public:
      Vertex (int i): label(i) {
          visited = 0;
      }
      int getLabel () {
         return label;
      }
      void setLabel (int i) {
          label = i;
      }
      int getVisited() {
          return visited;
      }
      void setVisited(int i) {
         visited = i;
      }
};
  
class Edge {
   private:
     Vertex *src;
     Vertex *dst;
     int wt;
     int indx;
     Edge *next;
   public:
      Edge(Vertex *src, Vertex *dst, int wt, int indx) {
          this->src = src;
          this->dst = dst;
          this->wt = wt;
          this->indx = indx;
          next = NULL;
      }

      int getWeight() {
        return wt;
      }

      int  getIndex() {
        return indx;
      }

      void setWeight(int w) {
         wt = w;
      }

      void setIndex(int i) {
         indx = i;
      }

     Vertex * getSource() {
          return src;
     }  

     void setSource(Vertex *v) {
          src = v;
     }  

     Vertex * getDestination() {
          return dst;
     }  

     void setDestination(Vertex *v) {
          dst = v;
     }  

     Edge * getNext () {
         return this->next;
     }
    
     void setNext (Edge *next) {
         this->next = next;
     }    
};
     
class Graph {
   private:
      int V;
      int E;
      int edge_count;
      Vertex **vertices;
      Edge  **adjList;

   public:
     Graph(int m, int n): V(m), E(n) {

        vertices = new Vertex*[V]; //Allocate array of pointer to vertex
        adjList  = new Edge*[V];  //Allocate buckets in adjacency List
        edge_count = 0;
 
        int i=0;
        while (i<V) {
          vertices[i] = new Vertex(i+1);
          adjList[i++]    = NULL;
        }
     } 
     
     int GetVertices() {
        return V;
     }

     int GetEdges() {
         return E;
     }
     
     Vertex * GetVertexAtIndex(int i) {
         if (i >= V) {
            return NULL;
         }
         return vertices[i];   
     }

     void AddEdge (int src, int dst, int wt) {
         Edge *e = new Edge(vertices[src-1], vertices[dst-1], wt, ++edge_count);
         Edge *tmp = adjList[src-1];
         adjList[src-1] = e;
         e->setNext(tmp);
     }

     //RESET the visited vertices
     void ResetGraphVisited() {
        int i=0;
        while (i<V) {
          vertices[i++]->setVisited(0);
        }
     } 

     //Depth First Search Graph Traversal
     void DFS (int label) {
         Edge *e = adjList[label-1];
         if (!e && !vertices[label-1]->getVisited()) {
            cout << label << " ";
            vertices[label-1]->setVisited(1);
            return;
         } else if (!e && vertices[label-1]->getVisited()) { 
             return;
         }
         Vertex *source = e->getSource();  
         Vertex *destination = e->getDestination();  
          
         if (source->getVisited()) {                    //Boundary Condition for recursive call, if no edge or verted already visited.
            return;          
         }

         source->setVisited(1);
         cout << source->getLabel() << " " ;    

         while (e) {
            destination = e->getDestination();  
            DFS(destination->getLabel());
            e = e->getNext();
         }
     }
};
     
int main() {
   Graph *g = new Graph(9, 25);
   g->AddEdge(1, 2, 1);
   g->AddEdge(2, 3, 1);
   g->AddEdge(3, 4, 1);
   g->AddEdge(4, 1, 1);
   g->AddEdge(2, 5, 1);
   g->AddEdge(3, 8, 1);
   g->AddEdge(5, 6, 1);
   g->AddEdge(6, 7, 1);
   g->AddEdge(7, 8, 1);
   g->AddEdge(8, 5, 1);
   int i=1;
   while (i < 9) {
    cout << "DFS from" << i << endl;
    g->DFS(i++);
    g->ResetGraphVisited();
    cout<<endl;
   }
}          
        

