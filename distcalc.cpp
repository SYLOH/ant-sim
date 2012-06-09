#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>

using namespace std;

#define num_nodes 30
int main(){
	float distArray[num_nodes][num_nodes];
	float nodeList[num_nodes][2];
	float x,y;
	int i = 0;
	FILE* input;
	input = fopen("oliver30.txt","r");

	while (fscanf(input, "%f %f", &x, &y) != EOF) {
		cout<<x<<" "<<y<<endl;
		nodeList[i][0] = x;
		nodeList[i][1] = y;
		i++;
	}
	
	ofstream output;
	output.open("oliver30_d.txt");
	for (int j =0; j< num_nodes;j++){
		for (int k =0; k< num_nodes;k++){
			int dx, dy;
			dx = nodeList[j][0]- nodeList[k][0];
			dy = nodeList[j][1]- nodeList[k][1];
			distArray[j][k]= sqrt((dx*dx)+(dy*dy));
			cout<<distArray[j][k]<<" ";
			output<<distArray[j][k]<<" ";
		}
		cout<<endl;
		output<<endl;	
	}
	output.close();

	

	return 0;
}
