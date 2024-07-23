#include <stdio.h>
#include <linux/joystick.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("/dev/input/js0", O_RDONLY);

    char number_of_axes;
	ioctl (fd, JSIOCGAXES, &number_of_axes);

    printf("Number of axes: %d\n", number_of_axes);

    struct js_event e, p;

    while (1) {
        p = e;
        read(fd, &e, sizeof(e));
        if (p.value != e.value) {
            printf("Event value: %u\n", (unsigned int) e.value);
        }
    }

    return 0;
}

