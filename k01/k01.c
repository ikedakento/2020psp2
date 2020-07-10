#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(double val,double ave,int a);
extern double var_online(double val,double ave,double ave_square,int a);

int main(void)
{
    double val ;
    double var ;
    double ave = 0;
    double ave_square =0;
    int a = 1;
    double b;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;

    printf("input the filename of sample:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    printf("the filename of sample: %s\n",fname);

    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%lf",&val);
        var = var_online(val,ave,ave_square,a);
        ave = ave_online(val,ave,a);
        ave_square = ave_online(val*val,ave_square,a);
        a++;
    }
    
    b = var * (a - 1) / (a - 2);

    printf("sample mean:%.2lf\n",ave);

    printf("sample variance:%.2lf\n",var);
    printf("population mean(estimated):%2lf\n",ave);
    printf("population variance (estimated):%.2lf\n",b);

    
    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }


    return 0;


}

double ave_online(double val,double ave,int a){
    double c;
    c = ave * (a - 1) / a + val / a ;
    return c;
}

double var_online(double val, double ave, double ave_square, int a){
    double d;
    d = ave_square * (a -1) / a+ val * val / a - ave_online(val,ave,a) * ave_online(val,ave,a);
    return d;
}



