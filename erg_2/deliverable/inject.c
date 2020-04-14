#include <stdio.h>

int fork(){
    printf("\nThis time you won't see the second call because fork is prohibited\n\n");
    return 666;
}