#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <ctime>
#include "map.hpp"


using namespace std;

//const int n=60; // horizontal size of the map
//const int m=60; // vertical size size of the map

//
////static int map[n][m];
//static int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
//static int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
//static int dir_map[n][m]; // map of directions
const int dir=8; // number of possible directions to go at any position
// if dir==4
//static int dx[dir]={1, 0, -1, 0};
//static int dy[dir]={0, 1, 0, -1};
// if dir==8
static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

