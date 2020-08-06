#include "Graph.h"

Graph & BuildPrimeGraph (vector<int> primes, int k) {
	vector<int>::iterator it = primes.begin();
	int level = 0;
	int len = primes.len();
	int num = 0;
	for (int i=0 i < len; i++) {
	    if (num > k) {
	        break;
            }
            num = num + pow(len, i);
	    level++;
	}

        Graph *g = new Graph(num);
	Node  *n = new Node;
	n->v = 1;
	for (int i=0; i<len; i++) {
            Node *tmp = new Node;
            tmp->v = primes[i];	    
	    g->UNAddEdge(n, tmp);
	} 
}
        	

		

     
