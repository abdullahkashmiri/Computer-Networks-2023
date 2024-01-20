//21l7512 bscs 5g1 cn lab 7 q2 server .c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>


bool isThreadAvaliable[3];
int currentUsers = 0;

struct thread_struct
{
    int client_s;
    int index;
};

#define MAX_LINE_LENGTH 100

// Function to extract name and cnic from the input string
void extractNameAndCnic(char *input, char *name, char *cnic)
{
    char *token = strtok(input, "/");
    strcpy(name, token);

    token = strtok(NULL, "/");
    strcpy(cnic, token);
}

// Function to compare names and CNICs
bool compareNameAndCnic(char *name1, char *cnic1, char *name2, char *cnic2)
{
   
    // Find the position of the newline character in cnic2
    size_t newlinePos = strcspn(cnic2, "\n");
    if (newlinePos > 0) {
        cnic2[newlinePos - 1] = '\0';
    }
    // Compare names and CNICs
    bool result = (strcmp(name1, name2) == 0) && (strcmp(cnic1, cnic2) == 0);
    return result;
}

// Function to find and update a line in the file
bool findInFile(const char *filename, const char *input)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    char name[MAX_LINE_LENGTH];
    char cnic[MAX_LINE_LENGTH];

    extractNameAndCnic(input, name, cnic);

    char line[MAX_LINE_LENGTH];
    long int file_position = 0;
    bool found = false;

    // Read each line from the file and compare with the input
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char tempName[MAX_LINE_LENGTH];
        char tempCnic[MAX_LINE_LENGTH];

        extractNameAndCnic(line, tempName, tempCnic);

        if (compareNameAndCnic(name, cnic, tempName, tempCnic))
        {
            found = true;
            break;
        }
        file_position = ftell(file);
    }

    fclose(file);

    if (found)
    {
        file = fopen(filename, "r+");

        if (file == NULL)
        {
            perror("Error opening file");
            exit(1);
        }
        fseek(file, file_position, SEEK_SET);

        // Replace the first digit in CNIC with a hyphen
        name[0] = '-';

        // Update the line in the file
        fprintf(file, "%s/%s\n", name, cnic);

        fclose(file);
    }
    else
    {
        printf("Entry not found in the file.\n");
    }

    return found;
}


void *server_work(void *thread_struct)
{
    struct thread_struct *t_st = (struct thread_struct *)thread_struct;
    int client_sock = t_st->client_s;
    int index = t_st->index;
    char server_message[2000], client_message[2000];

    // Cleaning the Buffers
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Receive the message from the client
    if (recv(client_sock, client_message, sizeof(client_message), 0) < 0)
    {
        printf("Receive Failed. Error!!!!!\n");
        currentUsers--;
        isThreadAvaliable[index] = true;
        close(client_sock);
        pthread_exit(NULL);
    }

printf("client : %s", client_message);
 char nameAndCnic[2000];
strcpy(nameAndCnic, client_message);

    // Remove newline character from input
    client_message[strcspn(client_message, "\n")] = 0;

    if (findInFile("Voters_List.txt", client_message))
    {
        printf("Match found in the database.\n");
  

 
if (send(client_sock, "Welcome new Voter, Please select the Sign of you candidate to vote", strlen("Welcome new Voter, Please select the Sign of you candidate to vote"), 0) < 0) {
    printf("Send Failed. Error!!!!!\n");
    currentUsers--;
    isThreadAvaliable[index] = true;
    close(client_sock);
    pthread_exit(NULL);
}

//------------
 
 const char *filename = "Candidates_List.txt";
FILE *file = fopen(filename, "r");

// Check if the file was opened successfully
if (file == NULL) {
    perror("Error opening file");
    return 1;
}

char line[MAX_LINE_LENGTH];

// Read and display each line from the file
while (fgets(line, sizeof(line), file) != NULL) {
    // Remove newline character from the line
    line[strcspn(line, "\n")] = 0;

    

    // Send the message back to the client
    if (send(client_sock, line, strlen(line), 0) < 0) {
        printf("Send Failed. Error!!!!!\n");
        currentUsers--;
        isThreadAvaliable[index] = true;
        close(client_sock);
        pthread_exit(NULL);
    }
 
    sleep(2);
}
 

// Close the file
fclose(file);

 
    strcpy(server_message, "data completed");
    if (send(client_sock, server_message, strlen(server_message), 0) < 0)
    {
        printf("Send Failed. Error!!!!!\n");
        currentUsers--;
        isThreadAvaliable[index] = true;
        close(client_sock);
        pthread_exit(NULL);
    } 

    strcpy(server_message, "data completed");
    if (send(client_sock, server_message, strlen(server_message), 0) < 0)
    {
        printf("Send Failed. Error!!!!!\n");
        currentUsers--;
        isThreadAvaliable[index] = true;
        close(client_sock);
        pthread_exit(NULL);
    } 

    strcpy(server_message, "data completed");
    if (send(client_sock, server_message, strlen(server_message), 0) < 0)
    {
        printf("Send Failed. Error!!!!!\n");
        currentUsers--;
        isThreadAvaliable[index] = true;
        close(client_sock);
        pthread_exit(NULL);
    } 
//-------------



	 // Cleaning the Buffers
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Receive the message from the client
    if (recv(client_sock, client_message, sizeof(client_message), 0) < 0)
    {
        printf("Receive Failed. Error!!!!!\n");
        currentUsers--;
        isThreadAvaliable[index] = true;
        close(client_sock);
        pthread_exit(NULL);
    }
 

 // Strings to be printed to the file
 
    char vote[20];
	strcpy(vote, client_message);

    // File pointer
    FILE *ofile;

    // Open the file in write mode ("w")
    ofile = fopen("output.txt", "w");

    // Check if the file was opened successfully
    if (ofile == NULL) {
        perror("Error opening file");
        return ;  // Return an error code
    }

    // Print strings to the file
    fprintf(ofile, "Name and CNIC: %s\n", nameAndCnic);
    fprintf(ofile, "Vote: %s\n", vote);

    // Close the file
    fclose(ofile);

    printf("Data written to output.txt successfully.\n");


    }
    else
    {
        printf("No match found in the database.\n");
    }

    // Send the message back to the client
    strcpy(server_message, "No match found in the database.");
    if (send(client_sock, server_message, strlen(server_message), 0) < 0)
    {
        printf("Send Failed. Error!!!!!\n");
        currentUsers--;
        isThreadAvaliable[index] = true;
        close(client_sock);
        pthread_exit(NULL);
    }

    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    isThreadAvaliable[index] = true;
    currentUsers--;
    close(client_sock);
    pthread_exit(NULL);
}

