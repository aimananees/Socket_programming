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
#define BUFFER 1024

main(int argc,char **argv){

	struct sockaddr_in remote_server;
	int sock;
	int f[BUFFER];
	int output;
	int r1,r2,r4,r8;

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
	int i;
	printf("enter the data\n");
	for(i=0;i<12;i++)
	{
		if(!(i==4||i==8||i==10||i==11))
		scanf("%d",&f[i]);
	}

	r1=(f[9]^f[7]^f[5]^f[3]^f[1]);
	r2=(f[9]^f[6]^f[5]^f[2]^f[1]);
	r4=(f[7]^f[6]^f[5]^f[0]);
	r8=(f[3]^f[2]^f[1]^f[0]);
	f[11]=r1;
	f[10]=r2;
	f[8]=r4;
	f[4]=r8;

	printf("enter the error bit\n");
	scanf("%d",&output);
	if(f[12-output]==1)
	f[12-output]=0;
	else
	f[12-output]=1;
	write(sock,f,sizeof(f));
	printf("data written\n");
	close(sock);

}
