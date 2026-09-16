#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int count = 0;

int main(int argc, char *argv[]){

	// display format/usage for user

	if(argc == 1){
		printf("format: ./nxping [ip address] [port]\n");
		exit(0);
	}

	// if input is detected as being 1 CLI argument short or too many of them

	else if(argc == 2 || argc > 3){
		printf("too many/little CLI arguments. type './nxping' for help on how to use nxping.\n\n");
		exit(1);
	}

	else{

	int port = atoi(argv[2]);

	// create socket
	int socket_thing;
	socket_thing = socket(AF_INET, SOCK_STREAM, 0);

	// specifying address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	int pton_result = inet_pton(AF_INET, argv[1], &server_address.sin_addr);

	if(pton_result == 0){
		printf("invalid IP address");
		exit(1);
	}

	else if(pton_result < 0){
		perror("inet_pton");
		exit(1);
	}

	// connection
	
	int connection = connect(socket_thing, (struct sockaddr *) &server_address, sizeof(server_address));

	if(connection != -1){
		printf("connection established at %s at port %s, seq=%d\n", argv[1], argv[2], count);
		count++;
	}

	else{
		printf("Connection failed.");
		exit(1);
	}

      }

	return 0;
}
