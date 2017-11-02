#include "fractGUI.h"
#include <QMenu>
#include <QMenuBar>
#include <QMouseEvent>
#include <QPainter>
#include <QImage>
#include <QStatusBar>
#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <cstdlib>
#include <iostream>
#include <string>
#include <QFileDialog>
#include <QTime>
#include <ctime>

FractGUI::FractGUI(QWidget *parent)
    : QMainWindow(parent)
{
  QAction *quitA = new QAction("&Quit", this);
  QAction *saveA = new QAction("&Save ...", this);
  QAction *loadA = new QAction("&Load ...", this);
  QAction *saveImgA = new QAction("Save &image as ...", this);

  QMenu *file;
  file = menuBar()->addMenu("&File");
  file->addAction(saveA);
  connect(saveA, SIGNAL(triggered()), this, SLOT(saveToFile()));
  
  file->addAction(loadA);
  connect(loadA, SIGNAL(triggered()), this, SLOT(loadFromFile()));
  
  file->addAction(saveImgA);
  connect(saveImgA, SIGNAL(triggered()), this, SLOT(saveImage()));
  
  file->addAction(quitA);
  connect(quitA, SIGNAL(triggered()), qApp, SLOT(quit()));
  
  char text[16];
  QMenu *zoomM;
  QAction* resetA;
  zoomM = menuBar()->addMenu("&Zoom");
  
  resetA= new QAction("&Reset", this);
  zoomM->addAction(resetA);
  connect(resetA, SIGNAL(triggered()), this, SLOT(resetZoom()));
  
  for(register int i=0;i<nZI;i++){
    sprintf(text,"%2.1fX",zoomList[i]);
    zoomA[i]= new QAction(text, this);
    zoomA[i]->setCheckable(true);
    zoomA[i]->setChecked(false);
    zoomM->addAction(zoomA[i]);
    connect(zoomA[i], SIGNAL(triggered()), this, SLOT(selectZoom()));
  }
  selZoom=3;
  zoomA[selZoom]->setCheckable(true);
  zoomA[selZoom]->setChecked(true);
  zoomMag=zoomList[selZoom];
  
  cusZoom= new QAction("&Custom zoom ...", this);
  zoomM->addAction(cusZoom);
  cusZoom->setCheckable(true);
  cusZoom->setChecked(false);
  connect(cusZoom, SIGNAL(triggered()), this, SLOT(selectZoom()));
  
  QMenu *setngsM;
  setngsM = menuBar()->addMenu("&Settings");
  aspRatA = new QAction("&Keep aspect ratio", this);
  connect(aspRatA, SIGNAL(triggered()), this, SLOT(keepAspRat()));
  aspRatA->setCheckable(true);
  setngsM->addAction(aspRatA);

  QAction* precA = new QAction("Change &precision ...", this);
  setngsM->addAction(precA);
  connect(precA, SIGNAL(triggered()), this, SLOT(showPrecision()));
  QAction* anglA = new QAction("Rotation &angle ...", this);
  setngsM->addAction(anglA);
  connect(anglA, SIGNAL(triggered()), this, SLOT(showAngle()));
  QAction* resolA = new QAction("Change &resolution ...", this);
  setngsM->addAction(resolA);
  connect(resolA, SIGNAL(triggered()), this, SLOT(showChangeResol()));
  QAction* eqnA = new QAction("Change &equation ...", this);
  setngsM->addAction(eqnA);
  connect(eqnA, SIGNAL(triggered()), this, SLOT(showEquation()));
  QAction* colA = new QAction("Change &colors ...", this);
  setngsM->addAction(colA);
  connect(colA, SIGNAL(triggered()), this, SLOT(showColors()));
  
  QMenu *videoM;
  videoM = menuBar()->addMenu("&Video");
  QAction *saveVA = new QAction("&Save script ...", this);
  QAction *loadVA = new QAction("&Load script ...", this);
  QAction *makeScriptA = new QAction("&Make script ...", this);
  QAction *makeVideoA = new QAction("&Make slides ...", this);
  
  videoM->addAction(saveVA);
  connect(saveVA, SIGNAL(triggered()), this, SLOT(saveVToFile()));
  
  videoM->addAction(loadVA);
  connect(loadVA, SIGNAL(triggered()), this, SLOT(loadVFromFile()));
  
  videoM->addAction(makeScriptA);
  connect(makeScriptA, SIGNAL(triggered()), this, SLOT(showVideo()));
  
  videoM->addAction(makeVideoA);
  connect(makeVideoA, SIGNAL(triggered()), this, SLOT(makeVideo()));
  
  QMenu *aboutM;
  aboutM = menuBar()->addMenu("&Help");
  QAction *controlA = new QAction("&Control", this);
  aboutM->addAction(controlA);
  connect(controlA, SIGNAL(triggered()), this, SLOT(showControl()));
  QAction *aboutA = new QAction("&About", this);
  aboutM->addAction(aboutA);
  connect(aboutA, SIGNAL(triggered()), this, SLOT(showAbout()));
  
  
  menuHeight=file->geometry().height();
  
  par = new Tparams();
  par->load();

  aspRatA->setChecked(par->aspectRat());
  move(par->wx(), par->wy());
  resize(par->ww(),par->wh());
  
  Fract = new Tfractal(par->width(),par->height(),par->prec());
  
  qApp->installEventFilter(this);
  
  LMB=ALT=CTRL=SHFT=false;
  mx=my=0;  // last mouse click
  
  status = new QLabel(this);
  statusBar()->addPermanentWidget(status,1);
  setStatus();
  
  dialogSetZoom = new customZoom(zoomMag,this);
  dialogPrecision = new precision(par->prec(),this);
  dialogChangeResol = new changeResol(par->width(),par->height(),this);
  dialogEquation = new equation(this);
  dialogColors = new colors(this);
  dialogAngle = new angle(0.0,this);
  dialogVPoints = new videoPoints(this);

  resetZoom();
  srand(time(NULL));
}

FractGUI::~FractGUI()
{
  par->setAspectRat(aspRatA->isChecked());
  par->save();
  
  delete par;
  delete Fract;
  
  delete dialogSetZoom;
  delete dialogPrecision;
  delete dialogChangeResol;
  delete dialogEquation;
  delete dialogColors;
  delete dialogAngle;
}

void FractGUI::saveToFile()
{
  QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save Fractal"), "",
         tr("Fractal (*.frc);;All Files (*)"));
  
  if (fileName.isEmpty()) return;
  else{
    if (!fileName.contains(".frc")) fileName+=".frc";
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    out.writeRawData((char*)&xw,sizeof(double));
    out.writeRawData((char*)&yw,sizeof(double));
    out.writeRawData((char*)&zw,sizeof(double));
    out.writeRawData((char*)&alp,sizeof(double));
    
    char* buf;
    int j=0;
    buf=dialogEquation->getEquation();
    do out.writeRawData((char*)&buf[j],1);
    while(buf[j++]!='\0');
    
    for(int i=0;i<6;i++){
      buf=dialogColors->getColorEquation(i);
      j=0;
      do out.writeRawData((char*)&buf[j],1);
      while(buf[j++]!='\0');
    }
    
    file.close();
  }
}

