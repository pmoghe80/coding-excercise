#include <bits/stdc++.h>

using namespace std;

// Complete the biggerIsGreater function below.
string biggerIsGreater(string w) {
    int i=0;
    int found = 0;

    if (w.size() == 1) {
         return w;
    } else if (w.size() == 2) {
        if (w[0] < w[1]) {
            char tmp = w[0];
            w[0] = w[1];
            w[1] = tmp;
            return w;
        }
    }

    // dhkc

    for (i=w.size()-2; i >= 0 ; i--) {
        if (w[i] < w[i+1]) {
            found = 1;
            break;
        }
    }
    string return_str = "no answer";
    if (!found) {
         //cout << "no answer" << endl;
         return return_str;
    }

    int c_found = w[i];
    int c_found_indx = i;  
    int c_ceil = w[i+1];
    int  c_ceil_indx;
    found = 0;
    while (++i < w.size()) {
        if (c_found < w[i] &&  c_ceil >= w[i]) {
            c_ceil = w[i];
            c_ceil_indx = i;
            found = 1;
        }
    }
 
    string tmp_str = "no answer 1"; 
    if (!found) {
        return tmp_str;
    }
 
    char tmp = w[c_ceil_indx];
    w[c_ceil_indx] = w[c_found_indx];
    w[c_found_indx] = tmp;
    string::iterator it;
    i = 0;
 
    for (it = w.begin(); it != w.end(); it++) {
         if (i == c_found_indx+1) {
            break;  
         }
         i++;
    }

    sort(it, w.end());
    return w;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int T;
    cin >> T;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int T_itr = 0; T_itr < T; T_itr++) {
        string w;
        getline(cin, w);

        string result = biggerIsGreater(w);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
