#include <iomanip>
#include "params.h"
#include <iostream>

Tparams::Tparams()
{
}

Tparams::~Tparams()
{
//   delete [] zList;
}

void Tparams::load(const char* dir)
{
  string path(dir);
  path+="params.ini";
	
  ifstream parFile(path.c_str());

  // Window parametres
  parFile>>_wx>>_wy>>_ww>>_wh;
  newLine(parFile);
  
  // keep aspect ratio fixed?
  parFile>>_aspRat;
  newLine(parFile);
  
  // Picture resolution
  parFile>>_width>>_height;
  newLine(parFile);
  
  // number of iterations for determination of convergence
  parFile>>_prec;
  newLine(parFile);

//   // number of skiped initial frames
//   parFile>>_nSkipFrames;
//   newLine(parFile);
//   
//   // number of zooming points
//   parFile>>_nZmPts;
//   newLine(parFile);
//   
//   zList = new zmLst[_nZmPts];
//   
//   // load zooming points
//   for(register int i=0;i<_nZmPts;i++){
//     parFile>>zList[i].x>>zList[i].y>>zList[i].treshold>>zList[i].moveSpeed>>zList[i].zoomSpeed;
//     newLine(parFile);
//   }

  parFile.close();
  
  return;
}

void Tparams::save(const char* dir)
{
  string path(dir);
  path+="params.ini";
  
  ofstream parFile(path.c_str());
  
  // Window parametres
  parFile<<_wx<<" "<<_wy<<" "<<_ww<<" "<<_wh<<"\t\t\t\t// window position and size\n";
  
  // keep aspect ratio fixed?
  parFile<<_aspRat<<"\t\t\t\t// keep aspect ratio fixed?\n";
  
  // Picture resolution
  parFile<<_width<<" "<<_height<<"\t\t\t\t// resolution\n";
  
  // number of iterations for determination of convergence
  parFile<<_prec<<"\t\t\t\t// number of iterations for determination of convergence\n";
  
//   // number of skiped initial frames
//   parFile<<_nSkipFrames<<"\t\t\t\t// number of skiped initial frames\n";
//   
//   // number of zooming points
//   parFile<<_nZmPts<<"\t\t\t\t// number of zooming points\n";
//   
//   // save zooming points
//   for(register int i=0;i<_nZmPts;i++){
//     parFile<<zList[i].x<<" "<<zList[i].y<<" "
//            <<zList[i].treshold<<" "<<zList[i].moveSpeed<<" "
//            <<zList[i].zoomSpeed<<'\n';
//   }
  
  parFile.close();
}

void Tparams::setWinPars(int x, int y, int w, int h)
{
  _wx=x;
  _wy=y;
  _ww=w;
  _wh=h;
}

void Tparams::setWinPos(int x, int y)
{
  _wx=x;
  _wy=y;
}

void Tparams::setWinSiz(int w, int h)
{
  _ww=w;
  _wh=h;
}

void newLine(ifstream& file)
{
  char line[256];

  file.get(line,256,'\n');
  file.get();
  return;
}
