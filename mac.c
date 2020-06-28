int get_mac_addr(char *addr)
{
    int sock, i;
    struct ifreq ifreq;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("create socket error\n");
        goto err;
    }
    strcpy(ifreq.ifr_name, "eth0");
    if(ioctl(sock, SIOCGIFHWADDR, &ifreq)<0) {
        perror("SIOCGIFHWADDR");
        goto err;
    }
    for (i=0; i<6; i++) {
        sprintf(addr+i*2, "%02x", (unsigned char)ifreq.ifr_hwaddr.sa_data[i]);
    }
    return 0;
err:
    return -1;
}
