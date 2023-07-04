#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/firewire-cdev.h>

int main()
{
    // Open the first FireWire node; should be local
    int fd = open("/dev/fw0", O_RDWR);

    char buf[16*1024], rbuf[4*1024] = {};
    union fw_cdev_event *e = (void *) buf;

    // Allocate the first 2 GiB of address space
    struct fw_cdev_allocate a = {
        .offset = 0, .length = (__u32) 2<<30
    };

    if (ioctl(fd, FW_CDEV_IOC_ALLOCATE, &a) == -1)
    {
        perror("ioctl"); return 1;
    }

    // Wait for read/write requests to the space
    while (read(fd, buf, sizeof(buf)) != -1)
    {
        if (e->common.type == FW_CDEV_EVENT_REQUEST)
        {
            // Respond with rbuf = (0x0, 0x0, ..., length)
            struct fw_cdev_send_response r = {
                .rcode  = RCODE_COMPLETE,
                .handle = e->request.handle,
                .length = e->request.length,
                .data   = (__u64) rbuf
            };

            if (ioctl(fd, FW_CDEV_IOC_SEND_RESPONSE, &r) == -1)
            {
                perror("ioctl"); return 1;
            }
        }
    }

    close(fd);
    return 0;
}
