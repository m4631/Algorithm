struct NodeInit {
	bool c;
    NodeInit(bool c = 0){
        this->c = c;
    }
};
struct Node
{
    int cntA, cntB, carry , sz;
    //cntA : barbaros
    //cntB : bucaneros
    bool HasCarry;
    Node(){
        this->carry = 0;
        this->sz = 1;
        HasCarry = 0;
    }
    Node(NodeInit n) {
        this->cntA = (n.c == 0);
        this->cntB = (n.c == 1);
        this->carry = 0;
        this->sz = 1;
        HasCarry = 0;
    }
    Node operator+(const Node &N)const {
        Node ret;
        ret.cntA = this->cntA + N.cntA;
        ret.cntB = this->cntB + N.cntB;
        ret.carry = 0;
        ret.HasCarry = 0;
        ret.sz = this->sz + N.sz;
        return ret;
    }
    void update(int action)
    {
    	if(action == 0){ // nothing

    	}else if(action == 1){
    		swap(cntA,cntB);
    	}else if(action == 2){
    		cntA = sz;
    		cntB = 0;
    	}else if(action == 3){
    		cntA = 0;
    		cntB = sz;
    	}

    	this->HasCarry = 1;
    	if(action >= 2)
    		this->carry = action;
    	else
    		this->carry ^= action;

    }
    void clear(){
        this->HasCarry = 0;
        this->carry = 0;
    }
};
struct SegmentTree
{
    Node *V;
    int N;
    SegmentTree(int N)
    {
        this->V = new Node[4 * N];
        this->N = N;
    }
    ~SegmentTree(){ delete [] this->V; }

    void create(vector<NodeInit> &VEC,int n = 1,int b = 0,int e = -1)
    {
        if(e == -1) e = N - 1;
        if(b == e){
            V[n] = Node(VEC[b]);
        }
        else
        {
            create(VEC,2*n,b,(e+b)/2);
            create(VEC,2*n+1,(e+b)/2+1,e);
            V[n] = V[2*n] + V[2*n+1];
        }
    }

    Node query(int i, int j, int n = 1,int b = 0,int e = -1)
    {
        if(e == -1)e = N - 1;
        if(i <= b && e <= j)return V[n];
        else
        {
            if(V[n].HasCarry)
            {
                V[2*n  ].update(V[n].carry);
                V[2*n+1].update(V[n].carry);
                V[n].clear();
            }
            int mid = (b+e)/2;
            if(i > mid)return query(i,j,2*n+1,mid+1,e);
            if(j <=mid)return query(i,j,2*n,b,mid);
            return query(i,j,2*n,b,mid) + query(i,j,2*n+1,mid+1,e);
        }
    }

    void update(int i,int j,int t,int n = 1,int b=0,int e=-1)
    {
        if(e == -1)e = N - 1;
        if(i <= b && e <= j)
        {
            V[n].update(t);
        }
        else if(i > e || j < b)
            return;
        else
        {
            if(V[n].HasCarry)
            {
                V[2*n  ].update(V[n].carry);
                V[2*n+1].update(V[n].carry);
                V[n].clear();
            }
            int mid = (b+e)/2;
            update(i,j,t,2*n,b,mid);
            update(i,j,t,2*n+1,mid+1,e);
            V[n] = V[2*n] + V[2*n+1];
        }

    }

    void print(int n = 1, int b = 0, int e = -1, int level = 0){
    	if(e == -1) e= N-1;
    	if(b == e){
    		cout << string(level*4, ' ') << "(" << V[n].cntA << "," << V[n].cntB << ")" <<endl;
    	}else{
    		print(2*n+1, (b+e)/2 +1, e, level+1);
    		cout << string(level*4, ' ') << "(" << V[n].cntA << "," << V[n].cntB << ")" <<endl;
    		print(2*n, b, (b+e)/2, level+1);
    	}
    }
};
