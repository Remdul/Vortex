/*Your goal is to connect to port 5842 on vortex.labs.overthewire.org and read in 4 unsigned integers in host byte order.
 * Add these integers together and send back the results to get a username and password for vortex1. This information can
 * be used to log in using SSH.
 */

#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>

using namespace std;

int main()
{
    struct addrinfo hostInfo;
    struct addrinfo *hostInfoList;
    int wasSuccessful;

    memset(&hostInfo, 0, sizeof hostInfo);  // Clear the memory. (getaddrinfo needs it)
    hostInfo.ai_family = AF_UNSPEC;         // IPV4 or IPV6. Don't care.
    hostInfo.ai_socktype = SOCK_STREAM;     // TCP Communications Only

    wasSuccessful = getaddrinfo("vortex.labs.overthewire.org", "5842", &hostInfo, &hostInfoList);
    if (wasSuccessful != 0)
    {
        cout << "Failed at getaddrinfo." << endl;
    }
    cout << "Found: " << wasSuccessful << endl;
    int newSocket;
    newSocket = socket(hostInfoList->ai_family, hostInfoList->ai_socktype, hostInfoList->ai_protocol); // Create new Socket with IPV4/6, TCP, and Protocol (default)
    if (newSocket == -1)
    {
        cout << "Failed to create Socket." << endl;
    }
    wasSuccessful = connect(newSocket, hostInfoList->ai_addr, hostInfoList->ai_addrlen);
    if (wasSuccessful == -1)
    {
        cout << "Failed to Connect." << endl;
    }
    ssize_t bytesReceived;
    char receiveBuffer[1000];
    bytesReceived = recv(newSocket, receiveBuffer,1000,0);
    if (bytesReceived == 0)
    {
        cout << "Server Killed Connection" << endl;
    }
    if (bytesReceived == -1)
    {
        cout << "Receive Error. Ears were clogged. Try again?" << endl;
    }
    cout << "Data Received. Outputting Now." << endl;
    for (int i = 0; i < sizeof(receiveBuffer); i++)
    {
        cout << receiveBuffer[i];
    }
    cout << receiveBuffer << endl;
    freeaddrinfo(hostInfoList);
    close(newSocket);

}
