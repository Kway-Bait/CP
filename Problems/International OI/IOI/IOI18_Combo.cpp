#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>

using namespace std;
#define ll long long
#define ull unsigned long long
#define f first
#define s second
#define PF push_front
#define PB push_back
#define MP make_pair
#define max(a, b) ((a > b)? a : b)
#define min(a, b) ((a < b)? a : b)
#define max3(a, b, c) max(max(a, b), c)
#define min3(a, b, c) min(min(a, b), c)

const int N = 2e3 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;

int press(string s);

string guess_sequence(int n){
    string str = "";
    char c[4] = {'A', 'B', 'X', 'Y'};

    // Get first char
    int temp = press("AB");
    if(temp) str = press("A")? 'A' : 'B';
    else str = press("X")? 'X' : 'Y';

    // 1 Press OP
    int val[3];
    for(int i = 0, ind = 0; i < 4; i++){
        if(c[i] == str[0]) continue;
        val[ind++] = i;
    }

    for(int i = 1; i < n-1; i++){
        int type = 0;
        string query = "";
        for(int j = 0; j < 4; j++){
            if(c[j] == str[0]) continue;
            if(!type){
                for(int k = 0; k < 4; k++){
                    if(c[k] == str[0]) continue;
                    query += (string)(str + c[j] + c[k]);
                }
            }else if(type == 1){
                query += (string)(str + c[j] + str[0]);
            }
            type++;
        }

        temp = press(query);

        str += c[val[i + 2 - temp]];
    }
    

    // Get last char
    if(n > 1){
        string query = str + 'A' + str + 'B';
        temp = press(query);
        if(temp == n) str += (press(str + 'A') == n)? 'A' : 'B';
        else str += (press(str + 'X') == n)? 'X' : 'Y';
    }
    
    return str;
}