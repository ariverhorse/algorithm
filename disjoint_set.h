#ifndef DISJOINSET
#define DISJOINSET

#include <vector>
#include <iostream>
#define ROOT -1

#define mymax(x, y)  ((x)>(y))?(x):(y)

struct set_node{
	int idx;
	int parent;
	int rank;
	set_node(int i, int p, int r) : idx(i), parent(p), rank(r) { }
};

class disjoint_set {
private:
    std::vector<set_node> _v;

public:
    disjoint_set(int size);
    ~disjoint_set() {};

    int ds_find(int idx);
    void ds_union(int l, int r);
    void print_all_sets(); 
};


disjoint_set::disjoint_set(int size) { 
    for(size_t i =0; i<size; ++i) {
	set_node nd(i, ROOT, 0);
	_v.push_back(nd);
    }
}

int disjoint_set::ds_find(int idx) {
    std::vector<int> path;
    int parent = _v[idx].parent;
    while(parent!= ROOT) {
	path.push_back(idx);
	idx = parent;
	parent = _v[idx].parent;
    }

    //path compression
    for(int i=0; i<path.size(); ++i) {
	_v[path[i]].parent = idx;
	_v[path[i]].rank   = 1;
    }

    return idx;
}

void disjoint_set::ds_union(int l, int r) {	
   int s1 = ds_find(l);
   int s2 = ds_find(r);
   if(s1!=s2)  {
	if(_v[s1].rank >  _v[s2].rank) {
		_v[s2].parent = s1;
		_v[s1].rank = mymax(_v[s1].rank, (_v[s2].rank+1));
	} else {
		_v[s1].parent = s2;
		_v[s2].rank = mymax(_v[s2].rank, (_v[s1].rank+1));
	}
   }
}

void disjoint_set::print_all_sets() {
	for(int i=0; i<_v.size(); ++i)  {
		int root = _v[i].idx;
		std::vector<int> ss;
		for(int i=0; i<_v.size(); ++i)  {
			if(ds_find(i) == root || ds_find(i) == ROOT) 
				ss.push_back(i);
		}
		if(ss.size()>0) {	
			std::cout<<"{";
			for(int j=0; j<ss.size()-1; ++j) 
				std::cout<<ss[j]<<",";
			std::cout<<ss[ss.size()-1];
			std::cout<<"}"<<std::endl;
		}
	}
		
	std::cout<<std::endl;
}


#endif
