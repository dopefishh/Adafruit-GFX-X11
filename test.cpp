#include <stdio.h>
#include <X11/Xlib.h>
#include "X11_GFX.h"

#include <unistd.h>

int main(void)
{
	Display *display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "error opening display\n");
		exit(1);
	}

	X11_GFX gfx = X11_GFX(display, 100, 100);
	for(int i = 0; i<100; i+=1) {
		gfx.drawLine(1, 1, 99, i, 1);
		gfx.drawLine(1, 1, i, 99, 1);
	}
	sleep(10);
	XCloseDisplay(display);
	return 0;
}