void FractGUI::loadFromFile()
{
  QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Fractal"), "",
         tr("Fractal (*.frc);;All Files (*)"));
   
  if (fileName.isEmpty()) return;
  else{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_5);
    in.readRawData((char*)&xw,sizeof(double));
    in.readRawData((char*)&yw,sizeof(double));
    in.readRawData((char*)&zw,sizeof(double));
    in.readRawData((char*)&alp,sizeof(double));
    
    char buf[1024];
    int j;
    
    j=0;
    do in.readRawData((char*)&buf[j],1);
    while(buf[j++]!='\0');
    dialogEquation->setEquation(buf);
    
    for(int i=0;i<6;i++){
      j=0;
      do in.readRawData((char*)&buf[j],1);
      while(buf[j++]!='\0');
      dialogColors->setColorEquation(i,buf);
    }
    
    file.close();
    
    dialogEquation->compileEqn();
    Fract->reloadLib();
    dialogColors->compileEqns();
    Fract->reloadLibc();
    dialogAngle->setAngle(alp);
    
    setStatus();
    drawNewFract();
  }

}

void FractGUI::saveVToFile()
{
  QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save Slide Show Script"), "",
         tr("Slide show script (*.fss);;All Files (*)"));
  
  if (fileName.isEmpty()) return;
  else{
    if (!fileName.contains(".fss")) fileName+=".fss";
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    
    char* buf;
    int j=0;
    buf=dialogEquation->getEquation();
    do out.writeRawData((char*)&buf[j],1);
    while(buf[j++]!='\0');
    
    for(int i=0;i<6;i++){
      buf=dialogColors->getColorEquation(i);
      j=0;
      do out.writeRawData((char*)&buf[j],1);
      while(buf[j++]!='\0');
    }
    
    int N=Fract->points.size();
    list<zoomPoint>::iterator it=Fract->points.begin();
    out.writeRawData((char*)&N,sizeof(int));
    for(int i=0;i<N;i++){
      out.writeRawData((char*) &(*it),sizeof(zoomPoint));
      it++;
    }
    
    file.close();
  }
}

void FractGUI::loadVFromFile()
{
  QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Slide Show Script"), "",
         tr("Slide show script (*.fss);;All Files (*)"));
   
  if (fileName.isEmpty()) return;
  else{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_5);

    char buf[1024];
    int j;
    
    j=0;
    do in.readRawData((char*)&buf[j],1);
    while(buf[j++]!='\0');
    dialogEquation->setEquation(buf);
    
    for(int i=0;i<6;i++){
      j=0;
      do in.readRawData((char*)&buf[j],1);
      while(buf[j++]!='\0');
      dialogColors->setColorEquation(i,buf);
    }
    
    int N;
    zoomPoint zp;
    in.readRawData((char*)&N,sizeof(int));
    Fract->points.clear();
    for(int i=0;i<N;i++){
      in.readRawData((char*)&zp,sizeof(zoomPoint));
      Fract->points.push_back(zp);
    }
    
    file.close();
    
    dialogVPoints->makeTable();
    dialogEquation->compileEqn();
    Fract->reloadLib();
    dialogColors->compileEqns();
    Fract->reloadLibc();
    
    setStatus();
    drawNewFract();
  }

}

void FractGUI::saveImage()
{
  QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save Fractal Image"), "",
         tr("Image (*.tga);;All Files (*)"));
  
  if (fileName.isEmpty()) return;
  else{
    //if (!fileName.contains(".tga")) fileName+=".tga";
    if (!Fract->saveImage(fileName.toLocal8Bit())){
        qDebug()<<"Saving image fail.\n";
        qApp->exit();
    }
  }
}

void FractGUI::resetZoom()
{
  xw=0.0;
  yw=0.0;
  zw=10.0;
  alp=0.0;
  dialogAngle->setAngle(alp);
  drawNewFract();
}

void FractGUI::selectZoom()
{
  int newSel=-1;
  
  if (cusZoom->isChecked()){  // Custom zoom magnitude is selected
    zoomA[selZoom]->setChecked(false);
    dialogSetZoom->setZoom(zoomMag);
    dialogSetZoom->exec();
    zoomMag=dialogSetZoom->getZoom();
    setStatus();
    selZoom=-1;
  }else{
    for(register int i=0;i<nZI;i++)   // Check what is selected
      if (zoomA[i]->isChecked() && i!=selZoom){
        newSel=i;
        break;
      }
    if (newSel==-1){                   // Nothnig is selected
      if (selZoom==-1){
        cusZoom->setChecked(true);
        dialogSetZoom->exec();
        zoomMag=dialogSetZoom->getZoom();
        setStatus();
      }else zoomA[selZoom]->setChecked(true);// Select last zoom 
    }else{
      if (selZoom!=newSel)
        zoomA[selZoom]->setChecked(false);
      zoomMag=zoomList[newSel];
      selZoom=newSel;
      setStatus();
    }
  }
  repaint();
}

 void FractGUI::setZoom(double newZoom)
 {
   zoomMag=newZoom;
 }

void FractGUI::paintEvent(QPaintEvent *e)
{
  QPainter painter(this);
  
  QRect rctI(0, menuHeight, rct.width(), rct.height());
  
  QImage img(Fract->getImage(),par->width(), par->height(),
             3*par->width(),QImage::Format_RGB888);
  
  painter.drawImage(rctI, img);
  
  if (LMB && !CTRL){
    QPen pen(Qt::white, 1, Qt::DotLine);  
    painter.setPen(pen);
    painter.drawRect(rctZ);
  }
}

void FractGUI::mouseReleaseEvent(QMouseEvent* e)
{
  int x,y;
  double X,Y,al;

  if (e->button() == Qt::LeftButton || 
      e->button() == Qt::MiddleButton){
    LMB=false;
    if (!CTRL){
      if (rctZ.width()<0){
        rctZ.setWidth(-rctZ.width());
        rctZ.setHeight(-rctZ.height());
        rctZ.setX(rctZ.x()-rctZ.width());
        rctZ.setY(rctZ.y()-rctZ.height());
      }
      rctZ.setWidth(e->pos().x()-rctZ.x());
      rctZ.setHeight(rctZ.width()*
       (rct.height())/double(rct.width()));
      x=rctZ.x()+0.5*rctZ.width();
      y=rctZ.y()+0.5*rctZ.height()-menuHeight;
      X=zw*(x/double(rct.width())-0.5);
      Y=zw*(0.5-y/double(rct.height()))*
           (par->height()/double(par->width()));
      al=-alp*deg2rad;
      xw+=(X*cos(al)-Y*sin(al));
      yw+=(X*sin(al)+Y*cos(al));
      if (rctZ.width()<=1) zw/=zoomMag;
      else zw*=rctZ.width()/double(rct.width());
      setStatus();
      drawNewFract();
    }
  }
}

