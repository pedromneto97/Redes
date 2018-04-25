#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char *argv[]) {
    struct sockaddr_in sad;     /* structure to hold server’s IP address */
    int clientSocket;           /* socket descriptor */
    struct hostent *ptrh;       /* pointer to a host table entry   */

    char Sentence[128];
    char modifiedSentence[128];
    char *host;
    int port, n;

    host = argv[1];
    port = atoi(argv[2]);

    clientSocket = socket(PF_INET, SOCK_STREAM, 0); /* create client socket  */

    memset((char *) &sad, 0, sizeof(sad));  /* clear sockaddr structure  */
    sad.sin_family = AF_INET;   /* set family to Internet   */
    sad.sin_port = htons((u_short) port);
    ptrh = gethostbyname(host);   /* convert host name to IP adr */
    memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length);

    /* connect socket to specified server */
    connect(clientSocket, (struct sockaddr *) &sad, sizeof(sad));

    /* get input stream from the user */
    //fgets(Sentence, 128, stdin);

    struct stat st;
    stat(argv[3], &st);
    int t = st.st_size;
    /* send sentence to server */
    n = write(clientSocket, (char *) &t, sizeof(int));
    printf("%d\n", t);

    /*
     * Envia o nome
     */
    printf("%s\n", argv[3]);
    char *nome = strrchr(argv[3], '/');
    printf("%s\n", nome + 1);
    n = write(clientSocket, nome + 1, strlen(nome) + 1);

    FILE *file;
    if ((file = fopen(argv[3], "rb")) != NULL) {
        char buffer[t];
        while (ftell(file) < t) {
            fread(buffer, sizeof(char), t, file);
        }
        write(clientSocket, buffer, t);
        fclose(file);
    }


    /* read line from the server and write the modified sentence to screen*/
//  n=read(clientSocket, modifiedSentence, sizeof(modifiedSentence));
//  if (n >= 0)
//    modifiedSentence[n] = '\0';
//  printf("FROM SERVER: %s\n" , modifiedSentence);

    /* close connection */
    close(clientSocket);
}
