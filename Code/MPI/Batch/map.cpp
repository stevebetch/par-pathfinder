#include "map.h"

void mapClass::map(const char *filename)
{
    numEl=0;
    xleng=0;
    yleng=0;
    numBlocks=0;
     bitmap_image image(filename);
    imager=image;
    if (!imager)
    {
        printf("Error - Failed to open: input.bmp\n");
        return ;
    }
  //  std::cout<<"Image opened. Begin conversion to gray scale"<<std::endl;
    imager.convert_to_grayscale();//just in case. Gunna set a threashold.
    xleng= imager.width();
    yleng= imager.height();
//    std::cout<<"Image length, height:"<<xleng<<","<<yleng<<std::endl;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    
  //  std::cout<<"Begin resizing the maricies"<<std::endl;
    std::vector<std::vector<int>> temp(xleng,std::vector<int>(yleng));
    pntMap=temp;
    open_nodes=temp;
    closed_nodes=temp;
    dir_map=temp;
    
    
    
   // pntMap.resize(xleng);
    //open_nodes.resize(xleng);
//    closed_nodes.resize(xleng);
//    dir_map.resize(xleng);
  //  std::cout<<"Begin resizing the maricies"<<std::endl;
    
//    for(int i=0;i<xleng;i++)
//    {
//       // std::cout<<i<<std::endl;
//        
//     //   pntMap[i].resize(yleng);
//       // std::cout<<"pntMap complete"<<std::endl;
////        open_nodes[i].resize(yleng);
//       // std::cout<<"open_nodes complete"<<std::endl;
//        closed_nodes[i].resize(yleng);
//      //  std::cout<<"closed_nodes complete"<<std::endl;
//        dir_map[i].resize(yleng);
//       // std::cout<<"dir_map complete"<<std::endl;
//        
//    }
//
//    for(auto &it : open_nodes)
//    {
//        it.resize(yleng);
//    }
//    
//    for(auto &it : closed_nodes)
//    {
//        it.resize(yleng);
//    }
//    
//    for(auto &it : dir_map)
//    {
//        it.resize(yleng);
//    }
    
  //  std::cout<<"Begin loading the maricies"<<std::endl;
    
    for(int i=0;i<xleng;i++)
    {
        
        for(int j=0;j<yleng;j++)
        {
            closed_nodes[i][j]=0;
            open_nodes[i][j]=0;
            dir_map[i][j]=0;
            
            imager.get_pixel(i,j,red,green,blue); //red,green and blue should all be the same value
            if(red>128)//White
            {
                pntMap[i][j]=0;
            }
            else //black
            {
                pntMap[i][j]=9;
                numBlocks++;
            }
            
        }
        
    }
    
    return;
}

void mapClass::MapPtChng(int x, int y, int change)
{
    pntMap[x][y]=change;
    return;
    
}

void mapClass::OutputMap(std::string filename)
{

    unsigned char Nored=0;
    unsigned char Nogreen=0;
    unsigned char Noblue=0;
    unsigned char Fullred=255;
    unsigned char Fullgreen=255;
    unsigned char Fullblue=255;
    
    bitmap_image image2=imager;
    
    
    for(int i=0; i<xleng;i++)
    {
        
        for(int j=0;j<yleng;j++)
        {
            if(pntMap[i][j]==2) //start point
            {
                image2.set_pixel(i,j,Nored,Fullgreen,Noblue);
            }
            if(pntMap[i][j]==3) //route
            {
                image2.set_pixel(i,j,Nored,Nogreen,Fullblue);
            }
            if(pntMap[i][j]==4) //End
            {
                image2.set_pixel(i,j,Fullred,Nogreen,Noblue);
            }
        }
    }
    
    image2.save_image(filename);
    
}

void mapClass::OpenPtChng(int x, int y, int change)
{
    open_nodes[x][y]=change;
//     std::cout<<"x,y,xhange:"<<x<<" "<<y<<" "<<open_nodes[x][y]<<std::endl;
}

void mapClass::ClosedPtChng(int x, int y, int change)
{closed_nodes[x][y]=change;
    return;
}

void mapClass::dirPtChng(int x, int y, int change)
{dir_map[x][y]=change;
    return;
}






