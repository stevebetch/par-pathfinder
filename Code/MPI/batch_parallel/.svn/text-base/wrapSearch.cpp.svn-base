#ifndef wrapSearch_H_
#define wrapSearch_H_

// printer.h code goes here
#include "wrapSearch.h"
#endif


#include <memory>
#include "pathfind.h"
using namespace PathFind;
using namespace std;

int glob=0;




resultInfo pathFind(headerInfo &header)
{
    
    mapClass Map;//header.Map;
    resultInfo results;
   // std::string name= header.cstr;
    const char* cstr[6] ={"maps/50map.bmp","maps/50mapAOR.bmp","maps/1000AOR_wObs.bmp","maps/100map.bmp","maps/1000Geometric.bmp","maps/cross50.bmp"};

    
    Map.map(cstr[header.loopnum%6]);
    //results.success=success;
    //results.time_elapsed=time_elapsed;
    int n=Map.getXleng();
    int m=Map.getYleng();
    int xB=header.xB;
    int yB=header.yB;
    
    results.xA=0;
    results.yA=0;
    
    results.xB=header.xB;
    results.yB=header.yB;
    results.pathlength=sqrt(pow(0-xB,2) +pow(0-yB,2));
    results.xleng=n;
    results.yleng=m;
   // results.Map=Map;
    //int xStart=xA;
//    int yStart=yA;
//    int xFinish=xB;
//    int yFinish=yB;
    results.success=0;
    results.loopnum=header.loopnum;
    
    auto_ptr<Search> search;
    search.reset(new AStar<>());
    search->setNodesLimit(m*n);
   // SearchUtils searchUtils;
     Tiling tiling(Map);
    bool w=0;
    w= search->findPath(tiling, tiling.getNodeId(0,0),tiling.getNodeId(xB,yB));
    const vector<int>& path = search->getPath();
    tiling.printFormatted(Map, path);
    //results.Map=Map;
    
    if(w!=0)
    {
        results.success=1;
    }
    
    return results; // no route found
}






