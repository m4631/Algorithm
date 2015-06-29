class TwoColorable {
   int N;
   
   bool dfs(int u, int color) {
      if (colors[u] >= 0)
         return colors[u] == color;
      colors[u] = color;
      for (int j = 0; j < adj[u].size(); ++j) {
         if (!dfs(adj[u][j], color^1))
            return false;
      }
      return true;
   }
public:
   // input: adjacency list
   VVI adj;
   // output: color of each vertex (0 or 1) if graph is bipartite
   VI colors;
   TwoColorable(int _N) : N(_N), adj(VVI(_N)) {}
   bool valid = true;
   
   // returns true if graph is bipartite
   bool process() {
      colors = VI(N, -1);
      for (int u = 0; u < N; ++u){
         if (colors[u] < 0){
        	 if(!dfs(u, 0))
               return false;  
         }
      }
      return true;
   }
};
