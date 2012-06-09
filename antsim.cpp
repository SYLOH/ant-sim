#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <climits>
#include <cstring>
#include <stdlib.h>
#include <cmath>
#include "antsim.h"



using namespace std;
int numNodes;


int main(int argc, char* argv[]){
	int argParser;
	if (argc!= 2){
		return 0;
	}
	argParser = atoi(argv[1]);
	cout<<argParser<<endl<<endl;
	if ( argParser == 1){
		numNodes= 10;
		colony mColony;
		for(int i = 0; i<100; i++){
			cout<< endl<<endl<<"Iteration: "<<i<<endl;
			mColony.runAnts();
			mColony.mMap.printTrails();
			mColony.applyUpdate();
			cout<<mColony.shortestPathLen<<endl;
			mColony.printShortestPath();
		
		}
	}
	if ( argParser == 2){
		numNodes= 30;
		float percentage;
		int precomputed =10628;
		colony mColony("oliver30_d.txt");
		for(int i = 0; i<100; i++){
			cout<< endl<<endl<<"Iteration: "<<i<<endl;
			mColony.runAnts();
			mColony.mMap.printTrails();
			cout<<mColony.shortestPathLen<<endl;
			percentage =((float)mColony.shortestPathLen/(float)precomputed);
			cout<<percentage<<"%"<<endl;
			mColony.printShortestPath();
		
		}
		mColony.mMap.printTrails();
	}
	if ( argParser == 3){
		numNodes= 30;
		colony colony1("oliver30_d.txt");
		colony colony2("oliver30_d.txt");
		colony colony3("oliver30_d.txt");
		colony colony4("oliver30_d.txt");

		for(int i = 0; i<500; i++){
			cout<< endl<<endl<<"Iteration: "<<i<<endl;
			colony1.runAnts();
			colony2.runAnts();
			colony3.runAnts();
			colony4.runAnts();

			colony1.colonyTransfer(.4,colony4);
			colony1.colonyTransfer((-.1),colony2);
			colony2.colonyTransfer(.4,colony4);
			colony2.colonyTransfer((-.1),colony3);
			colony3.colonyTransfer(.4,colony4);
			colony3.colonyTransfer((-.1),colony1);
			colony4.colonyTransfer(.4,colony4);
	//		colony4.colonyTransfer((-.1),colony2);

			colony1.applyUpdate();
			colony2.applyUpdate();
			colony3.applyUpdate();
			colony4.applyUpdate();

			cout<<colony1.shortestPathLen<<endl;
			colony1.printShortestPath();
			cout<<colony2.shortestPathLen<<endl;
			colony2.printShortestPath();
			cout<<colony3.shortestPathLen<<endl;
			colony3.printShortestPath();
			cout<<colony4.shortestPathLen<<endl;
			colony4.printShortestPath();
		
		}
		colony1.mMap.printTrails();
		
	}	

	if ( argParser == 4){
		numNodes= 10;
		colony colony1;
		colony colony2;
		colony colony3;
		colony colony4;

		for(int i = 0; i<400; i++){
			cout<< endl<<endl<<"Iteration: "<<i<<endl;
			colony1.runAnts();
			colony2.runAnts();
			colony3.runAnts();
			colony4.runAnts();
		

			colony1.colonyTransfer(.4,colony4);
			colony1.colonyTransfer((-.1),colony2);
			colony2.colonyTransfer(.4,colony4);
			colony2.colonyTransfer((-.1),colony3);
			colony3.colonyTransfer(.4,colony4);
			colony3.colonyTransfer((-.1),colony1);
			colony4.colonyTransfer(.4,colony4);
	//		colony4.colonyTransfer((-.1),colony2);

			colony1.applyUpdate();
			colony2.applyUpdate();
			colony3.applyUpdate();
			colony4.applyUpdate();

			cout<<colony1.shortestPathLen<<endl;
			colony1.printShortestPath();
			cout<<colony2.shortestPathLen<<endl;
			colony2.printShortestPath();
			cout<<colony3.shortestPathLen<<endl;
			colony3.printShortestPath();
			cout<<colony4.shortestPathLen<<endl;
			colony4.printShortestPath();
		
		}
		colony1.mMap.printTrails();
	
		cout<<endl;
		colony2.mMap.printTrails();
	
		cout<<endl;
		colony3.mMap.printTrails();
	
		cout<<endl;
	}
	return 0;
}


