#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <netinet/in.h>
#include <net/if.h> 

int main() {
    int fd;
    struct ifreq ifr;
    char iface[] = "eno1"; // Corrected interface name
    unsigned char *mac;

    // Create socket
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Set up structure for IP address retrieval
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = '\0'; // Ensure null termination

    // Get IP address
    if (ioctl(fd, SIOCGIFADDR, &ifr) == -1) {
        perror("Failed to get IP address");
        close(fd);
        return 1;
    }
    printf("Interface: %s\n", iface);
    printf("IP Address: %s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

    // Get MAC address
    if (ioctl(fd, SIOCGIFHWADDR, &ifr) == -1) {
        perror("Failed to get MAC address");
        close(fd);
        return 1;
    }
    mac = (unsigned char *)&ifr.ifr_hwaddr.sa_data;
    printf("MAC Address: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    close(fd);
    return 0;
}

