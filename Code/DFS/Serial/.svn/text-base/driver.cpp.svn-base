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

#include <dirent.h>
#include <regex>
#include <vector>
#include <omp.h>

#include "timer.c"

//#include "node.h"
#ifndef wrapSearch_H_
#define wrapSearch_H_

// printer.h code goes here
#include "wrapSearch.h"
#endif

#include "mainLoop.h"
//#include "map.h"

#if !defined (_OPENMP)
#  error "*** Must compile this file with OpenMP! ***"
#endif




using namespace std;


bool debugMain=0;

bool exists_test (const std::string& name) {
    //bool file_exists(const std::string& s) {
    std::ifstream iff(name.c_str());
    return iff.is_open();
}


int main(int argc, char* argv[])
{
    
    
    stopwatch_init ();
    struct stopwatch_t* timer = stopwatch_create (); //assert (timer);'
    
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
            
            string tempName="maps/temp.txt";
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
                        string temp="maps/";
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
     stopwatch_start (timer);
   
    vector <resultInfo> results (trials);
    
    headerInfo header;
   // header.allMaps=allMaps;
    header.count=count;
//#pragma omp parallel  shared(allMaps,argv,filenames,trials,header,count,results)
    {
//#pragma omp for schedule(static)
    for(int i=0;i<trials;i++)
    {
        header.loopnum=i;
        
        if(allMaps==0)
        {
           header.cstr=dir;
        }
        else
        {
            // cout<<"check count:"<<i<<" "<<count<<endl;
            int num=i%count;
            
            if(num==count)
            {
                //  cout<<"changing  num"<<endl;
                num=num-count;
            }
            
           string name=filenames[num];
            //        name=dir+name;
            //        cout<<name<<endl;
            
          //  const char* cstr = name.c_str();
            header.cstr=name;
            
        }

        
        
        
        
        cout<<endl;
        cout<<"Begin Trial "<<i+1<<"!"<<endl;
        cout<<"--------------------------------------------------"<<endl;
        results[i]=mainLoop(header);
        cout<<endl;
    }
    }
    
    long double time_elapsed = stopwatch_stop (timer);
    printf ("Sequential Total runtime: %Lg seconds\n",
            time_elapsed);

    
    std::string outName;
    std::string outStats;
    int num=1;
    int loopd=0;
    
    for(int i=0;i<trials;i++)
    {
        while(1)
        {
            std::ostringstream convert;
            convert<<num;
            std::ostringstream convert1;
            convert1<<i;
            outName= "runs/Run_" + convert.str()+"_"+convert1.str();
            outStats="runs/Run_stats.csv";
            outName=outName +".bmp";
            
            loopd++;
            if(exists_test(outName))
            {
                num++;
            }
            else
            {
                
                results[i].Map.OutputMap(outName);
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
                    stats<<results[i].success<<","<<results[i].time_elapsed<<","<<results[i].xA<<","<<results[i].yA<<","<<results[i].xB<<","<<results[i].yB<<","<<results[i].xleng<<","<<results[i].yleng<<","<<results[i].pathlength<<std::endl;
                    stats.close();
                }
                else
                { std::cout<<"\nUNABLE TO OPEN FILE"<<std::endl;
                    return 0;
                }
                break;
            }
            
            if((num>1000)|(loopd>1000))
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
    stats<<"3"<<","<<time_elapsed<<","<<""<<","<<""<<","<<""<<","<<""<<","<<""<<","<<""<<","<<""<<std::endl;
        stats.close();
    }
    else
    { std::cout<<"\nUNABLE TO OPEN FILE"<<std::endl;
        return 0;
    }

    
    
    
}