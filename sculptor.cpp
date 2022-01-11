#include "Sculptor.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

Sculptor::Sculptor(int mx, int my, int mz){
  x = mx;
  y = my;
  z = mz;

  mat = new Voxel **[x];

  for (int i = 0; i < x; i++) {
		mat[i] = new Voxel *[y];
	}

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			mat[i][j] = new Voxel[z];

		}
	}

	for (int i = 0; i < x; i++) { // Atribuindo valores iniciais
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++) {
				mat[i][j][k].isOn = false;
				mat[i][j][k].r = 0;
				mat[i][j][k].g = 0;
				mat[i][j][k].b = 0;
				mat[i][j][k].a = 0;
			}
		}
	}
}

Sculptor::~Sculptor(){
  for (int i = 0; i < x; i++) { // Liberando as memorias
		for (int j = 0; j < y; j++) {
			delete[] mat[i][j];
		}
	}
	for (int i = 0; i < x; i++) {
		delete[] mat[i];
	}
	delete[] mat;
}

void Sculptor::setColor(float mr, float mg, float mb, float ma){
  // atribuiremos a cor com que estamos trabalhando no momento
  r = mr;
  g = mg;
  b = mb;
  a = ma;
}

void Sculptor::putVoxel(int mx, int my, int mz){
  // atribui verdadeiro para aquele voxel em especifico e atribui a cor atual do desenho
  mat[mx][my][mz].isOn = true;
  mat[mx][my][mz].r = r;
  mat[mx][my][mz].g = g;
  mat[mx][my][mz].b = b;
  mat[mx][my][mz].a = a;
}

void Sculptor::cutVoxel(int mx, int my, int mz){
  // atribui falso para aquele voxel em especifico
  mat[mx][my][mz].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
  int i, j, k;
  for(i=x0;i<x1;i++){
    for(j=y0;j<y1;j++){
      for(k=z0;k<z1;k++){
        putVoxel(i, j, k);
      }
    }
  }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
  int i, j, k;
  for(i=x0;i<x1;i++){
    for(j=y0;j<y1;j++){
      for(k=z0;k<z1;k++){
        cutVoxel(i, j, k);
      }
    }
  }
}

void Sculptor::putSphere(int xc, int yc, int zc, int r){
  //r² = x²+y²+z², logo
  double dist;
  int i, j, k;
  for(i=0;i<x;i++){
    for(j=0;j<y;j++){
      for(k=0;k<z;k++){
        dist = (pow(i - xc, 2) + pow(j - yc, 2) + pow(k - zc, 2)); 
        if (dist<=pow(r,2)){
          putVoxel(i, j, k);
        }
      }
    }
  }
}

void Sculptor::cutSphere(int xc, int yc, int zc, int r){
  //r² = x²+y²+z², logo
  double dist;
  int i, j, k;
  for(i=0;i<x;i++){
    for(j=0;j<y;j++){
      for(k=0;k<z;k++){
        dist = (pow(i - xc, 2) + pow(j - yc, 2) + pow(k - zc, 2)); 
        if (dist<=pow(r,2)){
          cutVoxel(i, j, k);
        }
      }
    }
  }
}

void Sculptor::putEllipsoid(int xc, int yc, int zc, int rx, int ry, int rz){
  //Formula da elipsoide: (x-x0)²/rx² + (y-y0)²/ry² + (z-z0)²/rz² <= 1
  double dist;
  int i, j, k;
  if(rx==0){
    for(j=0;j<=y;j++){
      for(k=0;k<=z;k++){
        dist = (pow(j-yc, 2)/pow(ry,2)) + (pow(k-zc, 2)/pow(rz,2));
        if(dist <=1){
          putVoxel(xc, j, k);
        }
      }
    }
  } else if(ry==0){
    for(i=0;i<=x;i++){
      for(k=0;k<=z;k++){
        dist = (pow(x-xc, 2)/pow(rx,2)) + (pow(k-zc, 2)/pow(rz,2));
        if(dist <=1){
          putVoxel(i, yc, k);
        }
      }
    }
  } else if(rz==0){
    for(i=0;i<=x;i++){
      for(j=0;j<=y;j++){
        dist = (pow(i-xc, 2)/pow(rx,2)) + (pow(j-yc, 2)/pow(ry,2));
        if(dist <=1){
          putVoxel(i, j, zc);
        }
      }
    }
  } else{
    for(i=0;i<x;i++){
      for(j=0;j<y;j++){
        for(k=0;k<z;k++){
          dist = (pow(i-xc, 2)/pow(rx,2)) + (pow(j-yc, 2)/pow(ry,2)) + (pow(k-zc, 2)/pow(rz,2));
          if(dist<=1){
            putVoxel(i, j, k);
          }
        }
      }
    }
  }
}

