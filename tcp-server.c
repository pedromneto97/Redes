#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void main(int argc, char *argv[]) {
    struct sockaddr_in sad;                /* structure to hold server’s IP address */
    struct sockaddr_in cad;                /* structure to hold client’s IP address */
    int welcomeSocket, connectionSocket;   /* socket descriptor      */
    struct hostent *ptrh;
    char clientSentence[128];
    char nome[255];
    char *ic, *is;
    int port, n, alen;

    port = atoi(argv[1]);

    /* create welcoming socket at port and bind a local address */
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

    memset((char *) &sad, 0, sizeof(sad));  /* clear sockaddr structure */
    sad.sin_family = AF_INET;            /* set family to Internet   */
    sad.sin_addr.s_addr = INADDR_ANY;    /* set the local IP address */
    sad.sin_port = htons((u_short) port); /* set the port number      */

    bind(welcomeSocket, (struct sockaddr *) &sad, sizeof(sad));

    /* Specify the maximum number of clients that can be queued */
    listen(welcomeSocket, 10);

    /* Main server loop – accept and handle requests  */
    while (1) {

        /* Wait on welcoming socket for contact by client   */
        connectionSocket = accept(welcomeSocket, (struct sockaddr *) &cad, &alen);
        /*
         * Pega o tamanho do arquivo
         */
        int tam;
        n = read(connectionSocket, &tam, sizeof(int));
        printf("%d\n", tam);
        /*
         * Pega o nome do arquivo
         */
        n = read(connectionSocket, nome, sizeof(nome));
        printf("%s\n\n");

        /*
         * Cria um buffer
         */

        char p_array[tam];
        while (recv(connectionSocket, p_array, sizeof(p_array), 0) > 0) {
            read(connectionSocket, p_array, tam);
        }
        FILE *arq;
        arq = fopen(nome, "wb");
        fwrite(p_array, 1, sizeof(p_array), arq);
        fclose(arq);


        /* write out the result to socket       */
//    n=write(connectionSocket, capitalizedSentence, strlen(capitalizedSentence)+1);
    }
    close(connectionSocket);
}
