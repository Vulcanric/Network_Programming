#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/* I am Server */
int main(void)
{
	int serversockfd, clientsockfd;
	struct sockaddr_in serveraddress;
	struct sockaddr_in clientaddress;
	char *serverip = "127.0.0.2";

	/* Buffers for receiving data */
	char message[1024] = {0};

	/* Create server socket */
	serversockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* Set address and port number for the server */
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(3000);
	inet_pton(AF_INET, serverip, &serveraddress.sin_addr.s_addr);

	/*  Binds the address to the socket */
	if (bind(serversockfd, &serveraddress, sizeof(serveraddress)) != -1)
		printf("Socket was bound successfully!\n");
	else
		fprintf(stderr, "Failed to bind\n");

	/* Listen for incoming connections by connect() */
	if (listen(serversockfd, 10) != -1)
		printf("Server is listening...\n");

	/* Accept the connection to the server socket */
	socklen_t clientAddressSize = sizeof(clientaddress);
	if ((clientsockfd = accept(serversockfd, &clientaddress, &clientAddressSize)) != -1)
	{
		printf("clientsockfd: %d\n", clientsockfd);
		printf("Connection has been accepted successfully!\nConnection is from %s\n", inet_ntoa(clientaddress.sin_addr));
	}
	else
	{
		printf("Failed to accept incomming connections\n");
		perror("accept");
	}

	/* Receiving data from client */
	printf("%ld bytes were received!\n", recv(clientsockfd, message, 1024, 0));
	printf("clientsockfd: %d\n", clientsockfd);
	printf("%s\n", message);

	return (0);
}
