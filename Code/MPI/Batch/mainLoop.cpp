
#include "mainLoop.h"

//
//struct headerInfo{
//    
//    //int allMaps;
//    int loopnum;
//    int count;
//    const char* cstr;
//};
//
//struct resultInfo{
//    int success;
//    long double time_elapsed;
//    int xA;
//    int yA;
//    int xB;
//    int yB;
//    int xleng;
//    int yleng;
//    double pathlength;
//    mapClass Map;
//};
//



resultInfo mainLoop(headerInfo &header)
{
    stopwatch_init ();
    struct stopwatch_t* timer0 = stopwatch_create (); assert (timer0);

//    std::cout<<"Clock started"<<std::endl;
    stopwatch_start (timer0);
    resultInfo results;
    results=pathFind(header);
    
    long double time_elapsed = stopwatch_stop (timer0)*pow(10,3);
  //  std::cout<< "Path calculated"<<std::endl;
    
    if(results.success==0) std::cout<<"An empty route generated! "<<std::endl;
   
 //   std::cout<<"Time to calculate the route (ms): "<<time_elapsed<<std::endl;
 
    results.time_elapsed=time_elapsed;
    
    
    
        return results;
}
