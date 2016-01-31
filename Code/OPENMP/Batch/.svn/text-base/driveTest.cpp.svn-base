//This is the main serial driver code. The old main.cpp has been rewritten and is called by this file.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include <sstream>
#include <stdio.h>      /* printf, NULL */
#include <random>
#include <dirent.h>
#include <regex>
#include <vector>
#include <cilk/cilk.h>

#include "timer.c"

//#include "node.h"
#ifndef astar_H_
#define astar_H_

// printer.h code goes here
#include "astar.h"
#endif

#include "mainLoop.h"
//#include "map.h"





using namespace std;





//based loosely on the wikipedia excerpt on A* and a basic recipe from:
//http://code.activestate.com/recipes/577457-a-star-shortest-path-algorithm/
//Any code used has been heavily modified to be extendable and more robust. Original code only had one hard coded map and tons of global variabls.

bool debug =0;

// Determine priority (in the priority queue)
bool operator<(const node  a, const node  b)
{
    return a.getPriority() > b.getPriority();
}

int BREAKPOINT()
{
    return 0;
}



typedef std::mt19937 MyRNG;
uint32_t seed_val=37; //get the same random stream for each time we run this driver. Good for comparisons.

MyRNG rng;                   // e.g. keep one global instance (per thread)

void initialize(MyRNG rng)
{
    rng.seed(seed_val);
}


bool debugMain=0;

bool exists_test (const std::string& name) {
    //bool file_exists(const std::string& s) {
    std::ifstream iff(name.c_str());
    return iff.is_open();
}


