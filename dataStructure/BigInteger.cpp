struct BigIntegerNaive {
	string N;
	BigIntegerNaive(){
		N = "0";
	}
	BigIntegerNaive(string S){
		N = S;
	}
	int size()const{
		return N.size() - (N[0] == '-');
	}
	BigIntegerNaive operator*(const BigIntegerNaive &B)const{
		int tn = N[0] == '-';
		int on = B.N[0] == '-';
		vector<int> V(N.size() + B.N.size() + 10);
		for(int i = 0; i < this->size(); ++i){
			int td = N[N.size()-i-1] - '0';
			int c = 0;
			for(int j = 0; j < B.size(); ++j){
				int od = B.N[B.N.size()-j-1] - '0';
				int nd = od * td + c;
				V[i+j] += nd;
			}
		}
		string C = "";
		for(int i = 1; i < V.size(); ++i){
			V[i] += V[i-1] / 10;
			V[i-1] %= 10;
		}
		while(V.size() > 0 && V.back() == 0)
			V.pop_back();
		if(V.size() == 0)V.push_back(0);
		for(int i = 0; i < V.size(); ++i){
			C += V[V.size() - i - 1] + '0';
		}
		return BigIntegerNaive((tn!=on ? "-" : "") + C);
		
	}
	bool operator<(const BigIntegerNaive &B)const{
		int tn = N[0] == '-';
		int on = B.N[0] == '-';
		if(tn != on){
			return tn;
		}else{
			int ts = N.size();
			int os = B.N.size();
			if(ts != os){
				return ts < os;
			}else{
				return N < B.N;
			}
		}
	}
	string str()const{
		return N;
	}
};
