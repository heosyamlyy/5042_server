//
// Created by liuyang016 on 5/24/20.
//

#include "server.h"
#include "connection.h"
#include "game.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
using namespace std;
static pthread_t threads[MAXCONNECTION];
volatile int i = 0;

//creates server with default port defined in header
server::server() {
    //default constructor. Nothing fun here
}

//creates server on user specified port
server::server(int port) {
    this->PORT = port;
}

struct tokens : std::ctype<char> {
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
map<string, std::string> mappify(string const& s)
{
    std::map<std::string, std::string> m;

    std::string key, val;
    std::istringstream iss(s);

    while(std::getline(std::getline(iss, key, ':') >> std::ws, val))
        m[key] = val;

    return m;
}

/**
 * This is a function check username and password
 *
 * Search given userName from userPasswordHut file and check the password
 * accordingly
 *
 * INPUT: String userName
 * INPUT: String password
 * OUTPUT: bool true if authorized, else false
*/
bool server::authenticate(std::string userName, std::string password) {
    const char *fileName="../userPasswordHut.txt";
    ifstream paramFile;
    paramFile.open(fileName);
    string line;
    string key;
    map <string, string> valueMap;
    if (paramFile.is_open()) {
        while(getline(paramFile, line)) {
            cout<<line<<endl;
            map <string, string> tempMap = mappify(line);
            for (auto const& s: tempMap) {
                valueMap[s.first] = s.second;
            }
        }
    }
    paramFile.close();

    for (auto const& s : valueMap) {
        cout <<s.first<< "->"<<s.second<<endl;
        if (s.first == userName) {
            if (s.second == password) {
                //cout<< "Login successful!"<<endl;
                return true;
            }
        }
    }
    //cout<<"Incorrect username or password!"<<endl;
    return false;
}

// Usage example: filePutContents("./yourfile.txt", "content", true);
void filePutContents(const string& name, const string& content, bool append = false) {
    ofstream outfile;
    if (append)
        outfile.open(name, ios_base::app);
    else
        outfile.open(name);
    outfile << content<<endl;
}
void registration(string username, string password) {
    string line = username + ": " + password;

    filePutContents("../userPasswordHut.txt", line, true);
}

/**
 * This is a function to handle logging into the server
 *
 * Reads RPC from the client, and performs actions based on it:
 *		connect;<userName>;<password> calls authenticate() to authorize login
 *      all others: report errors back to client
 *
 * INPUT: int socket which is set-up for client communication
 * OUTPUT: bool true if login is successful; else false
*/
bool server::login(int socket) {
    bool bLogin = false;
    //int attempts = 3; //max attempts to login, not implemented
    char buffer[1024] = { 0 };
    ssize_t status;

    status = read(socket, buffer, 1024);
    if(status == -1 || status == 0) {
        std::cout << "Read Error" << status << std::endl;
        close(socket);
        return false;
    }
    printf("%sReply Recieved\n", SERVER);

    std::vector<std::string> clientCommand = splitBuffer(buffer);
    buffer[1024] = { 0 };

    while (!bLogin) {
        if (clientCommand[0] == "rpc") {
            if (clientCommand[1] == "connect") {
                if (authenticate(clientCommand[3], clientCommand[5])) {
                    printf("%sLogin Credentials verified\n", SERVER);

                    std::string reply = "reply=success;error=null";
                    status = send(socket, reply.c_str(), reply.size() + 1, 0);
                    if(status == -1 || status == 0) {
                        std::cout << "Read Error" << status << std::endl;
                        close(socket);
                        return false;
                    }
                    bLogin = true;
                }
                else {
                    printf("%sUserID or Password is wrong\n", SERVER);
                    std::string reply = "reply=fail;error=UserID or Password is wrong";
                    status = send(socket, reply.c_str(), reply.size() + 1, 0);
                    if(status == -1 || status == 0) {
                        std::cout << "Read Error" << status << std::endl;
                        close(socket);
                        return false;
                    }
                }
            }
            else {
                printf("%sUnauthorized command submitted (unrecognized RPC)\n", SERVER);
                std::string reply = "reply=unauthorized;error=Unauthorized command, please log-in and retry";
                send(socket, reply.c_str(), reply.size() + 1, 0);
            }
        }
        else {
            printf("%sUnauthorized command submitted (not an RPC)\n", SERVER);
            std::string reply = "reply=unauthorized;error=unauthorized command, please log-in and retry";
            send(socket, reply.c_str(), reply.size() + 1, 0);
        }

        //attempts--;

        //server ready to get new attempt of username/password
        if (!bLogin/* && attempts > 0*/) {
            status  = read(socket, buffer, 1024);
            if(status == -1 || status == 0) {
                std::cout << "Read Error" << status << std::endl;
                close(socket);
                return false;
            }
            printf("%sReply Recieved\n", SERVER);

            clientCommand = splitBuffer(buffer);
            std::cout << clientCommand[0] << std::endl;
        }
    }
    return bLogin;
}


/**
 * This is a function to start-up the server instance
 *
 * Sets up the server and socket options. Also has logic
 * for running first time set-up options the first time the function
 * is called on an instance.
 *
 * INPUT: Reference to a sockaddr_in struct
 * INPUT: Reference to an int server_fd
*/
void server::serverSetup(struct sockaddr_in &address, int &server_fd){
    int opt = 1;

    if (this->bFirstRun == true) {
        //Do stuff for initial server set-up like read password file
        //into a map, etc
        this->bFirstRun = false;
    }

    // Create socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("ERROR: socket failed");
        exit(EXIT_FAILURE);
    }
    printf("%sGot Socket\n", SERVER);