void FractGUI::mousePressEvent(QMouseEvent* e)
{
  double X,Y,al;
  int x = e->pos().x();
  int y = e->pos().y()-menuHeight;
       
  if ((e->button() == Qt::LeftButton || 
       e->button() == Qt::MiddleButton) && !CTRL){
    LMB=true;
    rctZ.setX(e->pos().x());
    rctZ.setY(e->pos().y());
    rctZ.setWidth(0);
    rctZ.setHeight(0);
  }
  if (!LMB){
  
    X=zw*(x/double(rct.width())-0.5);
    Y=zw*(0.5-y/double(rct.height()))*
          (par->height()/double(par->width()));
    al=-alp*deg2rad;
    xw+=(X*cos(al)-Y*sin(al));
    yw+=(X*sin(al)+Y*cos(al));
    if((e->button() == Qt::LeftButton && CTRL) || // Zoom when ctrl+LMB
       (e->button() == Qt::MiddleButton)){      // or MMB
      zw/=zoomMag;
    }
    if(e->button() == Qt::RightButton){
      zw*=zoomMag;
    }
    
    setStatus();
    drawNewFract();
  }
}

void FractGUI::wheelEvent(QWheelEvent* e)
{
  int x = e->pos().x();
  int y = e->pos().y()-menuHeight;
  
  if (e->delta()==0) return;
  
  xw+=zw*(x/double(rct.width())-0.5);
  yw-=zw*(y/double(rct.height())-0.5)
          *(par->height()/double(par->width()));
  if(e->delta() > 0){
    zw/=zoomMag;
  }
  if(e->delta() < 0){
    zw*=zoomMag;
  }
  
  setStatus();
  drawNewFract();
}

void FractGUI::keyPressEvent(QKeyEvent * e)
{
  double dy,dl,al;
  bool newPos=false;
  
  if (e->key() == Qt::Key_Escape)  qApp->quit();
  
  if (e->key() == Qt::Key_Control) CTRL=true;
  if (e->key() == Qt::Key_Shift)   SHFT=true;
  if (e->key() == Qt::Key_Alt)     ALT= true;
  
  if (e->key() == Qt::Key_R && ALT) showChangeResol();
  
  if (e->key() == Qt::Key_E && ALT) showEquation();
  
  if (e->key() == Qt::Key_C && ALT) showColors();
  
  if (e->key() == Qt::Key_W && ALT) showPrecision();
  
  if (e->key() == Qt::Key_A && ALT) showAngle();
  
  if (e->key() == Qt::Key_F5) resetZoom();
  
  if (e->key() == Qt::Key_S && CTRL) saveToFile();
  
  if (e->key() == Qt::Key_L && CTRL) loadFromFile();
  
  if (e->key() == Qt::Key_I && CTRL) saveImage();
  
  dl=zw*(0.1+(SHFT?0.15:0.0)+(ALT?0.25:0.0)+(CTRL?0.5:0.0));
  dy=par->height()/double(par->width());  
  if (e->key() == Qt::Key_Left){
    newPos=true;
    al=(180.0-alp)*deg2rad;
    xw+=dl*cos(al);
    yw+=dl*sin(al);
  }
  if (e->key() == Qt::Key_Right){
    newPos=true;
    al=(0.0-alp)*deg2rad;
    xw+=dl*cos(al);
    yw+=dl*sin(al);
  }
  if (e->key() == Qt::Key_Down){
    newPos=true;
    al=(270.0-alp)*deg2rad;
    xw+=dy*dl*cos(al);
    yw+=dy*dl*sin(al);
  }
    if (e->key() == Qt::Key_Up){
    newPos=true;
    al=(90.0-alp)*deg2rad;
    xw+=dy*dl*cos(al);
    yw+=dy*dl*sin(al);
  }
  if (newPos){
    drawNewFract();
  }
}

void FractGUI::keyReleaseEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Control) CTRL=false;
  if (e->key() == Qt::Key_Shift)   SHFT=false;
  if (e->key() == Qt::Key_Alt)     ALT= false;
}

bool FractGUI::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::MouseMove)
  {
    if (LMB && !CTRL){
      QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
      rctZ.setY(mouseEvent->pos().y());
      if (SHFT){
        int w=rctZ.width();
        rctZ.setX(mouseEvent->pos().x()-rctZ.width()); // move when shift is pressed
        rctZ.setWidth(w);
      }
      else rctZ.setWidth(mouseEvent->pos().x()-rctZ.x());
      
      
      rctZ.setHeight(rctZ.width()*
       (rct.height())/double(rct.width()));
      repaint();
    }
  }
  return false;
}

void FractGUI::resizeEvent(QResizeEvent* e)
{
  rct = this->geometry();
  par->setWinSiz(width(),height());
  if (aspRatA->isChecked()) 
    rct.setHeight(rct.width()*par->height()/double(par->width()));
  else rct.setHeight(rct.height()-2*menuHeight);
}

void FractGUI::keepAspRat()
{
  rct = this->geometry();
  if (aspRatA->isChecked()) 
    rct.setHeight(rct.width()*par->height()/double(par->width()));
  else rct.setHeight(rct.height()-2*menuHeight);
  
  repaint();
}

void FractGUI::moveEvent(QMoveEvent* e)
{
  par->setWinPos(x(),y());
}

void FractGUI::setStatus()
{
  char stMes[256];
  
  sprintf(stMes,"scale: %e x,y,aplha: %e %e %5.1f;  zoom magnitude: %3.1f; resolution, W: %d, H: %d; Precision: %d",zw,xw,yw,alp/deg2rad,zoomMag,par->width(),par->height(),par->prec());
  
  status->setText(stMes);

}

double FractGUI::getZoom() const
{
  return zoomMag;
}

void FractGUI::showPrecision()
{
  dialogPrecision->exec();
  if (par->prec()!=dialogPrecision->getPrec()){
    par->setPrec(dialogPrecision->getPrec());
    Fract->setMaxNumIt(par->prec());
    drawNewFract();
  }
}

void FractGUI::showAngle()
{
  dialogAngle->exec();
  if (alp!=dialogAngle->getAngl()){
    alp=dialogAngle->getAngl();
    drawNewFract();
  }
}

void FractGUI::showVideo()
{
  dialogVPoints->show();
  dialogVPoints->raise();
}

