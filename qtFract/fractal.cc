#include <omp.h>
#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include "fractal.h"

extern "C" {
int (*func)(complex<double>&, int, bool&);
char (*Rc)(complex<double> &p,complex<double> &r,int it,double zm);
char (*Gc)(complex<double> &p,complex<double> &r,int it,double zm);
char (*Bc)(complex<double> &p,complex<double> &r,int it,double zm);
char (*Rd)(complex<double> &p,complex<double> &r,double zm);
char (*Gd)(complex<double> &p,complex<double> &r,double zm);
char (*Bd)(complex<double> &p,complex<double> &r,double zm);
}

Tfractal::Tfractal(const int w,const int h, const int maxIt):
                   width(w),height(h),maxNumIt(maxIt){
  TGA = new Ttga(width,height);
  outputFormat=1;
  
  listZPts = 0;
  libHandle=libcHandle=0;
  
  readColFuncs();
  readEquation();
  
  reloadLib();
  reloadLibc();
  
  initPointMove();
  
  pFce[0]=&Tfractal::x1;
  pFce[1]=&Tfractal::x2;
  pFce[2]=&Tfractal::x4;
  pFce[3]=&Tfractal::cosx;
  pFce[4]=&Tfractal::ix2;
  pFce[5]=&Tfractal::ix4;
  pFce[6]=&Tfractal::sinx;
  pFce[7]=&Tfractal::tanhx;
}

Tfractal::~Tfractal()
{
  delete TGA;
  dlclose(libHandle);
  dlclose(libcHandle);
}

void Tfractal::reloadLib()
{
  char* err;
  if (libHandle) dlclose(libHandle);
  
  ::func=0;
  
  libHandle = dlopen ("func/function.so", RTLD_LAZY);
  if (!libHandle) {
     cout<<"Function library load fails!\n";
  }
  ::func = (int (*)(complex<double>&, int, bool&))dlsym(libHandle, "func");
  err=dlerror();
  if (err!=NULL){
    cout<<err<<"\nFunction pointer extract fails!\n";
  }
}

void Tfractal::reloadLibc()
{
  char* err;
  if (libcHandle) dlclose(libcHandle);
  
  //::Rc=::Gc=::Bc=::Rd=::Gd=::Bd=0;
  
  libcHandle = dlopen ("func/colors.so", RTLD_LAZY);
  if (!libcHandle) {
     cout<<"Colors library load fails!\n";
  }
  ::Rc = (char (*)(complex<double>&,complex<double>&,int,double))
          dlsym(libcHandle, "Rc");
  err=dlerror();
  if (err!=NULL){
    cout<<err<<"\nFunction pointer extract fails!\n";
  }
  ::Gc = (char (*)(complex<double>&,complex<double>&,int,double))
          dlsym(libcHandle, "Gc");
  err=dlerror();
  if (err!=NULL){
    cout<<err<<"\nFunction pointer extract fails!\n";
  }
  ::Bc = (char (*)(complex<double>&,complex<double>&,int,double))
          dlsym(libcHandle, "Bc");
  err=dlerror();
  if (err!=NULL){
    cout<<err<<"\nFunction pointer extract fails!\n";
  }
  ::Rd = (char (*)(complex<double>&,complex<double>&,double))
          dlsym(libcHandle, "Rd");
  err=dlerror();
  if (err!=NULL){
    cout<<err<<"\nFunction pointer extract fails!\n";
  }
  ::Gd = (char (*)(complex<double>&,complex<double>&,double))
          dlsym(libcHandle, "Gd");
  err=dlerror();
  if (err!=NULL){
    cout<<err<<"\nFunction pointer extract fails!\n";
  }
  ::Bd = (char (*)(complex<double>&,complex<double>&,double))
          dlsym(libcHandle, "Bd");
  err=dlerror();
  if (err!=NULL){
    cout<<err<<"\nFunction pointer extract fails!\n";
  }
}

void Tfractal::readEquation()
{
  string line;
  int pos=0;
  ifstream eqnFile("func/lib-c");
  if (!eqnFile.is_open()) cout<<"File func/lib-c does not found!\n";
    
  for(register int i=0;i<13;i++){
    getline(eqnFile, line);
    pos+=sprintf(firstPart+pos,"%s\n",line.c_str());
  }
  
  eqnFile.get(equationLine,1024,'\n');
  eqnFile.get();

  pos=0;
  for(register int i=0;i<15;i++){
    getline(eqnFile, line);
    pos+=sprintf(secondPart+pos,"%s\n",line.c_str());
  }
  eqnFile.close();
}

