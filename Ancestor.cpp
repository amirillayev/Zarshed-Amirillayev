#include <iostream>
#include <cmath>
using namespace std;

vector<int> tin, tout, depth;
vector<vector<int>> up;
int logN, timer = 0;

void dfs(vector<vector<int>> &graph, int v, int p){
    tin[v]=++timer;

    up[v][0]=p;
    for (int i = 1; i < logN; i++){
        up[v][i]=up[up[v][i-1]][i-1];
    }
    
    for (auto &to : graph[v]){
        if (to!=p){
            depth[to]=depth[v]+1;
            dfs(graph,to,v);
        }
    }
    
    tout[v]=++timer;
}

bool isAncestorOf(int a, int b){
    return tin[a]<=tin[b] && tout[a]>=tout[b];
}

int lca(int a, int b){
    if (isAncestorOf(a,b)) return a;
    if (isAncestorOf(b,a)) return b;

    for (int k = logN - 1; k >= 0; k--){
        if (!isAncestorOf(up[a][k],b)){
            a=up[a][k];
        }
    }

    return up[a][0];
}

int distance(int a, int b){
    return depth[a]+depth[b]-2*depth[lca(a,b)];
}

int main(){
    int n; cin >> n;
    vector<vector<int>> graph(n);

    tin.assign(n,0);
    tout.assign(n,0);
    depth.assign(n,0);

    logN = ceil(log2(n));
    up.assign(n,vector<int>(logN,0));

    for (int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(graph,0,0); // 0 as a root

    return 0;
}
