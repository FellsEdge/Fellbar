// Debuging

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <X11/Xlib.h>


static Display *dpy;

void
setstatus(char *status) {
	XStoreName (dpy, DefaultRootWindow(dpy), status);
	XSync (dpy, False);
}

void
getbat(char *bat) {
	FILE *fp = fopen("/sys/class/power_supply/BAT0/capacity", "r");
	char buf[16];
	int charge;
	fgets(buf, 16, fp);
	bat[15] = 0;
	fclose(fp);
	if (buf[2] == 10) {
		snprintf(bat, 16, "%c%c%%", buf[0], buf[1]);
	} else {
		snprintf(bat, 16, "%s%%", buf);
	}

}

void gettime (char *str, int buffsize) {
	time_t timet = time(NULL);
	strftime(str, buffsize, "%a %b %d | %H:%M:%S", localtime(&timet));
}

int
main(void)
{
	char status[512];
	char bat[16];
	char time[64];

	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "fellbar cannot open display.\n");
		return 1;
	}

	for (;;sleep(1)) {
		gettime(time, 64);
		getbat(bat);
		snprintf(status, 512, " %s | %s ", time, bat);
		
	
		setstatus(status);
	}
	
	XCloseDisplay(dpy);

	return 0;
}
