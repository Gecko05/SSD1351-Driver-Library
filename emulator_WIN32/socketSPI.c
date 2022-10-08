#include "socketSPI.h"
#include <stdbool.h>

#define DEFAULT_BUFLEN 512

typedef enum {
    DISCONNECTED,
    CONNECTED,
    SENDING,
    RECEIVING
} SOCKET_STATUS;

typedef enum {
    CONNECT,
    SEND,
    DISCONNECT
} COMMAND;

typedef struct {
    COMMAND command;
    uint8_t *data;
} input;

SOCKET_STATUS STATE = DISCONNECTED;
SOCKET ConnectSocket = INVALID_SOCKET;

WSADATA wsaData;

bool initSocketSPI();
bool sendDataToSocket(uint8_t* dataBytes, uint32_t len);
void closeSocketSPI();

SOCKET_STATUS changeState(COMMAND command, uint8_t* data) {
    // switch(command) {
    //     case CONNECT :
    //         if (STATE == DISCONNECTED) {
    //             if (initSocketSPI()) {
    //                 STATE = CONNECTED;
    //             }
    //         }
    //     case SEND :
    //         // Connect if necessary, then continue sending the data
    //         if (STATE == DISCONNECTED) {
    //             if (initSocketSPI()) {
    //                 STATE = CONNECTED;
    //             }
    //         }
    //         if (STATE == CONNECTED) {
    //             STATE = SENDING;
    //             sendByteToSocket(data);
    //             STATE = CONNECTED;
    //         }
    //     case DISCONNECT :
    //         if (STATE == CONNECTED) {
    //             closeSocketSPI();
    //             STATE = DISCONNECTED;
    //         }
    //     default:
    //     break;
    // }
}

void socketSPISendData(uint8_t *dataBytes, uint32_t len) {
    //changeState(SEND, dataByte);
    initSocketSPI();
    sendDataToSocket(dataBytes, len); 
    closeSocketSPI();
}

bool initSocketSPI() {
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return false;
    }

    struct addrinfo *result = NULL, *ptr = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    
    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", "9988", &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return false;
    }

    ptr = result;

    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    // Connect to server.
    iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    // Should really try the next address returned by getaddrinfo
    // if the connect call failed
    // But for this simple example we just free the resources
    // returned by getaddrinfo and print an error message

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return false;
    }
    return true;
}

bool sendDataToSocket(uint8_t* dataBytes, uint32_t len) {
    int recvbuflen = DEFAULT_BUFLEN;

    const char *sendbuf = (char*)dataBytes;

    // Send an initial buffer
    int iResult = send(ConnectSocket, sendbuf, len, 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        //printf("tried: %i len: %i\n", dataBytes[0], len);
        closesocket(ConnectSocket);
        WSACleanup();
        return false;
    }

    //printf("Bytes Sent: %ld\n", iResult);

    // shutdown the connection for sending since no more data will be sent
    // the client can still use the ConnectSocket for receiving data
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return false;
    }
    return true;
}

void closeSocketSPI() {
    closesocket(ConnectSocket);
    WSACleanup();
}