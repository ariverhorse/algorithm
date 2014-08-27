#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

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
	graph g(6);
	g.connect(0,1,10);
	g.connect(0,3,9);
	g.connect(1,4,8);
	g.connect(2,4,4);
	g.connect(2,5,7);
	g.connect(3,1,5);
	g.connect(4,3,6);
	g.connect(5,5,3);
	return g;
}

int main() {
	graph g = gen_graph();
	g.show_graph();
	vector<edge> v = g.get_all_edges();
	sort(v.begin(), v.end(), edge_compare);
	for(int i=0; i<v.size(); ++i)
		cout<<v[i].weight<<" "<<v[i].src<<" "<<v[i].dest<<endl; 
}
