struct normalize{
	map<int, int> MP;
	map<int, int> RE;
	VI arr;
	
	normalize(VI V, int ini){
		arr = V;
		sort(V.begin(), V.end());
		int k = ini;
		for(int i=0; i<V.size(); i++){
			if(!MP.count(V[i])){
				MP[ V[i] ] = k;
				RE[ k ] = V[i];
				k++;
			}
		}
		for(int i=0; i<arr.size(); i++){
			arr[i] = MP[ arr[i] ];
		}
	}
	
	int getId(int num){
		return MP[num];
	}
	
	int getNum(int id){
		return RE[id];
	}
	
	VI getArray(){
		return arr;
	}
	
};
