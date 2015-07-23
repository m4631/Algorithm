struct LIS{
	int N;
	vector<int> V;
	vector< vector<pair<int, int> > > pos;
	vector<int> seq;
	
	LIS(VI V){
		this->V = V;
		N = V.size();
		pos = vector< vector<pair<int, int> > >(N);
	}
	
	fenwick FE;
	
	int length(){
		int L;
		for(int i=0; i<N; i++){
			int v = FE.sum(V[i]-1);
			FE.update(V[i], v+1);
			pos[v+1].push_back(make_pair(V[i], i));
			L = max(v+1, L);
		}
		return L;
	}
	
	int sequence(){
		int L = length();
		int an = INF;
		int p = INF;
		
		while(L > 0){
			for(int i=pos[L].size()-1; i>=0; i--){
				if(pos[L][i].first < an && pos[L][i].second < p){
					an = pos[L][i].first;
					p = pos[L][i].second;
					L--;
					seq.push_back(an);
					break;
				}
			}
		}
		reverse(seq.begin(), seq.end());
		return seq;
	}
	
};
