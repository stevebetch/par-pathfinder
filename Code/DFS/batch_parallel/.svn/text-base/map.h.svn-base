#include "bitmap_image.hpp"
#include <vector>

typedef std::vector <std::vector<int> > mat;

class mapClass
{
    int numEl;
    int xleng;
    int yleng;
    int numBlocks;
    

    bitmap_image imager;
    
    
public:
    mat pntMap;
    mat open_nodes;
    mat closed_nodes;
    mat dir_map;
    void map(const char *filename);
    
    int MapPt(int x,int y){ return pntMap[x][y];};
    void MapPtChng(int x, int y, int change);
    
    int OpenPt(int x,int y){ return open_nodes[x][y];};
    void OpenPtChng(int x, int y, int change);
    
    int ClosedPt(int x,int y){ return closed_nodes[x][y];};
    void ClosedPtChng(int x, int y, int change);
    
    int dirPt(int x,int y){ return dir_map[x][y];};
    void dirPtChng(int x, int y, int change);
    
    void OutputMap(std::string filename);
    int getXleng() {return xleng;};
    int getYleng() {return yleng;};
//    
//    void addNode(int xpos, int ypos, int blk)//block if ==1
//    {
//        if(ypos==0)//new row
//        {
//            resizeMapRow();//adds one more row to the pntMap.
//        }
//        if(ypos>=yleng)//need a new col
//        {
//            resizeMapCol();
//        }
//        
//        //Time to create the new struct node.
//        
//        mapBlk *newNode= new
//        
//    }
//    mapBlk accessNeighborNode(int direction) // 1=up,2=left,3=down,4=right
//    void resizeMapCol(); //called by addNode
//    void resizeMapRow(); //called by addNode

//private:
//
//    void loadMap(bitmap_image image)
//    {
//        
//    }
};

