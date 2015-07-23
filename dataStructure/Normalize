struct normalize{
	map<int, int> MP;
	map<int, int> RE;
	
	normalize(VI V, int ini){
		sort(V.begin(), V.end());
		int k = ini;
		for(int i=0; i<V.size(); i++){
			if(!MP.count(V[i])){
				MP[ V[i] ] = k;
				RE[ k ] = V[i];
				k++;
			}
		}
	}
	
	int getId(int num){
		return MP[num];
	}
	
	int getNum(int id){
		return RE[id];
	}
	
};
