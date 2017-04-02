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

void quick_sort(int a[],int l,int u)
{
    int j;
    if(l<u)
    {
        j=partition(a,l,u);
        quick_sort(a,l,j-1);
        quick_sort(a,j+1,u);
    }
}

int partition(int a[],int l,int u)
{
    int v,i,j,temp;
    v=a[l];
    i=l;
    j=u+1;
    
    do
    {
        do
            i++;
            
        while(a[i]<v&&i<=u);
        
        do
            j--;
        while(v<a[j]);
        
        if(i<j)
        {
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
    }while(i<j);
    
    a[l]=a[j];
    a[j]=v;
    
    return(j);
}

main(int argc, char **argv){
	struct sockaddr_in server;
	struct sockaddr_in client;
	int sock;
	int cli;
	//int ans;
	int sockaddr_len=sizeof(struct sockaddr_in);
	//For receiving
	int data[MAX_DATA];


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

		read(cli,data,MAX_DATA);
		int numbers=data[0];
		for(int i=1;i<=numbers;i++){
			printf("%d\n",data[i]);
		}
		quick_sort(data,1,data[0]);

		for(int i=1;i<=numbers;i++){
			printf("%d\n",data[i]);
		}

	close(sock);

}
