/*
        UDP_Server. This Program will will create the Server side for UDP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/
//21l7512 abdullah dar bscs 5g1 lab 6
#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //// Needed for socket creating and binding
#include <arpa/inet.h> //inet_addr
#include<stdbool.h>

int isNum(char n) {
if( n >='1' && n<='9') {
return 1;
} else {
return 0;
}
}


int main(void)
{
        int socket_desc;
        struct sockaddr_in server_addr, client_addr;
        char server_message[2000], client_message[2000];
        int client_struct_length = sizeof(client_addr);
        char database[100][11];
        int i=0;
        for(i=0;i<100;i++) {
        strcpy(database[i] ,"-");
      
        }
       
        //Cleaning the Buffers
       
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
       
        //Creating UDP Socket
       
        socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
       
        printf("Socket Created\n");
       
        //Binding IP and Port to socket
       
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // bind your socket to localhost only, if you want connect any particular ip you should mention it in INET_ADDR.
       
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
       
        printf("Bind Done\n");
       
        while(1) {
        printf("Listening for Messages...\n\n");
       
        //Receive the message from the client
       
        if (recvfrom(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr*)&client_addr,&client_struct_length) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
 
        printf("Received Message from IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

        printf("Client Message: %s\n",client_message);
      
       
        //YY-AAAA-CI (For check in) (e.g., 12-4159-CI)
       
        char error[2000] = "Please Enter correct format: (Incorrect)-> ";
        char result[2000];
        int len = strlen(client_message);
        
       
        if(len != 10) {
        	strcat(error,client_message);
        	strcpy(server_message, error);
        } else {
        	if(isNum(client_message[0]) == 1 && isNum(client_message[1]) == 1 && isNum(client_message[3]) == 1 && isNum(client_message[4]) == 1 && isNum(client_message[5]) == 1 && isNum(client_message[6]) == 1 && client_message[2] == '-' && client_message[7] == '-' && client_message[8] == 'C' && (client_message[9] =='I' || client_message[9] =='O' )) {
      
        //format is coorrect ;
       char rollNo[7];
       strncpy(rollNo,client_message,7);
       
      //if user is adding
        if(client_message[9] == 'I') {
        
        bool isFound = false;
        //find if already exists
        for(i =0 ;i< 100 ; i++) {
        	if(strcmp(database[i] ,rollNo)==0) {
       		
        		strcpy(result,"You are Already Here : ");
        		strcat(result, rollNo);
        		strcpy(server_message, result);
        		isFound = true;
        		break;
        	}
        }
        //if user is not present
        if(isFound == false) {
  		bool isupdated = false;
        	for(i=0; i< 100; i++) {
        	
        		if(strcmp(database[i] ,"-")==0) {
        			strcpy(database[i], rollNo);
        			strcpy(result,"Welcome Student : ");
        			strcat(result, rollNo);
        			strcpy(server_message, result);
        			isupdated = true;
        			break;
        		}
       
        	}
        //if database is already full
        	if(isupdated == false && isFound == true) {
        		strcpy(result,"[FULL] No more space left for more students : ");
        		
        		strcat(result, rollNo);
        		strcpy(server_message, result);
        		}
        	}
        }
        else if(client_message[9] == 'O') {
        // if user is exiting
        bool isFound = false;
        //find if already exists
       
        	for(i =0 ; i< 100 ; i++) {
        		if(strcmp(database[i] , rollNo)==0) {
        			strcpy(result,"Have a nice Day!! Good Bye Student: ");
        			
        			strcat(result, rollNo);
        			strcpy(server_message, result);
        			strcpy(database[i],"-");
        			isFound = true;
        			break;
        			}
        		}
        //if user is not present
        	if(isFound == false) {
        	       
  			strcpy(result,"You didn't check in today. Contact System Administrator" );
  			strcpy(server_message, result);
        		}
       
        	}
       
        }
        else {
        	
        	
        	strcpy(result,"Format is Incorrect" );
        	strcat(result,client_message);
        	strcpy(server_message, result);
        }
        }
       
       
        printf("\nAll Students Registered are \n");
        for(i=0; i< 100; i++) {
        	if(strcmp(database[i], "-")!=0)  {
        		printf("Student ID: %s\n", database[i]);
        	}
        }

      	printf("\n");
      	
        //Send the message back to client
       
      
       
        if (sendto(socket_desc, server_message, strlen(server_message), 0, (struct sockaddr*)&client_addr,client_struct_length)<0)
        {
                printf("Send Failed. Error!!!!!\n");
                return -1;
        }
       
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        memset(result,'\0',sizeof(result));
        memset(error,'\0',sizeof(error));
        }
        //Closing the Socket
       
        close(socket_desc);
        return 0;      
}
//--


