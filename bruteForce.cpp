#include <iostream>
#include <algorithm>
#include <climits>
#include <fstream>
using namespace std;

int main () {
	int nodes[] = {0,1,2,3,4,5,6,7,8,9};
	int shortestPath[10];
	int distArray[10][10];
	int len, shortest = INT_MAX;
	ifstream file;
	file.open("dist.txt");
	for(int i =0;i<10;i++){
		for(int j =0; j<10;j++){
			file>>distArray[i][j];
		}
	}

  	sort (nodes,nodes+10);

  	do {
    		cout<<nodes[0];
		len = 0;
		for(int i = 0; i<9;i++){
			len += distArray[nodes[i]][nodes[i+1]];
		}
			len += distArray[nodes[9]][nodes[0]];

		if(len < shortest){
			shortest = len;
			for(int i=0;i<10;i++){
				shortestPath[i]= nodes[i];
			}

		}
  	} while ( next_permutation (nodes,nodes+10) );
	cout<<endl<<"shortest path len: "<<shortest<<endl;
	for(int i=0;i<10;i++){
		cout<< shortestPath[i]<< " ";
		
	}
	cout<<endl;
  	return 0;
}
