#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstdlib>
#include<omp.h>
#include"fractal.h"
#include"params.h"

using namespace std;

int main(int argc, char* argv[])
{
  int nth;
  Tparams *par;
  Tfractal *Fract;

  if (argc<2){
    cout<<"The name of the script is required!\n Program terminated.\n";
    return 1;
  }
  
  //cout<<setfill(' ')<<setw(5)<<scientific<<setprecision(6);
  cout<<"Initialization.\n";
#pragma omp parallel shared(nth)
#pragma omp master
{
  nth=omp_get_num_threads();
}
  cout<<"Number of openMP threads: "<<nth<<"\n";
  par = new Tparams();
  par->load();
  Fract = new Tfractal(par->width(),par->height(),par->prec());

  cout<<"Loading Slide Show Script...\n";
  fstream in(argv[1],fstream::in | fstream::binary);
  if (!in.is_open()){
    cout<<"Unable to open scprit file: "<<argv[1]<<"\n Program terminated.\n";
    return 2;
  }

  char* buf;
  int j;
  
  buf=Fract->getEqnLine();
  j=0;
  do in.read((char*)&buf[j],1);
  while(buf[j++]!='\0');
  
  for(int i=0;i<6;i++){
    buf=Fract->getColLine(i);
    j=0;
    do in.read((char*)&buf[j],1);
    while(buf[j++]!='\0');
  }

  cout<<"Compiling equation library...\n";
  Fract->compileEq();
  Fract->reloadLib();
  cout<<"Compiling color library...\n";
  Fract->compileColEq();
  Fract->reloadLibc();
  
  cout<<"Getting visit points...\n";
  int N;
  zoomPoint zp;
  in.read((char*)&N,sizeof(int));
  Fract->points.clear();
  cout<<"Number of points: "<<N<<endl;
  for(int i=0;i<N;i++){
    in.read((char*)&zp,sizeof(zoomPoint));
    Fract->points.push_back(zp);
  }

  in.close();
  
  long diskSize;
  cout<<"Calculations started...\n";
  if (Fract->points.size()>1){
    Fract->initPointMove();
    cout<<"A total number of images:"<< Fract->getWorkTotal()<<"\n";
    diskSize=Fract->getTotalSize();
    cout<<"A total size of images on the disk (uncompressed): "<< diskSize/(1024*1024*1024)<<"GB "
        << (diskSize%(1024*1024*1024))/(1024*1024)<<"MB\n";
    clock_t times,timea,timee,lt;
    times = clock();
    lt=0;
    while(Fract->movePoint()){
      timea=(clock()-times)/(CLOCKS_PER_SEC*nth);
      if (timea-lt>=100){
        lt=timea;
        timee=timea/60.0;
        timea=int(timea/(60.0*Fract->getWorkDone())-timee);
        cout<<"Progress: "<<setw(5)<<float(100.0*Fract->getWorkDone())
            <<"%; Elapsed time: "<<setw(2)<<timee/60
            <<"h "<<setw(2)<<timee%60
            <<"m; Remaining time: "<<setw(2)<<timea/60
            <<"h "<<setw(2)<<timea%60<<"m\n";
      }
    }
    cout<<"Done!\n";
  }else{
    cout<<"The number of points in the list is not sufficient.\n The minimum number of points is two.\n";
  }

  delete par;
  delete Fract;
  cout<<"End!\n\n";
  
  return 0;
}
