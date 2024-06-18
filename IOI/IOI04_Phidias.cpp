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

const int N = 600 + 5;
const int M = 1e9 + 7; 
const int INF = 0x3f3f3f3f;

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    vector<pair<int, int>> v;
    int w, h, n;
    cin >> w >> h >> n;
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        v.PB(MP(a, b));
    }

    // dp[i][j]: minimum total wasted area of size i x j
    int dp[N][N];

    // Initialize dp array
    for(int i = 0; i <= w; i++){
        for(int j = 0; j <= h; j++){
            dp[i][j] = i * j;
        }
    }
    for(int i = 0; i < n; i++) dp[v[i].f][v[i].s] = 0;

    //-- Solve DP --//
    for(int i = 1; i <= w; i++){
        for(int j = 1; j <= h; j++){
            // Fixed width, split height
            for(int k = 0; k*2 <= j; k++){
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j-k]);
            }

            // Fixed height, split width
            for(int k = 0; k*2 <= i; k++){
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i-k][j]);
            }
        }
    }

    cout << dp[w][h] << endl;
    
}