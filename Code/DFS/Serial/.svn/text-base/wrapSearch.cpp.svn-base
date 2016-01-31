#ifndef wrapSearch_H_
#define wrapSearch_H_

// printer.h code goes here
#include "wrapSearch.h"
#endif

#include <random>
#include <memory>
#include "pathfind.h"
using namespace PathFind;
using namespace std;

int glob=0;


//const int MAP_WIDTH = 20;
//const int MAP_HEIGHT = 20;

typedef std::mt19937 MyRNG;
uint32_t seed_val=37; //get the same random stream for each time we run this driver. Good for comparisons.

MyRNG rng;                   // e.g. keep one global instance (per thread)

void initialize(MyRNG rng)
{
    rng.seed(seed_val);
}


resultInfo pathFind(headerInfo &header)
{
    
    mapClass Map;
    
    std::string name= header.cstr;
    const char* cstr =name.c_str();
    Map.map(cstr);
    
    MyRNG moo;
    initialize(moo);
    
    int n=Map.getXleng();
    int m=Map.getYleng();
    std::uniform_int_distribution<uint32_t> Xdist(0,n-1);
    std::uniform_int_distribution<uint32_t> Ydist(0,m-1);
    
    //
    int xA, yA, xB, yB;
    xA=0; //Start at the origin. Simulates a home base for a drone.
    yA=0;
    xB=Xdist(moo);
    yB=Ydist(moo);
    
    int loopCtrl=1;
    while(loopCtrl)
    {
        loopCtrl=0;
        if(Map.MapPt(xA,yA)!=0) //picked an obstical. Pick a new point..
        {
            xA=Xdist(moo); //Wanted the orgin, but for some reason its blocked.
            yA=Ydist(moo);
            loopCtrl=1;
        }
        
        if(Map.MapPt(xB,yB)!=0) //picked an obstical. Pick a new point..
        {
            xB=Xdist(moo);
            yB=Ydist(moo);
            loopCtrl=1;
        }
        
        if(sqrt(pow(xA-xB,2)+pow(yA-yB,2))<(n/2)) // Not far enough apart.... Pick new points.
        {
            // xA=Xdist(rng);
            // yA=Ydist(rng);
            xB=Xdist(moo);
            yB=Ydist(moo);
            
            loopCtrl=1;
        }
        
    }
    
    resultInfo results;
    
    //results.success=success;
    //results.time_elapsed=time_elapsed;
    results.xA=xA;
    results.yA=yA;
    results.xB=xB;
    results.yB=yB;
    results.pathlength=sqrt(pow(xA-xB,2) +pow(yA-yB,2));
    results.xleng=n;
    results.yleng=m;
   // results.Map=Map;
    //int xStart=xA;
//    int yStart=yA;
//    int xFinish=xB;
//    int yFinish=yB;
    results.success=0;
    
    
    auto_ptr<Search> search;
    search.reset(new FringeSearch<>());
    search->setNodesLimit(m*n);
   // SearchUtils searchUtils;
     Tiling tiling(Map);
    bool w=0;
    w= search->findPath(tiling, tiling.getNodeId(xA,yA),tiling.getNodeId(xB,yB));
    const vector<int>& path = search->getPath();
    tiling.printFormatted(Map, path);
    results.Map=Map;
    
    if(w!=0)
    {
        results.success=1;
    }
    
    return results; // no route found
}






