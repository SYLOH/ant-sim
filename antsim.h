#ifndef ANTSIM_H_
#define ANTSIM_H_

#include <cstring>
#define maxNodes 100
#define numAnts 10

#define evaporationCoeff 0.9
#define trailBaseline 20
#define distWeight 1
//#define minValue 0.01
#define minValue 0
#define antPheremoneAmount 20.0

using namespace std;
class map;
class ant;
class colony;

class ant{	
	int selectNextNode(map mMap, bool * visitedNodes, int curNode);
	public:
	int path[maxNodes];
	float pathLen;
	int * getPath();
	bool findPath(int time);
	void genPath(map mMap);
	int getPathLen();
	unsigned int id;//unique id to allow for different RNG seeding
};

class map{
	public:
	float distArray[maxNodes][maxNodes];
	float trailArray[maxNodes][maxNodes];
	float updateArray[maxNodes][maxNodes];
	int loadFile();
	int loadFile(const char* fileName);
	void initTrails();
	void initUpdate();
	void printTrails();
	void printDists();
};

class colony{
	void evaporateTrails();
	void depositePhermones(ant mAnt);
	
	public:
	colony();
	colony(const char* fileName);
	ant ants[numAnts];
	float shortestPath[maxNodes] ;
	float shortestPathLen;
	map mMap;
	void runAnts();
	void printShortestPath();
	void colonyTransfer(float effect, colony oColony);
	void applyUpdate();
	
	
};

#endif
