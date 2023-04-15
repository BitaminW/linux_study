#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

static void child(){
    printf("I'm child!! my pid is %d\n", getpid());
    exit(EXIT_SUCCESS); // 자식 프로세스를 종료 시켜준다. 좀비 프로세스 방지
}

static void parent(pid_t pid_c){
    printf("I'm parent!! my pid is %d and the pid of my child is %d\n", getpid(), pid_c);
    exit(EXIT_SUCCESS);
}

int main(){
    pid_t ret;
    
    //fork()는 실패하면 -1, 부모 프로세스에는 새로운 자식 pid가 반환되고, 자식 프로세스에는 0이 반환됨
    ret = fork();
    if(ret == -1) err(EXIT_FAILURE, "fork() faild");
    
    printf("처음 시작 프로세스의 pid: %d\n", getpid());

    if(ret == 0){   // 자식 프로세스라면
        child();
    }else{          
        printf("what is %d\n", ret);
        parent(ret);
    }

    // 여기 까지 온다면 프로세스 생성에 문제가 생겼다는 뜻
    err(EXIT_FAILURE, "shouldn't reach here");
}
