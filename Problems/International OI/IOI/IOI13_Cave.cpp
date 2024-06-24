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

#include "cave.h"

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

const int N = 7e4 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;

int tryCombination(int S[]);

void answer(int S[], int D[]);

void exploreCave(int n){
    int ans[n], con[n];
    for(int i = 0; i < n; i++) ans[i] = -1;

    // Generate query
    int all_on[n];
    for(int i = 0; i < n; i++) all_on[i] = 1;

    set<int> remain;
    for(int i = 0; i < n; i++) remain.insert(i);

    for(int door = 0; door < n; door++){
        // Determine current door correct switch status
        int val = tryCombination(all_on);
        bool status = (val > door || val == -1);

        // Binary search using Binary jumping
        int pos = n;
        for(int i = 4096, base = 0; i > 0; i /= 2){
            if(base + i > (int)remain.size()) continue;
            
            int temp[n];
            for(int j = 0; j < n; j++) temp[j] = ans[j];

            int counter = base + i, cur_pos = n;
            for(auto j = remain.begin(); j != remain.end(); j++){
                temp[*j] = (counter > 0)? status : !status;
                if(counter > 0) cur_pos = *j;
                counter--;
            }

            val = tryCombination(temp);
            if(val > door || val == -1) pos = min(pos, cur_pos);
            else base += i;
        }

        con[pos] = door;
        ans[pos] = status;
        all_on[pos] = status;
        remain.erase(pos);
    }

    answer(ans, con);
}