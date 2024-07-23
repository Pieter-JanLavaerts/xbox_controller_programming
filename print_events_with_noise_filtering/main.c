#include <stdio.h>
#include <linux/joystick.h>
#include <fcntl.h>
#include <unistd.h>

#define PAST_N 10 // size of past event array

//function to check if e is in pastea
int in(struct js_event pastea[], struct js_event e) { 
    for (int i = 0; i < PAST_N; i++) {
        if (
                pastea[i].value == e.value &&
                pastea[i].type == e.type &&
                pastea[i].number == e.number
           ) {
            return 1;
        }
    }
    return 0;
}

void printe(struct js_event e) {
    printf(
            "{value: %d,\ttype: %u,\tnumber: %u}\n", 
            (unsigned int) e.type, 
            (unsigned int) e.number,
            (int) e.value
          );
}

int is_button_press(struct js_event e) { 
    return e.value == 1;
}

int is_button_release(struct js_event e) { 
    return e.value == 0;
}

int main() {
    int fd = open("/dev/input/js0", O_RDONLY);

    char number_of_axes;
	ioctl (fd, JSIOCGAXES, &number_of_axes);

    printf("Number of axes: %d\n", number_of_axes);

    struct js_event pastea[PAST_N]; //past event array
    int pasti = 0;
    int pasteainit = 0;

    struct js_event e;
    while (1) {
        read(fd, &e, sizeof(e));

        if (is_button_press(e)) { 
            printe(e);
        } else if (is_button_release(e)) { 
            continue;
        } else {
            if (!in(pastea, e)) {
                pastea[pasti].value = e.value;
                pastea[pasti].type = e.type;
                pastea[pasti].number = e.number;

                pasti++;
                pasti %= PAST_N;

                if (pasti == 0) {
                    pasteainit = 1;
                }

                if (pasteainit) {
                    printe(e);
                }
            }
        }
    }

    return 0;
}

