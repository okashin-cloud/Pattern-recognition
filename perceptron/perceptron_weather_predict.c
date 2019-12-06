#include<stdio.h>
#include<math.h>
#define N 3
#define C 3//クラス数
#define P 8//パターン数

double multi(double x[][N],double w[][N],int p,int c);
int max(double *g);

int main(int argc, char* argv[]){
  double rho = 1.0;
  int i,j,c,p,m;
  int class_decision=1;//クラス判定をする
  int f=0;
  double a;
  double x[P][N];
  double w[C][N];
  double g[C];
  int count=0;

  double g_12[N],g_13[N],g_23[N];//gij(x)=gi(x)-gj(x)
  int class_1=0,class_2=0,class_3=0;//多数決で使う
  double sum=0;
  double pattern_x=-0.8,pattern_y=-0.4;//この座標の天気を予測する


  double s,t,u,q,y;


  FILE *fp;
  FILE *fp2;
  FILE *fp3;

  //重みをファイルに保存するため
  fp=fopen("sample.dat","w");
  fp2=fopen("sample2.dat","w");
  fp3=fopen("sample3.dat","w");

  //学習パターンの座標
  //晴れ
  x[0][0]=1;
  x[0][1]=4.5;
  x[0][2]=8;

  x[1][0]=1;
  x[1][1]=4;
  x[1][2]=3;

  x[2][0]=1;
  x[2][1]=2.5;
  x[2][2]=2.5;
  //曇り
  x[3][0]=1;
  x[3][1]=3;
  x[3][2]=0.3;

  x[4][0]=1;
  x[4][1]=0;
  x[4][2]=0;
  //雨
  x[5][0]=1;
  x[5][1]=-1;
  x[5][2]=-0.5;

  x[6][0]=1;
  x[6][1]=-4;
  x[6][2]=-1;

  x[7][0]=1;
  x[7][1]=-6;
  x[7][2]=-3.5;
  

  //重み 
  w[0][0]=6;
  w[0][1]=2;
  w[0][2]=1;

  w[1][0]=2;
  w[1][1]=1;
  w[1][2]=5;

  w[2][0]=1;
  w[2][1]=6;
  w[2][2]=1;
  //9回更新されなかったら、ループを抜ける
  while(f<8){
    
    for(p=0;p<P;p++){
      
      for(c=0; c < C; c++){
	g[c] = multi(x,w,p,c);
      }
      
      //最大値のクラスを判定   
      m=max(g);
      
      //クラスの決定をする
      if(p<3)
	class_decision=1;
      else if(p<5)
	class_decision=2;
      else
	class_decision=3;
      
      if(m!=class_decision){
	//新しい重み
	
	for(j=0;j<N;j++){
	  w[m-1][j]=w[m-1][j]-rho*x[p][j];
	  
	  w[class_decision-1][j]=w[class_decision-1][j]+rho*x[p][j];
	  f=0;	
	}   
      }
      
      count++;
      f++;         
      if(f==9)
	break;
    } 
    //重みwをファイルに出力
  }      
  for(i=0;i<C;i++){
    for(j=0;j<N;j++){
      if(i==0)
	g_12[j]=w[i][j]-w[i+1][j];//hare-kumori
      else if(i==1)
	g_13[j]=w[i-1][j]-w[i+1][j];//hare-ame
      else
	g_23[j]=w[i-1][j]-w[i][j];//kumori-ame
    }
  }
  
  sum=g_12[0]+g_12[1]*pattern_x+g_12[2]*pattern_y;
  if(sum>0)
    class_1++;
  else
    class_2++;
  
  sum=g_13[0]+g_13[1]*pattern_x+g_13[2]*pattern_y;
  if(sum>0)
    class_1++;
  else
    class_3++;
  
  sum=g_23[0]+g_23[1]*pattern_x+g_23[2]*pattern_y;
  if(sum>0)
    class_2++;
  else
    class_3++;
  
  
  if(class_1>class_2 && class_1>class_3)
    printf("晴れ\n");
  else if(class_2>class_3)
    printf("曇り\n");
  else
    printf("雨\n");

   s=w[0][0]-w[1][0];
     t=w[0][1]-w[1][1];
     u=w[0][2]-w[1][2];
  

     for(q=-5;q<=5;q=q+0.05){
       y=(-t)/u*q+(-s)/u;
       fprintf(fp,"%f %f\n",y,q);
     }

     s=w[1][0]-w[2][0];
     t=w[1][1]-w[2][1];
     u=w[1][2]-w[2][2];

     for(q=-5;q<=5;q=q+0.05){
       y=(-t)/u*q+(-s)/u;
       fprintf(fp2,"%f %f\n",y,q);
     }

     s=w[2][0]-w[0][0];
     t=w[2][1]-w[0][1];
     u=w[2][2]-w[0][2];

     for(q=-5;q<=5;q=q+0.05){
       y=(-t)/u*q+(-s)/u;
       fprintf(fp3,"%f %f\n",y,q);
     }
     

}

double multi(double x[][N],double w[][N],int p,int c){
  
  int i,j;
  double sum=0;
  
  for(i=0;i<N;i++){
    sum=sum+(w[c][i])*(x[p][i]);
  }
  return sum;
}

int max(double *g){

  int c;
  int m=-100;
  int class;

  for(c=0;c<C;c++){
    if(g[c]>m){
      m=g[c];
      class=c+1;
    }
  }
  return class;
}
