#ifndef TFRACTAL
#define TFRACTAL

#include<complex>
#include<list>
#include"tga.h"
#include"jpge.h"

using namespace std;

typedef struct retrn{    // custom type for Konv function
  complex<double> r;  // Point in complex plain
  int it;             // number of iterations
} ret;

typedef struct{
  double x,y,zm,al,sp;
  int mx,my,ma,mz;
} zoomPoint;

const double PI_2=asin(1.0);
const double PI=2.0*asin(1.0);

class Tfractal
{
  private:
    
   int width;
   int height;
   int maxNumIt;
   zoomPoint *listZPts;
   Ttga *TGA;
   int outputFormat;
   void *libHandle;
   void *libcHandle;
   
   char equationLine[1024];
   char firstPart[1024];
   char secondPart[1024];
   char colLine[6][1024];
   char fPar[128],fPar2[128];
   char head[256];
   
   double l,dl;    // Parametres for moving window
   int count,cMax;
  
   void readColFuncs();
   void readEquation();
   
   bool conv(const complex<double> &z0, ret &rtrn);
   //int (*func)(complex<double>&, int, bool&);
   
   double x1(double x);
   double x2(double x);
   double x4(double x);
   double sinx(double x);
   double ix2(double x);
   double ix4(double x);
   double cosx(double x);
   double tanhx(double x);
   void setDl();
   
   double (Tfractal::*pFce[8])(double);
   
  public:
  Tfractal(const int w,const int h,const int maxIt);
  ~Tfractal();
  
  unsigned char* getImage(){return TGA->getData();};
  void calcFract(const double, const double, const double, const double);
  bool saveImage(const char *name);
  void changeRes(int, int);
  void reloadLib();
  void reloadLibc();
  void setMaxNumIt(int m){maxNumIt=m;}
  void initPointMove();
  bool movePoint();
  float getWorkDone();
  char* getEqnLine(){return equationLine;}
  char* getColLine(int i){return colLine[i];}
  void compileEq();
  void compileColEq();
  long getTotalSize();
  int getWorkTotal();
  
  
  list<zoomPoint> points;
  list<zoomPoint>::iterator it;
  
};


#endif // TFRACTAL
