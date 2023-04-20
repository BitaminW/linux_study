#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

static void child(){
    char *args[] = {"/bin/echo", "hello", NULL};
    printf("I'm child1 my pid is %d.\n", getpid());
}
