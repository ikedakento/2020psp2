#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define mu_a = 170.8;
#define mu_b = 169.7;
#define sigma_a = 5.43;
#define sigma_b= 5.5;

extern double p_stdnorm(double z);

int main(void)
{
    double val;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;
    double L1=1,L2=1;
    double a;
    double b;

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
    a=0;
    b=0;
    a = (val - mu_a) / sigma_a;
    b = (val - mu_b) / sigma_b;
    L1 =L1 * p_stdnorm(a);
    L2 =L2 * p_stdnorm(b);

    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    printf("L_A: %f\n",L1);
    printf("L_B: %f\n",L2);

    return 0;


}

double p_stdnorm(double z){
    return 1 * exp(-z*z/2) / sqrt(2*M_PI);

}

