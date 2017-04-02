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

char *hamming(char *input,int len) {
    int in_num[len],i;
    for (i=0; i < len; i++) {
        in_num[len-i-1] = input[i] - '0';
    }
    int red = 0,index=0,j;
    index=0;
    while (pow(2,red) < len+red+1) { red++; }
    int hammed[len+red+1];
    for (i=1; i< len+red+1; i++) {
        if (!power_of_2(i)) {
            hammed[i] = in_num[index++];
        }
        else {
            hammed[i] = 0;
        }
    }
    int k = 1;
    while (k < pow(2,red)+1) {
        int xor = 0;
        for (j=k+1; j < len+red+1; j++) {
            if (seq(j,k)) {
                xor ^= hammed[j];
            }
        }
        hammed[k] = xor;
        k*=2;
    }
    char *ans = malloc(sizeof(char) * (len+red+1));
    for (i=len+red;i>0;i--) {
        ans[i] = hammed[i] + '0';
    }
    ans[0] = '\0';
    char *answer = malloc(sizeof(char) * (len+red+1));
    for (i=len+red;i>=0;i--) {
        answer[i] = ans[len+red-i];
    }
    return answer;
}


int main(int argc,char **argv)
{
    int i,j;
    char *input = malloc(sizeof(char)*80);
    struct sockaddr_in remote_server;
    int sock;
    char input[BUFFER];
    char output[BUFFER];
    int len;
    int ans;

    if((sock=socket(AF_INET,SOCK_STREAM,0)) == ERROR){
        perror("socket");
        exit(-1);
    }
    remote_server.sin_family=AF_INET;
    remote_server.sin_port=htons(atoi(argv[2]));
    remote_server.sin_addr.s_addr=inet_addr(argv[1]);
    bzero(&remote_server.sin_zero,8);

    if((connect(sock,(struct sockaddr *)&remote_server,sizeof(struct sockaddr_in))) == ERROR){
        perror("connect");
        exit(-1);
    }
    //Server code ends here and user input starts here
    int red = 0;
    printf("Enter the string: ");
    scanf("%s",input);
    int len = strlen(input);
    while (pow(2,red) < len+red+1) { red++; }
    char *answer = malloc(sizeof(char)*(80));
    answer = hamming(input,len);
    puts(answer);
    //Ends here
    write(sockfd,answer,len+red+1);
    close(sockfd);
    return 0;
}