void Tfractal::readColFuncs()
{
  string line;
  int pos=0;
  
  ifstream colFile("func/libc-c");
  if (!colFile.is_open()) cout<<"File func/libc-c does not found!\n";
  
  for(register int i=0;i<8;i++){
    getline(colFile, line);
    pos+=sprintf(head+pos,"%s\n",line.c_str());
  }
  
  getline(colFile, line);
  sprintf(fPar,"%s\n",line.c_str()+7);
  
  getline(colFile, line);
  pos=sprintf(colLine[0],"%s\n",line.c_str()+13);
  colLine[0][pos-3]='\0';
  
  for(register int i=1;i<3;i++){
    getline(colFile, line);
    getline(colFile, line);
    getline(colFile, line);
    pos=sprintf(colLine[i],"%s\n",line.c_str()+13);
    colLine[i][pos-3]='\0';
  }
  
  getline(colFile, line);
  getline(colFile, line);
  sprintf(fPar2,"%s\n",line.c_str()+7);
  
  getline(colFile, line);
  pos=sprintf(colLine[4],"%s\n",line.c_str()+13);
  colLine[4][pos-3]='\0';
  
  for(register int i=3;i<6;i++){
    getline(colFile, line);
    getline(colFile, line);
    getline(colFile, line);
    pos=sprintf(colLine[i],"%s\n",line.c_str()+13);
    colLine[i][pos-3]='\0';
  }
  
  colFile.close();
}

void Tfractal::compileEq()
{
  int error,i;
  ofstream fout("func/test.cc", ios_base::out|ios_base::trunc);
  fout<<firstPart<<equationLine<<"\n"<<secondPart;
  fout.close();
  
  error=system("g++ -O3 -fPIC -shared func/test.cc -o func/test.so");
  
  if (error){
    error = system("rm func/test.cc func/test.so");
    cout<<"Error occurred during compilation. "
        <<"Please check your equation.";
    return;
  }
  
  error=system("mv func/test.cc func/lib-c; mv func/test.so func/function.so");
  i=0;
  while(equationLine[i]!='\0')
    i++;
}

void Tfractal::compileColEq()
{
  int error,i;
  char fName[6][3]={"Rc","Gc","Bc","Rd","Gd","Bd"};
  char colName[3][6]={"Red","Green","Blue"};
  char conDiv[2][11]={"convergent","divergent"};
  char text[128];
  ofstream fout;

  for(i=0;i<6;i++){ // Check if all function can be compiled
    fout.open("func/test.cc", ios_base::out|ios_base::trunc);
    fout<<head;
    fout<<"char "<<fName[i]<<(i<3?fPar:fPar2)
        <<" return char("<<colLine[i]<<");\n}\n";
    fout<<"}\n";
    fout.close();
    
    error=system("g++ -O3 -fPIC -shared func/test.cc -o func/test.so");
    
    if (error){
      error = system("rm func/test.cc func/test.so");
      cout<<"Error occurred during compilation. ";
      sprintf(text,"Please check your %s %s equation.",
            conDiv[i/3],colName[i%3]);
      cout<<text;
      return;
    }
  }
  
  for(int j=0;j<6;j++){
    i=0;
    while(colLine[j][i]!='\0')
      i++;
  }
  
  fout.open("func/test.cc", ios_base::out|ios_base::trunc);
  fout<<head;
  for(i=0;i<6;i++)
    fout<<"char "<<fName[i]<<(i<3?fPar:fPar2)
        <<" return char("<<colLine[i]<<");\n}\n";
  fout<<"}\n";
  fout.close();
  
  error=system("g++ -O3 -fPIC -shared func/test.cc -o func/test.so");
  error=system("mv func/test.cc func/libc-c; mv func/test.so func/colors.so");

}

bool Tfractal::conv(const complex<double> &z0, ret &rtrn)
{
  complex<double> z(z0);
  bool cRes;
  
  rtrn.it=::func(z,maxNumIt,cRes);
  if (!cRes){
    rtrn.r= z;
    return false;
  }
  
  rtrn.r= z;
  return true;
}

void Tfractal::calcFract(const double xw, const double yw, 
                         const double zw, const double alp)
{
  double X1,X2,Y1,Y2,dx,dy,Xs,Ys,Xc,Yc;
  int x,y;
  complex<double> p;
  retrn r;
  
  X1=xw-0.5*zw;           // Frame of zoom window
  X2=xw+0.5*zw;
  Y2=yw+0.5*zw*height/double(width);
  Y1=Y2-double(height)/double(width)*(X2-X1);
  Xs=(X2-X1)*sin(-alp)/double(width);
  Ys=(Y2-Y1)*sin(-alp)/double(height);
  Xc=(X2-X1)*cos(-alp)/double(width);
  Yc=(Y2-Y1)*cos(-alp)/double(height);

  #pragma omp parallel shared(Xs,Ys,Xc,Yc) private(x,y,p,r,dx,dy)
  #pragma omp for
  for(y=0;y<height;y++){
    for(x=0;x<width;x++){
      dx=Xc*(x-0.5*width)-Ys*(y-0.5*height);
      dy=Xs*(x-0.5*width)+Yc*(y-0.5*height);
      p=complex<double>(xw+dx,yw+dy);
      
      if (conv(p, r)){   // series convergate for point p
        TGA->setPixelRGB(x,y,
                         ::Rc(p,r.r,r.it,zw),
                         ::Gc(p,r.r,r.it,zw),
                         ::Bc(p,r.r,r.it,zw) );
      }else{        // series divergate for point p
        TGA->setPixelRGB(x,y,
                         ::Rd(p,r.r,zw),
                         ::Gd(p,r.r,zw),
                         ::Bd(p,r.r,zw) );
      }
    }
  }
}

