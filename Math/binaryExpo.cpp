int binaryExpo(int b, int e){
	if(e == 0){
		return 1;
	}
	if(e == 1){
		return b % MOD;
	}
	if(e%2 == 0){
		return binaryExpo((b*b)%MOD, e/2);
	}else{
		return (binaryExpo((b*b)%MOD, e/2)*b)%MOD;
	}
}
