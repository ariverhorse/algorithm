#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <limits>
#include <set>
#include "disjoint_set.h"
#include "priority_queue.h"
//MST algorithm

using namespace std;

struct edge {
	int src;
	int dest;
	int weight;
};

struct vertex {
	int source;
	list<edge> adj_list;
};

bool edge_compare(const edge& e1, const edge& e2) {
	return e1.weight <= e2.weight;
}	



class graph {
private:
	int vertex_num;
	vector<vertex> graph_node;

public:
	graph(int n) : vertex_num(n) {
		for(int i=0; i<n; ++i) {
			vertex v;
			v.source = i;
			graph_node.push_back(v);
		}
	}

	void connect(int source, int dest, int weight) {
		edge e;
		e.src  = source;
		e.dest = dest;
		e.weight = weight;
		graph_node[source].adj_list.push_back(e);

	}

	vector<edge> get_all_edges() {
		vector<edge> e;
		for(int i=0; i<vertex_num; ++i)	 {
			list<edge>::iterator iter = graph_node[i].adj_list.begin();
			while(iter!=graph_node[i].adj_list.end()) {
				e.push_back(*iter);
				++iter;
			}
		}
		return e;
	}

	vector<edge>  get_all_connections(int src) {
		vector<edge> e = get_all_edges();
		vector<edge> s;
		edge edg;
		for(int i=0; i<e.size(); ++i) {
			if(e[i].src == src) {
				edg.src = src;
				edg.dest = e[i].dest;
				edg.weight = e[i].weight;
				s.push_back(edg);
			}
			else if(e[i].dest == src) {
				edg.src  = src;
				edg.dest = e[i].src;
				edg.weight = e[i].weight; 
				s.push_back(edg);
			}
		}
		return s;
	}

	vector<edge> mst_prim() {
		priority_queue q(0);
		qdata d;
		for(int i=0; i<graph_node.size(); ++i) {
			d.id = graph_node[i].source;
			d.key = (i==0)? 0 : std::numeric_limits<int>::max();
			int* pre = new int;
			*pre = -1;
			d.data = static_cast<void*>(pre);
			q.insert(d); 
		}
		cout<<"Init..."<<endl;
		q._print_map();
		vector<edge> es;
		int twt =0;
		while(!q.empty()) {
			qdata a = q.extract_min();
			int   src = a.id;
			int   pre = *(static_cast<int*>(a.data));
			int   wt  = a.key;
			if(pre!=-1) {
				edge e;
				e.src = pre;
				e.dest = src;
				e.weight = wt;
				es.push_back(e);
				twt += wt;
			}
			vector<edge> s = get_all_connections(src);	
			vector<edge>::iterator siter = s.begin();
			vector<edge>::iterator eiter = s.end();
			while(siter!=eiter) {
				int dest = (*siter).dest;
				int old_key = q.get_key(dest);
				int new_key = (*siter).weight;
				if(q.is_in_heap(dest) && old_key > new_key) {
					q.decrease_key_by_id(dest, new_key);
					*static_cast<int*>(q.get_data(dest)) = src;		
				        //cout<<"Update "<<dest<<" weight to "<<new_key<<" pre to "<<src<<endl;	
				}	
				++siter;
			}
			//cout<<q<<endl;	 
		}
		cout<<"MST edge weight is: "<<twt<<endl;	
		q._print_map();	
		return es; 	
	}

	vector<edge> mst_kruskal() {
		vector<edge> edges;
		vector<edge> all_edges = get_all_edges();
		sort(all_edges.begin(), all_edges.end(), edge_compare);
		disjoint_set ds_set(vertex_num);
		int mst_weight = 0;
		for(int i=0; i<all_edges.size(); ++i) {
			edge e = all_edges[i];
			int  src  = e.src;
			int  dest = e.dest;
			if(ds_set.ds_find(src) != ds_set.ds_find(dest)) {
				mst_weight += e.weight;
				edges.push_back(e);
				ds_set.ds_union(src, dest);	
			} 		
		}	
		cout<<"MST edge weight is: "<<mst_weight<<endl;		
		return edges;
	}

	void show_graph() {
		for(int i=0; i<vertex_num; ++i) {
			cout<<"["<<graph_node[i].source<<"] ";
			list<edge>::iterator iter = graph_node[i].adj_list.begin();
			while(iter!=graph_node[i].adj_list.end()){ 
				cout<<"->"<<"("<<(*iter).src<<","<<(*iter).dest<<","<<(*iter).weight<<")";
				++iter;
			}
			cout<<endl;
		}

	}
};

graph gen_graph() {
	//a b c d e f g h i
        //0 1 2 3 4 5 6 7 8 
	graph g(9);
	g.connect(0,1,4);
	g.connect(0,7,8);
	g.connect(1,7,11);
        g.connect(1,2,8);
	g.connect(2,8,2);
	g.connect(8,7,7);
	g.connect(7,6,1);
	g.connect(8,6,6);
	g.connect(2,3,7);
	g.connect(2,5,4);
	g.connect(6,5,2);
	g.connect(3,5,14);
	g.connect(3,4,9);
	g.connect(4,5,10);	
	return g;
}

int main() {
	graph g = gen_graph();
	g.show_graph();
	vector<edge> v = g.mst_kruskal();
	cout<<"MST edges .. "<<endl;
	for(int i=0; i<v.size(); ++i)
		cout<<v[i].weight<<"-> ("<<v[i].src<<", "<<v[i].dest<<" )"<<endl;

 	v = g.mst_prim();
	cout<<"MST edges .. "<<endl;
	for(int i=0; i<v.size(); ++i)
		cout<<v[i].weight<<"-> ("<<v[i].src<<", "<<v[i].dest<<" )"<<endl;


}
