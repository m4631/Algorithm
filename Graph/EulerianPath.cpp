struct EulerianPath {
    struct Edge{
        int u,v,used;
        int getV(int u){
            return this->u == u ? v : u;
        }
    };
    bool directed;
    VVI adj;
    vector<Edge> E;
    VI cId, outDeg, inDeg;
    int N;
    EulerianPath(int N, int directed = false){
        this->directed = directed;
        this->N = N;
        adj = VVI(N);
        cId = VI(N);
        outDeg= VI(N);
        inDeg = VI(N);
    }
    void addEdge(int u,int v){
        Edge e = (Edge){ u, v, 0 };
        adj[u].push_back(E.size());
        outDeg[u]++;
        inDeg[v]++;
        if(!directed){
            adj[v].push_back(E.size());
            outDeg[v]++;
            inDeg[u]++;
        }
        E.push_back(e);
    }
    vector<int> getEulerPath(){
        int st = -1, cnt = 0;
        for(int i = 0; i < N; ++i){
            if(st == -1 && outDeg[i])
                st = i;
            if(directed){
                int d = outDeg[i] - inDeg[i];
                if(d > 1)return vector<int>();
                if(d ==1)st = i, cnt++;
                if(cnt>=2)return vector<int>();
            }else{
                int d = outDeg[i];
                if(d%2!=0)st = i, cnt++;
                if(cnt> 2)return vector<int>();
            }
        }
        stack<int> STK;
        STK.push(st);
        vector<int> ret;
        while(STK.size()){
            int u = STK.top();
            bool found = false;
            while(cId[u] < adj[u].size()){
                Edge &e = E[adj[u][cId[u]++]];
                if(e.used)continue;
                e.used = true;
                int v = e.getV(u);
                found = true;
                STK.push(v);
                break;
            }
            if(!found){
                STK.pop();
                ret.push_back(u);
            }
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }
};
