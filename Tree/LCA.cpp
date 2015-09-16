vector< vector<II> >g;
LL D[MAX];
int L[MAX];
int C[MAX][21];
bool visited[MAX];
int n;

void dfs(int src, int level){
	visited[src] = true;
	L[src] = level;
	for(int i=0; i<g[src].size(); i++){
		int v = g[src][i].first;
		if(!visited[v]){
			dfs(v, level+1);
			C[v][0] = src;
		}
	}
}

void calc(){
	for(int i=1; i<20; i++){
		for(int j=0; j<n; j++){
			if( C[j][i-1] != -1 ){
				C[j][i] = C[ C[j][i-1] ][i-1];
			}
		}
	}
}

int goUp(int node, int D){
	for(int i=19; i>=0; i--){
		 while( (1<<i) <= D ){
			 node = C[node][i];
			 D -= (1<<i);
		 }
	}
	return node;
}

int lca(int n1, int n2){
	if ( L[n1] < L[n2] )
		n2 = goUp(n2, L[n2]-L[n1]);
	if ( L[n2] < L[n1] )
		n1 = goUp(n1, L[n1]-L[n2]);
	if(n1 == n2) return n1;
	for(int i=19; i>=0; i--){
		while(C[n1][i] != C[n2][i]){
			n1 = C[n1][i];
			n2 = C[n2][i];
		}
	}
	return C[n1][0];
}
