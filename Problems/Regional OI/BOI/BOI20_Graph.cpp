#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
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

const int N = 2e5 + 5;
const int M = 1e9 + 7; 
const int INF = 0x3f3f3f3f;

int n, m;
bool vis[N]{false}, vis2[N]{false}, found = false, valid = true;
vector<double> ans;
vector<pair<double, double>> v(N, MP(1, 0));
vector<set<pair<int, int>>> adj(N, set<pair<int, int>>());

void take_value(int cur){
    ans.PB(-v[cur].s * v[cur].f);

    vis2[cur] = true;

    for(pair<int, int> p : adj[cur]){
        if(!vis2[p.f]) take_value(p.f);
    }
}

void fill(int cur){
    if(!valid) return;

    vis[cur] = true;
    vis2[cur] = true;

    for(pair<int, int> p : adj[cur]){
        if(!vis2[p.f]){
            v[p.f] = MP(0, p.s - v[cur].s);
            fill(p.f);
        }else if(p.f != cur){
            if(p.s - v[cur].s != v[p.f].s){
                valid = false;
                return;
            }
        }
    }
}

void DFS(int cur, int prev = -1){
    if(found) return;
    if(!valid) return;

    vis[cur] = true;

    for(pair<int, int> p : adj[cur]){
        if(p.f == prev) continue;
        if(p.f == cur){
            v[cur] = MP(0, (double)p.s/2);
            fill(cur);
            found = true;
            return;
        }
        if(vis[p.f]){
            double new_a = -v[cur].f;
            double new_b = p.s - v[cur].s;
            if(v[p.f].f == new_a){
                if(new_b != v[p.f].s){
                    valid = false;
                    return;
                }
            }else {
                /*
                    a1x + b1 = a2x + b2
                    x(a1 - a2) = b2 - b1
                    x = (b2 - b1)/(a1 - a2)
                */
                double temp_x = (new_b - v[p.f].s)/(v[p.f].f - new_a);
                v[cur] = MP(0, v[cur].f * temp_x + v[cur].s);
                v[p.f] = MP(0, p.s - v[cur].s);
                fill(cur);
                found = true;
                return;
            }
        }else {
            if(v[cur].f != 0){
                double new_a = -v[cur].f;
                double new_b = p.s - v[cur].s;
                v[p.f] = MP(new_a, new_b);
            }else {
                v[p.f] = MP(0, p.s - v[cur].s);
            }
            DFS(p.f, cur);

            // Return update
            if(found) break;
            if(v[p.f].f == 0) v[cur] = MP(0, p.s - v[p.f].s);
        }
    }
}


int main(){
    
    // ifstream cin();
    // ofstream cout();
    
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b, x;
        cin >> a >> b >> x;
        adj[a].insert(MP(b, x));
        adj[b].insert(MP(a, x));
    }

    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            found = false;
            v[i] = MP(1, 0);
            DFS(i);
            // No fixed solution case
            if(valid && v[i].f != 0){
                ans.clear();
                take_value(i);
                sort(ans.begin(), ans.end());

                memset(vis2, false, sizeof(vis2));
                
                double temp_x;
                int s = ans.size();
                if(s%2){
                    temp_x = ans[s/2];
                }else {
                    temp_x = (ans[s/2] + ans[s/2 - 1])/2;
                }
                v[i] = MP(0, temp_x);
                fill(i);
            }
        }
    }

    if(valid){
        cout << "YES" << endl;
        for(int i = 1; i <= n; i++){
            cout << v[i].s << ' ';
        }
    }else {
        cout << "NO" << endl;
    }
    
}