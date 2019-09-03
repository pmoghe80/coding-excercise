#include <iostream>
#include <vector>
using namespace std;

/*
 * This function was inefficient when the first loop was not
 * commented where for every index we had another loop for
 * traversing ahead. But current code is efficient one with O(n)
 * complexity.
 */ 
void SubArrInEff (vector<int> *cont, int sum) {
    vector<int>::iterator it = cont->begin();
    vector<int>::iterator it1 = cont->begin();
    int tmp_sum = 0;
    bool found_sub = false;

    //while (it != cont->end()) {
       it1 = it; 
       while (it1 != cont->end()) {
           tmp_sum = tmp_sum + *it1;
           if (tmp_sum == sum) {                 
               found_sub = true;
               break;
           } else if (tmp_sum > sum) {
                while (tmp_sum > sum) {
                      tmp_sum = tmp_sum - *it;
                      it++;
                }
                continue;
           }
           it1++;
       }
       if (found_sub) {
           cout << "Find Sub starting at " << *it <<  " and ending " << *it1 << endl;
           return;
           //break;
       }
      // tmp_sum = 0;
      // it++;         
    //}
}

int main() {
   int num_arr[] = {2,2,3,4,5,6,7,8,9,10};
   vector<int> num(num_arr, num_arr + sizeof(num_arr)/sizeof(int));

   SubArrInEff(&num, 11);
   return 0;  
}

