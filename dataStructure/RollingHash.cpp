struct rollingHash{
	LL hash;
	int N;
	LL pot[100000];
	
	void prec(){
		LL p = 1;
		for(int i=0; i<100000; i++){
			pot[i] = p;
			p = (p*31LL) % MOD;
		}
	}
	
	rollingHash(){		
		prec();
	}
	
	void calculate(string s){
		N = s.size();
		for(int i=0; i<s.size(); i++){
			hash = (hash*31LL + s[i]) % MOD;
		}
	}
	
	void addFront(char c){
		hash = (hash*31LL + c) % MOD;
	}
	
	void addBack(char c){
		hash = ( c*pot[N] + hash ) % MOD;
	}
	
	void deleteBack(char c){
		hash = ((( hash - (c * pot[N-1]) ) % MOD) + MOD) % MOD ; 
	}
	
	void deleteFront(char c){
		hash = hash / 31LL;
	}
};
