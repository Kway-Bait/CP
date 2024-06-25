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

const int N = 5e4 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();

    int k, n, m, q;
    cin >> k >> n >> m >> q;
    
    ll par[N][5][16];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){
            for(int step = 0; step < 16; step++){
                par[i][j][step] = INF;
            }
        }
    }

    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        par[a][b%k][0] = w;
    }

    for(int i = 1; i < 16; i++){
        for(int j = 0; j < n; j++){
            for(int pos = 0; pos < k; pos++){
                for(int temp = 0; temp < k; temp++){
                    int jump = j + (1 << (i-1))*k - j%k + temp;
                    if(jump >= n) continue;
                    par[j][pos][i] = min(par[j][pos][i], par[j][temp][i-1] + par[jump][pos][i-1]);
                }
            }
        }
    }

    while(q--){
        int a, b;
        cin >> a >> b;

        int pa = a/k, pb = b/k;

        if(pb <= pa){
            cout << "-1" << endl;
            continue;
        }

        vector<ll> dp(k, INF);
        dp[a%k] = 0;
        for(int i = 15; i >= 0; i--){
            if(((pb - pa) >> i) & 1){
                vector<ll> cur(k, INF);
                for(int j = 0; j < k; j++){
                    for(int from = 0; from < k; from++){
                        cur[j] = min(cur[j], dp[from] + par[pa*k + from][j][i]);
                    }
                }
                dp = cur;
                pa += (1 << i);
            }
        }

        cout << ((dp[b%k] == INF)? -1 : dp[b%k]) << endl;
    }
}