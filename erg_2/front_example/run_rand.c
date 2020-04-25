#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
    int i=0;

    srand(time(NULL));
    for (i=0;i < 3; i++)
    {
        printf("%d\n",rand()%1000);
    }
    
}