#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <strings.h>
#include "dvd.h"

void
usage(void)
{
	printf(
	"Usage: Ndvd -[vhrc] -[x|n n] -[c color] -[s speed]\n"
	"-x n             start at the n-th column\n"
	"-y n             start at the n-th line\n"
	"-c color         change the color of the box\n"
	"   color = green | red | blue | white |\n"
	"          yellow | cyan | magenta | black\n"
	"-s speed         run in custom speed\n"
	"   speed = slow | meduim | fast\n"
	"-v               show the version and misc infos\n"
	"-h               show available commands\n"
	"-r               run in rainbow mode\n"
	"-C               run in corner mode\n"
	);
}

void
version(void)
{
	printf(
	"Ndvd v0.1\n\n"
	);
}

int
main(int argc, char *argv[])
{
	int color = 0;
	int x = 0, y = 0;
	int dx = 1, dy = 1;
	int rainbow;
	int speed = 200000;
	int corner = 0;
	char optchr;

	while ((optchr = getopt(argc, argv, "vc:hrs:x:y:C")) != EOF) {
		switch (optchr) {
		case 'c':
			if (!strcasecmp(optarg, "green"))
				color = COLOR_GREEN;
			else if (!strcasecmp(optarg, "red"))
				color = COLOR_RED;
			else if (!strcasecmp(optarg, "blue"))
				color = COLOR_BLUE;
			else if (!strcasecmp(optarg, "white"))
				color = COLOR_WHITE;
			else if (!strcasecmp(optarg, "yellow"))
				color = COLOR_YELLOW;
			else if (!strcasecmp(optarg, "cyan"))
				color = COLOR_CYAN;
			else if (!strcasecmp(optarg, "magenta"))
				color = COLOR_MAGENTA;
			else if (!strcasecmp(optarg, "black"))
				color = COLOR_BLACK;
			else
				goto fail;
			break;

		case '?':
			usage();
			goto fail;

		case 'v':
			version();
			goto skip;

		case 'h':
			usage();
			goto skip;

		case 'r':
			rainbow = 1;
			break;

		case 's':
			if (!strcasecmp(optarg, "slow"))
				speed = 600000;
			else if (!strcasecmp(optarg, "medium"))
				speed = 200000;
			else if (!strcasecmp(optarg, "fast"))
				speed = 80000;
			break;

		case 'x':
			if (!sscanf(optarg, "%d", &x)) {
				usage();
				goto fail;
			}
			break;

		case 'y':
			if (!sscanf(optarg, "%d", &y)) {
				usage();
				goto fail;
			}
			break;

		case 'C':
			corner = 1;
			break;

		}
	}

	draw(color, x, y, dx, dy, rainbow, speed, corner);

skip:	return 0;

fail:	return 1;
}
