#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>
#include <map>

typedef struct _qdata {
	int id;
	int key;
	void* data;
} qdata;


class priority_queue {
friend std::ostream& operator<<(std::ostream& os, priority_queue& q); 
private:
	std::vector<qdata>   _v;
	std::map<int, int>   _m;
	int             _size;	
	inline int _parent(int i) { return (i-1)>>1; }
	inline int _left(int i)   { return (i<<1)+1; }
	inline int _right(int i)  { return (i+1)<<1; }
	inline void _swap(int a, int b);
	void _min_heapify(int i);
	void _build_heap();
public:
	priority_queue(int size) : _size(size) { } 
	~priority_queue( )  { }	
	void insert(qdata x);
	qdata min();
	qdata extract_min();
	void decrease_key(int idx, int key);
	void decrease_key_by_id (int id, int key);
	int  get_key(int id) { int idx = _m[id]; return _v[idx].key; }
	void* get_data(int id) { int idx = _m[id]; return _v[idx].data; }
	inline bool empty() { return _v.size()==0 ; }
	bool  is_in_heap(int id)  { 
		for(int i=0; i<_v.size(); ++i) 
			if(_v[i].id == id) 
				return true;

		return false;		
	}
};

std::ostream& operator<<(std::ostream& os, priority_queue& q) {
	for(int i=0; i<q._v.size(); ++i) 
		os<<i<<": "<<"id="<<q._v[i].id<<"  key="<<q._v[i].key<<" "<<std::endl;
	os<<std::endl;
	return os;
} 

qdata priority_queue::min() {
	if(_v.size()==0) {
		std::cout<<"Error! Empty priority queue!"<<std::endl;
		exit(1);
	}
	return _v[0];
}

qdata priority_queue::extract_min() {
	if(_v.size()==0) {
		std::cout<<"Error! Empty priority queue!"<<std::endl;
		exit(1);
	}
	qdata min = _v[0];
	_v[0]=_v[_v.size()-1];
	_v.pop_back();
	_min_heapify(0);
	return min;	
}

void priority_queue::decrease_key(int idx, int key) {
	if(_v[idx].key < key) return;
	_v[idx].key = key;
	while(idx>0 && _v[_parent(idx)].key > _v[idx].key) {
		_swap(idx, _parent(idx));
		idx = _parent(idx);
	}

}


void priority_queue::decrease_key_by_id(int id, int key) {
	int idx = _m[id];
	decrease_key(idx, key);	
}

void priority_queue::insert(qdata x) {
	_v.push_back(x);		
	_v[_v.size()-1].key = 99999;
	_m[x.id] = _v.size()-1;
	decrease_key(_v.size()-1, x.key);	
}

void priority_queue::_swap(int a, int b) {
	qdata tmp;
	tmp = _v[a];
	_v[a] = _v[b];
	_v[b] = tmp;
	_m[_v[a].id] = a;
	_m[_v[b].id] = b;
}

void priority_queue::_min_heapify(int i) {
	int l = _left(i);
	int r = _right(i);
	int smallest;
	if(l<= _v.size()-1 && _v[l].key < _v[i].key)
		smallest = l;
	else
		smallest = i;
	
	if(r<=_v.size()-1 && _v[r].key < _v[smallest].key)
		smallest = r;
	//std::cout<<i<<" "<<l<<" "<<r<<" "<<" "<<smallest<<std::endl;
	//std::cout<<_v[i].key<<" "<<_v[l].key<<" "<<_v[r].key<<" "<<std::endl;
	if(smallest != i) { 
		_swap(smallest, i);
		_min_heapify(smallest);
	} 
}

void priority_queue::_build_heap() {
	for(int i=_v.size()-1; i>=0; --i) {
		_min_heapify(i);
	}
}


#endif
