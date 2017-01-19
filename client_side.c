
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(){

        //Create a socket
        int network_socket;
        network_socket = socket(AF_INET,SOCK_STREAM,0);
                //socket(domain_of_socket,type_of_socket,protocol)
                //AF_INET -- INTERNET SOCKET
                //SOCK_STREAM -- TCP
                //0 -- USING THE DEFAULT TCP SOCKET

        //Specify the address for the socket
        struct sockaddr_in server_address;
        server_address.sin_family=AF_INET; //Type of address the socket is working
        server_address.sin_port=htons(9002); //htons convert the port_number into specified data format which could be understood by the structure.It basically takes the port_number
                                             the socket will connect to.
        server_address.sin_addr.s_addr=INADDR_ANY; //Actual port address i.e IP Address.INADDR_ANY refers to 0.0.0.0

        //To connect the socket
        int connection_status = connect(network_socket,(struct sockaddr *) &server_address,sizeof(server_address)); //Returns 0 if everything is fine.-1 if there exists an error.

        if(connection_status == -1){
                printf("Error in connecting the socket.");
        }

        //Receive data from the server.
        char server_response[250];
        recv(network_socket,&server_response,sizeof(server_response),0);

        //Print out Server's response
        printf("The server sent the data: %s\n",server_response);


        //Close the socket
        close(network_socket);

}
