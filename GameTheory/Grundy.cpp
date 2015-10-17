struct Game{
    int L;
    
    Game(int L){
        this->L = L;
    }
 
    vector<Game> applyMove(int p){
        vector<Game> vg;
        //code
        return vg;
    }
    bool isValid(int p){
        //code
        return true;
    }
};

int Grundy(Game g){
	
	//MEMO!!!!!
 
    set<int> S;
    for(int i=0; i<g.L; i++){
		if(!g.isValid(i))continue;
		vector<Game> vv = g.applyMove(i);
		int X = 0;
		for(int k=0; k<vv.size(); k++){
			X ^= Grundy(vv[k]);
		}
		S.insert(X);
    }
    int i = 0;
    while(S.count(i))i++;
    return i;
}