int main(void)
{
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
    pthread_t thread[5];
    struct thread_struct thread_st[5];
    int i = 0;
    int a = 0;
    for (a = 0; a < 5; a++)
    {
        isThreadAvaliable[a] = true;
    }

    // Creating Socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0)
    {
        printf("Could Not Create Socket. Error!!!!!\n");
        return -1;
    }

    printf("Socket Created\n");

    // Binding IP and Port to socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Binding
    if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Bind Failed. Error!!!!!\n");
        return -1;
    }

    printf("Bind Done\n");

    while (1)
    {
        // Put the socket into Listening State
        if (listen(socket_desc, 1) < 0)
        {
            printf("Listening Failed. Error!!!!!\n");
            return -1;
        }

        printf("Listening for Incoming Connections.....\n");

        // Accept the incoming Connections
        client_size = sizeof(client_addr);

        client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &client_size);

        if (client_sock < 0)
        {
            printf("Accept Failed. Error!!!!!!\n");
            return -1;
        }

        printf("Client Connected with IP: %s and Port No: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        if (currentUsers < 5)
        {
            currentUsers++;

            for (i = 0; i < 5; i++)
            {
                if (isThreadAvaliable[i] == true)
                {
                    isThreadAvaliable[i] = false;
                    thread_st[i].client_s = client_sock;
                    thread_st[i].index = i;
                    pthread_create(&thread[i], NULL, server_work, (void *)&thread_st[i]);
                    break;
                }
            }
        }
        else
        {
            char server_message[2000], client_message[2000];

            // Cleaning the Buffers
            memset(server_message, '\0', sizeof(server_message));
            memset(client_message, '\0', sizeof(client_message));

            // Receive the message from the client
            if (recv(client_sock, client_message, sizeof(client_message), 0) < 0)
            {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
            }

            printf("Client Message: %s\n", client_message);

            // Send the message back to client
            strcpy(server_message, "Server is FULL");

            if (send(client_sock, server_message, strlen(server_message), 0) < 0)
            {
                printf("Send Failed. Error!!!!!\n");
                return -1;
            }

            memset(server_message, '\0', sizeof(server_message));
            memset(client_message, '\0', sizeof(client_message));

            // Closing the Socket
            close(client_sock);
        }
    }

    // Closing the Socket
    close(socket_desc);

    return 0;
}
