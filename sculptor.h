#ifndef SCULPTOR_H
#define SCULPTOR_H

struct Voxel {
  float r,g,b; // Cores
  float a; // Transparencia
  bool isOn; // Incluido ou nao
};

class Sculptor{
  private:
  float r, g, b, a; // cores
  int x, y, z; // dimensoes
  Voxel*** mat; // ponteiro triplo para matriz 3d
  public:
  Sculptor(int mx, int my, int mz);
  virtual ~Sculptor();
  void setColor(float mr, float mg, float mb, float ma);
  void putVoxel(int mx, int my, int mz);
  void cutVoxel(int mx, int my, int mz);
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void putSphere(int xc, int yc, int zc, int r);
  void cutSphere(int xc, int yc, int zc, int r);
  void putEllipsoid(int xc, int yc, int zc, int rx, int ry, int rz);
  void cutEllipsoid(int xc, int yc, int zc, int rx, int ry, int rz);
  void writeOFF(char* filename);
  protected:
};



#endif // SCULPTOR_H
