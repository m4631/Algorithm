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

VS V;

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	string s;
	getline(cin, s);
	getline(cin, s);
	while(T--){
		bool f;
		do{
			f = getline(cin, s);
			V.push_back(s);
		}while(s.size() > 0 && f);
//		for(int i=0; i<4; i++){
//			getline(cin, s);
//			V.push_back(s);
//		}
//		
		map<string, int> SS;
		map<string, int> SS1;
		map<int, string> RE;
		VS name(V.size());
		VS party(V.size());
		vector<VS> club(V.size());
		
		int k = 1;
		int c = 0;
		
		for(int i=0; i<V.size(); i++){
			int p1;
			for(p1=0; p1<V[i].size(); p1++){
				if(V[i][p1] == ' ') break;
				name[i] += V[i][p1];
			}
			for(p1 = p1+1; p1 < V[i].size(); p1++){
				if(V[i][p1] == ' ') break;
				party[i] += V[i][p1];
			}
			while(p1 < V[i].size()){
				string temp;
				for(p1 = p1+1; p1 < V[i].size(); p1++){
					if(V[i][p1] == ' ') break;
					temp += V[i][p1];
				}
				if(!SS1.count(temp)){
					SS1[temp] = c;
					RE[c] = temp;
					c++;
				}
				club[i].push_back(temp);
			}
			if(!SS.count(party[i]))
				SS[party[i]] = k++;
		}
		MaxFlowDinic MD( 80000 );
		
		map<string, int>::iterator it;
		for(it = SS.begin(); it != SS.end(); it++){
			MD.add_edge(0, it->second, SS.size()%2==0? SS.size()/2-1:SS.size()/2);
		}
		
		k = SS.size() + 1;
		for(int i=0; i<V.size(); i++, k++){
			int p = SS[party[i]];
			MD.add_edge(p, k, 1);
			for(int j=0; j<club[i].size(); j++){
				MD.add_edge(k, SS1[club[i][j]] + SS.size() + 1 + V.size(), 1);
			}
		}
		
		for(it = SS1.begin(); it != SS1.end(); it++){
			MD.add_edge( (it->second) + SS.size() + 1 + V.size(), 
					SS1.size() + SS.size() + 1 + V.size(), 1);
		}
		
		int res = MD.dinic(0, SS1.size() + SS.size() + 1 + V.size());
		if(res < SS1.size()){
			cout << "Impossible." << endl;
		}else{
			for(int i=0; i<MD.edges.size(); i+=2){
				if(MD.edges[i].v == SS1.size() + SS.size() + 1 + V.size()) continue;
				if(MD.edges[i].u < SS.size() + 1) continue;
				if(MD.edges[i].flow <= 0) continue;
				int u = MD.edges[i].u;
				int v = MD.edges[i].v;
				u -= (SS.size() + 1);
				v -= (SS.size() + 1 + V.size());
				cout << name[u] << " " << RE[v] << endl;
			}
		}
		if(T > 0){
			cout << endl;
		}
	}
    return 0;
}

/*
2

fred dinosaur jets jetsons
john rhinocerous jets rockets
mary rhinocerous jetsons rockets
ruth platypus rockets

fred dinosaur jets jetsons
john rhinocerous jets rockets
mary rhinocerous jetsons rockets
ruth platypus rockets

 */
