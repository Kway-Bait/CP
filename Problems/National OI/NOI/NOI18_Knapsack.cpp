#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <functional>
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
#define PB push_back
#define MP make_pair
#define max(a, b) ((a > b)? a : b)
#define min(a, b) ((a < b)? a : b)

const int N = 1e5 + 5;
const int M = 1e9 + 7; 
const int INF = 0x3f3f3f3f;
const int MAXS = 2e3 + 5;

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    int S, n, v[N], w[N], k[N];
    cin >> S >> n;
    for(int i = 0; i < n; i++){
        cin >> v[i] >> w[i] >> k[i];
    }

    // Group same weight
    vector<pair<int, int>> item[MAXS];
    for(int i = 0; i < n; i++){
        item[w[i]].PB(MP(v[i], k[i]));
    }

    // Final consideration array
    vector<pair<int, int>> arr;
    for(int i = 1; i <= S; i++){
        if(item[i].empty()) continue;
        sort(item[i].rbegin(), item[i].rend());
        int num = (S/i); // Can only take this quantity of current weight
        for(pair<int, int> p : item[i]){
            for(int k = 0; k < min(num, p.s); k++){
                // Pushback {Weight, Value}
                arr.PB(MP(i, p.f));
            }
            num -= p.s;
            if(num <= 0) break;
        }
    }

    // Start DP
    int dp[MAXS]{0};
    for(int i = 0; i < (int)arr.size(); i++){
        for(int j = S; j >= arr[i].f; j--){
            dp[j] = max(dp[j], dp[j - arr[i].f] + arr[i].s);
        }
    }

    cout << dp[S] << endl;
}