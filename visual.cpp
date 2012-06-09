#include<iostream>
#include<fstream>
#include <stdio.h>
#include <cstring>


using namespace std;
int main(){
	int x,y;
	FILE* input;
	char* charLine;

	char vis[50][50];
	for (int i =0; i<50;i++){
		for (int j = 0; j<50;j++){
			vis[i][j] = ' ';	
		}
	}

	input = fopen("vertex.txt","r");
	while (fscanf(input, "%d %d", &x, &y) != EOF) {
		cout<<x<<" "<<y<<endl;
		vis[x][y]= '*';
	}


	for (int i =0; i<50;i++){
		for (int j = 0; j<50;j++){
			cout<<vis[i][j];	
		}
		cout<<endl;
	}
	return 0;
}