void FractGUI::makeVideo()
{
  QMessageBox msgBox;
  char stMes[256];
  
  if (Fract->points.size()>1){
    Fract->initPointMove();
    //clock_t times,timea,timee,lt;
    //times = clock();
    QTime t;
    int times,timea, timee, lt;
    t.start();
    lt=0;
    while(Fract->movePoint()){
      //timea=(clock()-times)/CLOCKS_PER_SEC;
      timea=t.elapsed()/1000;
      //qDebug()<<timea<<" "<<lt;
      if (timea-lt>=1){
        lt=timea;
        timee=timea/60.0;
        timea=int(timea/(60.0*Fract->getWorkDone())-timee);
        sprintf(stMes,"Progress: %4.1f\%; Elapsed time: %3dh %2dm; Remaining time: %3dh %2dm",100.0*Fract->getWorkDone(),timee/60,timee%60,timea/60,timea%60);
        status->setText(stMes);
        repaint();
      }
    }
    sprintf(stMes,"Done!");
      status->setText(stMes);
      repaint();
  }else{
    msgBox.setWindowTitle("Error");
    msgBox.setInformativeText("The number of points in the list is not sufficient.\n The minimum number of points is two.");
    msgBox.exec();
  }
}

void FractGUI::getWinAtrs(double *x,double *y,double *al,double *zm) const
{
  *x=xw;
  *y=yw;
  *al=alp;
  *zm=zw;
}

void FractGUI::setWinAtrs(double x,double y,double al,double zm)
{
  xw=x;
  yw=y;
  alp=al;
  zw=zm;
  
  drawNewFract();
}

void FractGUI::showControl()
{
  QMessageBox msgBox;
  msgBox.setWindowTitle("Control help");
  msgBox.setInformativeText("LMB - zoom in\nMMB - zoom in\nRMB - zoom out\nLMB drag - draw zoom box\n      (+Shift to move box)\nmouse wheel - zoom in/out\nArrows - move on the plane\n      (+Shift,Alt,Ctrl faster move)\nAlt+W - set precision\nAlt+A - set rotation angle\nAlt+R - set resolution\nAlt+E - set equation\nAlt+C - set colors\nCtrl+S - save fractal\nCtrl+L - load fractal\nCtrl+I - save TGA image");
  msgBox.exec();
}

void FractGUI::showAbout()
{
  QMessageBox msgBox;
  msgBox.setWindowTitle("About");
  msgBox.setText("Fractal Zero\nSimple program for demonstration beauty of complex number and series.");
  msgBox.setInformativeText("Written by Jan Skala in 2014.");
  msgBox.exec();
}

void FractGUI::showChangeResol()
{
  dialogChangeResol->exec();
  if (par->width()!=dialogChangeResol->getWidth() ||
      par->height()!=dialogChangeResol->getHeight() ){
    par->setWidth(dialogChangeResol->getWidth());
    par->setHeight(dialogChangeResol->getHeight());
    Fract->changeRes(par->width(),par->height());

    keepAspRat();
    drawNewFract();
  }
}

void FractGUI::showEquation()
{
  dialogEquation->exec();
  if (dialogEquation->isChanged()){
    fstream fout("eqnLog.txt", ios_base::out|ios_base::app);
    fout<<dialogEquation->getEquation()<<"\n";
    fout.close();
    Fract->reloadLib();
    drawNewFract();
  }
}

void FractGUI::showColors()
{
  dialogColors->exec();
  if (dialogColors->isChanged()){
    fstream fout("colLog.txt", ios_base::out|ios_base::app);
    for(int i=0;i<6;i++)
      fout<<dialogColors->getColorEquation(i)<<"\n";
    fout<<"\n";
    fout.close();
    Fract->reloadLibc();
    drawNewFract();
  }
}

void FractGUI::drawNewFract()
{
  status->setText("Calculating...");
  repaint();
  Fract->calcFract(xw,yw,zw,alp);
  if (!Fract->saveImage("temp")){
      qDebug()<<"Saving TGA fail.\n";
      qApp->exit();
  }
  setStatus();
  repaint();  
}


// Dialog Window -- set custom zoom magnitude

customZoom::customZoom(double zm, QWidget *parent) : QDialog(parent)
{

  textLabel = new QLabel("Zoom magnitude: ");
  
  textEdit = new QLineEdit();
  setZoom(zm);
  connect(textEdit, SIGNAL(returnPressed()), this, SLOT(accept()));
  QFontMetrics metrics(QApplication::font());
  textEdit->setFixedSize(metrics.width("9999999.99"),1.5*metrics.height());

  okButton = new QPushButton(QString::fromLocal8Bit("Ok"));
  connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
  okButton->setDefault(true);
  
  QGridLayout *layout = new QGridLayout;

  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->addWidget(textLabel, 0, 0,1,2);
  layout->addWidget(textEdit, 0, 3,1,1);
  layout->addWidget(okButton, 0,4,1,2);
  setLayout(layout);
  
  setWindowTitle(tr("Set zoom magnitude"));
  setModal(true);
}

void customZoom::setZoom(double zm)
{
  char num[24];
  curValue=zm;
  sprintf(num,"%6.2f",curValue);
  textEdit->setText(QString::fromLocal8Bit(num));
}

double customZoom::getZoom()
{
  bool isOk;
  double val;
  
  val = textEdit->text().replace(",", ".").toDouble(&isOk);
  
  if (isOk) return val;
  else{
    val = 4.0;
    setZoom(val);
    return val;
  }
}


// Dialog Window -- set precision

precision::precision(int pr, QWidget *parent) : QDialog(parent)
{

  textLabel = new QLabel("Precision of convergence determination: ");
  
  textEdit = new QLineEdit();
  setPrec(pr);
  connect(textEdit, SIGNAL(returnPressed()), this, SLOT(accept()));
  QFontMetrics metrics(QApplication::font());
  textEdit->setFixedSize(metrics.width("999999"),1.5*metrics.height());

  okButton = new QPushButton(QString::fromLocal8Bit("Ok"));
  connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
  okButton->setDefault(true);
  
  QGridLayout *layout = new QGridLayout;

  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->addWidget(textLabel, 0, 0,1,2);
  layout->addWidget(textEdit, 0, 3,1,1);
  layout->addWidget(okButton, 0,4,1,2);
  setLayout(layout);
  
  setWindowTitle(tr("Convergence precision"));
  setModal(true);
}

void precision::setPrec(int pr)
{
  char num[24];
  sprintf(num,"%4d",pr);
  textEdit->setText(QString::fromLocal8Bit(num));
}

int precision::getPrec()
{
  bool isOk;
  int val;
  
  val = textEdit->text().toInt(&isOk);
  
  if (isOk){
    if (val<10) val=10;
    if (val>9999) val=9999;
    setPrec(val);
    return val;
  }else{
    val = 100;
    setPrec(val);
    return val;
  }
}


// Dialog Window -- change fractal resolution

