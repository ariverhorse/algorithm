#include "priority_queue.h"

using namespace std;

int main() {
	priority_queue q(0);
	qdata d;
	for(int i=0; i<20; ++i) {
		d.key = rand()%20;
		d.id = i;
		cout<<"Insert key :  "<<d.key<<endl;
		q.insert(d);
	}
	cout<<q<<endl;

	int id;
	int key;	
	while(1) {
		cout<<"Please input the id that you want to decrease: "<<endl;
		cin>> id;	
		cout<<"Please input the key that you want to decrease: "<<endl;
		cin>> key;
		q.decrease_key_by_id(id, key);		
		cout<<q<<endl;	
	}
	//while(!q.empty()) {
	//	d = q.extract_min();
	//	cout<<"Extract key: "<<d.key<<endl;
	//}							

	
}

