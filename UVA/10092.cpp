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
#include <ctime>
#include <set>
#include <cassert>

using namespace std;

const int INF = 1000000009;
const int MOD = 1000000000;

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

int main(){
	int nk, np;
	while(cin >> nk >> np && nk!=0 && np!=0){
		MaxFlowDinic D(nk+np+5);
		VI aux;
		int R = 0;
		for(int i=0; i<nk; i++){
			int c;
			cin >> c;
			R += c;
			aux.push_back(c);
			D.add_edge(0, i+1, c);
		}
		for(int i=0; i<np; i++){
			int k;
			cin >> k;
			for(int j=0; j<k; j++){
				int ct;
				cin >> ct;
				D.add_edge(ct, i+nk+1, INF);
			}
			D.add_edge(i+nk+1, nk+np+1);
		}
		
		int d = D.dinic(0, nk+np+1);
		bool an = true;
		
		int res[np];
		memset(res, 0, sizeof(res));
		for(int i=0; i<D.edges.size(); i+=2){
			if(D.edges[i].u == 0 || D.edges[i].v == nk+np+1) continue;
			if(D.edges[i].flow <= 0) continue;
			if(D.edges[i].v <= nk) continue;
			res[ D.edges[i].v-1-nk ] = D.edges[i].u;
		}
		for(int i=1; i<=nk; i++){
			int r = 0;
			for(int j=0; j<np; j++){
				if(res[j] == i){
					r++;
				}
			}
			if(r != aux[i-1]) an = false;
		}
		
		if(an && d == R){
			cout << 1 << endl;
			for(int i=1; i<=nk; i++){
				for(int j=0; j<np; j++){
					if(res[j] == i){
						cout << j+1 << " ";
					}
				}
				cout << endl;
			}
		}else{
			cout << 0 << endl;
		}
	}
}

