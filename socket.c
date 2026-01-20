#include <stdio.h>  
#include <stdlib.h>  
#include <winsock2.h>
#include <windows.h>     
#include <ws2tcpip.h>
#define PORT 443

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[]) {

    int iResult;
    WSADATA data;
    struct sockaddr_in server;

    printf("Winsock initializing...\n");
    iResult = WSAStartup(MAKEWORD(2, 2), &data);
        if (iResult != 0) {
        printf("WSAStartup failed (Error Code) : %d\n",WSAGetLastError());
        return 1;
    };

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) {
        printf("Socket Creation Failed (Error Code): %d\n",WSAGetLastError());
        WSACleanup();
        return 1;
    };

    printf("Socket Initialized\n");    
        server.sin_addr.s_addr = inet_addr("1.1.1.1");
	    server.sin_family = AF_INET;
	    server.sin_port = htons(PORT);

    if (connect(s , (struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR){
	    printf("Connection failed (Error code) : %d\n", WSAGetLastError());
	    return 1;
    };
    
    printf("Cloudflare responded...");
    closesocket(s);
    WSACleanup();
    return 0;
}
