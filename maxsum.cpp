//Given an array of n positive integers. Write a program to find the sum of maximum sum subsequence of the given array such that the intgers in the subsequence are sorted in increasing order. For example, if input is {1, 101, 2, 3, 100, 4, 5}, then output should be 106 (1 + 2 + 3 + 100), if the input array is {3, 4, 5, 10}, then output should be 22 (3 + 4 + 5 + 10) and if the input array is {10, 5, 4, 3}, then output should be 10

#include <iostream>
#include <vector>

using namespace std;


int maxsum(const vector<int>& v) {
	int size = v.size();
	vector<int> value (size, 0);
	value[0] = v[0];	
	int mmx = v[0];
	for(int i=1; i<size; ++i) {
		int max = v[i];
		for(int j=i-1; j>=0; --j) {
			if(v[j] <= v[i] && (value[j]+v[i] > max)) {   
				max = value[j] + v[i];
			}
		}
		value[i] =max;	
		if(value[i] > mmx) 
			mmx = value[i];
	}
	return mmx;
}


int main() {

    vector<int> numbers;
    int v;
    while(cin>>v) {
	numbers.push_back(v);
    }
    cout<<"max sum value is: "<< maxsum(numbers)<<endl;

}
