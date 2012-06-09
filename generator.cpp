#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ctime>

using namespace std;
int main(){
	int i;
	int x,y;
	ofstream file;

	srand((unsigned)time(0));//reseeds the rng
	file.open("vertex.txt");
	for(i=0; i<10;i++){
		x = rand()%50;
		y = rand()%50;
		cout << x<<" "<<y<<endl;
		file << x<<" "<<y<<endl;
	}
	file.close();
	return 0;
}