#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <deque>
#include <limits>

using namespace std;

class edge {
private:
	int v;
	int w;
	int flow;
	int capacity;
public:
	edge(int v, int w, int c) {
		this->v        = v;
		this->w        = w;
		this->flow     = 0;
		this->capacity = c;
	}

	edge(const edge& e) {
		v = e.v;
		w = e.w;
		flow = e.flow;
		capacity = e.capacity;
	}
	int residueflowTo(int dest) {
		if(dest == w) 
			return (capacity-flow);
		else
			return flow;
	}

	void addresidueflowTo(int vertex, int delta) {
		if(vertex == w) 
			flow+=delta;
		else 
			flow-=delta;

	}

	int from() const {
		return v;
	}

	int to() const {
		return w;
	}

	int flw() const {
		return flow;
	}

	int cap() const {
		return capacity;
	}	

	int other(int vertex) {
		if(vertex == v) 
			return w;
		else
			return v;
	}

	string tostring() const {
		string str;
		char vstr[10];
		char wstr[10];
		char fstr[10];
		char cstr[10];
		sprintf(vstr, "%d", v);
		sprintf(wstr, "%d", w);
		sprintf(fstr, "%d", flow);
		sprintf(cstr, "%d", capacity);
		str += string(vstr) + string("->") + string(wstr) +string(" ") + string(fstr) +string("/") + string(cstr);
		return str;
	}
};

struct vertex {
	int source;
	list<edge*> adj_list;
};

class graph {
private:
	int vertex_num;
	vector<vertex> graph_node;
	vector<edge*>  edgeTo;
public:
	graph(int n) : vertex_num(n) {
		for(int i=0; i<n; ++i) {
			vertex v;
			v.source = i;
			graph_node.push_back(v);
			edgeTo.push_back(NULL);
		}
	}

	void addedge(edge* e) {
		graph_node[e->from()].source = e->from();
		graph_node[e->from()].adj_list.push_back(e);
		graph_node[e->to()].source = e->to();
		graph_node[e->to()].adj_list.push_back(e);	
	}


	bool has_augment_path(int src, int dest) {
		deque<int> q;
		q.push_back(src);
		vector<bool> marked = vector<bool>(vertex_num, false);
		marked[src] = true;
		while(!q.empty()) {
			int v = q.front();
			q.pop_front();
			if(v == dest) { 
				return true;
			}
			list<edge*>::iterator iter  = graph_node[v].adj_list.begin();
			list<edge*>::iterator end   = graph_node[v].adj_list.end();
			while(iter!=end) {
				int w = (*iter)->other(v);
				if(!marked[w] && (*iter)->residueflowTo(w)>0) {
					q.push_back(w);	
					edgeTo[w] = *iter;
					marked[w] = true;
				}		
				++iter;
			}
		}
		
		return false;	
	}

	int max_flow(int src, int dest) {
		while(has_augment_path(src, dest)) {
			int delta = numeric_limits<int>::max();
			int other = dest;
			while(other!=src) {
				int flow = edgeTo[other]->residueflowTo(other);
				if(flow < delta)
					delta = flow;	
				other = edgeTo[other]->other(other);	
			}	
			other = dest;
			while(other!=src) {
				edgeTo[other]->addresidueflowTo(other, delta);
				other = edgeTo[other]->other(other);	
			}	
		}
		
	       	int flow = 0;
 		list<edge*>::iterator iter  = graph_node[src].adj_list.begin();
		list<edge*>::iterator end   = graph_node[src].adj_list.end();
		while(iter!=end) {
			if((*iter)->from() == src) {
				flow += (*iter)->flw();
			}
			++iter;
		}
		return flow;
	}

	void show_graph() {
		for(int i=0; i<vertex_num; ++i) {
			cout<<"["<<graph_node[i].source<<"] ";
			list<edge*>::iterator iter = graph_node[i].adj_list.begin();
			while(iter!=graph_node[i].adj_list.end()){ 
				cout<<(*iter)->tostring()<<"    ";
				++iter;
			}
			cout<<endl;
		}

	}
};


int main(int argc, char** argv) {
 	if(argc!=2) {
		cout<<"Error! Usage maxflow <file> "<<endl;
		return 1;
	}

	ifstream in(argv[1]);
	if(!in) {
		cout<<"Error! Cannot open file "<<argv[1]<<endl;
		return 1;
	}

	int num_vertex;
	int num_edge;
	in >> num_vertex;
	in >> num_edge;
	graph g(num_vertex);
	for(int i=0; i<num_edge; ++i) {
		int src, dest, cap;
		in>>src>>dest>>cap;
		edge  *e = new edge(src, dest, cap);
		g.addedge(e);	
	}
	g.show_graph();
	cout<<"Max flow is "<<endl;
	cout<<g.max_flow(0, 5)<<endl;	
	g.show_graph();
}
