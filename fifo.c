#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>     /*used for file handling*/
#include <sys/stat.h>  /*used for mkfifo function*/
#include <sys/types.h> /*when compiled in gcc, mkfifo() has dependency on both types.h and stat.h*/

int main()
{
    char fname[50], buffer[1025];
    int req, res, n, file;
    mkfifo("req.fifo", 0777);
    mkfifo("res.fifo", 0777);
    printf("Waiting for request...\n");
    req = open("req.fifo", O_RDONLY);
    res = open("res.fifo", O_WRONLY);
    read(req, fname, sizeof(fname));
    printf("Received request for %s\n", fname);
    file = open(fname, O_RDONLY);
    if (file < 0)
        write(res, "File not found\n", 15);
    else
    {
        while ((n = read(file, buffer, sizeof(buffer))) > 0)
        {
            write(res, buffer, n);
        }
    }
    close(req);
    close(res);
    unlink("req.fifo");
    unlink("res.fifo");
    return 0;
}
// Client side
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    char fname[50], buffer[1025];
    int req, res, n;
    req = open("req.fifo", O_WRONLY);
    res = open("res.fifo", O_RDONLY);
    if (req < 0 || res < 0)
    {
        printf("Please Start the server first\n");
        exit(-1);
    }
    printf("Enter filename to request:\n");
    scanf("%s", fname);
    write(req, fname, sizeof(fname));
    printf("Received response\n");
    while ((n = read(res, buffer, sizeof(buffer))) > 0)
    {
        write(1, buffer, n);
    }
    close(req);
    close(res);
    return 0;
}