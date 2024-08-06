// client
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    // create a soc
    int soc = socket(PF_INET, SOCK_STREAM, 0);

    // configure the socket
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htnos(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter file name: ");
    char fname[50];
    scanf("%s", &fname);

    // send the request
    if (sendto(soc, fname, strlen(fname) + 1, 0, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("Something went wrong sending a request to server!");
    }

    // showing the reponse on the screen
    int readBytes;
    char buffer[50];
    while (readBytes = recvfrom(soc, buffer, sizeof(buffer), 0, NULL, NULL) > 0)
    {
        printf("%s \n", buffer);
    }

    close(soc);
    return 0;
}

// server
int main()
{
    // create a soc
    int soc = socket(PF_INET, SOCK_STREAM, 0);

    // configure the socket
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htnos(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // bind the socket
    bind(soc, (struct sockaddr *)&addr, sizeof(addr));

    struct sockaddr_in client;
    int sizeOfClient = sizeof(client);
    // fname
    char fname[50];
    int n = recvfrom(incomingRequest, fname, sizeof(fname) - 1, 0, (struct sockaddr *)&client, &sizeOfClient);
    fname[n] = '\0';

    int fd = open(fname, O_RDONLY);

    char buffer[50];
    int bytesRead;
    while (bytesRead = read(fd, buffer, sizeof(buffer)) > 0)
    {
        send(incomingRequest, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, sizeOfClient);
    }
    close(fd);
    close(incomingRequest);
    close(soc);

    return 0;
}
