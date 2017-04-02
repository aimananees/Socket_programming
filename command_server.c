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

main(int argc, char **argv){
	struct sockaddr_in server;
	struct sockaddr_in client;
	int sock;
	int cli;
	FILE *fp;
	//int ans;
	int sockaddr_len=sizeof(struct sockaddr_in);
	
	char s[80],f[80], command[80];
	strcpy(f, "temp.txt") ;

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
	printf("\n client connected");
  read(cli,command,80);
  printf("\n name of the command: %s\n",command);
  strcat(command, " > ") ;
  strcat(command, f) ;
  system(command) ;
  fp=fopen(f,"r");
  printf("\n name of the file: %s",f);
  while(fgets(s,80,fp)!=NULL){
    //      printf("%s",s);
      write(cli,s,sizeof(s));
  }
  close(cli);
  fclose(fp);
}