void ant::genPath(map mMap){
	pathLen = 0;
	int curNode = 0;
	int nextNode;
	bool visitedNodes[numNodes];
	for (int i = 0;i<numNodes;i++){
		visitedNodes[i]= false;
	}
	path[0] = 0;
	
	for(int i = 1;i<numNodes; i++){
		
		visitedNodes[curNode]=true;
		//select from remaining nodes
		nextNode = selectNextNode(mMap, visitedNodes, curNode);
		pathLen += mMap.distArray[curNode][nextNode];
		path[i] = nextNode;
		curNode = nextNode;
		
	}
	//adds in the return completing the circuit
	pathLen += mMap.distArray[curNode][0];
	
	

}
int ant::selectNextNode(map mMap, bool * visitedNodes, int curNode){
	float total=0;
	float nodeCounter=0;
	float randResult;
	
	//create the random horizon
	for (int i = 0; i < numNodes; i++){
		if(!visitedNodes[i]){
			total += mMap.trailArray[curNode][i]*pow((1/mMap.distArray[curNode][i]),distWeight);
		}
	}
	srand((unsigned)time(0)+id);//reseed the RNG
	randResult = total * ((float)rand()/(float)RAND_MAX);//rolls the dice
	
	for (int i= 0; i < numNodes; i++){
		if(!visitedNodes[i]){
			nodeCounter += mMap.trailArray[curNode][i]*pow((1/mMap.distArray[curNode][i]),distWeight);
			if (nodeCounter >= randResult){
				return i;
			}
		}
	}
	
	return 0;	
}

int map::loadFile(){
	return loadFile("dist.txt");
}

int map::loadFile(const char* fileName){
	ifstream file;
	file.open(fileName);
	if(! file.is_open()){
		return 0;
	}
	for(int i =0;i<numNodes;i++){
		for(int j =0; j<numNodes;j++){
			file>>distArray[i][j];
		}
	}
	return 1;
}

void map::initTrails(){
	for(int i =0;i<numNodes;i++){
		for(int j =0; j<numNodes;j++){
			trailArray[i][j]= trailBaseline;
		}
	}

}

void map::initUpdate(){
	for(int i =0;i<numNodes;i++){
		for(int j =0; j<numNodes;j++){
			updateArray[i][j]= 0;
		}
	}

}

void map::printDists(){
	for(int i =0;i<numNodes;i++){
		for(int j =0; j<numNodes;j++){
			cout<<distArray[i][j]<<" ";
		}
		cout<<endl;
	}

}

void map::printTrails(){
	for(int i =0;i<numNodes;i++){
		for(int j =0; j<numNodes;j++){
			cout<<trailArray[i][j]<<" ";
		}
		cout<<endl;
	}

}

colony::colony(){
	mMap.loadFile();
	mMap.initTrails();
	mMap.initUpdate();
	shortestPathLen = INT_MAX;
	for(int i=0; i< numAnts;i++){
		ants[i].id = i;
	}

	mMap.printDists();
	cout<<endl;
}
colony::colony(const char * fileName){
	mMap.loadFile(fileName);
	mMap.initTrails();
	mMap.initUpdate();
	shortestPathLen = INT_MAX;
	for(int i=0; i< numAnts;i++){
		ants[i].id = i;
	}

	mMap.printDists();
	cout<<endl;
}

void colony::runAnts(){
	for (int i = 0; i< numAnts; i++){
		ants[i].genPath(mMap);
	}
	
	evaporateTrails();

	for (int i = 0; i< numAnts; i++){
		
		if(ants[i].pathLen < shortestPathLen){
			shortestPathLen = ants[i].pathLen;
			
			for(int c = 0; c< numNodes;c++){
				shortestPath[c] = ants[i].path[c];
			}
		}
		depositePhermones(ants[i]);
	}
	

}

void colony::evaporateTrails(){
	for(int i =0;i<numNodes;i++){
		for(int j =0; j<numNodes;j++){
			mMap.trailArray[i][j] *= (1-evaporationCoeff);
			if(mMap.trailArray[i][j] < minValue){
				mMap.trailArray[i][j]= minValue;
			}			
		}
	}
}

void colony::depositePhermones(ant mAnt){
	for(int i = 0; i<numNodes-1;i++){
		mMap.trailArray[mAnt.path[i]][mAnt.path[i+1]] += (antPheremoneAmount/mAnt.pathLen);	
	}
	mMap.trailArray[mAnt.path[numNodes-1]][mAnt.path[0]] +=(antPheremoneAmount/mAnt.pathLen);
}

void colony::printShortestPath(){
	for(int i =0; i< numNodes; i++){
		cout<< shortestPath[i]<<" ";
	}
	cout<<endl;
}

void colony::colonyTransfer(float effect, colony oColony){
	for(int i = 0; i< numNodes; i++){
		for(int j = 0; j< numNodes; j++){
			mMap.updateArray[i][j] += effect * oColony.mMap.trailArray[i][j];
			
		}
	}

}

void colony::applyUpdate(){
	for(int i = 0; i< numNodes; i++){
		for(int j = 0; j< numNodes; j++){
			mMap.trailArray[i][j] += mMap.updateArray[i][j];
			if(mMap.trailArray[i][j]<0){
				mMap.trailArray[i][j]= 0;
			}
		}
	}
	mMap.initUpdate();
}




