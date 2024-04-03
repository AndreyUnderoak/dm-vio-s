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

#include "FullSystem/SemanticObject.h"



class SemanticReceiver {
public:
    SemanticReceiver(int port, int max_pairs);
	void run();
	std::vector<SemanticObject> get_objects();
private:
	std::vector<SemanticObject> objects;
	std::vector<int> 			datagramm_array;
    int to_int16(u_int8_t &litle, u_int8_t &big);
	int sockfd;
	struct sockaddr_in servaddr, cliaddr; 
	char* buffer;
	int max_pairs;
	bool new_objects;
};
