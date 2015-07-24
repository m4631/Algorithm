#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>
#include <map>
#include <bitset>
#include <string>
#include <cmath>
#include <set>

using namespace std;

const int INF = 1000000009;
const int MOD = 1000000007;

typedef long long LL;
typedef unsigned long long ULL;
typedef priority_queue <int> PQ;
typedef pair <int, int> II;
typedef priority_queue <II> PQII;
typedef map <int, int> MI;
typedef map <string, int> MSI;
typedef vector <int> VI;
typedef vector <VI> VVI;
typedef vector <LL> VL;
typedef vector <VL> VVL;
typedef vector <string> VS;
typedef vector < II > VII;

struct Edge {
   int u, v;
   int rev;  // index of reverse edge
   int cap, flow;
   Edge(int _u, int _v, int _rev = 0, int _cap = 1) :
     u(_u), v(_v), rev(_rev), cap(_cap), flow(0) {}
};

class MaxFlowDinic {
   int N;
   VI sp_par, sp_D;

   bool augmenting_path_bfs(int src, int dst, int mincap = 0) {
      sp_par.assign(N, -1);
      sp_D.assign(N, -1);

      sp_D[src] = 0;
      queue<int> q;
      q.push(src);
      while (!q.empty()) {
         int cur = q.front();
         q.pop();
         for (int j = 0; j < (int) adj[cur].size(); ++j) {
            int e = adj[cur][j];
            int v = edges[e].v;
            if (sp_D[v] < 0 && edges[e].cap - edges[e].flow > mincap) {
               sp_D[v] = sp_D[cur] + 1;
               sp_par[v] = e;
               q.push(v);
            }
         }
      }
      return sp_D[dst] >= 0;
   }

   VI last_edge;
   int update_flow_dfs(int u, int dst, int cfp = INF) {
      if (u == dst)
         return cfp;
      for (; last_edge[u] < adj[u].size(); ++last_edge[u]) {
         int e = adj[u][ last_edge[u] ];
         int u = edges[e].u;
         int v = edges[e].v;

         if (sp_D[v] == sp_D[u] + 1 && edges[e].cap - edges[e].flow > 0) {
            int res = update_flow_dfs(v, dst, min( cfp, edges[e].cap - edges[e].flow ));
            if (res > 0) {
               edges[e].flow += res;
               edges[ edges[e].rev ].flow = -edges[e].flow;  // -= cfp;
               return res;
            }
         }
      }
      return 0;
   }

public:
   vector<Edge> edges;
   VVI adj;  // adjacency lists of edge indices

   MaxFlowDinic(int _N) : N(_N), adj(VVI(_N)) {}
   
   void add_edge(int u, int v, int _cap=1) {
      int num_edges = edges.size();
      // forward edge
      edges.push_back( Edge(u, v, num_edges+1, _cap) );
      adj[u].push_back(num_edges++);
      // reverse edge
      edges.push_back( Edge(v, u, num_edges-1, 0) );
      adj[v].push_back(num_edges++);
   }

   int dinic(int s, int t) {
      N = int(adj.size());
      for (int j = 0; j < (int) edges.size(); ++j)
         edges[j].flow = 0;

      VI path;
      int res = 0;

      while ( augmenting_path_bfs(s, t) ) {
   		last_edge.assign(N, 0);
   		while (true) {
   		   int cfp = update_flow_dfs(s, t);
   		   if (cfp <= 0) break;
   		   res += cfp;
   		}
      }
   return res;
   }

   vector<Edge> mincut(int s, int t) {
      dinic(s, t);  
      vector<Edge> res;
      for (int k = 0; k < edges.size(); ++k) {
         const Edge& e = edges[k];
         if (e.cap > 0 && sp_D[e.u] >= 0 && sp_D[e.v] < 0) 
            res.push_back(e);
      }
      return res;
   }
};

int main() {
	ios_base::sync_with_stdio(false);
	int n, m;
	int T = 1;
	while(cin >> n && n != 0){
		cin >> m;
		int s = 0;
		MaxFlowDinic MD(60000);
		for(int i=0; i<n; i++){
			int v, a, b;
			cin >> v >> a >> b;
			s += v;
			MD.add_edge(0, i+1, v);
			for(int j=a; j<b; j++){
				MD.add_edge(i+1, j+n+1, 1);
			}
		}
		
		for(int i=0; i<=50000; i++){
			MD.add_edge(i+n+1, n+1+50001, m);
		}
		
		int r = MD.dinic(0, n+1+50001);
		VVI res(n);
		if(r == s){
			cout << "Case "<<T<< ": Yes" << endl;
			for(int i=0; i<MD.edges.size(); i+=2){
				if(MD.edges[i].u == 0) continue;
				if(MD.edges[i].v == n+1+50001) continue;
				if(MD.edges[i].flow <= 0) continue;
				int u = MD.edges[i].u - 1;
				int v = MD.edges[i].v - n - 1;
				res[u].push_back(v);
			}
			for(int i=0; i<n; i++){
				VII aux;
				int ini = res[i][0], fi = res[i][0]+1;
				for(int j=1; j<res[i].size(); j++){
					if(res[i][j] == fi){
						fi = res[i][j] + 1;
					}else{
						aux.push_back(make_pair(ini, fi));
						ini = res[i][j];
						fi = res[i][j] + 1;
					}
				}
				aux.push_back(make_pair(ini, fi));
				cout << aux.size() << " ";
				for(int i=0; i<aux.size(); i++){
					cout << "(" << aux[i].first << "," << aux[i].second << ")";
					if(i < aux.size()-1) cout << " ";
				}
				cout << endl;
			}
		}else{
			cout << "Case "<<T<< ": No" << endl;
		}
		T++;
	}
    return 0;
}