changeResol::changeResol(int wn,int hn, QWidget *parent) : QDialog(parent)
{
  int tw,th;
  QStringList oList;
  
  wl[0]=640;hl[0]=480;
  wl[1]=800;hl[1]=600;
  wl[2]=1280;hl[2]=720;
  wl[3]=1366;hl[3]=768;
  wl[4]=1600;hl[4]=900;
  wl[5]=1920;hl[5]=1080;
  wl[6]=2048;hl[6]=1152;
  wl[7]=2560;hl[7]=1440;
  wl[8]=3840;hl[8]=2160;
  wl[9]=7680;hl[9]=4320;
  wl[10]=15360;hl[10]=8640;
  
  textLabel1 = new QLabel("width: ");
  textLabel2 = new QLabel("height: ");

  QFontMetrics metrics(QApplication::font());
  tw=metrics.width("999999999");
  th=metrics.height();
  
  textEdit1 = new QLineEdit();
  connect(textEdit1, SIGNAL(returnPressed()), this, SLOT(accept()));
  textEdit1->setFixedSize(tw,th);
  
  textEdit2 = new QLineEdit();
  connect(textEdit2, SIGNAL(returnPressed()), this, SLOT(accept()));
  textEdit2->setFixedSize(tw,th);
  
  oList<<"640x480"<<"800x600"<<"1280x720"<<"1366x768"<<"1600x900"<<"1920x1080"<<"2048x1152"
       <<"2560x1440"<<"3840x2160"<<"7680x4320"<<"15360x8640";
  cBox = new QComboBox();
  cBox->addItems(oList);
  connect(cBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleSelectionChanged(int)));
  
  setValues(wn,hn);
  checkResolution();

  okButton = new QPushButton(QString::fromLocal8Bit("Ok"));
  connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
  okButton->setDefault(true);
  
  QGridLayout *layout = new QGridLayout;

  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->addWidget(textLabel1, 0, 0,1,2);
  layout->addWidget(textEdit1, 0, 3,1,1);
  layout->addWidget(okButton, 0,4,1,2);
  layout->addWidget(textLabel2, 1, 0,1,2);
  layout->addWidget(textEdit2, 1, 3,1,1);
  layout->addWidget(cBox, 1, 4,1,2);
  setLayout(layout);
  
  setWindowTitle(tr("Set fractal resolution"));
  setModal(true);
}

void changeResol::checkResolution()
{
  for(int i=0;i<11;i++)
    if (w==wl[i] && h==wl[i]){
      cBox->setCurrentIndex(i);
      break;
    }
}

void changeResol::handleSelectionChanged(int i)
{
  setValues(wl[i],hl[i]);
}

void changeResol::setValues(int wn, int hn)
{
  char num[24];
  
  w=wn;
  h=hn;
  
  sprintf(num,"%d",w);
  textEdit1->setText(QString::fromLocal8Bit(num));
  sprintf(num,"%d",h);
  textEdit2->setText(QString::fromLocal8Bit(num));
  
  checkResolution();
}

void changeResol::setWidth(int wn)
{
  char num[24];
  w=wn;
  sprintf(num,"%d",w);
  textEdit1->setText(QString::fromLocal8Bit(num));
  
  checkResolution();
}

void changeResol::setHeight(int hn)
{
  char num[24];
  h=hn;
  sprintf(num,"%d",h);
  textEdit2->setText(QString::fromLocal8Bit(num));
  
  checkResolution();
}

int changeResol::getWidth()
{
  bool isOk;
  int val;
  
  val = textEdit1->text().toInt(&isOk);
  
  if (isOk){
    if (val<16) val=16;
    if (val>1024*64) val=1024*64;
  }else{
    val = w;
  }
  setWidth(val);
  return val;
}

int changeResol::getHeight()
{
  bool isOk;
  int val;
  
  val = textEdit2->text().toInt(&isOk);
  
  if (isOk){
    if (val<16) val=16;
    if (val>1024*64) val=1024*64;
  }else{
    val = h;
  }
  setHeight(val);
  return val;
}


// Dialog Window -- equation

equation::equation(QWidget *parent) : QDialog(parent)
{

  textLabel = new QLabel("Equation in C/C++ format, c - constant complex number, z - varying number:");
  
  textEdit = new QLineEdit();
  connect(textEdit, SIGNAL(returnPressed()), this, SLOT(checkEq()));
  QFontMetrics metrics(QApplication::font());
  textEdit->setFixedSize(60*metrics.width("9"),2*metrics.height());
  
  readEquation();
  setEquation();

  okButton = new QPushButton(QString::fromLocal8Bit("Ok"));
  connect(okButton, SIGNAL(clicked()), this, SLOT(checkEq()));
  //okButton->setDefault(true);
  
  cancelButton = new QPushButton(QString::fromLocal8Bit("cancel"));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
  
  QGridLayout *layout = new QGridLayout;

  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->addWidget(textLabel, 0, 0,1,1);
  layout->addWidget(okButton, 0,1,1,2);
  layout->addWidget(textEdit, 1, 0,1,1);
  layout->addWidget(cancelButton, 1,1,1,2);
  setLayout(layout);
  
  setWindowTitle(tr("Equation"));
  setModal(true);
  
  changed=false;
}

void equation::checkEq()
{
  QMessageBox msgBox;
  int error,i;
  ofstream fout("func/test.cc", ios_base::out|ios_base::trunc);
  fout<<firstPart<<textEdit->text().toLocal8Bit().data()<<"\n"<<secondPart;
  fout.close();
  
  error=system("g++ -O3 -fPIC -shared func/test.cc -o func/test.so");
  
  if (error){
    error = system("rm func/test.cc func/test.so");
    msgBox.setWindowTitle("Error");
    msgBox.setText("Error occurred during compilation.");
    msgBox.setInformativeText("Please check your equation.");
    msgBox.exec();
    return;
  }
  
  error=system("mv func/test.cc func/lib-c; mv func/test.so func/function.so");
  i=0;
  while( (equationLine[i]=*(textEdit->text().toLocal8Bit().data()+i))!='\0')
    i++;
  
  changed=true;
  accept();
}

void equation::cancel()
{
  int error = system("rm func/test.cc func/test.so");
  setEquation();
  accept();
}

void equation::setEquation()
{
  textEdit->setText(QString::fromLocal8Bit(equationLine));
}

void equation::setEquation(char* str)
{
  textEdit->setText(QString::fromLocal8Bit(str));
}

char* equation::getEquation()
{
  return textEdit->text().toLocal8Bit().data();
}

void equation::readEquation()
{
  string line;
  int pos=0;
  ifstream eqnFile("func/lib-c");
  if (!eqnFile.is_open()) qDebug()<<"File func/lib-c does not found!\n";
    
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
  //qDebug()<<firstPart<<equationLine<<"\n"<<secondPart;
}

bool equation::isChanged()
{
  bool bck=changed;
  changed=false;
  
  return bck;
}

// Dialog Window -- colors

