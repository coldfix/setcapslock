#include <stdio.h>

#include <strings.h>

#include <X11/Xlib.h>
#include <X11/XKBlib.h>

#define CAPSLOCK 2


void setcaps(int on)
{
   Display* display = XOpenDisplay(NULL);
   XkbLockModifiers(display, XkbUseCoreKbd, CAPSLOCK, on ? CAPSLOCK : 0);
   XCloseDisplay(display);
}


void usage(const char* program_name)
{
    printf("Usage: %s [on|off]\n\n", program_name);
    printf("Use '%s' to disable your caps key");
}


int main(int argc, char** argv)
{
    if (argc > 2) {
        usage(argv[0]);
        return 1;
    }

    int on = 1;
    if (argc == 2) {
        if (strcasecmp(argv[1], "on") == 0) {
            on = 1;
        }
        else if (strcasecmp(argv[1], "off") == 0) {
            on = 0;
        }
        else {
            usage(argv[0]);
            return 1;
        }
    }

    setcaps(on);
    return 0;
}
