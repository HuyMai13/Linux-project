#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "cs3423p8.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int concCmd (Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt) {
    int i;
    int j;
    int fd;
    pid_t pid;

    for(i=0; i < iCmdCnt; i++) {
        if((pid = fork()) < 0) {
            perror("fork error");
            return -1;
        } else if(pid == 0){ /* child process */
            if(cmdM[i].iStdinRedirectIdx != 0) {
                if((fd = open(tokenM[cmdM[i].iStdinRedirectIdx], O_RDONLY, S_IRUSR)) < 0) {
                    perror("open error");
                    return -1;
                }
                dup2(fd, STDIN_FILENO);
            }
            if(cmdM[i].iStdoutRedirectIdx != 0) {
                if((fd = open(tokenM[cmdM[i].iStdoutRedirectIdx], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0) {
                    perror("open error");
                    return -1;
                }
                dup2(fd, STDOUT_FILENO);
            }

            close(fd);

            if(cmdM[i].iEndIdx > 0) {
                int len = cmdM[i].iEndIdx-cmdM[i].iBeginIdx+2;
                char* argv[len+1];
                for(j=0; j<len; j++)
                    argv[j] = tokenM[cmdM[i].iBeginIdx+j-1];
                argv[len] = NULL;
                execvp(argv[0], argv);
            } else {
                char* argv[2];
                argv[0] = cmdM[i].szCmdNm;
                argv[1] = NULL;
                execvp(argv[0], argv);
            }

            perror("exec error");
            return -1;
        } else { /* parent process */
            fprintf(stderr, "\n%d %d ", getpid(), pid);
            if(cmdM[i].iEndIdx > 0) {
                for(j=cmdM[i].iBeginIdx-1; j <= cmdM[i].iEndIdx; j++) {
                    fprintf(stderr, "%s ", tokenM[j]);
                }
            } else {
                fprintf(stderr, "%s ", cmdM[i].szCmdNm);
            }
            if(i == iCmdCnt-1)
                fprintf(stderr, "\n\n");
        }
    }

    for(i=0; i < iCmdCnt; i++) {
        wait(NULL);
    }

    return 0;
}

int pipeCmd (Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt) {
    int i;
    int j;
    int fd[2];
    int fd1;
    pid_t pid;

    if(pipe(fd) < 0)
        perror("pipe error");
    for(i=0; i < iCmdCnt; i++) {
        if((pid = fork()) < 0) {
            perror("fork error");
            return -1;
        } else if(pid == 0){ /* child process */
            if(cmdM[i].iStdinRedirectIdx != 0) {
                if((fd1 = open(tokenM[cmdM[i].iStdinRedirectIdx], O_RDONLY, S_IRUSR)) < 0) {
                    perror("open error");
                    return -1;
                }
                dup2(fd1, STDIN_FILENO);
            }
            if(cmdM[i].iStdoutRedirectIdx != 0) {
                if((fd1 = open(tokenM[cmdM[i].iStdoutRedirectIdx], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0) {
                    perror("open error");
                    return -1;
                }
                dup2(fd1, STDOUT_FILENO);
            }

            close(fd1);

            if(i == 0) {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            } else {
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
            }

            if(cmdM[i].iEndIdx > 0) {
                int len = cmdM[i].iEndIdx-cmdM[i].iBeginIdx+2;
                char* argv[len+1];
                for(j=0; j<len; j++) {
                    argv[j] = tokenM[cmdM[i].iBeginIdx+j-1];
                }
                argv[len] = NULL;
                execvp(argv[0], argv);
            } else {
                char* argv[2];
                argv[0] = cmdM[i].szCmdNm;
                argv[1] = NULL;
                execvp(argv[0], argv);
            }

            perror("exec error");
            return -1;
        } else { /* parent process */
            fprintf(stderr, "\n%d %d ", getpid(), pid);
            if(cmdM[i].iEndIdx > 0) {
                for(j=cmdM[i].iBeginIdx-1; j<= cmdM[i].iEndIdx; j++)
                    fprintf(stderr, "%s ", tokenM[j]);
            } else {
                fprintf(stderr, "%s ", cmdM[i].szCmdNm);
            }
            if(i == iCmdCnt-1)
                fprintf(stderr, "\n\n");
        }
    }

    close(fd[0]);
    close(fd[1]);

    for(i=0; i < iCmdCnt; i++) {
        wait(NULL);
    }
    return 0;
}
