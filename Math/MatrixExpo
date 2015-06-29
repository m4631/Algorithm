VVI identity(int x){
	VVI id(x, VI(x, 0));
	for(int i=0; i<x; i++){
		id[i][i] = 1;
	}
	return id;
}

VVI multiply(VVI A, VVI B){
	int x = A.size();
	int y = A[0].size();
	int z = B[0].size();
	VVI C(x, VI(z, 0));
	for(int i=0; i<x; i++){
		for(int j=0; j<z; j++){
			for(int k=0; k<y; k++){
				C[i][j] = (C[i][j] + (A[i][k] * B[k][j])%MOD)%MOD;
			}
		}
	}
	return C;
}

VVI power(VVI A, int e){
	if(e == 0){
		return identity(A[0].size());
	}
	if(e == 1){
		for(int i=0; i<A.size(); i++){
			for(int j=0; j<A[i].size(); j++){
				A[i][j] %= MOD;
			}
		}
		return A;
	}
	if(e%2 == 0){
		//5^8 = 5^4*5^4 = (5*5)^4
		return power(multiply(A, A), e/2);
	}else{
		//5^9 = 5^4*5^4*5 = (5*5)^4*5
		return multiply( power(multiply(A, A), e/2), A);
	}
}
