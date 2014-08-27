#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <map>

using namespace std;

struct edge {
	int dest;
	int weight;
};

struct vertex {
	int source;
	list<edge> adj_list;
};

struct _node_info {
	int idx;
	int start_time;
	int end_time;
	_node_info(int a, int b, int c) : idx(a), start_time(b), end_time(c) { }
};

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
		e.dest = dest;
		e.weight = weight;
		graph_node[source].adj_list.push_back(e);

	}

	void show_graph() {
		for(int i=0; i<vertex_num; ++i) {
			cout<<"["<<graph_node[i].source<<"] ";
			list<edge>::iterator iter = graph_node[i].adj_list.begin();
			while(iter!=graph_node[i].adj_list.end()){ 
				cout<<"->"<<"("<<(*iter).dest<<","<<(*iter).weight<<")";
				++iter;
			}
			cout<<endl;
		}

	}

	void bfs(int source ) {
		vector<bool> visited(vertex_num, false);
		queue<int> myqueue;
		myqueue.push(source);
		while(!myqueue.empty()) {
			int idx = myqueue.front();
			cout<<"visited node "<<idx<<endl;
			visited[idx] = true;
			myqueue.pop();
			list<edge>::iterator iter = graph_node[idx].adj_list.begin();
			while(iter!=graph_node[idx].adj_list.end()) {
				if(!visited[(*iter).dest])
					myqueue.push((*iter).dest);
				++iter;
			}		
		}	
	}

	void _dfs(int source, int& time, vector<bool>& visited, list<_node_info>& l) {
		int idx = source;
		list<edge>::iterator iter = graph_node[idx].adj_list.begin();
		visited[idx] = true;
		int start_time = time;
		while(iter!=graph_node[idx].adj_list.end()) {
			if(!visited[(*iter).dest]){
				++time;
				_dfs((*iter).dest, time, visited, l);
			}
			++iter;
		}	
		int end_time = ++time;
		_node_info ni(idx, start_time, end_time);
		l.push_front(ni);
	        cout<<"Visited node "<<idx<<":"<<start_time<<" "<<end_time<<endl;
	}

	void dfs(list<_node_info> &l) {
		vector<bool> visited(vertex_num, false);
		int time = 0;
		for(int i=0; i<vertex_num; ++i)
			if(!visited[i]){
		   	    _dfs(i,time,visited, l);
			    ++time;	
			}
	}

	list<_node_info> topsort() {
		list<_node_info> topsort_list;
		dfs(topsort_list);
		return topsort_list;
	}

	void print_top_list(list<_node_info>& l)  {
		list<_node_info>::iterator iter = l.begin();
		while(iter!=l.end()) {	 
			cout<<"("<<iter->idx<<")"<<"["<<iter->start_time<<","<<iter->end_time<<"] ";
			++iter;
		}
		cout<<endl;
	} 
};

graph gen_graph() {
	graph g(6);
	g.connect(0,1,1);
	g.connect(0,3,1);
	g.connect(1,4,1);
	g.connect(2,4,1);
	g.connect(2,5,1);
	g.connect(3,1,1);
	g.connect(4,3,1);
	g.connect(5,5,1);
	return g;
}

int main() {
	graph g = gen_graph();
	g.show_graph();
	list<_node_info> l;
	g.dfs(l);
	l = g.topsort();
	g.print_top_list(l);
}
