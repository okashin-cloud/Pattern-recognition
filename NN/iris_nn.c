#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 5 //入力層の要素数
#define H 7 //中間層の要素数
#define C 3 //クラス数(出力層の要素数)
#define P 140 //パターン数


struct Pat{                                                       
  int cn; //クラス名                                                         
  double x[N]; //拡張特徴ベクトル                                            
};


double pow(double labels, double x);
double sigmoid(double x);


int main(int argc,char* argv[]){

  int i,j,k;

  struct Pat pat[P];
  FILE *p,*p_2;
  char filename[256];

  double in[N];
  double w1[H][N],w2[C][H];
  double new_w2[C][H];
  double g2_1[C][H],g2_2[C],g2_3[C],g2_4[H];
  double g_1[H],g1[H],g_2[C],g2[C];
  double rho=0.1; 
  double Eo[C], Etotal;
  double labels[P][C];
  double eo[C];


  double temp;
  double e[H];
  double gw[H][N];
  int flag=0,count=0,count_2;
  int total=0;


  p=fopen(argv[1],"r");
  for(i=0;i<P;i++){
    pat[i].x[0]=1.0;
    fscanf(p,"%lf %lf %lf %lf %d",&pat[i].x[1],&pat[i].x[2],&pat[i].x[3],&pat[i].x[4],&pat[i].cn);
    printf("pattern%d : %d %lf %lf %lf %lf %lf\n",i,pat[i].cn,pat[i].x[0],pat[i].x[1],pat[i].x[2],pat[i].x[3],pat[i].x[4]);
  }
  fclose(p);

  for(i=0;i<P;i++){
    for(j=0;j<C;j++){
      if(pat[i].cn==j){
	labels[i][j]=1;
      }
      else{
	labels[i][j]=0;
      }
    }
  }
  
  srand((unsigned)time(NULL));
  for(i=0;i<H;i++){
    for(j=0;j<N;j++){
      w1[i][j]=rand()%9+1;
      w1[i][j]=w1[i][j]/10;
    }
  }
  for(i=0;i<C;i++){
    for(j=0;j<H;j++){
      w2[i][j]=rand()%9+1;
      w2[i][j]=w2[i][j]/10;
    }
  }
  
  while(flag==0){
    for(k=0;k<P;k++){
      total+=1;
      
      
      for(i=0;i<N;i++){
	in[i]=pat[k].x[i]/10;
	
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

      }
      
      Etotal=0;
      for(i=0;i<C;i++){
	Eo[i]=pow(labels[k][i],g2[i]);

	Etotal=Etotal+Eo[i];
      }
    
      
      count_2=0;
      for(i=0;i<C;i++){
	if(fabs(g2[i]-labels[k][i])<0.1){
	  count_2+=1;
	}
	else{
	  count=0;
	}
      }
      if(count_2==C){
	count+=1;
      }
   
      if(count==P){
	flag=1;
	break;
      }
      
         
      for(i=0;i<C;i++){
	g2_2[i]=-(labels[k][i]-g2[i]);
	g2_3[i]=g2[i]*(1-g2[i]);
	eo[i]=g2_2[i]*g2_3[i];
	for(j=0;j<H;j++){
	  g2_4[j]=g1[j];
	  g2_1[i][j]=g2_2[i]*g2_3[i]*g2_4[j];

	}

      }
      
         
      for(i=0;i<C;i++){
	for(j=0;j<H;j++){
	  new_w2[i][j]=w2[i][j]-rho*g2_1[i][j];

	}

      }
      
      for(i=0;i<H;i++){
	temp=0;
	for(j=0;j<C;j++){
	  temp=temp+eo[j]*w2[j][i];
	}
	e[i]=temp*g1[i]*(1-g1[i]);

      }
      
      for(i=0;i<C;i++){
	for(j=0;j<H;j++){
	  w2[i][j]=new_w2[i][j];
	}
      }
      
         
      for(i=0;i<H;i++){
	for(j=0;j<N;j++){
	  gw[i][j]=e[i]*in[j];

	}

      }
      
       
      for(i=0;i<H;i++){
	for(j=0;j<N;j++){
	  w1[i][j]=w1[i][j]-rho*gw[i][j];

	}

      }
    }
  }

  p_2=fopen("iris_wlast.dat","w");
  for(i=0;i<H;i++){
    for(j=0;j<N;j++){
      fprintf(p_2,"%lf ",w1[i][j]);
    }
    fprintf(p_2,"\n");
  }
  fclose(p_2);
  p_2=fopen("iris_ulast.dat","w");
  for(i=0;i<C;i++){
    for(j=0;j<H;j++){
      fprintf(p_2,"%lf ",w2[i][j]);
    }
    fprintf(p_2,"\n");
  }
  fclose(p_2);
}

//最小二乗誤差関数
double pow(double t, double x){
  return pow(x-t,2)/2;
}

//シグモイド関数
double sigmoid(double x){
  return 1.0 / (1.0 + exp(-x));
}