colors::colors(QWidget *parent) : QDialog(parent)
{

  textLabel = new QLabel("Equation in C/C++ format, p - original complex number, r - return number, it - num. iteration, zm - scale:");
  textLabelCon = new QLabel("Convergent colors:");
  textLabelRc = new QLabel("Red:");
  textLabelGc = new QLabel("Green:");
  textLabelBc = new QLabel("Blue:");
  textLabelDiv = new QLabel("Divergent colors:");
  textLabelRd = new QLabel("Red:");
  textLabelGd = new QLabel("Green:");
  textLabelBd = new QLabel("Blue:");
  
  QFontMetrics metrics(QApplication::font());
  for(register int i=0;i<6;i++){
    textEdit[i] = new QLineEdit();
    connect(textEdit[i], SIGNAL(returnPressed()), this, SLOT(checkEq()));
    textEdit[i]->setFixedSize(40*metrics.width("9"),1.5*metrics.height());
  }
  
  readColFuncs();
  setColFuncs();

  okButton = new QPushButton(QString::fromLocal8Bit("Ok"));
  connect(okButton, SIGNAL(clicked()), this, SLOT(checkEq()));
  okButton->setDefault(true);

  cancelButton = new QPushButton(QString::fromLocal8Bit("cancel"));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
  
  QGridLayout *layout = new QGridLayout;

  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->addWidget(textLabel, 0, 0,1,3);
  layout->addWidget(textLabelCon, 1, 0,1,1);
  layout->addWidget(textLabelRc, 2, 0,1,1);
  layout->addWidget(textLabelGc, 3, 0,1,1);
  layout->addWidget(textLabelBc, 4, 0,1,1);
  layout->addWidget(textLabelDiv, 5, 0,1,1);
  layout->addWidget(textLabelRd, 6, 0,1,1);
  layout->addWidget(textLabelGd, 7, 0,1,1);
  layout->addWidget(textLabelBd, 8, 0,1,1);
  
  layout->addWidget(textEdit[0], 2, 1,1,1);
  layout->addWidget(textEdit[1], 3, 1,1,1);
  layout->addWidget(textEdit[2], 4, 1,1,1);
  layout->addWidget(textEdit[3], 6, 1,1,1);
  layout->addWidget(textEdit[4], 7, 1,1,1);
  layout->addWidget(textEdit[5], 8, 1,1,1);
  
  layout->addWidget(okButton, 1,2,1,1);
  layout->addWidget(cancelButton, 2,2,1,1);
  setLayout(layout);
  
  setWindowTitle(tr("Color settings"));
  setModal(true);
  
  changed=false;
}

char* colors::getColorEquation(int i)
{
  return textEdit[i]->text().toLocal8Bit().data();
}

void colors::setColorEquation(int i, char *str)
{
  textEdit[i]->setText(QString::fromLocal8Bit(str));
}

void colors::checkEq()
{
  QMessageBox msgBox;
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
        <<" return char("<<textEdit[i]->text().toLocal8Bit().data()<<");\n}\n";
    fout<<"}\n";
    fout.close();
    
    error=system("g++ -O3 -fPIC -shared func/test.cc -o func/test.so");
    
    if (error){
      error = system("rm func/test.cc func/test.so");
      msgBox.setText("Error occurred during compilation.");
      sprintf(text,"Please check your %s %s equation.",
            conDiv[i/3],colName[i%3]);
      msgBox.setInformativeText(text);
      msgBox.exec();
      return;
    }
  }
  
  for(int j=0;j<6;j++){
    i=0;
    while( (colLine[j][i]=*(textEdit[j]->text().toLocal8Bit().data()+i))!='\0')
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

  changed=true;
  accept();
}

void colors::cancel()
{
  int error=system("rm func/test.cc func/test.so");
  setColFuncs();
  accept();
}

void colors::setColFuncs()
{
  for(register int i=0;i<6;i++)
    textEdit[i]->setText(QString::fromLocal8Bit(colLine[i]));
}

void colors::readColFuncs()
{
  string line;
  int pos=0;
  
  ifstream colFile("func/libc-c");
  if (!colFile.is_open()) qDebug()<<"File func/libc-c does not found!\n";
  
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
  pos=sprintf(colLine[3],"%s\n",line.c_str()+13);
  colLine[3][pos-3]='\0';
  for(register int i=4;i<6;i++){
    getline(colFile, line);
    getline(colFile, line);
    getline(colFile, line);
    pos=sprintf(colLine[i],"%s\n",line.c_str()+13);
    colLine[i][pos-3]='\0';
  }
  
  colFile.close();
}

bool colors::isChanged()
{
  bool bck=changed;
  changed=false;
  
  return bck;
}

// Dialog Window -- set angle

angle::angle(double alp, QWidget *parent) : QDialog(parent)
{

  textLabel = new QLabel("Angle: ");
  
  textEdit = new QLineEdit();
  connect(textEdit, SIGNAL(returnPressed()), this, SLOT(accept()));
  QFontMetrics metrics(QApplication::font());
  textEdit->setFixedSize(metrics.width("999999"),1.5*metrics.height());

  okButton = new QPushButton(QString::fromLocal8Bit("Ok"));
  connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
  okButton->setDefault(true);
  
  slider = new QSlider( Qt::Horizontal);
  slider->setRange( 0, 360 );
  connect( slider, SIGNAL(valueChanged(int)), this, SLOT(setAngl(int)) );
  
  setAngle(alp);
  
  QGridLayout *layout = new QGridLayout;

  //layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->addWidget(textLabel, 0, 0,1,2);
  layout->addWidget(textEdit, 0, 3,1,1);
  layout->addWidget(okButton, 0,4,1,2);
  layout->addWidget(slider, 1,0,1,6);
  setLayout(layout);
  
  setWindowTitle(tr("Rotation angle"));
  setModal(true);
}

void angle::setAngl(int alp)
{
  char num[24];
  sprintf(num,"%d",alp);
  textEdit->setText(QString::fromLocal8Bit(num));
}

void angle::setAngle(double alp)
{
  char num[24];
  sprintf(num,"%4d",int(alp/deg2rad));
  textEdit->setText(QString::fromLocal8Bit(num));
  slider->setValue( int(alp/deg2rad) );
}

double angle::getAngl()
{
  bool isOk;
  double val;
  
  val = textEdit->text().replace(',','.').toDouble(&isOk);
  
  if (isOk){
    if (val<0) val=0;
    if (val>360) val=360;
  }else{
    val = 0;
  }
  val=val*deg2rad;
  setAngle(val);
  return val;
}

// Dialog Window -- set Slide Show Points Settings

