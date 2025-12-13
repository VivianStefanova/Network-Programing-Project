#include"mergeSort.h"
#include<iostream>


#include <WS2tcpip.h>
#include <string.h>
#include <sys/types.h>

#define PORT "4950"




//TO DO- enforce number of threads <= hardware concurrency for user input
int main() {

    
    int listener;

	struct addrinfo hints, * serverInfo, * p;

    //set 0s to hints
    memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

    //get server ip address
    int rv;
	if ((rv = getaddrinfo(NULL, PORT, &hints, &serverInfo)) != 0) {
		fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
		exit(1);
	}
	p = serverInfo;
	// loop through all the results and bind to the first we can
	for(p = serverInfo; p != NULL; p = p->ai_next) {
		if ((listener = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}

		if (p == NULL) {
			fprintf(stderr, "listener: failed to bind socket\n");
			return 2;
		}

		if (bind(listener, p->ai_addr, p->ai_addrlen) == -1) {
			//close(sockfd);
			shutdown(listener, 2);
			perror("listener: bind");
			continue;
		}

		break;
	}

	// server starts listening on socket
	if (listen(listener, SOMAXCONN) == -1) {
		perror("listen");
		exit(3);
	}

    std::cout << "Server is listening on port " << PORT << std::endl;
    std::cout << "Server IP address:" << printf("%s\n", inet_ntoa(((struct sockaddr_in*)p->ai_addr)->sin_addr));

    freeaddrinfo(serverInfo);

    std::cout << "Server is running..." << std::endl;
    return 0;
    
}