#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netpacket/packet.h>

#ifdef __USE_GTK
    #include <gtk/gtk.h>
#endif

char *ether_ntoa(u_char *hwaddr){
    static char str[18];
    snprintf(str,sizeof(str),"%02x:%02x:%02x:%02x:%02x:%02x",hwaddr[0],hwaddr[1],hwaddr[2],hwaddr[3],hwaddr[4],hwaddr[5]);
    return str;
}

char *ip_ntoa(u_int32_t ipaddr){
    u_char *d = (u_char *)&ipaddr;
    static char str[16];
    snprintf(str,sizeof(str),"%d.%d.%d.%d",d[0],d[1],d[2],d[3]);
    return str;
}

void PrintEtherHeader(u_char *buf){
    struct ether_header *eth;
    eth = (struct ether_header *)buf;
    printf("MAC ADDRESS : %17s > ",ether_ntoa(eth->ether_shost));
    printf("%17s | ",ether_ntoa(eth->ether_dhost));
}


void PrintIpHeader(u_char *buf){
    struct iphdr *ip;
    ip= (struct iphdr *)buf;
    printf("IP ADDRESS : %s > ",ip_ntoa(ip->saddr));
    printf("%s | ",ip_ntoa(ip->daddr));
}

#ifdef __USE_GTK
void PrintIpHeaderGTK(u_char *buf){
    struct iphdr *ip;
    ip= (struct iphdr *)buf;
    g_print("IP ADDRESS : %s > ",ip_ntoa(ip->saddr));
    printf("%s | ",ip_ntoa(ip->daddr));
}
#endif

void PrintUdpHeader(u_char *buf){
    struct udphdr *ptr;
    ptr = (struct udphdr *)buf;
    printf("PORT NUMBER : %u > %u |CHECK SUM : %u\n",ntohs(ptr->source),ntohs(ptr->dest),ntohs(ptr->check));
}


void AnalyzeIPpacket(u_char *buf){
    u_char *ptr;
    struct iphdr *ip;
    ptr = buf;
    ptr += sizeof(struct ether_header);
    PrintIpHeader(ptr);
    ip = (struct iphdr *)ptr;
}

#ifdef __USE_GTK
void AnalyzeIPpacketGTK(u_char *buf){
    u_char *ptr;
    struct iphdr *ip;
    ptr = buf;
    ptr += sizeof(struct ether_header);
    PrintIpHeaderGTK(ptr);
    ip = (struct iphdr *)ptr;
}
#endif