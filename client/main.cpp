#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <istream>
#include <vector>
#include <iterator> //for spliting
#include <cstring> //for spliting
#include <sstream> //for spliting
#define DEFAULTHOSTNAME "127.0.0.1"
#define DEFAULTPORT "12105"
#define USER "USER> "


//Function Declarations
int connectToServer(char *hostName, char *port, int &mySocket);
std::string loginRPC();
std::string registrationRPC();
std::string sendRPC(int socket, std::string RPC);
std::string disconnectRPC(int & sock);
std::vector<std::string> splitBuffer(std::string buffer);


//struct to allow tokenized STL splitting of strings by multiple delimiters
struct tokens : std::ctype<char>
{
    tokens() : std::ctype<char>(get_table()) {}

    static std::ctype_base::mask const* get_table()
    {
        typedef std::ctype<char> cctype;
        static const cctype::mask *const_rc = cctype::classic_table();

        static cctype::mask rc[cctype::table_size];
        std::memcpy(rc, const_rc, cctype::table_size * sizeof(cctype::mask));

        //splits on = and ;, follow same format for additional delimiters.
        rc['='] = std::ctype_base::space;
        rc[';'] = std::ctype_base::space;

        return &rc[0];
    }
};

void ctrlC() {
    std::cout << "CTRL + C"<< std::endl;
}

bool checkPwdFormat(std::string input) {
    bool lowerLetter = false;
    bool upperLetter = false;
    bool digit = false;
    if (input.size() < 8) {
        return false;
    }
    for (char c : input) {
        if (c >= 97 && c <= 122) {
            lowerLetter = true;
        } else if (c >= 65 && c <= 90) {
            upperLetter = true;
        } else if (c >= 48 && c <= 57) {
            digit = true;
        } else{
            return false;
        }
    }
    return lowerLetter && upperLetter && digit;
}


//MAIN
int main(int argc, char const *argv[]) {
    int mySocket = 0;
    std::string serverReply;

    //use Defualt Hostname and port
    if (argc < 3) {
        printf("%sConnecting to IP: 127.0.0.1 | Port: 12105\n", USER);
        if (connectToServer((char *)DEFAULTHOSTNAME, (char *)DEFAULTPORT, mySocket) != -1) {
            serverReply = sendRPC(mySocket, loginRPC());

            std::vector<std::string> reply = splitBuffer(serverReply);

            while (reply[0] != "reply" || reply[1] != "success") {
                std::cout << reply[2] << ": ";
                for (int i = 3; i < (int) reply.size(); i++) {
                    std::cout << reply[i] << " ";
                }
                std::cout << std::endl;

                serverReply = sendRPC(mySocket, registrationRPC());
                reply = splitBuffer(serverReply);
                if (reply[0] != "reply" || reply[1] != "success") {
                    std::cout<<"Do you wish to Register for as an new user? (y/N)"<<std::endl;
                    std::string answer;
                    std::cin >> answer;
                    if (answer == "y") {
                        serverReply = sendRPC(mySocket, registrationRPC());
                        reply = splitBuffer(serverReply);
                    } else {
                        disconnectRPC(mySocket);
                    }
                    std::cout<<answer<<std::endl;

                }
            }

            std::cout << USER << "Login accepted!\n";

            char threadReply[1024] = { 0 };
            std::string message;

            while(true) {
                std::getline(std::cin, message);
                std::cout << sendRPC(mySocket, message) << std::endl;
            }

            read(mySocket, threadReply, 1024);
            std::cout << "Recieved: " << std::string(threadReply) << std::endl; //debug reply from server
            threadReply[1024] = { 0 };

            read(mySocket, threadReply, 1024);
            std::cout << "Recieved: " << std::string(threadReply) << std::endl; //debug reply from server
            threadReply[1024] = { 0 };

            read(mySocket, threadReply, 1024);
            std::cout << "Recieved: " << std::string(threadReply) << std::endl; //debug reply from server
            threadReply[1024] = { 0 };

            /*
            // Get a random number for the waiting time
            srand((unsigned int)time(NULL));
            int waitingTime = (rand() % 10) + 1;
            std::cout << USER << "Waiting Time: " << waitingTime << " seconds" << std::endl;

            // Wait for few seconds
            sleep(waitingTime);*/

            // Run the disconnectRPC function
            disconnectRPC(mySocket);
            std::cout << std::endl;
        }
    }
        //use specified hostname and port
    else {
        printf("%sConnecting to IP: %s | Port: %s\n", USER,
               std::string(argv[1]).c_str(), std::string(argv[2]).c_str());
        if (connectToServer((char *)argv[1], (char *)argv[2], mySocket) != -1) {
            serverReply = sendRPC(mySocket, loginRPC());

            std::vector<std::string> reply = splitBuffer(serverReply);

            while (reply[0] != "reply" || reply[1] != "success") {
                std::cout << reply[2] << ": ";
                for (int i = 3; i < (int)reply.size(); i++) {
                    std::cout << reply[i] << " ";
                }
                std::cout << std::endl;

                serverReply = sendRPC(mySocket, loginRPC());
                reply = splitBuffer(serverReply);
                if (reply[0] != "reply" || reply[1] != "success") {
                    std::cout << "Do you wish to Register for as an new user? (y/N)" << std::endl;
                    std::string answer;
                    std::cin >> answer;
                    if (answer == "y") {
                        serverReply = sendRPC(mySocket, registrationRPC());
                        reply = splitBuffer(serverReply);
                    } else {
                        disconnectRPC(mySocket);
                    }
                }
            }

            // Get a random number for the waiting time
            srand((unsigned int)time(NULL));
            int waitingTime = (rand() % 10) + 1;
            std::cout << USER << "Waiting Time: " << waitingTime << " seconds" << std::endl;

            // Wait for few seconds
            sleep(waitingTime);

            // Run the disconnectRPC function
            disconnectRPC(mySocket);
            std::cout << std::endl;
        }
    }

    return 1;
}


