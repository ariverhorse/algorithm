#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>

typedef struct _qdata {
	int key;
	void* data;
} qdata;

class priority_queue {
private:
	vector<qdata> _v;
	int   _size;	
	inline int parent(int i) { return (i-1)>>1; }
	inline int left(int i)   { return i<<1+1; }
	inline int right(int i)  { return (i+1)<<1; }
	inline void _swap(int a, int b);
	void min_heapify(int i);
	void build_heap();
public:
	priority_queue(int size) : _size(size) { } 
	~priority_queue( )  { }	
	void insert(qdata x);
	qdata min();
	qdata extract_min();
	void decrease_key(int idx, int key);
};

qdata priority_queue::min() {
	if(_v.size()==0) {
		cout<<"Error! Empty priority queue!"<<endl;
		exit(1);
	}
	return _v[0];
}

qdata priority_queue::extract_min() {
	if(_v.size()==0) {
		cout<<"Error! Empty priority queue!"<<endl;
		exit(1);
	}
	qdata min = _v[0];
	_v[0]=_v[_v.size()-1];
	_v.pop_back();
	min_heapify(0);
	return min;	
}

void priority_queue::decrease_key(int idx, int key) {
	_v[idx].key = key;
	while(idx>=0 && _v[parent[idx]].key > _v[idx].key) {
		_swap(idx, parent[idx]);
		idx = parent[idx];
	}

}

void priority_queue::insert(qdata x) {
	_v.push_back(x);		
	_v[_v.size()-1].key = 9999;
	decrease_key(_v.size()-1, x.key);	
}

void priority_queue::_swap(int a, int b) {
	qdata tmp;
	tmp.key = _v[a].key;
	tmp.data = _v[a].data;
	_v[a].key  = _v[b].key;
	_v[a].data = _v[b].data;
	_v[b].key = tmp.key;
	_v[b].data = tmp.data; 		
}

void priority_queue::min_heapify(int i) {
	int l = left(i);
	int r = right(i);
	int smallest;
	if(l<= _v.size()-1 && _v[l].key < _v[i].key)
		smallest = l;
	else
		smallest = i;
	
	if(r<=_v.size()-1 && _v[r].key < smallest)
		smallest = r;
	if(smallest != i) { 
		_swap(smallest, i);
		min_heapify(smallest);
	} 
}

void priority_queue::build_heap() {
	for(int i=_v.size()-1; i>=0; --i) {
		min_heapify(i);
	}
}


#endif
