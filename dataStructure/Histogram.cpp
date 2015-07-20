struct histogram{
	int N;
	vector< int > H; 
	stack< pair<int, int> > st;
	
	histogram(vector< int > H){
		this->N = H.size();
		this->H = H;
	}
	
	void onlyForMatrix(vector< vector< string > > table, int row){
		N = table[row].size();
		H[N-1] = (table[row][N-1]=='1');
		for(int j=N-2; j>=0; j--){
			H[j] = (table[row][j]=='1')? H[j+1]+1 : 0;
		}
	}
	
	int solve(){
		int res = 0;
		for(int i=0; i<N; i++){
			if(H[i] == 0){
				while(!st.empty()){
					res = max(res, (i-st.top().second)*st.top().first);
					st.pop();
				}
				continue;
			}
			if(!st.empty() && st.top().first <= H[i]){
				st.push(make_pair(H[i], i));
			}else{
				int p = i;
				while(!st.empty() && st.top().first > H[i]){
					p = st.top().second;
					res = max(res, (i-st.top().second)*st.top().first);
					st.pop();
				}
				st.push(make_pair(H[i], p));
			}
		}
		while(!st.empty()){
			res = max(res, (N-st.top().second)*st.top().first);
			st.pop();
		}
		return res;
	}
};
