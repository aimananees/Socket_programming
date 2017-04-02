ude<netinet/in.h>
#include<sys/types.h>
#define SERV_PORT 10000
void main(int argc,char **argv)
{
int i,j;
int c1,c2,c4,c8;
ssize_t n;
FILE *fp;
int s[80],f[80];
struct sockaddr_in serv,clie;
int listfd,connfd,clilen;
listfd=socket(AF_INET,SOCK_STREAM,0);
bzero(&serv,sizeof(serv));
serv.sin_family=AF_INET;
serv.sin_port=htons(SERV_PORT);
bind(listfd,(struct sockaddr *)&serv,sizeof(serv));
listen(listfd,1);
clilen=sizeof(clie);
connfd=accept(listfd,(struct sockaddr *)&clie,&clilen);
printf("\n client connected");
read(connfd,f,80);
printf("\nthe data\n");
for(i=0;i<12;i++)
{
printf("%d",f[i]);
}
c1=(f[11]^f[9]^f[7]^f[5]^f[3]^f[1]);
c2=(f[10]^f[9]^f[6]^f[5]^f[2]^f[1]);
c4=(f[8]^f[7]^f[6]^f[5]^f[0]);
c8=(f[4]^f[3]^f[2]^f[1]^f[0]);
if(!(c1==0&&c2==0&&c4==0&&c8==0))
printf("\nerror bit :%d%d%d%d\n",c8,c4,c2,c1);
else
printf("no error\n");
close(listfd);
}


