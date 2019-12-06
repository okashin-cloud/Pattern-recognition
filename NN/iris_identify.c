#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 5 //入力層の要素数
#define H 7 //中間層の要素数
#define C 3 //クラス数
#define P 10  //パターン数

struct Pat{  
  int c_name; //クラス名                                                         
  double x[N]; //拡張特徴ベクトル                                            
};

double sigmoid(double x);

int main(int argc,char* argv[]){

  int i,j,k;

  struct Pat pat[P];
  FILE *p1,*p2, *p3 ;

  double in[N];
  double w1[H][N],w2[C][H];
  double g_1[H],g1[H],g_2[C],g2[C];
  double rho=0.1;
  double max=0;
  int max_c;
  int count=0;

 
  p1=fopen(argv[1],"r");
  for(i=0;i<P;i++){
    pat[i].x[0]=1.0;
    fscanf(p1,"%lf %lf %lf %lf %d",&pat[i].x[1],&pat[i].x[2],&pat[i].x[3],&pat[i].x[4],&pat[i].c_name);
    printf("pattern%d : %d %lf %lf %lf %lf %lf\n",i,pat[i].c_name,pat[i].x[0],pat[i].x[1],pat[i].x[2],pat[i].x[3],pat[i].x[4]);
  }
  for(k=0;k<P;k++){

    max=0;
    max_c=0;

   
    p2=fopen("iris_wlast.dat","r");
    for(i=0;i<H;i++){
      for(j=0;j<N;j++){
	fscanf(p2,"%lf",&w1[i][j]);
      }
    }
    p3 =fopen("iris_ulast.dat","r");
    for(i=0;i<C;i++){
      for(j=0;j<H;j++){
	fscanf(p3 ,"%lf",&w2[i][j]);
      }
    }

   
    for(i=0;i<N;i++){
      in[i]=pat[k].x[i];
     
    }
      
   
    for(i=0;i<H;i++){
      g_1[i]=0;
      for(j=0;j<N;j++){
	g_1[i]=g_1[i]+w1[i][j]*in[j];
      }

    }
      

    for(i=0;i<H;i++){
      g1[i]=sigmoid(g_1[i]);

    }
      
   
    for(i=0;i<C;i++){
      g_2[i]=0;
      for(j=0;j<H;j++){
	g_2[i]=g_2[i]+w2[i][j]*g1[j];
      }
   
    }
    
  
    for(i=0;i<C;i++){
      g2[i]=sigmoid(g_2[i]);
      if(max<g2[i]){
	max=g2[i];
	max_c=i;
      }
      printf("g2[%d]=%lf\n",i,g2[i]);
    }    
    printf("pn=%d,max_c=%d,max=%lf\n",k,max_c,max); 
    if(max_c==pat[k].c_name){
      count+=1;
    }
  }
  printf("classrate=%.2lf\n",count/P);
}

//シグモイド関数
double sigmoid(double x){
  return 1.0 / (1.0 + exp(-x));
}

