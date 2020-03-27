#include <stdio.h>
#include <lib.h>
#include <stdlib.h>

int getprocnr(int PID) 
{
    message _msg;
    _msg.m1_i1 = PID;
    return _syscall(MM_PROC_NR, GETPROCNR, &_msg);
}

int main(int argc, char *argv[]) {
    int pid;
    int arg = atoi(argv[1]);

    if (argc != 2) 
    {
        printf("Wrong number of arguments\n");
        return 0;
    }
    
    for (pid = arg; pid <= arg + 10; pid++) {
        int index = getprocnr(pid);
        if (index == -1)
            printf("Syscall returned an error PID:%d Error code:%d\n", pid, errno);
        else
            printf("PID:%d Process index:%d\n", pid, index);
    }

    return 0;
}
