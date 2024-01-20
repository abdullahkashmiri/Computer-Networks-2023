//l217512 abdullah dar cn lab 5 q1


/*
        TCP_Client. This Program will implement the Client Side for TCP_Socket Programming.
        It will get some data from user and will send to the server and as a reply from the
        server, it will get its data back.
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr



int isVowel(char* str) {
	int len = strlen(str), i=0;
		for(i=0;i<len;i++){
		if(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'||str[i]=='A'||str[i]=='E'||str[i]=='I'||str[i]=='O'||str[i]=='U')
			return 1;
		} 
	return 0;
} 

char *reverse(char * str) {
if(str == NULL)
return str;
	int len = strlen(str);
	int st = 0;
	int en = len -1;
	while(st<en) {
	char temp = str[st];
	str[st] = str[en];
	str[en] = temp;
	st++;
	en--;
	}
return str;
}

int main(void)
{
        int socket_desc;
        struct sockaddr_in server_addr;
        char server_message[2000], client_message[2000];
        
        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Specifying the IP and Port of the server to connect
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        //Now co

int isVowel(char* str) {
	int len = strlen(str), i=0;
		for(i=0;i<len;i++){
		if(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'||str[i]=='A'||str[i]=='E'||str[i]=='I'||str[i]=='O'||str[i]=='U')
			return 1;
		} 
	return 0;
} 

char *reverse(char * str) {
if(str == NULL)
return str;
	int len = strlen(str);
	int st = 0;
	int en = len -1;
	while(st<en) {
	char temp = str[st];
	str[st] = str[en];
	str[en] = temp;
	st++;
	en--;
	}
return str;
}
        if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
                printf("Connection Failed. Error!!!!!");
                return -1;
        }
        
        printf("Connected\n");
        
        //Get Input from the User
        
        printf("Enter Message: ");
        gets(client_message);                                     //One is that gets() will only get character string data. 
                                                       //		will get only one variable at a time.
																//  reads characters from stdin and loads them into str
        //Send the message to Server
        
        if(send(socket_desc, client_message, strlen(client_message),0) < 0)
        {
                printf("Send Failed. Error!!!!\n");
                return -1;
        }
        
        //Receive the message back from the server
        
        if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Server Message: %s\n",server_message);

	int len = strlen(server_message);
	char *token, *output, str[200] = "";
	token=strtok(server_message," ");
	while(token!= NULL) {
	printf("token %s\n",token);
	if(isVowel(token)==0) 
	{
	output = reverse(token);
	printf("modified token %s\n",output);
	int l = strlen(output);
	//output[l] = ' ';
	strcat(str, output);

	}
	else {
	output = token;
	printf("simple token %s\n",output);
	int l1 = strlen(output);
	//output[l1] = ' ';
	strcat(str, output);

	}
	strcat(str," ");
	
	token= strtok(NULL," ");		
	}
      	printf("str : %s",str);
	
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Closing the Socket
        
        close(socket_desc);
        
        return 0;
}
