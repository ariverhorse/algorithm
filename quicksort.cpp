#include <iostream>
#include <vector>
#include <iterator>

#define NUM 50
using namespace std;

// quick sort

int partition(vector<int>& v, int s, int e) {
	int i,j;
	for(i=s-1, j=s;j<=e; ++j) {
		if(v[j]<=v[e]) 
			swap(v[j], v[++i]);
	} 	
	return i;
}
void myqsort(vector<int>& v, int s, int e ) {
	if(s<e) { 
		int mid = partition(v, s, e);
		myqsort(v, s, mid-1);
		myqsort(v, mid+1, e);
	}	
}

int main() {
	vector<int> v;
	for(int i=0; i<NUM; ++i) 
		v.push_back(rand()%NUM);

	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;

	myqsort(v, 0, v.size()-1);

	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;
}