//Function Definitions
/**
 * This is a function to generate the login RPC for the server.
 *
 * OUTPUT: login RPC as a string
 * Generated RPC format="rpc=connect;username=<Your user>;password=<Your password>;"
*/
std::string registrationRPC() {
    std::string RPC = "rpc=connect;";
    std::string username, password;
    //Collect login info
    std::cout << USER << "Enter username with minimum length of 6: ";
    getline(std::cin, username);
    while(username.size()< 6) {
        std::cout << USER << "Re-enter username: ";
        getline(std::cin, username);
    }
    std::cout << USER << "Enter password with minimum length of 8 \n including an upper case letter, \n a lower case letter, and an number: ";
    getline(std::cin, password);
    while(!checkPwdFormat(password)) {
        std::cout << USER << "Re-enter password: ";
        getline(std::cin, password);
    }

    //generate RPC from log in info
    RPC += "username=!" + username + ";password=" + password + ";";
    //std::cout << "loginRPC() generated: " << RPC << std::endl; //debug RPC generator

    return RPC;
}

/**
 * This is a function to generate the login RPC for the server.
 *
 * OUTPUT: login RPC as a string
 * Generated RPC format="rpc=connect;username=<Your user>;password=<Your password>;"
*/
std::string loginRPC() {
    std::string RPC = "rpc=connect;";
    std::string username, password;

    //Collect login info
    std::cout << USER << "Enter username: ";
    getline(std::cin, username);
    std::cout << USER << "Enter password: ";
    getline(std::cin, password);

    //generate RPC from log in info
    RPC += "username=" + username + ";password=" + password + ";";
    //std::cout << "loginRPC() generated: " << RPC << std::endl; //debug RPC generator

    return RPC;
}

/**
 * This is a function to send RPCs to the server and read their reply
 *
 * Input: int socket to send/recieve messages
 * Input: string RPC message to send
 * Output: returns the reply from the server as a string
 * output format = "reply=<fail or success>;error=<error or null>

*/
std::string sendRPC (int socket, std::string RPC) {
    char reply[1024] = { 0 };

    ssize_t status;
    status = send(socket, RPC.c_str(), RPC.size() + 1, 0);
    if(status == -1) {
        std::cout << status << "Send Error" << std::endl;
    }
    //std::cout << "Sent " << RPC << " to " << socket << std::endl; //debug send to server

    status = read(socket, reply, 1024);
    if(status == -1){
        std::cout << status << "Read Error" << std::endl;
    }
    //std::cout << "Recieved: " << reply << std::endl; //debug reply from server

    return std::string(reply);
}

/**
 * This is a function to disconnect from the Server and close the socket
 * This is a special case were no additional communication will be possible.
 *
 * INPUT: Reference to open socket
 * Generated RPC format="rpc=disconnect"
 *
 * OUTPUT: returns the reply from the server as a string
 * output format="status=<error status>;error=<error or null>;
*/
std::string disconnectRPC(int & sock) {
    char reply[1024] = { 0 };

    //disconnect RPC
    std::string disconnectMessage = "rpc=disconnect;";

    //Send the disconnect rpc and receive a message from the Server
    std::cout << sendRPC(sock, disconnectMessage) <<std::endl;

    // Close the client socket
    if (true) { //optional logic for reading server reply and performing additional actions before closing socket
        std::cout << "disconnected, socket " << sock << " closed.\n";
        close(sock);
    }

    return std::string(reply);
}

/**
 * This is a function to start a connection with the Server.
*/
int connectToServer(char *hostName, char *port, int &mySocket) {
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons((uint16_t)atoi(port));
    serv_addr.sin_family = AF_INET;


    // Create a socket
    if ((mySocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\nERROR: Socket creation \n";
        return -1;
    }

    // Converts the character string src into a network address structure,
    // then copies the network address structure to dst
    if (inet_pton(AF_INET, hostName, &serv_addr.sin_addr) <= 0) {
        std::cout << "\nERROR: Invalid address/Address not supported \n";
        return -1;
    }

    // Connects the socket to the address specified by addr
    if (connect(mySocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nERROR: Connection Failed \n");
        return -1;
    }

    return mySocket;
}


/**
 * This is a function to split up replies from the server
 *
 * uses the "tokens" struct, and <istream> + <iterator> libs
 * splits on chars defined in the "tokens" struct into a
 * vector of strings
 *
 * Input: String with delimiters
 * Output: Vector of strings, broken on the set delimiters
*/
std::vector<std::string> splitBuffer(std::string buffer) {
    std::stringstream ss(buffer);
    ss.imbue(std::locale(std::locale(), new tokens()));
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vec(begin, end);

    return vec;
}
