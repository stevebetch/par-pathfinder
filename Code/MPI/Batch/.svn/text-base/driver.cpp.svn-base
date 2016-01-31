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
//#include <omp.h>
#include <mpi.h>
//#include "mpi_fprintf.h"
#include <random>
#include "timer.c"

//#include "node.h"
#ifndef wrapSearch_H_
#define wrapSearch_H_

// printer.h code goes here
#include "wrapSearch.h"
#endif

#include "mainLoop.h"
//#include "map.h"

//#if !defined (_OPENMP)
//#  error "*** Must compile this file with OpenMP! ***"
//#endif




using namespace std;

//const int MAP_WIDTH = 20;
//const int MAP_HEIGHT = 20;

typedef std::mt19937 MyRNG;
uint32_t seed_val=37; //get the same random stream for each time we run this driver. Good for comparisons.

MyRNG rng;                   // e.g. keep one global instance (per thread)

void initialize(MyRNG rng)
{
    rng.seed(seed_val);
}


//void PackupData(headerInfo header, MPI_Comm comm, int sendRank)
//{
//    int BUFSIZE=sizeof(header);
//    char buf[BUFSIZE];
//    int pos =0;
//    int P;
//    MPI_Comm_size (MPI_COMM_WORLD, &P);
//    
//    MPI_Pack(&header.xB, 1, MPI_INT, buf, BUFSIZE, &pos,comm);
//    MPI_Pack(&header.yB, 1, MPI_INT, buf, BUFSIZE, &pos,comm);
//    MPI_Pack(&header.loopnum, 1, MPI_INT, buf, BUFSIZE, &pos,comm);
//    MPI_Pack(&header.count, 1, MPI_INT, buf, BUFSIZE, &pos,comm);
//    MPI_Pack(&header.cstr, sizeof(header.cstr), MPI_CHAR, buf, BUFSIZE, &pos,comm);
//    MPI_Send(buf,pos,MPI_PACKED,P-1,0, MPI_COMM_WORLD);
//}
//
//headerInfo Unpack(MPI_Comm comm, int rank)
//{
//    char buf[10000];
//    headerInfo header;
//    MPI_Status Stat;
//    int pos=0;
//    
//    MPI_Recv(&buf,1,MPI_PACKED,0,0, comm, & Stat);
//    MPI_Unpack(buf,10000,&pos,&header.xB,1,MPI_INT,comm);
//    MPI_Unpack(buf,10000,&pos,&header.yB,1,MPI_INT,comm);
//    MPI_Unpack(buf,10000,&pos,&header.loopnum,1,MPI_INT,comm);
//    MPI_Unpack(buf,10000,&pos,&header.count,1,MPI_INT,comm);
//    MPI_Unpack(buf,10000,&pos,&header.cstr,1,MPI_CHAR,comm);
//    
//    return header;
//}
//
//
//void PackupDataRes(resultInfo results, int rank)
//{
//    int BUFSIZE=sizeof(results);
//    char buf[BUFSIZE];
//    int pos =0;
//    
//    MPI_Pack(&results.xB, 1, MPI_INT, buf, BUFSIZE, &pos,MPI_COMM_WORLD);
//    MPI_Pack(&results.yB, 1, MPI_INT, buf, BUFSIZE, &pos,MPI_COMM_WORLD);
//    MPI_Pack(&results.xleng, 1, MPI_INT, buf, BUFSIZE, &pos,MPI_COMM_WORLD);
//    MPI_Pack(&results.yleng, 1, MPI_INT, buf, BUFSIZE, &pos,MPI_COMM_WORLD);
//    MPI_Pack(&results.success, 1, MPI_INT, buf, BUFSIZE, &pos,MPI_COMM_WORLD);
//    MPI_Pack(&results.time_elapsed, 1, MPI_LONG_DOUBLE, buf, BUFSIZE, &pos,MPI_COMM_WORLD);
//    MPI_Pack(&results.pathlength, 1, MPI_DOUBLE, buf, BUFSIZE, &pos,MPI_COMM_WORLD);
//    MPI_Send(buf,pos,MPI_PACKED,0,rank, MPI_COMM_WORLD);
//}
//
//resultInfo UnpackRes( int rank)
//{
//    char buf[10000];
//    resultInfo results;
//    MPI_Status Stat;
//    int pos=0;
//    
//    MPI_Recv(&buf,1,MPI_PACKED,0,0, MPI_COMM_WORLD, & Stat);
////    MPI_Unpack(&results.xB, 1, MPI_INT, buf, BUFSIZE, &pos,comm);
////    MPI_Unpack(&results.yB, 1, MPI_INT, buf, BUFSIZE, &pos,comm);
////    MPI_Unpack(&results.xleng, 1, MPI_INT, buf, BUFSIZE, &pos,comm);
////    MPI_Unpack(&results.yleng, 1, MPI_INT, buf, BUFSIZE, &pos,comm);
////    MPI_Unpack(&results.success, 1, MPI_INT, buf, BUFSIZE, &pos,comm);
////    MPI_Unpack(&results.time_elapsed, 1, MPI_LONG_DOUBLE, buf, BUFSIZE, &pos,comm);
////    MPI_Unpack(&results.pathlength, 1, MPI_DOUBLE, buf, BUFSIZE, &pos,comm);
//    
//    MPI_Unpack(buf,10000,&pos,&results.xB,1,MPI_INT,MPI_COMM_WORLD);
//    MPI_Unpack(buf,10000,&pos,&results.yB,1,MPI_INT,MPI_COMM_WORLD);
//    MPI_Unpack(buf,10000,&pos,&results.xleng,1,MPI_INT,MPI_COMM_WORLD);
//    MPI_Unpack(buf,10000,&pos,&results.yleng,1,MPI_INT,MPI_COMM_WORLD);
//    MPI_Unpack(buf,10000,&pos,&results.success,1,MPI_INT,MPI_COMM_WORLD);
//    MPI_Unpack(buf,10000,&pos,&results.time_elapsed,1,MPI_LONG_DOUBLE,MPI_COMM_WORLD);
//    MPI_Unpack(buf,10000,&pos,&results.pathlength,1,MPI_DOUBLE,MPI_COMM_WORLD);
//    return results;
//}