videoPoints::videoPoints(FractGUI *parent) : QDialog(parent)
{
  mainWin = parent;
  
  resize(720,480);

  okButton = new QPushButton(QString::fromLocal8Bit("Ok"));
  connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
  canButton = new QPushButton(QString::fromLocal8Bit("Cancel"));
  connect(canButton, SIGNAL(clicked()), this, SLOT(reject()));

  addButton = new QPushButton(QString::fromLocal8Bit("Add"));
  connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));
  addButton->setDefault(true);
  insButton = new QPushButton(QString::fromLocal8Bit("Insert"));
  connect(insButton, SIGNAL(clicked()), this, SLOT(insRow()));
  showButton = new QPushButton(QString::fromLocal8Bit("Show"));
  connect(showButton, SIGNAL(clicked()), this, SLOT(showSlide()));
  delButton = new QPushButton(QString::fromLocal8Bit("Delete"));
  connect(delButton, SIGNAL(clicked()), this, SLOT(delRow()));
  randButton = new QPushButton(QString::fromLocal8Bit("Randomize"));
  connect(randButton, SIGNAL(clicked()), this, SLOT(randomizeMoves()));
  clrButton = new QPushButton(QString::fromLocal8Bit("Clear"));
  connect(clrButton, SIGNAL(clicked()), this, SLOT(clearTable()));
  loadButton = new QPushButton(QString::fromLocal8Bit("Load"));
  connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));
  saveButton = new QPushButton(QString::fromLocal8Bit("Save"));
  connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
  
  //connect(this,SIGNAL(aboutToQuit()),this,SLOT(cancelQuit()));

  
  table = new QTableWidget();
  QStringList list;
  list<<"scale"<<"x"<<"y"<<"alpha"<<"move x"<<"move y"<<"move a"<<"move z"<<"speed";
  table->setRowCount(0);
  table->setColumnCount(9);
  table->setHorizontalHeaderLabels(list);
  QFontMetrics metrics(QApplication::font());
  table->setColumnWidth(0,2*metrics.width("99999"));
  table->setColumnWidth(1,2*metrics.width("99999"));
  table->setColumnWidth(2,2*metrics.width("99999"));
  table->setColumnWidth(3,2*metrics.width("999"));
  table->setColumnWidth(4,2*metrics.width("tanh"));
  table->setColumnWidth(5,2*metrics.width("tanh"));
  table->setColumnWidth(6,2*metrics.width("tanh"));
  table->setColumnWidth(7,2*metrics.width("tanh"));
  table->setColumnWidth(8,2*metrics.width("999"));
  
  QGridLayout *layout = new QGridLayout;
  layout->addWidget(table,      0,0, 11,6);
  layout->addWidget(addButton,  0,6, 1,1);
  layout->addWidget(showButton, 1,6, 1,1);
  layout->addWidget(insButton,  2,6, 1,1);
  layout->addWidget(delButton,  3,6, 1,1);
  layout->addWidget(randButton, 4,6, 1,1);
  layout->addWidget(clrButton,  5,6, 1,1);
  layout->addWidget(loadButton, 6,6, 1,1);
  layout->addWidget(saveButton, 7,6, 1,1);
  layout->addWidget(okButton,   9,6, 1,1);
  layout->addWidget(canButton, 10,6, 1,1);
  setLayout(layout);
  
  setWindowTitle(tr("Slide show points settings"));
  setModal(false);
}

void videoPoints::reject()
{
  makeTable();
  done(0);
}

void videoPoints::addRow()
{
  insertRow(table->rowCount());
}

void videoPoints::showSlide()
{
  list<zoomPoint>::iterator it;
  int j,row;
  
  row=table->currentRow();
  
  for(j=0,it=points.begin();it!=points.end();it++,j++)
    if (j==row){
      mainWin->setWinAtrs(it->x,it->y,it->al,it->zm);
      break;
    }
    
  
}

void videoPoints::insertRow(int row)
{
  double x,y,al,zm,sp;
  QTableWidgetItem *item;
  QComboBox *cBox;
  QStringList oList;
  int i,j,index;
  char str[32];
  bool isOk;
  zoomPoint zp;
  list<zoomPoint>::iterator it;
  
  oList<<"x^1"<<"x^2"<<"x^4"<<"cos"<<"ix^2"<<"ix^4"<<"sin"<<"tanh";
  mainWin->getWinAtrs(&x,&y,&al,&zm);
  table->insertRow(row);
  i=row;
  
  sprintf(str,"%5.3e",zm);
  item = new QTableWidgetItem(str);
  table->setItem(i,0,item);
  item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
  
  sprintf(str,"%5.3e",x);
  item = new QTableWidgetItem(str);
  table->setItem(i,1,item);
  item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
  
  sprintf(str,"%5.3e",y);
  item = new QTableWidgetItem(str);
  table->setItem(i,2,item);
  item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

  sprintf(str,"%5.1f",al/deg2rad);
  item = new QTableWidgetItem(str);
  table->setItem(i,3,item);
  item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
  
  if (i>0) index = static_cast<QComboBox*>(table->cellWidget(i-1,4))->currentIndex();
  else index=7;
  cBox = new QComboBox();
  cBox->addItems(oList);
  table->setCellWidget(i,4,cBox);
  cBox->setCurrentIndex(index);
   
  if (i>0) index = static_cast<QComboBox*>(table->cellWidget(i-1,5))->currentIndex();
  else index=7;
  cBox = new QComboBox();
  cBox->addItems(oList);
  table->setCellWidget(i,5,cBox);
  cBox->setCurrentIndex(index);
  
  if (i>0) index = static_cast<QComboBox*>(table->cellWidget(i-1,6))->currentIndex();
  else index=7;
  cBox = new QComboBox();
  cBox->addItems(oList);
  table->setCellWidget(i,6,cBox);
  cBox->setCurrentIndex(index);
  
  if (i>0) index = static_cast<QComboBox*>(table->cellWidget(i-1,7))->currentIndex();
  else index=7;
  cBox = new QComboBox();
  cBox->addItems(oList);
  table->setCellWidget(i,7,cBox);
  cBox->setCurrentIndex(index);
  
  if (i>0) sp = table->item(i-1,8)->text().replace(",", ".").toDouble(&isOk);
  else sp = 0.1;
  if (!isOk) sp = 0.9;
  else{
    if (sp<0.0) sp = 0.0;
    if (sp>1.0) sp = 1.0;
  }
  
  sprintf(str,"%5.3f",sp);
  item = new QTableWidgetItem(str);
  table->setItem(i,8,item);
  item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
  
  zp.x=x;
  zp.y=y;
  zp.al=al*deg2rad;
  zp.zm=zm;
  zp.sp=table->item(i,8)->text().replace(",", ".").toDouble(&isOk);
  zp.mx=static_cast<QComboBox*>(table->cellWidget(i,4))->currentIndex();
  zp.my=static_cast<QComboBox*>(table->cellWidget(i,5))->currentIndex();
  zp.ma=static_cast<QComboBox*>(table->cellWidget(i,6))->currentIndex();
  for(j=0,it=points.begin();it!=points.end();it++,j++)
    if (j==row){
      points.insert(it,zp);
      break;
    }
  if (points.size()==0 || points.size()==(unsigned)row)
    points.push_back(zp);
  
  table->resizeColumnsToContents();
}