    // Forcefully attach socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR,
                   &opt, sizeof(opt))) {
        perror("ERROR: setsockopt");
        exit(EXIT_FAILURE);
    }

    //set-up address struct
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attach socket to the port
    printf("%sAbout to bind\n", SERVER);
    if (::bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0) {
        perror("ERROR: bind failed");
        exit(EXIT_FAILURE);
    }

    printf("%sReady, listening for connections\n", SERVER);
    if (listen(server_fd, 3) < 0) {
        perror("ERROR: listen");
        return;
    }

}


/**
 * This is a function to assign sockets to clients
 *
 * sets up a new socket, verifies user by calling the login() function
 * then creates a connection object pointer for that user which contains
 * all the connection info.
 *
 * INPUT: Reference to a sockaddr_in struct
 * INPUT: Reference to an int server_fd
*/
void server::createConnection(struct sockaddr_in &address, int &server_fd) {
    int newSocket; //might need to be dynamically allocated if for multiple users
    int addrlen = sizeof(address);

    connection *newConnection = new connection(0, server_fd, address);

    printf("\n%sWaiting\n", SERVER);
    if ((newSocket = accept(server_fd, (struct sockaddr *) &address,
                            (socklen_t *)&addrlen)) < 0) {
        perror("ERROR: accept");
        exit(EXIT_FAILURE);
    }

    // Accept a new client and generate a new socket for the client
    printf("%sAccepted Connection\n", SERVER);

    if (login(newSocket)) {
        newConnection->setSocket(newSocket);
        //start game using my connection
        newConnection->setThreadNum(i);
        pthread_create(&threads[i++], nullptr, task, (void *) newConnection);
        printf("%sNew connection created\n", SERVER);
    } else {
        delete newConnection;
    }
}

/*pthread_t p1;
//connection *newConnection = new connection(new_socket, server_fd, address);
pthread_create(&p1, nullptr, startTask, nullptr);
printf("%sClosing Game Thread\n", SERVER);
pthread_join(p1, nullptr);
//delete newConnection;
*/

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
std::vector<std::string> server::splitBuffer(std::string buffer) {
    std::stringstream ss(buffer);
    ss.imbue(std::locale(std::locale(), new tokens()));
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vec(begin, end);
    return vec;
}

//Modify this to change server function. In this case it plays a game.
void server::startTask(connection* myConnection) {
    myConnection->setThreadNum(i);
    pthread_create(&threads[i++], nullptr, task, (void *) myConnection);
    printf("%sClosing Game Thread\n", SERVER);
    //pthread_join(p1[myConnection->getThreadNum()], nullptr);
//	myConnection->end();
}

void *server::task(void *arg) {
    connection *myConnection = (connection *) arg;
    printf("%sRunning Game on Thread\n", SERVER);

//	game *newGame = new game(myConnection); // pass in *myConnection
//	newGame->playGame();
//	delete newGame;
    std::string reply = "Ansewr";
    char buffer[1024] = { 0 };
    ssize_t status;

    while(true) {
        status = read(myConnection->getSocket(), buffer, 1024);
        if(status == -1 || status == 0){
            std::cout << status << "Read Error" << std::endl;
            myConnection->closeSocket();
            pthread_exit(NULL);
        } else {
            std::cout << "Successful Read " << status << std::endl;
            status = send(myConnection->getSocket(), reply.c_str(), reply.size() + 1, 0);
            if(status == -1 || status == 0){
                std::cout << status << "Write Error" << std::endl;
                myConnection->closeSocket();
                pthread_exit(NULL);
            }
        }
//        if(std::string(buffer) == "quit") {
//            printf("%sClosing Game Thread\n", SERVER);
//            pthread_exit(NULL);
//            //pthread_join(threads[myConnection->getThreadNum()], nullptr);
//        }
    }
    return nullptr;
}