/** Smallest message to test (in words) */
#define MIN_MSGLEN 1

/** Largest message to test (in words) */
#define MAX_MSGLEN (1 << 28)

/** Minimum time (seconds) for a set of trials */
#define MIN_TIME 0.2

bool debugMain=0;

bool exists_test (const std::string& name) {
    //bool file_exists(const std::string& s) {
    std::ifstream iff(name.c_str());
    return iff.is_open();
}


int main(int argc, char* argv[])
{
    
    
    ////////////////////////////////////////////////////////////////////////////
    //MPI stuff
    
    
    /* MPI stuff */
    int rank = 0;
    int P = 0;
    
    
    /* Message buffer */
   // resultInfo* msgbuf = NULL;
   // int msglen = 0;
  //  int min_msglen = MIN_MSGLEN;
    
    /* Start MPI */
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);	/* Get process id */
    MPI_Comm_size (MPI_COMM_WORLD, &P);	/* Get number of processes */
    
    
    system("source /nethome/sboettcher3/setup-gcc-4.9.1.bash");
    //////////////////////////////////////////////////////////////////////
    
    //if(rank==0){
    stopwatch_init ();
    struct stopwatch_t* timer = stopwatch_create (); //assert (timer);'
   // }
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
        
      if (rank == 0)
      {
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
    }

    
    
    //assert(filename);
    //assert(trials);
    
    //Need to load in the various map files and randomly choose one.
    //then need to send the filename to the mainLoop function. In the parallel versions once we
    //start benchmarking, should pull the begining/end points up here so that theres an valid
    //comparison between methods.
    vector <headerInfo> header (trials);
    vector <resultInfo> result (trials);
    headerInfo headr;
    
    if(rank==0)
    {
        MyRNG moo;
        initialize(moo);
        
        // header.allMaps=allMaps;
        
        const char* cstr ;
        
        for(int q=0;q<trials;q++)
        {
            header[q].count=count;
            mapClass Map;
            
//            std::string name= header.cstr;
//            const char* cstr =name.c_str();
            
            
            if(allMaps==0)
            {
               // header[q].cstr=argv[2];
                cstr=argv[2];
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
                
                cstr = name.c_str();
                //header[q].cstr=cstr;
                
            }
            //const char* cstr2 ="maps/1000AOR_wObs.bmp";
            Map.map(cstr);
            

            
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

            header[q].xB=xB;
            header[q].yB=yB;
           // header[q].Map=Map;
        }
        
    }
    
