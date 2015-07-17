struct histogram{
	int N;
	vector< vector<int> > H; 
	vector< string > table; 
	stack< pair<int, int> > st;
	
	histogram(vector<string> table){
		this->N = table.size();
		this->table = table;
		this->H = vector< vector<int> >(N, vector<int>(N, 0));
	}
	
	void preprocess(){
		for(int i=0; i<N; i++){
			H[i][N-1] = (table[i][N-1]=='1');
			for(int j=N-2; j>=0; j--){
				H[i][j] = (table[i][j]=='1')? H[i][j+1]+1 : 0;
			}
		}
	}
	
	int solve(){
		preprocess();
		int res = 0;
		for(int j=0; j<N; j++){
			for(int i=0; i<N; i++){
				if(H[i][j] == 0){
					while(!st.empty()){
						res = max(res, (i-st.top().second)*st.top().first);
						st.pop();
					}
					continue;
				}
				if(!st.empty() && st.top().first <= H[i][j]){
					st.push(make_pair(H[i][j], i));
				}else{
					int p = i;
					while(!st.empty() && st.top().first > H[i][j]){
						p = st.top().second;
						res = max(res, (i-st.top().second)*st.top().first);
						st.pop();
					}
					st.push(make_pair(H[i][j], p));
				}
			}
			while(!st.empty()){
				res = max(res, (N-st.top().second)*st.top().first);
				st.pop();
			}
		}
		return res;
	}
};