void videoPoints::okClick()
{
  // apply all changes
  acceptChanges();
  
  // move list from temporary (working) list to final one
  //mainWin->Fract->points=points;
  accept();
}

void videoPoints::save()
{
  // apply all changes
  acceptChanges();
  
  // move list from temporary (working) list to final one
  mainWin->saveVToFile();
}

void videoPoints::load()
{
  mainWin->loadVFromFile();
}

void videoPoints::acceptChanges()
{
  list<zoomPoint>::iterator it;
  bool isOk;
  int i;
  // apply all changes
  for(it=points.begin(),i=0;it!=points.end();it++,i++){
    it->al=table->item(i,3)->text().replace(",", ".").toDouble(&isOk);
    if (isOk){
        if (it->al<0 || it->al>360) it->al-=360.0*((it->al<0?-1.0:0.0)+int(it->al/360));
        it->al*=deg2rad;
    }else  it->al = 0;
      
    it->sp=table->item(i,8)->text().replace(",", ".").toDouble(&isOk);
    if (!isOk) it->sp = 0.9;
    else{
      if (it->sp<0.0) it->sp = 0.0;
      if (it->sp>2.0) it->sp = 2.0;
    }
    it->mx=static_cast<QComboBox*>(table->cellWidget(i,4))->currentIndex();
    it->my=static_cast<QComboBox*>(table->cellWidget(i,5))->currentIndex();
    it->ma=static_cast<QComboBox*>(table->cellWidget(i,6))->currentIndex();
    it->mz=static_cast<QComboBox*>(table->cellWidget(i,7))->currentIndex();
  }
  // move list from temporary (working) list to final one
  mainWin->Fract->points=points;
}

double videoPoints::Rnd()
{
  return double(rand())/double(RAND_MAX);
}

void videoPoints::randomizeMoves()
{
  bool isOk;
  int zinxy[6]={0,1,2,3,7,7};
  int zina[9]={0,1,2,3,4,5,6,7,7};
  int zinz[5]={4,5,6,7,7}; // 5
  int zoutxy[6]={0,4,5,6,7,7};
  //int zouta={0,1,2,3,4,5,6,7,7};
  int zoutz[5]={1,2,3,7,7};
  double al,sp;
  char str[128];
  
  al=table->item(table->rowCount()-1,3)->text().replace(",", ".").toDouble(&isOk);
  sp=table->item(table->rowCount()-1,8)->text().replace(",", ".").toDouble(&isOk);
  for(int i=table->rowCount()-1;i>=1;i--){
    if (table->item(i-1,0)->text().replace(",", ".").toDouble(&isOk) >
        table->item(i,0)->text().replace(",", ".").toDouble(&isOk) ){
      static_cast<QComboBox*>(table->cellWidget(i,4))->setCurrentIndex(zinxy[rand()%6]);
      static_cast<QComboBox*>(table->cellWidget(i,5))->setCurrentIndex(zinxy[rand()%6]);
      static_cast<QComboBox*>(table->cellWidget(i,6))->setCurrentIndex(zina[rand()%9]);
      static_cast<QComboBox*>(table->cellWidget(i,7))->setCurrentIndex(zinz[rand()%5]);
    }else{
      static_cast<QComboBox*>(table->cellWidget(i,4))->setCurrentIndex(zoutxy[rand()%6]);
      static_cast<QComboBox*>(table->cellWidget(i,5))->setCurrentIndex(zoutxy[rand()%6]);
      static_cast<QComboBox*>(table->cellWidget(i,6))->setCurrentIndex(zina[rand()%9]);
      static_cast<QComboBox*>(table->cellWidget(i,7))->setCurrentIndex(zoutz[rand()%5]);
    }
    
    al+=(Rnd()-0.5)*180;
    if (al>360.0 || al<0.0) al-=360.0*((al<0?-1.0:0.0)+int(al/360));
    sprintf(str,"%5.1f",al);
    table->item(i,3)->setText(str);
    sp+=(Rnd()-0.5)*0.1;
    if (sp<0.2) sp=0.2;
    if (sp>0.9) sp=0.9;
    sprintf(str,"%5.3f",sp);
    table->item(i,8)->setText(str);
  }
  
  table->resizeColumnsToContents();
}

void videoPoints::clearTable()
{
  for(int i=table->rowCount()-1;i>=0;i--) table->removeRow(i);
  points.clear();
}

void videoPoints::insRow()
{
  // insert row into the table
  insertRow(table->currentRow());
  // inset point struct into list
}

void videoPoints::delRow()
{
  list<zoomPoint>::iterator it;
  int i,j;
  // delete row from the table
  table->removeRow(i=table->currentRow());
  // delete point struct from list
  for(j=0,it=points.begin();it!=points.end();it++,j++)
    if (j==i){
      points.erase(it);
      break;
    }
}

void videoPoints::makeTable()
{
  QTableWidgetItem *item;
  QComboBox *cBox;
  QStringList oList;
  int i;
  char str[32];
  list<zoomPoint>::iterator it;
  
  // remove all rows from table
  clearTable();
  
  oList<<"x^1"<<"x^2"<<"x^4"<<"cos"<<"ix^2"<<"ix^4"<<"sin"<<"tanh";
  
  // copy data from Factal list to table
  points=mainWin->Fract->points;
  it=points.begin();
  for(i=0;(unsigned)i<points.size();i++)
  {
    table->insertRow(i);
    
    sprintf(str,"%5.3e",it->zm);
    item = new QTableWidgetItem(str);
    table->setItem(i,0,item);
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    
    sprintf(str,"%5.3e",it->x);
    item = new QTableWidgetItem(str);
    table->setItem(i,1,item);
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    
    sprintf(str,"%5.3e",it->y);
    item = new QTableWidgetItem(str);
    table->setItem(i,2,item);
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    if (it->al>2.0*PI) it->al=it->al-PI*int(it->al/PI); 
    sprintf(str,"%5.1f",it->al/deg2rad);
    item = new QTableWidgetItem(str);
    table->setItem(i,3,item);
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
    
    cBox = new QComboBox();
    cBox->addItems(oList);
    table->setCellWidget(i,4,cBox);
    cBox->setCurrentIndex(it->mx);
    
    cBox = new QComboBox();
    cBox->addItems(oList);
    table->setCellWidget(i,5,cBox);
    cBox->setCurrentIndex(it->my);
    
    cBox = new QComboBox();
    cBox->addItems(oList);
    table->setCellWidget(i,6,cBox);
    cBox->setCurrentIndex(it->ma);
    
    cBox = new QComboBox();
    cBox->addItems(oList);
    table->setCellWidget(i,7,cBox);
    cBox->setCurrentIndex(it->mz);
    
    sprintf(str,"%5.3f",it->sp);
    item = new QTableWidgetItem(str);
    table->setItem(i,8,item);
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
    
    it++;
  }
  table->resizeColumnsToContents();
  
}


