#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libproc.h>

int main(int argc, char **argv)
{
    int ret;
    long pid;
    char *p;
    char cmdline[PROC_PIDPATHINFO_MAXSIZE];

    errno = 0;

    if (argc < 2) {
        printf("argc is: %d\n", argc);
        return -1;
    }

    pid = strtol(argv[1], &p, 10);

    if ((errno != 0) || *p != '\0' || pid > INT_MAX) {
        printf("PID error!\n");
        return -1;
    }

    if (ret = proc_pidpath(pid, cmdline, sizeof(cmdline)) <= 0) {
        fprintf(stderr, "PID is %d, %s", pid, strerror(errno));
        return errno;
    } else {
        printf("PID: %d, process name is: %s\n", pid, cmdline);
    }

    return 0;
}
