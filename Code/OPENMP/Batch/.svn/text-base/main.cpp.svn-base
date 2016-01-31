// Astar.cpp
// http://en.wikipedia.org/wiki/A*
// Compiler: Dev-C++ 4.9.9.2
// FB - 201012256
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include <sstream>
#include <stdio.h>
//#include "node.h"
#include "astar.h"
//#include "map.h"
using namespace std;

inline bool exists_test (const std::string& name) {
    return (std::ifstream(name));
}

bool debugMain=0;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    long int trials;
    string filename;
    if(argc!=3) //didnt pass the correct number of arguments
    {
    cout<<"\nIncorrect number of arguments passed! Format is : <a*> mapName.csv NumberOfTrials"<<endl;
        return 0;
    }
    else
    {
        // filename=argv[1];
        
        istringstream ss(argv[1]);
        int x;
        if (!(ss >> x))
            cerr << "Invalid number " << argv[1] << '\n';
        trials=x;
    }
        //assert(filename);
       // assert(trials);
        
        mapClass Map;
        Map.map(argv[2]);
    int n=Map.getXleng();
    int m=Map.getYleng();
    

    if(debugMain)
    {
    for(int y=0;y<m;y++)
    {
        for(int x=0;x<n;x++)
            if(Map.MapPt(x,y)==0)
                cout<<".";
            else if( Map.MapPt(x,y)==1)
                cout<<"O"; //obstacle
            else if( Map.MapPt(x,y)==2)
                cout<<"S"; //start
            else if( Map.MapPt(x,y)==3)
                cout<<"R"; //route
            else if( Map.MapPt(x,y)==4)
                cout<<"F"; //finish
        cout<<endl;
    }
        getchar(); // wait for a (Enter) keypress
    }
    
    
    int xA, yA, xB, yB;
    
    xA=rand()%n;
    xB=rand()%n;
    yA=rand()%m;
    yB=rand()%m;
    int loopCtrl=1;
    while(loopCtrl)
    {
        loopCtrl=0;
        if(Map.MapPt(xA,yA)==1) //picked an obstical. Pick a new point..
        {
                xA=rand()%n;
                yA=rand()%m;
            loopCtrl=1;
        }
        
        if(Map.MapPt(xB,yB)==1) //picked an obstical. Pick a new point..
        {
            xB=rand()%n;
            yB=rand()%m;
            loopCtrl=1;
        }
    }

    cout<<"Map Size (X,Y): "<<n<<","<<m<<endl;
    cout<<"Start: "<<xA<<","<<yA<<endl;
    cout<<"Finish: "<<xB<<","<<yB<<endl;
    // get the route
    clock_t start = clock();
    cout<<"Clock started"<<endl;
    string route=pathFind(xA, yA, xB, yB,  Map);
    cout<< "Path calculated"<<endl;
    
    if(route=="") cout<<"An empty route generated! "<<endl;
    clock_t end = clock();
    double time_elapsed = double(end - start);
    cout<<"Time to calculate the route (ms): "<<time_elapsed<<endl;
    cout<<"Route:"<<endl;
    cout<<route<<endl<<endl;

    // follow the route on the map and display it
    const int dir=8;
    static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
    static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};
    
    
    if(route.length()>0)
    {
        int j; char c;
        int x=xA;
        int y=yA;
        cout<<"About to change a mappt"<<endl;
        Map.MapPtChng(x,y,2);
        cout<<"mappt changed"<<endl;
        for(int i=0;i<route.length();i++)
        {
            c =route.at(i);
            j=atoi(&c); 
            x=x+dx[j];
            y=y+dy[j];
             Map.MapPtChng(x,y,3);
        }
         Map.MapPtChng(x,y,4);
    
        if(debugMain)
        {
        for(int y=0;y<m;y++)
        {
            for(int x=0;x<n;x++)
                if(Map.MapPt(x,y)==0)
                    cout<<".";
                else if( Map.MapPt(x,y)==1)
                    cout<<"O"; //obstacle
                else if( Map.MapPt(x,y)==2)
                    cout<<"S"; //start
                else if( Map.MapPt(x,y)==3)
                    cout<<"R"; //route
                else if( Map.MapPt(x,y)==4)
                    cout<<"F"; //finish
            cout<<endl;
        }
        }
    }
    
    string outName;
    string outStats;
    int num=1;
    int loopd=0;
 
    while(1)
    {
        ostringstream convert;
        convert<<num;
        outName= "runs/Run_" + convert.str();
        outStats="runs/Run_stats.csv";
        outName=outName +".bmp";
        
        loopd++;
        if(exists_test(outName))
        {
            num++;
        }
        else
        {
            
            Map.OutputMap(outName);
            ofstream stats;
            bool exists=0;
            if(exists_test(outStats))
            {
                exists=1;
                stats.open(outStats,ios::out|ios::app);
            }
            else
            {
            stats.open(outStats,ios::out);
            }
            int success=0;
            if(route=="")
            {
                success=0;
            }
            else
            {success=1;}
            
            
            if(stats.is_open())
            {
                if(!exists)
                {
                stats<<"Success, Time Elapsed,Xstart,Ystart, Xend,Yend,Xlength, Ylength, PathDist\n";
                }
                stats<<success<<","<<time_elapsed<<","<<xA<<","<<yA<<","<<xB<<","<<yB<<","<<n<<","<<m<<","<<sqrt(pow(xA-xB,2) +pow(yA-yB,2))<<endl;
                stats.close();
            }
            else
            { cout<<"\nUNABLE TO OPEN FILE"<<endl;
                return 0;
            }
            break;
        }
        
        if(num>100|loopd>100)
        {
            cout<<"\n CANT OPEN FILES... N>100... ending without saving"<<endl;
            break;
        }
        
    }
    
        return(0);
}