bool Tfractal::saveImage(const char *name)
{
  if (outputFormat==1){
    std::string sname(name);
    if (sname.find(".jpg")== std::string::npos &&
        sname.find(".JPG")== std::string::npos &&
        sname.find(".jpeg")== std::string::npos &&
        sname.find(".JPEG")== std::string::npos) sname+=".jpg";
    jpge::params prms;
    prms.m_quality=85;
    prms.m_two_pass_flag=true;
    return jpge::compress_image_to_jpeg_file(sname.c_str(), width, height, 3, 
                      TGA->getData(), prms);
  }
  
  return TGA->save(name);
}

void Tfractal::changeRes(int w, int h)
{
  width=w;
  height=h;
  TGA->changeRes(w,h);
}

void Tfractal::initPointMove()
{
  int i,N;

  count=0; 
  cMax=0;
  N=points.size();
  if (N<2) return;
  it=points.begin();
  for(i=0;i<N-1;i++){
    setDl();
    while(l<1.0){
      l+=dl;
      cMax++;
    }
    it++;
  }
  it=points.begin();
  setDl();
}

float Tfractal::getWorkDone()
{
  return (float)count/float(cMax);
}

int Tfractal::getWorkTotal()
{
  return cMax;
}

long Tfractal::getTotalSize()
{
  return long(cMax)*width*height*3;
}

bool Tfractal::movePoint()
{
  double theta,x,y,al,zm;
  char name[16];

  it++;   // Store values of the next point
  x=it->x;
  y=it->y;
  al=it->al;
  zm=it->zm;
  it--;
  theta=(this->*pFce[it->mx])(l);  // Move x-point
  x=theta*x + (1.0-theta)*it->x;
  theta=(this->*pFce[it->my])(l);  // Move y-point
  y=theta*y + (1.0-theta)*it->y;
  theta=(this->*pFce[it->ma])(l);  // Rotate angle
  al=theta*al + (1.0-theta)*it->al;
  // make a zoom...
  theta=(this->*pFce[it->mz])(l);
  zm=exp(theta*log(zm) + (1.0-theta)*log(it->zm));
  
  calcFract(x, y, zm, al);
  
  sprintf(name,"f%05d",count);
  count++;
  saveImage(name);
  
  l+=dl;
  if (l>=1.0){
    it++;
    it++;
    if (it==points.end()) return false;
    it--;
    setDl();
  }
  
  return true;
}

void Tfractal::setDl()
{
  double siz[4],max;
  
  it++;
  siz[0]=it->x;
  siz[1]=it->y;
  siz[2]=it->al;
  siz[3]=it->zm;
  it--;
  max=siz[2];
  siz[0]=2.0*fabs(siz[0]-it->x)/(it->zm+siz[3]);
  siz[1]=2.0*fabs(siz[1]-it->y)/(it->zm+siz[3]);
  siz[2]=fabs((siz[2]-it->al));
  if (siz[2]>PI){
    if (it->al>max){
      it++;
      it->al+=2.0*PI;
      siz[2]=it->al;
      it--;
    }else it->al+=2.0*PI;
    siz[2]=fabs((siz[2]-it->al));
  }
  siz[3]=2.0*fabs(log(siz[3])-log(it->zm));
  
  max=(siz[0]>siz[1]?siz[0]:siz[1]);
  max=(max>siz[2]?max:siz[2]);
  max=(max>siz[3]?max:siz[3]);
  dl=0.8*(0.001+it->sp*0.1)/max;
  l=0.0;
}

double Tfractal::x1(double x)
{
  return x;
}

double Tfractal::x2(double x)
{
  return x*x;
}

double Tfractal::x4(double x)
{
  return x*x*x*x;
}

double Tfractal::sinx(double x)
{
  return sin(x*PI_2);
}

double Tfractal::ix2(double x)
{
  return 1.0-(1.0-x)*(1.0-x);
}

double Tfractal::ix4(double x)
{
  double a=(1.0-x);
  return 1.0-a*a*a*a;
}

double Tfractal::cosx(double x)
{
  return 1.0-cos(x*PI_2);
}

double Tfractal::tanhx(double x)
{
  const double rs=0.5/(tanh(2.0));
  return (0.5+rs*tanh(-2.0+4.0*x));
}
