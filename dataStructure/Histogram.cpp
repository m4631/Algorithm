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
		stack< pair<int, int> > S;
		int r = 0;
		for(int i=0; i<H.size(); i++){
			int l = i;
			while(!S.empty() && H[i] < S.top().first){
				l = S.top().second;
				r = max(r, (i-S.top().second)*S.top().first);
				S.pop();
			}
			S.push(make_pair(H[i], l));
		}
		while(!S.empty()){
			int l = H.size();
			r = max(r, (l-S.top().second)*S.top().first);
			S.pop();
		}
		return r;
	}
};
