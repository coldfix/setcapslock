#include <stdio.h>

#include <strings.h>

#include <X11/Xlib.h>
#include <X11/XKBlib.h>


void set_modifier(int mod, int on)
{
    Display* display = XOpenDisplay(NULL);
    XkbLockModifiers(display, XkbUseCoreKbd, mod, on ? mod : 0);
    XCloseDisplay(display);
}


int get_modifier(int mod)
{
    XkbStateRec xkbState;
    Display* display = XOpenDisplay(NULL);
    XkbGetState(display, XkbUseCoreKbd, &xkbState);
    XCloseDisplay(display);
    return xkbState.locked_mods & mod;
}


void usage(const char* program_name)
{
    printf("Usage: %s (on|off|toggle|get) [MOD]\n\n", program_name);
}


int main(int argc, char** argv)
{
    int mod = LockMask;     // see <X11/X.h>
    int on = -1;

    if (argc == 3) {
        mod = 1<<atoi(argv[2]);
    }

    if (argc >= 2) {
        if (strcasecmp(argv[1], "on") == 0) {
            on = 1;
        }
        else if (strcasecmp(argv[1], "off") == 0) {
            on = 0;
        }
        else if (strcasecmp(argv[1], "toggle") == 0) {
            on = !get_modifier(mod);
        }
        else if (strcasecmp(argv[1], "get") == 0) {
            if (get_modifier(mod)) {
                printf("on\n");
            }
            else {
                printf("off\n");
            }
            return 0;
        }
    }

    if (on == -1) {
        usage(argv[0]);
        return 1;
    }

    set_modifier(mod, on);
    return 0;
}
