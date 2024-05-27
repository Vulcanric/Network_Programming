#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

/* I am Client */
int main(void)
{
	// Connection variables
	int clientsockfd;
	struct sockaddr_in serveraddress;
	char *serverip = "127.0.0.2";  /* Google's Ip address (South Africa) */

	// Communication variables
	char *message, response[2048] = {0};

	/* Create a Client socket (End-point-> |----| <- serverEnd-point) */
	clientsockfd = socket(AF_INET, SOCK_STREAM, 0);


	/* Setting the address that this client would be connect to (Servers address) */
	serveraddress.sin_port = htons(3000);  // (host to network short) put the byte in the port number in the correct order (Big endian/little endian)
	serveraddress.sin_family = AF_INET;
	// address.sin_addr.s_addr = ip;
	// inet presentation to network (inet_pton) -> Convert Ip to an unsigned integer and put into the pointer to address.sin_addr.s_addr
	inet_pton(AF_INET, serverip, &serveraddress.sin_addr.s_addr);


	if (connect(clientsockfd, &serveraddress, sizeof(serveraddress)) == 0)
		fprintf(stderr, "Connection was successful!\n");
	else
		dprintf(2, "Connection failed");


	/* Sending message and receiving a response */
	message = "GET / HTTP/1.1\r\nUser-Agent: EricsTerminalBrowser/0.1\r\nHost: EricsServer\r\n\r\n";
	printf("%ld bytes sent!\n", send(clientsockfd, message, strlen(message), 0));
	printf("%ld bytes read:\r\n", recv(clientsockfd, response, 2048, 0));
	printf("clientsockfd: %d\n", clientsockfd);
	printf("%s\n", response);
	return (0);
}
