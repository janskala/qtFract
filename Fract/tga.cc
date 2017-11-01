#include <fstream>
#include <string>
#include "tga.h"

Ttga::Ttga(const int w,const int h):width(w),height(h){
  data = new char[3*width*height];
}

Ttga::~Ttga()
{
  delete [] data;
}

void Ttga::setPixelRGB(const int x,const int y,const char r,const char g,const char b){
  // The picture is mirrored by axe y
  *(data+(3*(height-1-y)*width+3*x) + 0)=r;
  *(data+(3*(height-1-y)*width+3*x) + 1)=g;
  *(data+(3*(height-1-y)*width+3*x) + 2)=b;
}

bool Ttga::save(const char *name){
  const char head[12]={0,0,2,0,0,0,0,0,0,0,0,0};
  const char end[26]={0,0,0,0,0,0,0,0,'T','R','U','E','V','I','S','I','O','N','-','X','F','I','L','E',46,0};
  int i;

  std::string sname(name);
  if (sname.find(".tga")== std::string::npos &&
      sname.find(".TGA")== std::string::npos) sname+=".tga";
  std::ofstream fTGA(sname.c_str(), std::ios::out | std::ios::binary);
  if (!fTGA.is_open()) return false;

  fTGA.write(head,12);
  fTGA.write((char*)&width,2);
  fTGA.write((char*)&height,2);i=24;
  fTGA.write((char*)&i,1);i=32;
  fTGA.write((char*)&i,1);

  for(i=0;i<width*height;i++){
    fTGA.write((data+i*3+2),1);
    fTGA.write((data+i*3+1),1);
    fTGA.write((data+i*3+0),1);
  }
  fTGA.write(end,26);
  fTGA.close();

  return true;
}

void Ttga::changeRes(int w, int h)
{
  width=w;
  height=h;
  delete [] data;
  data = new char[3*width*height];
}