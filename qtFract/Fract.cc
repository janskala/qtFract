#include<iostream>
// #include<iomanip>
// #include<cstdlib>
#include"fractGUI.h"
#include <omp.h>

int main(int argc, char* argv[])
{

  QApplication app(argc, argv);  
    
  FractGUI window;
  
  window.setWindowTitle("Fractal Zero");
  window.show();
  
  return app.exec();
}

