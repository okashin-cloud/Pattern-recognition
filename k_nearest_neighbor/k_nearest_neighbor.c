#include<stdio.h>
#include<stdlib.h>
#define DATA_NUM 15
#define MITI_NUM 6
#define H 5
#define W 5


int main(int argc ,char *argv[]){

  FILE *files,*dataFile,*class2,*class7,*class9,*miti;

  int **data1,**data2;
 int **miti1;
 int pow_2=0,pow_7=0,pow_9=0;
 int **c_2,**c_7,**c_9;
 char *listfile = argv[1],*mitifile=argv[2];
 char fileName[256];

 int i,j,k,s,t,w,h;
 int number=0;
 
 files=fopen(listfile,"r");
 class2=fopen("class_2","w+");
 class7=fopen("class_7","w+");
 class9=fopen("class_9","w+");
 miti=fopen(mitifile,"r");


 c_2=(int**)malloc(H*sizeof(int*));

 for(s=0;s<H;s++){
   c_2[s]=(int*)malloc(W*sizeof(int));
 }

 c_7=(int**)malloc(H*sizeof(int*));

 for(s=0;s<H;s++){
   c_7[s]=(int*)malloc(W*sizeof(int));
 }

 c_9=(int**)malloc(H*sizeof(int*));

 for(s=0;s<H;s++){
   c_9[s]=(int*)malloc(W*sizeof(int));
 }

 for(s=0;s<H;s++){
   for(t=0;t<W;t++){
     c_2[s][t]=0;
     c_7[s][t]=0;
     c_9[s][t]=0;
   }
 }

 for(i = 0; i < DATA_NUM; i++){
   fscanf(files, "%s", fileName); //ファイル名を読み込む
   dataFile = fopen(fileName, "r");
   /*
     データ読み込み
   */

   fscanf(dataFile,"%d %d",&w,&h);
   data1=(int**)malloc(h*sizeof(int*));

   for(s=0;s<h;s++){
     data1[s]=(int*)malloc(w*sizeof(int));
   }

   for(s=0;s<h;s++){
     for(t=0;t<w;t++){
       fscanf(dataFile,"%d ",&data1[s][t]);
     }
   }
   if(i<5){
     for(s=0;s<h;s++){
       for(t=0;t<w;t++){
	 if(data1[s][t]==1)
	   //ファイルに書き込んでいく
	   c_2[s][t]=c_2[s][t]+1;	
       }
     }
   }
   else if(i<10){
     for(s=0;s<h;s++){
       for(t=0;t<w;t++){
	 if(data1[s][t]==1)
	   //ファイルに書き込んでいく
	   c_7[s][t]=c_7[s][t]+1;
       }
     }
   }
   else if(i<15){
     for(s=0;s<h;s++){
       for(t=0;t<w;t++){
	 if(data1[s][t]==1){
	   //ファイルに書き込んでいく
	   c_9[s][t]=c_9[s][t]+1;
	 }
       }
     }
   }
 }
 
 
 for(s=0;s<h;s++){
   for(t=0;t<w;t++){
     fprintf(class2,"%d ",c_2[s][t]);
     fprintf(class7,"%d ",c_7[s][t]);
     fprintf(class9,"%d ",c_9[s][t]);
   }
   fprintf(class2,"\n");
   fprintf(class7,"\n");
   fprintf(class9,"\n");

 }
 fclose(class2);
 fclose(class7);
 fclose(class9);
 
 
 fscanf(miti,"%d %d",&w,&h);
 miti1=(int**)malloc(h*sizeof(int*));
 
 for(s=0;s<h;s++){
     miti1[s]=(int*)malloc(w*sizeof(int));
 }
 
  for(s=0;s<h;s++){
    for(t=0;t<w;t++){
      fscanf(miti,"%d ",&miti1[s][t]);
    }
  }
 
 class2=fopen("class_2","r");
 class7=fopen("class_7","r");
 class9=fopen("class_9","r");




 data1=(int**)malloc(H*sizeof(int*));
 
 for(s=0;s<H;s++){
   data1[s]=(int*)malloc(W*sizeof(int));
 }
 
 
 for(s=0;s<H;s++){
   for(t=0;t<W;t++){
     fscanf(class2,"%d ",&data1[s][t]);
   }
 }
 
 
 for(s=0;s<h;s++){
   for(t=0;t<w;t++){
     pow_2=pow_2+(data1[s][t]-5*miti1[s][t])*(data1[s][t]-5*miti1[s][t]);
   }
 }
 
 for(s=0;s<h;s++){
   for(t=0;t<w;t++){
     fscanf(class7,"%d ",&data1[s][t]);
   }
 }
 for(s=0;s<h;s++){
   for(t=0;t<w;t++){
     pow_7=pow_7+(data1[s][t]-5*miti1[s][t])*(data1[s][t]-5*miti1[s][t]);
   }
 }
 
 for(s=0;s<h;s++){
   for(t=0;t<w;t++){
     fscanf(class9,"%d ",&data1[s][t]);
   }
 }
 for(s=0;s<h;s++){
   for(t=0;t<w;t++){
     pow_9=pow_9+(data1[s][t]-5*miti1[s][t])*(data1[s][t]-5*miti1[s][t]);
   }
 }

 
 if(pow_2<pow_7 && pow_2<pow_9)
   printf("認識結果 %d　距離 %d %d %d\n",2,pow_2,pow_7,pow_9);

 
 
 else if(pow_7<pow_9)
   printf("認識結果 %d 距離 %d %d %d\n",7,pow_2,pow_7,pow_9); 
 
 else
   printf("認識結果 %d 距離 %d %d %d\n",9,pow_2,pow_7,pow_9); 
}