//    else
//    {
//        headerInfo header;
//    }
    
    
    
    if(rank==0)
    {
     std::cout<<"Overall Clock started"<<std::endl;
     stopwatch_start (timer);
   }
//    if(rank==0)
//    vector <resultInfo> results (trials);
//    else
        resultInfo results;
        
    
    /* Output file */
 //   char outfile[255];
 //   FILE *fp = NULL; /* output file, only valid on rank 0 */
    
  //  sprintf (outfile, "%s-%d.dat", 'MPI_out_Rank', rank);
    
    /* Create a message buffer */
    
    
//#pragma omp parallel  shared(allMaps,argv,filenames,trials,header,count,results)
    vector <int> msgCountr (P);
    if(rank==0)
    {
//#pragma omp for schedule(static)
        int headerStandin[5];
        MPI_Comm_size (MPI_COMM_WORLD, &P);
        int count=0;
    for(int i=0;i<trials;i++)
    {
        header[i].loopnum=i;
        if(i%24==0)
        {
            result[i]=mainLoop(header[i]);
        }
        else
        {
        header[i].loopnum=i;
        
        headerStandin[0]=header[i].xB;
        headerStandin[1]=header[i].yB;
        headerStandin[2]=header[i].loopnum;
        headerStandin[3]=header[i].count;
        headerStandin[4]=1;
        int len=sizeof(int)*5;
        //const int rank_dest = rank + i;
        int rank_dest;
        
        rank_dest=(i)%P;
        
        if(rank_dest==0)
            rank_dest++;
        if(rank_dest>=P)
            rank_dest=P-1;
       // cout<<"Total Processors:"<<P<<endl;
       // cout<<"Rank dest:"<<rank_dest<<endl;
        const int msg_tag = 1000 + rank_dest; /* must match receiver's! */
        
        int* msg_send=headerStandin;
        
        MPI_Send(msg_send,len,MPI_INT,rank_dest,msg_tag,MPI_COMM_WORLD);
        
        msgCountr[rank_dest]++;
            count++;
       // PackupData(header[i],MPI_COMM_WORLD,i);
        
        //results[i]=mainLoop(header);
       // cout<<endl;
        }
    }
//        headerStandin[4]=0;
//        int* msg_send=headerStandin;
        
        
        for(int j=0;j<P;j++)
        {
            cout<<"Sent "<<j<< " "<<msgCountr[j]<<" messages"<<endl;
            int headerFin[5];
            headerFin[0]=0;
            headerFin[1]=0;
            headerFin[2]=0;
            headerFin[3]=0;
            headerFin[4]=0;
            int* mFinal=headerFin;
            MPI_Send(mFinal,sizeof(int)*5,MPI_INT,j,1000+j,MPI_COMM_WORLD);
        }
    }
    else
    {
        int hdrStndin[5];
        while(1)
        {
            int* msg_recv= hdrStndin;
            int len=sizeof(int)*5;
            int rank_source=0;
            int msg_tag=1000+rank;
            MPI_Status Stat;
            
            MPI_Recv(msg_recv,len,MPI_INT,rank_source,msg_tag,MPI_COMM_WORLD,&Stat);
            if(hdrStndin[4]==0)
                break;
            headr.xB=hdrStndin[0];
            headr.yB=hdrStndin[1];
            headr.loopnum=hdrStndin[2];
            headr.count=hdrStndin[3];
            
            cout<<endl;
            cout<<"Begin Trial "<<headr.loopnum+1<<"!"<<endl;
            cout<<"--------------------------------------------------"<<endl;
            results=mainLoop(headr);
            
            long double Res[10];
            Res[0]=results.success;
            Res[1]=results.time_elapsed;
            Res[2]=results.xA;
            Res[3]=results.yA;
            Res[4]=results.xB;
            Res[5]=results.yB;
            Res[6]=results.xleng;
            Res[7]=results.yleng;
            Res[8]=results.pathlength;
            Res[9]=results.loopnum;
            
            int rank_dest=0;
            int len2=sizeof(long double)*10;
            const int msg_tag2 = 1000 + rank_dest;
            long double* msg_send=Res;
            
            MPI_Send(msg_send,len2,MPI_LONG_DOUBLE,rank_dest,msg_tag2,MPI_COMM_WORLD);
            
            
        }
        //headr =Unpack(MPI_COMM_WORLD, rank);
        //results=mainLoop(headr);
        //PackupDataRes(results, rank);
    }
    
    if(rank==0)
    {
        cout<<"Begin collecting messages"<<endl;
        for(int i=1; i<P;i++)
        {
//            cout<<"collecting messages from "<<i<<endl;
            
            for(int k=0;k<msgCountr[i];k++ )
            {
                long double Res3[10];
                int source3=i;
                int len3=sizeof(long double)*10;
                const int msg_tag3 = 1000 ;
                long double* msg_recv3=Res3;
                 MPI_Status Stat3;
                
                MPI_Recv(msg_recv3,len3,MPI_LONG_DOUBLE,source3,msg_tag3,MPI_COMM_WORLD,&Stat3);
                
//               cout<< "Recieved message from "<<i<<endl;
                int num=int(Res3[9]);
                result[num].loopnum=int(Res3[9]);
//                cout<< "num="<<num<<endl;
                result[num].success=int(Res3[0]);
//                cout<< "success="<<int(Res3[0])<<endl;
                result[num].time_elapsed=Res3[1];
//                cout<< "time_elapsed="<<result[num].time_elapsed<<endl;
                result[num].xA=int(Res3[2]);
//                cout<< "result[num].xA="<<result[num].xA<<endl;
                result[num].yA=int(Res3[3]);
//                cout<< "result[num].yA="<<result[num].yA<<endl;
                result[num].xB=int(Res3[4]);
//                cout<< "result[num].xB="<<result[num].xB<<endl;
                result[num].yB=int(Res3[5]);
//                cout<< "num="<<i<<endl;
                result[num].xleng=int(Res3[6]);
//                cout<< "num="<<i<<endl;
                result[num].yleng=int(Res3[7]);
//                cout<< "num="<<i<<endl;
                result[num].pathlength=double(Res3[8]);
//                cout<< "Recieved message "<<k+1<<" of "<<msgCountr[i]<<" from "<<i<<endl;
//
//                long double Res[9];
//                Res[0]=results.success;
//                Res[01]=results.time_elapsed;
//                Res[02]=results.xA;
//                Res[03]=results.yA;
//                Res[04]=results.xB;
//                Res[05]=results.yB;
//                Res[06]=results.xleng;
//                Res[7]=results.yleng;
//                Res[8]=results.pathlength;
            }
        }
        
        long double time_elapsed = stopwatch_stop (timer);
        printf ("Sequential Total runtime: %Lg seconds\n",
                time_elapsed);
    
  //  int bsize=sizeof(results);
   // char buf[bsize];
//    MPI_Send(buf,pos,MPI_PACKED,P-1,0, MPI_COMM_WORLD);
    


    
    std::string outName;
    std::string outStats;
    int num=1;
    int loopd=0;
    
    for(int i=0;i<trials;i++)
    {
//        cout<<"moo "<<i+1<<"of "<<trials<<endl;
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
                
                //results[i].Map.OutputMap(outName);
//                results.Map.OutputMap(outName);
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
                
//                cout<<"moo"<<endl;
                
                if(stats.is_open())
                {
                    if(!exists)
                    {
                        cout<<"moo"<<endl;
                        stats<<"Success, Time Elapsed,Xstart,Ystart, Xend,Yend,Xlength, Ylength, PathDist, loopnum\n";
                    }
                    if(exists && i==0)
                    {stats<<endl;}
//                    cout<<"moo"<<endl;
                    stats<<result[i].success<<","<<result[i].time_elapsed<<","<<result[i].xA<<","<<result[i].yA<<","<<result[i].xB<<","<<result[i].yB<<","<<result[i].xleng<<","<<result[i].yleng<<","<<result[i].pathlength<<","<<result[i].loopnum<< std::endl;
//                    cout<<"moo"<<endl;
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
    
    
    
        cout<<"Data output. putting out final data"<<endl;
 
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
    
    printf ( "Shutting down MPI...\n");
    MPI_Finalize ();

    cout<<"Data output. shutting down"<<endl;
    return 0;
    
}
