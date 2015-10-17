struct trie{
	trie *child[26];
	bool endh;
	int nc;
	
	trie(){
		memset(child, 0, sizeof child);
		endh = false;
		nc = 0;
	}
	~trie(){
		for(int i=0; i<26; i++){
			delete child[i];
		}
	}
	void insert(string s){
		trie *cur = this;
		for(int i=0; i<s.size(); i++){
			char c = s[i];
			trie *next = cur->child[c-'a'];
			if(!next){
				next = cur->child[c-'a'] = new trie();
				cur->nc++;
			}
			cur = next;
		}
		cur->endh = true;
	}
	bool find(string s){
		trie *cur = this;
		for(int i=0; i<s.size(); i++){
			char c = s[i];
			trie *next = cur->child[c-'a'];
			if(!next){
				return false;
			}
			cur = next;
		}
		return cur->endh;
	}
};
