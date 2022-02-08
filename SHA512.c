#include <stdio.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <signal.h>
#include <errno.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/if_ether.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <openssl/sha.h>


void doSHA512(const char* string, char* mdString)
{
	unsigned char digest[SHA512_DIGEST_LENGTH];

	SHA512((unsigned char*)&string, strlen(string), (unsigned char*)&digest);

	for(int i=0;i<SHA512_DIGEST_LENGTH;i++)
		sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

	printf("SHA512 digest: %s\n", mdString);
}

int main()
{

	char* message = malloc(100);
	scanf("%s", message);

	char* md = malloc(500);
	doSHA512(message, md);

	return 0;
}