int main(int argc, char* argv[])
{
    
    
    stopwatch_init ();
    struct stopwatch_t* timerTot = stopwatch_create (); //assert (timer);'
    
    int allMaps=0;
    
    long int trials;
    vector<string> filenames;
    int count=1;
    string dir;
    stringstream ssDir;
    
    ssDir<<argv[2];
    ssDir>>dir;
    
    

    if(argc!=4) //didnt pass the correct number of arguments
    {
        cout<<"\nIncorrect number of arguments passed! Format is : <a*> mapName.csv NumberOfTrials RunAllMaps?(1 or 0 here)"<<endl;
        return 0;
    }
    else
    {
        
        
        //WE dont really care about the mapName now... Just pass the directory.
        
        istringstream ss(argv[1]);
        int x;
        if (!(ss >> x))
            cerr << "Invalid number " << argv[1] << '\n';
        trials=x;
        
        istringstream ssMps(argv[3]);
        if (!(ssMps >> x))
            cerr << "Invalid number " << argv[3] << '\n';
        
        allMaps=x;
        
        if(allMaps==1)
        {
            
            count=0;
            
////////////////////
///////// Apparently icpc cant handle c++11 regex...
///////// Rewriting section to work around the compiler issue.
            
            string tempName="/Users/stephan/Classes/Current/CSE6230/Project/par-pathfinder/Code/Cilk/maps/temp.txt";
            string line;
            std::ifstream iff(tempName.c_str());
            if((iff.is_open()))
            {
                iff.close();
                ifstream maps;
                maps.open(tempName);
                if(maps.is_open())
                {
                    while ( getline (maps,line) )
                    {
                        string temp="/Users/stephan/Classes/Current/CSE6230/Project/par-pathfinder/Code/Cilk/maps/";
                        temp=temp+line;
                        filenames.push_back(temp);
                        count++;
                    }
                    maps.close();
                }
                else
                {
                    cerr<<"maps/temp.txt could not be opened"<<'\n';
                }
                
            }
            
            else //chuck an error
            {
                cerr<<"WARNING: maps/temp.txt does not exist! Should be filled with all .png names"<<'\n';
                
            }
            
//           regex matchStr ("bmp");
////            auto m = cmatch ();
////            assert(m.empty());
//            
//           
//            string temp;
//            struct dirent *de;
//            DIR *dir = opendir(argv[2]);
//            if(!dir)
//            {
//                printf("opendir() failed! Does it exist?\n");
//                return 1;
//            }
//            stringstream ss;
//            
//            while((de = readdir(dir)))
//            {
//
//                
//                if (regex_search(de->d_name,matchStr)) {
//                    ++count;
//                   //cout<<de->d_name<<endl;
//                    filenames.push_back(de->d_name);
//                  //  cout<<filenames[count-1]<<endl;
//                }
//                //puts(de->d_name);
//                
//            }
//            closedir(dir);

        }

        
    }

    
    
    //assert(filename);
    //assert(trials);
    
    //Need to load in the various map files and randomly choose one.
    //then need to send the filename to the mainLoop function. In the parallel versions once we
    //start benchmarking, should pull the begining/end points up here so that theres an valid
    //comparison between methods.
    
     std::cout<<"Overall Clock started"<<std::endl;
     stopwatch_start (timerTot);
   
    vector <resultInfo> results (trials);
    vector <mapClass> Map (trials);
    
    headerInfo header;
    // header.allMaps=allMaps;
    header.count=count;
    
    for(int q=0;q<trials;q++)
    {
          header.loopnum=q;
        if(allMaps==0)
        {
            // stringstream ss2(argv[2]);
            header.cstr=dir;
        }
        else
        {
            // cout<<"check count:"<<i<<" "<<count<<endl;
            int num=q%count;
            
            if(num==count)
            {
                //  cout<<"changing  num"<<endl;
                num=num-count;
            }
            
            string name=filenames[num];
            //        name=dir+name;
            //        cout<<name<<endl;
            
            // const char* cstr = name.c_str();
            header.cstr=name;
            
        }
        
        std::string name= header.cstr;
        const char* cstr =name.c_str();
        Map[q].map(cstr);

    
    
    
    
    
    }
    
  
    
    cilk_for(int q=0;q<trials;q++)
    {
      
        
        
        cout<<endl;
        cout<<"Begin Trial "<<q+1<<"!"<<endl;
        cout<<"--------------------------------------------------"<<endl;
        
        stopwatch_init ();
        struct stopwatch_t* timer0 = stopwatch_create (); assert (timer0);
        
        
        //std::cout<<"Map Size (X,Y): "<<n<<","<<m<<std::endl;
        //    std::cout<<"Start: "<<xA<<","<<yA<<std::endl;
        //    std::cout<<"Finish: "<<xB<<","<<yB<<std::endl;
        // get the route
        
        std::cout<<"Clock started"<<std::endl;
        stopwatch_start (timer0);
//        resultInfo results;
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        //mapClass Map;
        //    while (1)
        //    {
        //        try{ //i/o errors. rertry.
                //            break;
        //            }
        //        catch(int w)
        //        {}
        //    }
        //    initialize();
        MyRNG moo;
        initialize(moo);
        int n=Map[q].getXleng();
        int m=Map[q].getYleng();
        std::uniform_int_distribution<uint32_t> Xdist(0,n-1);
        std::uniform_int_distribution<uint32_t> Ydist(0,m-1);
        
        //
        int xA, yA, xB, yB;
        xA=1; //Start at the origin. Simulates a home base for a drone.
        yA=1;
        xB=Xdist(moo);
        yB=Ydist(moo);
        
        int loopCtrl=1;
        while(loopCtrl)
        {
            loopCtrl=0;
            if(Map[q].MapPt(xA,yA)!=0) //picked an obstical. Pick a new point..
            {
                xA=Xdist(moo); //Wanted the orgin, but for some reason its blocked.
                yA=Ydist(moo);
                loopCtrl=1;
            }
            
            if(Map[q].MapPt(xB,yB)!=0) //picked an obstical. Pick a new point..
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
        
        //resultInfo results;
        
        //results.success=success;
        //results.time_elapsed=time_elapsed;
        results[q].xA=xA;
        results[q].yA=yA;
        results[q].xB=xB;
        results[q].yB=yB;
        results[q].pathlength=sqrt(pow(xA-xB,2) +pow(yA-yB,2));
        results[q].xleng=n;
        results[q].yleng=m;
        results[q].success=0;
        // results.Map=Map;
        int xStart=xA;
        int yStart=yA;
        int xFinish=xB;
        int yFinish=yB;
        
        
        
        static std::priority_queue<node> PriorQ[2]; // list of open (not-yet-tried) nodes
        static int Qindx; // PriorQ index
        //static node* n0;
        //static node* m0;
        static int i, j, x, y, xdx, ydy;
        int c;
        Qindx=0;
        // int m=Map.getXleng();
        // int n=Map.getYleng();
        const int dir=8;
        static int dx[8]={1, 1, 0, -1, -1, -1, 0, 1};
        static int dy[8]={0, 1, 1, 1, 0, -1, -1, -1};
        
        x=xStart;//fence post error else....
        y=yStart;
        
        int a=BREAKPOINT();
        
        a+=2;
        
        if(debug){
            std::cout<<"Map nodes reset"<<std::endl;}
        
        // create the start node and push into list of open nodes
        
        node n0(xStart, yStart, 0, 0);
        n0.updatePriority(xFinish, yFinish);
        PriorQ[Qindx].push(n0);
        Map[q].open_nodes[x][y]=n0.getPriority(); // mark it on the open nodes map
        if(debug){
            std::cout<< "begining search!"<<std::endl;}
        // A* search
        while(!PriorQ[Qindx].empty())
        {
            // get the current node w/ the highest priority
            // from the list of open nodes
            if(debug){
                std::cout<< "new node"<<std::endl;}
            node n0( PriorQ[Qindx].top().getxPos(), PriorQ[Qindx].top().getyPos(),
                    PriorQ[Qindx].top().getLevel(), PriorQ[Qindx].top().getPriority());
            
            x=n0.getxPos();
            y=n0.getyPos();
            
            PriorQ[Qindx].pop(); // remove the node from the open list
            
            
            if(x<n && y<m &&x>=0 && y>=0)
            {
                
                Map[q].open_nodes[x][y]=0;
                // mark it on the closed nodes map
                Map[q].closed_nodes[x][y]=1;
                
                // quit searching when the goal state is reached
                //if((*n0).estimate(xFinish, yFinish) == 0)
                if(x==xFinish && y==yFinish)
                {
                    if(debug){
                        std::cout<<"Path found!"<<std::endl;}
                    // generate the path from finish to start
                    // by following the directions
                    // int path=1;
                    
                    while(!(x==xStart && y==yStart))
                    {
                        j=Map[q].dir_map[x][y];
                        c=0+(j+8/2)%8;
                        //    path.push_back(c);
                        x+=dx[j];
                        y+=dy[j];
                    }
                    
                    results[q].Map=Map[q];
                    results[q].success=1;
                    // garbage collection
                    // delete n0;
                    // empty the leftover nodes
                    while(!PriorQ[Qindx].empty())
                    {PriorQ[Qindx].pop();}
                    break ;
                }
                
                // generate moves (child nodes) in all possible directions
                if(debug){
                    std::cout<< "check all the dirs"<<std::endl;}
                for(i=0;i<8;i++)
                {
                    xdx=x+dx[i]; ydy=y+dy[i];
                    
                    if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 ||Map[q].MapPt(xdx,ydy)==1
                         || Map[q].closed_nodes[xdx][ydy]==1))
                    {
                        if(debug){
                            std::cout<< "generate child nodes"<<std::endl;}
                        // generate a child node
                        node m0( xdx, ydy, n0.getLevel(),
                                n0.getPriority());
                        m0.nextLevel(i);
                        m0.updatePriority(xFinish, yFinish);
                        
                        // if it is not in the open list then add into that
                        if(Map[q].open_nodes[xdx][ydy]==0)
                        {
                            Map[q].open_nodes[xdx][ydy]=m0.getPriority();
                            PriorQ[Qindx].push(m0);
                            // mark its parent node direction
                            Map[q].dir_map[xdx][ydy]=(i+8/2)%8;
                        }
                        else if(Map[q].open_nodes[xdx][ydy]>m0.getPriority())
                        {
                            // update the priority info
                            Map[q].open_nodes[xdx][ydy]=m0.getPriority();
                            // update the parent direction info
                            Map[q].dir_map[xdx][ydy]=(i+8/2)%8;
                            
                            // replace the node
                            // by emptying one PriorQ to the other one
                            // except the node to be replaced will be ignored
                            // and the new node will be pushed in instead
                            while(!(PriorQ[Qindx].top().getxPos()==xdx &&
                                    PriorQ[Qindx].top().getyPos()==ydy))
                            {
                                PriorQ[1-Qindx].push(PriorQ[Qindx].top());
                                PriorQ[Qindx].pop();
                            }
                            PriorQ[Qindx].pop(); // remove the wanted node
                            
                            // empty the larger size PriorQ to the smaller one
                            if(debug){
                                std::cout<< "empty the larger size PriorQ to the smaller one"<<std::endl;}
                            if(PriorQ[Qindx].size()>PriorQ[1-Qindx].size()) Qindx=1-Qindx;
                            while(!PriorQ[Qindx].empty())
                            {
                                PriorQ[1-Qindx].push(PriorQ[Qindx].top());
                                PriorQ[Qindx].pop();
                            }
                            Qindx=1-Qindx;
                            PriorQ[Qindx].push(m0); // add the better node instead
                        }
                        else{
                            if(debug){
                                std::cout<< "about to garbage collect"<<std::endl;}
                            //  delete m0; // garbage collection
                            if(debug){
                                std::cout<< "garbage collection"<<std::endl;}
                        }
                        
                    }
                }
            }
            //   delete n0; // garbage collection
        }
        // delete m0;
        results[q].Map=Map[q];
        
        
        long double time_elapsed = stopwatch_stop (timer0)*pow(10,6);
        std::cout<< "Path calculated"<<std::endl;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if(results[q].success==0) std::cout<<"An empty route generated! "<<std::endl;
        
        std::cout<<"Time to calculate the route (ms): "<<time_elapsed<<std::endl;
        // cout<<"Route:"<<endl;
        //cout<<route<<endl<<endl;
        
        // follow the route on the map and display it
        //    const int dir=8;
        //    static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
        //    static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};
        
        
        if(results[q].success==1)
        {
            int j;
            //        int c;
            int x=results[q].xA;
            int y=results[q].yA;
            // cout<<"About to change a mappt"<<endl;
            results[q].Map.MapPtChng(x,y,2);
            // cout<<"mappt changed"<<endl;
            int i=0;
            while(1)
            {
                
                if((x==results[q].xB && y==results[q].yB) || i>(results[q].xleng+results[q].yleng)*2 )
                {
                    break;
                }
                j=results[q].Map.dir_map[x][y];
                //c=0+(j+8/2)%8;
                //    path.push_back(c);
                x+=dx[j];
                y+=dy[j];
                results[q].Map.MapPtChng(x,y,3);
                i++;
            }
            results[q].Map.MapPtChng(x,y,4);

//        results[q]=   mainLoop(header);
        cout<<endl;
    }
    }
    
    
    
    
    
    
    
    cilk_sync;
    long double time_elapsed_tot = stopwatch_stop (timerTot);
    printf ("Sequential Total runtime: %Lg seconds\n",time_elapsed_tot);

    
    std::string outName;
    std::string outStats;
    int num=1;
    int loopd=0;
    
    for(int q=0;q<trials;q++)
    {
        while(1)
        {
            std::ostringstream convert;
            convert<<num;
            std::ostringstream convert1;
            convert1<<q;
            outName= "/Users/stephan/Classes/Current/CSE6230/Project/par-pathfinder/Code/Cilk/runs/Run_" + convert.str()+"_"+convert1.str();
            outStats="/Users/stephan/Classes/Current/CSE6230/Project/par-pathfinder/Code/Cilk/runs/Run_stats_"+convert1.str()+".csv";
            outName=outName +".bmp";
            
            loopd++;
            if(exists_test(outName))
            {
                num++;
            }
            else
            {
                
                results[q].Map.OutputMap(outName);
                std::ofstream stats;
                bool exists=0;
                if(exists_test(outStats))
                {
                    exists=1;
                    stats.open(outStats,std::ios::out|std::ios::app);
                }
                else
                {
                    stats.open(outStats,std::ios::out);
                }
                
                
                
                if(stats.is_open())
                {
                    if(!exists)
                    {
                        stats<<"Success, Time Elapsed,Xstart,Ystart, Xend,Yend,Xlength, Ylength, PathDist\n";
                    }
                    stats<<results[q].success<<","<<results[q].time_elapsed<<","<<results[q].xA<<","<<results[q].yA<<","<<results[q].xB<<","<<results[q].yB<<","<<results[q].xleng<<","<<results[q].yleng<<","<<results[q].pathlength<<std::endl;
                    stats.close();
                }
                else
                { std::cout<<"\nUNABLE TO OPEN FILE"<<std::endl;
                    return 0;
                }
                break;
            }
            
            if(num>1000|loopd>1000)
            {
                std::cout<<"\n CANT OPEN FILES... N>100... ending without saving"<<std::endl;
                break;
            }
            
        }
    }
    
    
    
    
 
  //  std::string outStats;
   // outStats="runs/Run_stats.csv";
    std::ofstream stats;
    //bool exists=0;
    stats.open(outStats,std::ios::out|std::ios::app);
    if(stats.is_open())
    {
    stats<<"3"<<","<<time_elapsed_tot<<","<<""<<","<<""<<","<<""<<","<<""<<","<<""<<","<<""<<","<<""<<std::endl;
        stats.close();
    }
    else
    { std::cout<<"\nUNABLE TO OPEN FILE"<<std::endl;
        return 0;
    }

    
    
    
}
