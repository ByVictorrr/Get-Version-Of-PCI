#include <linux/pci.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "get_fw_v.h"

#define ROM_PATH "/sys/devices/pci0001:80/0001:80:02.0/0001:83:00.0/rom"


int read_erom_hdr(struct erom_img_hdr *hdr, int romfd){
    int ret;
    const int enable = 1;
    uint8_t sig1, sig2;
    if (write(romfd, &enable, sizeof(enable)) == -1){
        fprintf(stderr,"Something went wrong with write! %s\n", strerror(errno));
        return 0;
    }
    lseek(romfd, 0, SEEK_SET);
    if(read(romfd, (void*)hdr, sizeof(*hdr)) == -1){
        fprintf(stderr,"Something went wrong with read()! %s\n", strerror(errno));
        return 0;
    }

    return 1;
}

int main(){
    int romfd;
    struct erom_img_hdr hdr = {0};
    struct erom_img_data dat = {0};
    if((romfd=open(ROM_PATH, O_RDWR))==-1){
        fprintf(stderr, "not able to open ROM_PATH");
    }
    if(!read_erom_hdr(&hdr, romfd)){
       return -1; 
    }
    read(romfd, &dat, sizeof(dat));
    // next read the pci ds with ptr of header


    return 0;
}