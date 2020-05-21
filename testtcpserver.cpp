#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0); //Creatig Socket
    if (sock == -1)
    {
        cerr << "Error creating socket";
        return -1;
    }

    sockaddr_in sockadd;
    sockadd.sin_family = AF_INET; //IPv4
    sockadd.sin_port = htons(54000); //Binding to port number
    inet_pton(AF_INET, "0.0.0.0", &sockadd.sin_addr);
    if(bind(sock, (sockaddr*)&sockadd, sizeof(sockadd)) == -1)
    {
        cerr << "Unable to bind to either IP or port number";
        return -2;
    }
	
	 if(listen(sock, SOMAXCONN) == -1) //Check if it is listening
    {
        cerr << "Unable to listen";
        return -3;
    }

    sockaddr_in clientsock;
    socklen_t clientSize = sizeof(clientsock);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(sock,(sockaddr*)&clientsock, &clientSize);

    if(clientSocket == -1)
    {
        cerr << "Unable to connect to client";
        return -4;
    }

    close(sock);

    memset(host,0,NI_MAXHOST);
    memset(svc,0,NI_MAXSERV);
    int result = getnameinfo((sockaddr*)&clientsock, sizeof(clientsock), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

    if(result)
    {
      cout << host << "Connected to " << svc << endl;
    }
    else
    {
        inet_ntop(AF_INET, &clientsock.sin_addr, host, NI_MAXHOST);
        cout << host << "Connected to " << ntohs(clientsock.sin_port) << endl;
    }

    char buf[4096];
    while(true)
    {
        memset(buf,0,4096);
        int bytesRecv = recv(clientSocket, buf, 4096,0);
        if(bytesRecv == -1)
        {
            cerr << "Connection issue" << endl;
        }
        if(bytesRecv == 0)
        {
            cout << "Client Disconnected" << endl;
        }

        cout << "Received : " << string(buf,0,bytesRecv) << endl;

        send(clientSocket, &buf, bytesRecv + 1, 0);

  }

    close(clientSocket);
    return 0;
}

