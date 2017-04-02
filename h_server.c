#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include<strings.h>
#include<unistd.h>
#include<arpa/inet.h>
#define ERROR -1
#define MAX_CLIENTS 2
#define MAX_DATA 1024
#define BUFFER 1024


int seq(int x,int h) {
    return (x/h)%2;
}
 
int power_of_2(int x) {
    if (x == 1) return 1;
    while (x > 0) {
        if (x == 2) return 1;
        if (x%2 == 1) return 0;
        x /= 2;
    }
    return 1;
}
 
void hamcheck(char *input) {
    int len = strlen(input);
    char temp;
    int red = 0,index = 0,i,j;
    while (pow(2,red) < len) { red++; }
    int check[red];
    int k = 1;
    for (i = 0; i < (len + 1)/2; i++) {
	temp = input[i];
	input[i] = input[len-i];
	input[len-i] = temp;
    }
    while (k <= pow(2,red)+1) {
        int xor = 0;
        for (j=k; j <= len; j++) {
            if (seq(j,k)) {
                xor ^= input[j] - '0';
            }
        }
        check[index++] = xor;
        k*=2;
    }
    for (i = 0; i < red; i++) {
        printf("\n%d ",check[i]);
    }
}

main(int argc, char **argv){
    struct sockaddr_in server;
    struct sockaddr_in client;
    int sock;
    int cli;
    //int ans;
    int sockaddr_len=sizeof(struct sockaddr_in);
    //For receiving
    char f[80];
    //For sending
    char input[BUFFER];

    if((sock=socket(AF_INET,SOCK_STREAM,0)) == ERROR){
        perror("Server Socket");
        exit(-1);
    }

    server.sin_family=AF_INET;
    server.sin_port=htons(atoi(argv[1]));
    server.sin_addr.s_addr=INADDR_ANY;
    bzero(&server.sin_zero,8);

    if((bind(sock,(struct sockaddr *)&server,sockaddr_len)) == ERROR){
        perror("Bind");
        exit(-1);
    }

    if((listen(sock,MAX_CLIENTS)) == ERROR){
        perror("listen");
        exit(-1);
    }

    if((cli=accept(sock,(struct sockaddr *)&client,&sockaddr_len)) == ERROR){
            perror("accept");
            exit(-1);
    }
        read(cli,f,80);
        printf("Data received: %s",f);
        hamcheck(f);
       

    close(sock);

}
