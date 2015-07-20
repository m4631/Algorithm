#define HIGHESTSETBIT(mask) ( sizeof(int)*8-1-__builtin_clz((mask)) )

struct Edge {
   int u, v;
   int rev;  // index of reverse edge
   int cap, flow;
   Edge(int _u, int _v, int _rev = 0, int _cap = 1) :
     u(_u), v(_v), rev(_rev), cap(_cap), flow(0) {}
};

class MaxFlowEdmondsKarp {
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

public:
   vector<Edge> edges;
   VVI adj;  // adjacency lists of edge indices

   MaxFlowEdmondsKarp(int _N) : N(_N), adj(VVI(_N)) {}
   
   void add_edge(int u, int v, int _cap=1) {
      int num_edges = edges.size();
      // forward edge
      edges.push_back( Edge(u, v, num_edges+1, _cap) );
      adj[u].push_back(num_edges++);
      // reverse edge
      edges.push_back( Edge(v, u, num_edges-1, 0) );
      adj[v].push_back(num_edges++);
   }

   int edmonds_karp(int s, int t, bool scaled = false) {
      N = adj.size();
      for (int j = 0; j < (int) edges.size(); ++j)
         edges[j].flow = 0;

      int max_cap;
      if (scaled) {
         max_cap = 0;
         for (int j = 0; j < (int) edges.size(); ++j)
            max_cap = max(max_cap, edges[j].cap);
         if (max_cap <= 0)
            return 0;
      }
      else
         max_cap = 1;

      VI path;
      int res = 0;
      for (int dcap = 1 << HIGHESTSETBIT(max_cap); dcap > 0; dcap >>= 1) {
         while ( augmenting_path_bfs(s, t, dcap-1) ) {
            int cfp = INF;
            for (int curv = t; sp_par[curv] >= 0; ) {
               int e = sp_par[curv];
               cfp = min(cfp, edges[e].cap - edges[e].flow);
               curv = edges[e].u;
            }
            for (int curv = t; sp_par[curv] >= 0; ) {
               int e = sp_par[curv];
               edges[e].flow += cfp;
               edges[ edges[e].rev ].flow = -edges[e].flow;  // -= cfp;
               curv = edges[e].u;
            }
            res += cfp;
         }
      }
      return res;
   }

   vector<Edge> mincut(int s, int t) {
	  edmonds_karp(s, t);  
      vector<Edge> res;
      for (int k = 0; k < edges.size(); ++k) {
         const Edge& e = edges[k];
         if (e.cap > 0 && sp_D[e.u] >= 0 && sp_D[e.v] < 0) 
            res.push_back(e);
      }
      return res;
   }
};






