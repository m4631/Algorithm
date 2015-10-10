#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>
#include <map>
#include <bitset>
#include <string>
#include <cmath>
#include <set>
#include <climits>
#include <iomanip>
#include <cassert>

using namespace std;

const int INF = 1000000009;
const int MOD = 1000000007;

typedef long long LL;
typedef unsigned long long ULL;
typedef priority_queue <int> PQ;
typedef pair <int, int> II;
typedef priority_queue <II> PQII;
typedef map <int, int> MI;
typedef map <string, int> MSI;
typedef vector <int> VI;
typedef vector <double> VD;
typedef vector <VI> VVI;
typedef vector <LL> VL;
typedef vector <VL> VVL;
typedef vector <string> VS;
typedef vector < II > VII;

int B, P;

struct NodeInit {
	int f;
    NodeInit(int f){
        this->f = f;
    }
};

LL be(LL b, LL e){
	if(e==0) return 1%P;
	if(e==1) return b%P;
	if(e%2==0){
		return be((b*b)%P, e/2)%P;
	}else{
		return (be((b*b)%P, e/2)*b)%P;
	}
}

struct Node
{
    int f;
    //cntA : barbaros
    //cntB : bucaneros
    Node(){
        this->f = 0;
    }
    Node(NodeInit n) {
    	this->f = n.f;
    }
    Node operator+ (const Node &n) const {
        return Node((f+n.f)%P);
    }
    Node operator* (LL pr) const{
    	return Node((pr*f)%P);
    }
    void update(int v)
    {
    	this->f = v;
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
        	int mid = (e+b)/2;
            create(VEC,2*n,b,mid);
            create(VEC,2*n+1,mid+1,e);
            V[n] = V[2*n] + (V[2*n+1]*be(B, mid+1-b));
        }
    }

    Node query(int i, int j, int n = 1,int b = 0,int e = -1)
    {
        if(e == -1)e = N - 1;
        if(i <= b && e <= j)return V[n];
        else
        {
            int mid = (b+e)/2;
            if(i > mid)return query(i,j,2*n+1,mid+1,e);
            if(j <= mid)return query(i,j,2*n,b,mid);
            return query(i,j,2*n,b,mid) + (query(i,j,2*n+1,mid+1,e)*be(B, mid+1-max(b, i)));
        }
    }

    void update(int i,int t,int n = 1,int b=0,int e=-1)
    {
        if(e == -1)e = N - 1;
        if(b == e && b == i){
        	V[n].f = t%P;
        }
        else if(i > e || i < b)
            return;
        else
        {
            int mid = (b+e)/2;
            update(i,t,2*n,b,mid);
            update(i,t,2*n+1,mid+1,e);
            V[n] = V[2*n] + (V[2*n+1]*be(B, mid+1-b));
        }

    }
    
    void print(int n = 1, int b = 0, int e = -1, int level = 0){
    	if(e == -1) e= N-1;
    	if(b == e){
    		cout << string(level*4, ' ') << "(" << V[n].f << ")" <<endl;
    	}else{
    		print(2*n+1, (b+e)/2 +1, e, level+1);
    		cout << string(level*4, ' ') << "(" << V[n].f << ")" <<endl;
    		print(2*n, b, (b+e)/2, level+1);
    	}
    }
};

/*
10 1000003 6 8
E 1 3
E 2 4
E 3 5
E 4 6
E 5 7
E 6 8
H 1 6
H 2 5
*/

//struct bf{
//	VI arr;
//	bf(int N){
//		arr = VI(N, 0);
//	}
//	void update(int x, int v){
//		arr[x] = v;
//	}
//	int query(int i, int j){
//		int r=0;
//		LL p = 1;
//		for(int k=0; k<=(j-i); k++){
//			r = (r + (p*arr[j-k])%P)%P;
//			p = (p*B)%P;
//		}
//		return r;
//	}
//};
//
//int main(){
//	int L, N;
//	srand(123456);
//	while(true){
//		B = (rand()%(1000000000LL-2))+2;
//		P = (rand()%(1000000000LL-B-1))+B+1;
//		L = (rand()%10)+1;
//		N = (rand()%1000)+1;
//		vector< pair<int, II> > queries;
//		vector<NodeInit> V(L, NodeInit(0));
//		SegmentTree st(L);
//		st.create(V);
//		bf bb(L);
//		for(int i=0; i<N; i++){
//			int op = rand()%2;
//			if(op){
//				int x = rand()%L;
//				int y = (rand()%(L-x))+x;
//				queries.push_back(make_pair(op, II(x, y)));
//				int ra = st.query(L-y-1, L-x-1).f;
//				int rb = bb.query(x, y);
////				st.print();
////				cout << "----------" << endl;
//				if(ra != rb){
//					cout << B << " " << P << " " << L << " " << N << endl;
//					for(int k=0; k<queries.size(); k++){
//						cout << queries[k].first << " " << queries[k].second.first<< " " << queries[k].second.second<< endl;
//					}
//					cout << ra << " " << rb << endl;
//					return 0;
//				}
//			}else{
//				int x = rand()%L;
//				int y = rand()%(B-2);
//				queries.push_back(make_pair(op, II(x, y)));
//				st.update(L-x-1, y);
//				bb.update(x, y);
////				st.print();
////				cout << "----------" << endl;
//			}
//		}
//	}
//}

int main(){
//	ios_base::sync_with_stdio(false);
	int L, N;
	while(scanf("%d %d %d %d", &B, &P, &L, &N)!=EOF){
		if(B == 0 && P == 0 && L == 0 && N == 0) break;
		vector<NodeInit> V(L, NodeInit(0));
		SegmentTree st(L);
		st.create(V);
		for(int i=0; i<N; i++){
			char c[80];
			scanf("%s", c);
			if(c[0]=='H'){
				int x, y;
				scanf("%d %d", &x, &y);
				printf("%d\n", st.query(L-y, L-x).f);
//				st.print();
//				cout << "-------------------" << endl;
			}else{
				int x, v;
				scanf("%d %d", &x, &v);
				st.update(L-x, v);
//				st.print();
//				cout << "-------------------" << endl;
			}
		}
		printf("-\n");
	}
	return 0;
}
