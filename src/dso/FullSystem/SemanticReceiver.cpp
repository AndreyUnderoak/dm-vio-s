#include "FullSystem/SemanticReceiver.h"


SemanticReceiver::SemanticReceiver(int port, int max_pairs):max_pairs(max_pairs){
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

    buffer = new char [max_pairs*2]; //not forget to delete!!!
    memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 

    // Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(port); 

    // Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 


}
void SemanticReceiver::run(){
    while(1){
        int n; 

        socklen_t len = sizeof(cliaddr); //len is value/result 

        n = recvfrom(sockfd, (char *)buffer, 8*max_pairs*2, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len); 
        std::cout<<std::endl;
        // std::cout<<"px::python --> ";
        new_px = false;
        px.clear();
        for(int i = 0; i < 4; i+=2){
            int res = int((unsigned char)(buffer[i])<<8 | (unsigned char)(buffer[i+1]));
            px.push_back(res);
            std::cout<<res<<" ";
        }
        new_px = true;
        std::cout<<std::endl;
    }
}

std::vector<int> SemanticReceiver::get_px(){
    if(new_px){
        new_px=false;
        return px;
    }
    else{
        std::vector<int> p;
        return p;
    }
}
        