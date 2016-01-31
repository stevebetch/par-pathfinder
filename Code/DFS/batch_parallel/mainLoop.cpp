
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


    //std::cout<<"Map Size (X,Y): "<<n<<","<<m<<std::endl;
//    std::cout<<"Start: "<<xA<<","<<yA<<std::endl;
//    std::cout<<"Finish: "<<xB<<","<<yB<<std::endl;
    // get the route

    //std::cout<<"Clock started"<<std::endl;
    stopwatch_start (timer0);
    resultInfo results;
    results=pathFind(header);
    
    long double time_elapsed = stopwatch_stop (timer0)*pow(10,3);
    //std::cout<< "Path calculated"<<std::endl;
    
    if(results.success==0) std::cout<<"An empty route generated! "<<std::endl;
   
  //  std::cout<<"Time to calculate the route (ms): "<<time_elapsed<<std::endl;
   // cout<<"Route:"<<endl;
    //cout<<route<<endl<<endl;
    results.time_elapsed=time_elapsed;
    // follow the route on the map and display it
//    const int dir=8;
//    static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
//    static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};
    
    
    if(results.success==1)
    {
       // int j;
//        int c;
        int x=results.xA;
        int y=results.yA;
       // cout<<"About to change a mappt"<<endl;
       // results.Map.MapPtChng(x,y,2);
       // cout<<"mappt changed"<<endl;
       // int i=0;
//        while(1)
//        {
//            
//            if((x==results.xB && y==results.yB) || i>(results.xleng+results.yleng)*2 )
//            {
//                break;
//            }
//            j=results.Map.dir_map[x][y];
//            //c=0+(j+8/2)%8;
//            //    path.push_back(c);
//            x+=dx[j];
//            y+=dy[j];
//             results.Map.MapPtChng(x,y,3);
//            i++;
//        }
       //  results.Map.MapPtChng(x,y,4);
    
//        if(0)
//        {
//        for(int y=0;y<m;y++)
//        {
//            for(int x=0;x<n;x++)
//                if(Map.MapPt(x,y)==0)
//                    std::cout<<".";
//                else if( Map.MapPt(x,y)==1)
//                    std::cout<<"O"; //obstacle
//                else if( Map.MapPt(x,y)==2)
//                    std::cout<<"S"; //start
//                else if( Map.MapPt(x,y)==3)
//                    std::cout<<"R"; //route
//                else if( Map.MapPt(x,y)==4)
//                    std::cout<<"F"; //finish
//            std::cout<<std::endl;
//        }
//        }
    }
    
//    int success=0;
//    if(route==0)
//    {
//        success=0;
//    }
//    else
//    {success=1;}
    
    
    
//    resultInfo results;
    
    
    
        return results;
}
