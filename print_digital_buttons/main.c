#include <stdio.h>
#include <linux/joystick.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("/dev/input/js0", O_RDONLY);

    char number_of_axes;
	ioctl (fd, JSIOCGAXES, &number_of_axes);

    printf("Number of axes: %d\n", number_of_axes);

    struct js_event e;

    while (1) {
        read(fd, &e, sizeof(e));
        if (e.value == 1) {
            printf("Event type: %u\t Event number: %u\n", (unsigned int) e.type, (unsigned int) e.number);
        }
    }

    return 0;
}

