#include "disjoint_set.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main() {
   disjoint_set s(10);
   s.print_all_sets();
  
   int a, b;
   while(1) {
	cout<<"please input two number for union:"<<endl;
	cin >> a >> b;
	s.ds_union(a, b);
	s.print_all_sets();
   }
}
