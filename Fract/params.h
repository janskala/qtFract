#ifndef TPARAMS
#define TPARAMS

#include <string>
#include <fstream>
using namespace std;

class Tparams
{
  private:
//     typedef struct {    // structure for zooming
//       double x,y;       // coordinates of new point
//       double treshold;      // treshold to go to new zoom point
//       double zoomSpeed;     // when the new point is used
//       double moveSpeed;     // Speed of focusing to new point
//     } zmLst;            // New type zmLst
    
    int _wx;             // window x position
    int _wy;             // window y position
    int _ww;             // window width
    int _wh;             // window height
    
    bool _aspRat;        // keep aspect ratio fixed?
    
    int _width;          // width of picture
    int _height;         // height of picture
    
    int _prec;           // number of iterations for determination of convergence
    
//     int _nSkipFrames;    // number of skiped initial frames
//     
//     int _nZmPts;         // number of zooming points
//     
//     zmLst *zList;        // List of zooming points
    
  public:
  Tparams();
  ~Tparams();
  
  void load(const char* dir="./");
  void save(const char* dir="./");
  
  int wx(){return _wx;}
  int wy(){return _wy;}
  int ww(){return _ww;}
  int wh(){return _wh;}
  int width(){return _width;}
  int height(){return _height;}
  int prec(){return _prec;}
//   int nSkipFrames(){return _nSkipFrames;}
//   int nZmPts(){return _nZmPts;}
  bool aspectRat(){return _aspRat;}
/*  
  double zmX(int i){return zList[i].x;}
  double zmY(int i){return zList[i].y;}
  double zmT(int i){return zList[i].treshold;}
  double zmZS(int i){return zList[i].zoomSpeed;}
  double zmMS(int i){return zList[i].moveSpeed;}*/
  
//   void setMzX(int i, double x){zList[i].x=x;}
//   void setMzY(int i, double y){zList[i].y=y;}
  void setWidth(int w){_width=w;}
  void setHeight(int h){_height=h;}
  void setWinPars(int, int, int, int);
  void setWinSiz(int, int);
  void setWinPos(int, int);
  void setAspectRat(bool v){_aspRat=v;}
  void setPrec(int pr){_prec=pr;}
  
};


void newLine(ifstream& file);

#endif // TPARAMS
