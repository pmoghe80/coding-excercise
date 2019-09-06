#include <bits/stdc++.h>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct IndFq{
    int indx;
    int fq;
};

vector<string> split_string(string);

// Complete the equalizeArray function below.
int equalizeArray(vector<int> arr) {
     sort(arr.begin(), arr.end())  ;
        int meta[arr.size()];
       int  curr_indx=0; 
       for (int i=0;i<arr.size();i++){
           meta[i]=0;
       }
      
      for (int i=0;i<=(arr.size()-1);i++){
           if  (arr[i]==arr[i+1])
                meta[curr_indx]++;
            else {
                curr_indx=i;
                meta[curr_indx]=1; 
            } 
      }

       priority_queue<int,vector<int>, greater <int>> pq;
      
      for (int i=0; i<arr.size();i++ ){
           if (meta[i] ) {
               pq.push(meta[i]);
           }               
      }
      int count=0;
      cout<<pq.size()<<endl;
       while (pq.size() != 1){
           count=count+(pq.top());
            pq.pop();
       }
       return count;      
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int result = equalizeArray(arr);

    cout << result << "\n";

    //fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