void Sculptor::cutEllipsoid(int xc, int yc, int zc, int rx, int ry, int rz){
  //Formula da elipsoide: (x-x0)²/rx² + (y-y0)²/ry² + (z-z0)²/rz² <= 1
  double dist;
  int i, j, k;
  if(rx==0){
    for(j=0;j<=y;j++){
      for(k=0;k<=z;k++){
        dist = (pow(j-yc, 2)/pow(ry,2)) + (pow(k-zc, 2)/pow(rz,2));
        if(dist <=1){
          cutVoxel(xc, j, k);
        }
      }
    }
  } else if(ry==0){
    for(i=0;i<=x;i++){
      for(k=0;k<=z;k++){
        dist = (pow(x-xc, 2)/pow(rx,2)) + (pow(k-zc, 2)/pow(rz,2));
        if(dist <=1){
          cutVoxel(i, yc, k);
        }
      }
    }
  } else if(rz==0){
    for(i=0;i<=x;i++){
      for(j=0;j<=y;j++){
        dist = (pow(i-xc, 2)/pow(rx,2)) + (pow(j-yc, 2)/pow(ry,2));
        if(dist <=1){
          cutVoxel(i, j, zc);
        }
      }
    }
  } else{
    for(i=0;i<x;i++){
      for(j=0;j<y;j++){
        for(k=0;k<z;k++){
          dist = (pow(i-xc, 2)/pow(rx,2)) + (pow(j-yc, 2)/pow(ry,2)) + (pow(k-zc, 2)/pow(rz,2));
          if(dist<=1){
            cutVoxel(i, j, k);
          }
        }
      }
    }
  }
}

void Sculptor::writeOFF(char *filename){
  ofstream fout; // como chamar a biblioteca
  fout.open(filename); // abrindo o arquivo

  int i, j, k;
  int vx = 0; // Saber a quantidade de voxels ativos
  float c = 0.5; // definir os centros
  
  for(i=0;i<x;i++){
    for(j=0;j<y;j++){
      for(k=0;k<z;k++){
        if(mat[i][j][k].isOn){ // so conta se o isOn for verdadeiro
          vx++; 
        }
      }
    }
  }

  fout << "OFF" << endl;
  fout << vx*8 << " " << vx*6 << " " << 0 << endl; // Vertices, Faces, Arestas

  for(i=0;i<x;i++){
    for(j=0;j<y;j++){
      for(k=0;k<z;k++){
        if(mat[i][j][k].isOn){ // definindo os vertices a partir do centro
          fout << i-c << " " << j+c << " " << k-c << endl;
          fout << i-c << " " << j-c << " " << k-c << endl;
          fout << i+c << " " << j-c << " " << k-c << endl;
          fout << i+c << " " << j+c << " " << k-c << endl;
          fout << i-c << " " << j+c << " " << k+c << endl;
          fout << i-c << " " << j-c << " " << k+c << endl;
          fout << i+c << " " << j-c << " " << k+c << endl;
          fout << i+c << " " << j+c << " " << k+c << endl;
        }
      }
    }
  }

  vx = 0; // reiniciando a contagem
  fout << setiosflags(ios::fixed); // fixando os valores das cores

  for(i=0;i<x;i++){
    for(j=0;j<y;j++){
      for(k=0;k<z;k++){
        if(mat[i][j][k].isOn){ // DEFINIR AS FACE
          //FACE 0
          fout << 4 << " " << vx+0 << " " << vx+3 << " " << vx+2 << " " << vx+1 << " " << mat[i][k][j].r << " "  << mat[i][k][j].g << " " << mat[i][k][j].b << " " << mat[i][k][j].a << endl;
          //FACE 1
          fout << 4 << " " << vx+4 << " " << vx+5 << " " << vx+6 << " " << vx+7 << " " << mat[i][k][j].r << " "  << mat[i][k][j].g << " " << mat[i][k][j].b << " " << mat[i][k][j].a << endl;
          //FACE 2
          fout << 4 << " " << vx+0 << " " << vx+1 << " " << vx+5 << " " << vx+4 << " " << mat[i][k][j].r << " "  << mat[i][k][j].g << " " << mat[i][k][j].b << " " << mat[i][k][j].a << endl;
          //FACE 3
          fout << 4 << " " << vx+0 << " " << vx+4 << " " << vx+7 << " " << vx+3 << " " << mat[i][k][j].r << " "  << mat[i][k][j].g << " " << mat[i][k][j].b << " " << mat[i][k][j].a << endl;
          // FACE 4
          fout << 4 << " " << vx+3 << " " << vx+7 << " " << vx+6 << " " << vx+2 << " " << mat[i][k][j].r << " "  << mat[i][k][j].g << " " << mat[i][k][j].b << " " << mat[i][k][j].a << endl;
          //FACE 5
          fout << 4 << " " << vx+1 << " " << vx+2 << " " << vx+6 << " " << vx+5 << " " << mat[i][k][j].r << " "  << mat[i][k][j].g << " " << mat[i][k][j].b << " " << mat[i][k][j].a << endl;
          vx = vx + 8;
        }
      }
    }
  }
  fout.close();
}
