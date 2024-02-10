#pragma once

// Server side implementation of UDP client-server model 
#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include <vector>



class SemanticReceiver {
public:
    SemanticReceiver(int port, int max_pairs);
	void run();
	std::vector<int> get_px();
private:
    std::vector<std::vector<int>> pairs;
	std::vector<int> px;
    int to_int16(u_int8_t &litle, u_int8_t &big);
	int sockfd;
	struct sockaddr_in servaddr, cliaddr; 
	char* buffer;
	int max_pairs;
	bool new_px;
};