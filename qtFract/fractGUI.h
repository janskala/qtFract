#ifndef FRACTGUI_H
#define FRACTGUI_H

#include <QMainWindow>
#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QGridLayout>
#include <QString>
#include <QSlider>
#include <QComboBox>
#include"fractal.h"
#include"params.h"

#define nZI 10   // Number of predefined zooms in the list
#define deg2rad (3.141592654/180.0)

class customZoom;
class colors;
class changeResol;
class equation;
class precision;
class angle;
class videoPoints;

class FractGUI : public QMainWindow
{
  Q_OBJECT 
   
  friend class videoPoints; 
  
  public:
    FractGUI(QWidget *parent = 0);
    ~FractGUI();
    
    int getParResX(){return par->width();};
    int getParResY(){return par->height();};
    double getZoom() const;
    void getWinAtrs(double*,double*,double*,double*) const;
    void setWinAtrs(double,double,double,double);
    Tfractal *Fract;
    
  private slots:
    void selectZoom();
    void resetZoom();
    void setZoom(double);
    void showChangeResol();
    void showEquation();
    void showPrecision();
    void showColors();
    void showControl();
    void showVideo();
    void makeVideo();
    void showAbout();
    void keepAspRat();
    void saveToFile();
    void loadFromFile();
    void saveVToFile();
    void loadVFromFile();
    void saveImage();
    void showAngle();
    
  protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
    void moveEvent(QMoveEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    bool eventFilter(QObject*, QEvent*);
    void wheelEvent(QWheelEvent*);
    void setStatus();
    void drawNewFract();
    
    customZoom* dialogSetZoom;
    colors*  dialogColors;
    changeResol* dialogChangeResol;
    equation* dialogEquation;
    precision* dialogPrecision;
    angle* dialogAngle;
    videoPoints *dialogVPoints;
    
    QAction* zoomA[nZI];
    QAction* cusZoom;
    QAction* aspRatA;
    QRect rct,rctZ;
    QLabel* status;
    //zoomDial->show();
    Tparams *par;
    double xw,yw,zw,alp;
    //char status[256];
    int menuHeight;
    int mx,my;        // Last mouse click
    const float zoomList[nZI]={1.2f,1.5f,2.0f,4.0f,8.0f,16.0f,32.0f,64.0f,128.0f,512.0f};
    int selZoom;
    double zoomMag;
    bool LMB,ALT,CTRL,SHFT;
 
};


 class equation : public QDialog
 {
     Q_OBJECT
     
 public:
     equation(QWidget *parent = 0);
     bool isChanged();
     char* getEquation();
     void setEquation(char *);
     void compileEqn(){checkEq();};

 private slots:
     void checkEq();
     void cancel();
      
 private:

     QLineEdit *textEdit;
     QLabel *textLabel;
     QPushButton *okButton;
     QPushButton *cancelButton;
     bool changed;
     
     void readEquation();
     void setEquation();
     
     char equationLine[1024];
     char firstPart[1024];
     char secondPart[1024];
 };

 
 class customZoom : public QDialog
 {
     Q_OBJECT
     
 public:
     customZoom(double, QWidget *parent = 0);
     void setZoom(double);
     double getZoom();

 private slots:

 private:

     QLineEdit *textEdit;
     QLabel *textLabel;
     QPushButton *okButton;
     
     double curValue;
 };

 class precision : public QDialog
 {
     Q_OBJECT
     
 public:
     precision(int, QWidget *parent = 0);
     void setPrec(int);
     int getPrec();

 private slots:

 private:

     QLineEdit *textEdit;
     QLabel *textLabel;
     QPushButton *okButton;
 };
 
class changeResol : public QDialog
{
     Q_OBJECT
     
 public:
     changeResol(int,int, QWidget *parent = 0);
     void setValues(int,int);
     int getWidth();
     int getHeight();
     void setWidth(int);
     void setHeight(int);

 private slots:
     void handleSelectionChanged(int);

 private:

     QLineEdit *textEdit1;
     QLineEdit *textEdit2;
     QLabel *textLabel1;
     QLabel *textLabel2;
     QPushButton *okButton;
     QComboBox *cBox;
     int w,h;
     int wl[11],hl[11];
     
     void checkResolution();
};
 
class colors : public QDialog
 {
     Q_OBJECT
     
 public:
     colors(QWidget *parent = 0);
     bool isChanged();
     char* getColorEquation(int);
     void setColorEquation(int, char*);
     void compileEqns(){checkEq();};

 private slots:
     void checkEq();
     void cancel();
      
 private:

     QLineEdit *textEdit[6];
     QLabel *textLabel;
     QLabel *textLabelCon;
     QLabel *textLabelRc;
     QLabel *textLabelGc;
     QLabel *textLabelBc;
     QLabel *textLabelDiv;
     QLabel *textLabelRd;
     QLabel *textLabelGd;
     QLabel *textLabelBd;
     QPushButton *okButton;
     QPushButton *cancelButton;
     bool changed;
     
     void readColFuncs();
     void setColFuncs();
     
     char colLine[6][1024];
     char fPar[128],fPar2[128];
     char head[256];
 };
 
class angle : public QDialog
 {
     Q_OBJECT
     
 public:
     angle(double, QWidget *parent = 0);
     void setAngle(double);
     double getAngl();

 private slots:
     void setAngl(int);

 private:

     QLineEdit *textEdit;
     QLabel *textLabel;
     QSlider *slider;
     QPushButton *okButton;
 };
 
 
 class videoPoints : public QDialog
 {
  Q_OBJECT
     
  public:
    videoPoints(FractGUI *parent = 0);
    void makeTable();

  private slots:
    void addRow();
    void showSlide();
    void okClick();
    void load();
    void save();
    void clearTable();
    void insRow();
    void delRow();
    void randomizeMoves();
    double Rnd();
    //void cancelQuit();

  private:

    FractGUI *mainWin;
    QPushButton *okButton, *addButton, *loadButton, *saveButton,*showButton,
                *delButton, *clrButton, *insButton, *canButton, *randButton;
    QTableWidget *table;
    
    list<zoomPoint> points;
    
    void acceptChanges();
    void insertRow(int);
    void reject();
 };

#endif // FRACTGUI_H