#ifndef TTGA
#define TTGA

class Ttga
{
  private:
   int width;
   int height;
   
   char* data;
    
  public:
  Ttga(const int w,const int h);
  ~Ttga();
  
  unsigned char* getData(){return (unsigned char*)data;};
  void setPixelRGB(const int x,const int y,const char r,const char g,const char b);
  bool save(const char *name);
  void changeRes(int, int);
};


#endif // TTGA
