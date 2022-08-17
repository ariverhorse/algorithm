#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <map>
//BFS algorithm

using namespace std;

struct edge {
	int dest;
	int weight;
};

struct vertex {
	int source;
	list<edge> adj_list;
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
	g.bfs(0);
}
