#include "FullSystem/SemanticReceiver.h"


SemanticReceiver::SemanticReceiver(int port, int max_pairs):max_pairs(max_pairs){
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
    //max_pairs *5(num of nums in datagramm) *2(because data sends in 2 bytes per number)
    buffer = new char [max_pairs*5*2]; //not forget to delete!!!
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
        // std::cout<<"px::python --> ";
        new_objects = false;
        datagramm_array.clear();
        objects.clear();
        
        for(int i = 0; i < max_pairs*5*2; i+=2){
            int res = int((unsigned char)(buffer[i])<<8 | (unsigned char)(buffer[i+1]));
            datagramm_array.push_back(res);
        }
        for(int i = 0; i < max_pairs*5; i+=5){
            objects.push_back(SemanticObject(datagramm_array.at(i),
                                             datagramm_array.at(i+1),
                                             datagramm_array.at(i+2),
                                             datagramm_array.at(i+3),
                                             datagramm_array.at(i+4)));
        }
        new_objects = true;
        std::cout<<std::endl;
    }
}

std::vector<SemanticObject> SemanticReceiver::get_objects(){
    if(new_objects){
        new_objects=false;
        return objects;
    }
    else{
        std::vector<SemanticObject> p;
        return p;
    }
}
        
