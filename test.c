#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{
    pid_t p;

    p = fork();
    if (p > 0)
    {
        fork();
        printf("inside\n");
    }
    printf("outside\n");
    return (0);
}
