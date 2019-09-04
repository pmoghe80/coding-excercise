#include <iostream>
#include <vector> 
#include <map>

using namespace std;

int CountTriplets (vector<int> num) {
    vector<int>::iterator outer = num.begin();
    vector<int>::iterator inner = num.begin();
    map<int, bool> mymap;
    int count_triplet = 0;
    
    for (auto& p : num) {
        mymap[p] = true;
    }
    
    while (outer != num.end()) {
        inner = outer++;
        while (inner != num.end()) {
            if (mymap[(*inner) + (*outer)]) {
                count_triplet++;
            }
            inner++;
        }
        outer++;
    }
    return count_triplet ? count_triplet : -1;
}

int main() {
	//code
	int tc;
	int size; 
	cin >> tc;
	for (int i=0; i < tc; i++) {
	    cin >> size;
	    vector<int> num(size);
	    for (int j = 0; j < size; j++) {
	        cin >> num[j];
	    }
	    int tmp=0;;
	    tmp = CountTriplets(num);
	    cout << tmp << endl;
	}
	
	return 0;
}
