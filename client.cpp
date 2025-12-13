#include<iostream>
#include<vector>

#include<thread>
#include<chrono>

#include <string.h>
#include <sys/types.h>        
#include <cstdio>          
#include <cstdlib>          
#include <cstring>          
#include <sys/socket.h>     
#include <netinet/in.h>     
#include <arpa/inet.h>      
#include <netdb.h>          
#include <unistd.h>    

#define SERVERPORT "4950"

//Set random values in the arrays- two identical arrays for sorting speed comparison
void setRandomValues(std::
    vector<int> &arr1, int size){
    for (int i = 0; i < size; ++i) {
        // Random numbers between 0 and 9999
        arr1[i] = rand() % 10000;  
    }
}

int main() {
    int sockfd;
	struct addrinfo hints, * serverInfo, * p;

    std::this_thread::sleep_for(std::chrono::seconds(2));

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; 
	hints.ai_socktype = SOCK_STREAM;
	
    int rv;
	if ((rv = getaddrinfo("127.0.0.1", SERVERPORT, &hints, & serverInfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
    // Loop through results and connect
    for (p =  serverInfo; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) {
            perror("socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("connect");
            close(sockfd);
            continue;
        }

        break;
    }

    if (p == NULL) {
		fprintf(stderr, "talker: failed to create socket\n");
		return 2;
	}

    freeaddrinfo(serverInfo);

    std::cout << "Connected to server.\n";
    std::cout << "Client is running..." << std::endl;
    return 0;
    
}