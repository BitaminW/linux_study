#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

static void child(){
    char *args[] = {"/bin/echo", "hello", NULL};
    printf("I'm child1 my pid is %d.\n", getpid());
    fflush(stdout);
    execve("/bin/echo", args, NULL);
    err(EXIT_FAILURE, "exec() failed");
}

static void parent(pid_t pid_c){
    printf("I'm parent! my pid is %d and the pid of my child is %d.\n", getpid(), pid_c);
    exit(EXIT_SUCCESS);
}

int main(){
    pid_t ret;
    ret = fork();

    if(ret == -1)
        err(EXIT_FAILURE, "fork() failed");
    
    if(ret == 0){
        // fork() 함수가 자식 프로세스에 대해서는 0을 반환하기 때문에, 자식 프로세스는 이곳으로 들어옵니다.
        child();
    }else{
        // fork() 함수가 새로 생성된 자식 프로세스의 PID(>1)를 반환하기 때문에, 부모 프로세스는 이곳으로 들어옵니다
        parent(ret);
    }

    // 위 코드가 실행이 되지 않으면 이 곳에 도달한 것이기 때문에 에러발생
    err(EXIT_FAILURE, "shouldn't reach here");
}
