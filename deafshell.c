/*

    Deaf Shell (deafshell). A shell to use for ssh port forwarding.
    Copyright (C) 2010 François Cami <fcamiNSPfedoraprojectNSPorg>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.	If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define TRUE  (0 == 0)
#define FALSE (0 == 1)

const int slpt = 10;
const int strmax = 30;
int loop = TRUE;

void  sighandler(int sig)
{
	 signal(SIGINT, SIG_IGN);		/* ignore SIGINT     */
	 signal(SIGTERM, SIG_IGN);		/* ignore SIGTERM    */
	 loop = FALSE;
	 signal(SIGINT, sighandler);	/* reinstall SIGINT	 */
	 signal(SIGTERM, sighandler);	/* reinstall SIGTERM */
}

int main()
{

	char *username, *hostname, *buffer;
	struct timeval tstart, tstop;
	time_t starttime, stoptime;
	long difft, days, hours, minutes, seconds;

	signal(SIGTERM, sighandler);
	signal(SIGINT,  sighandler);

	hostname = getenv("HOSTNAME");
	username = getenv("USER");

	if (!username)
	{
		fprintf(stderr, "Unknown user name\n");
		exit(EXIT_FAILURE);
	}

	gettimeofday(&tstart, NULL);
	starttime = tstart.tv_sec;
	buffer = malloc(strmax);
	if (strftime(buffer, strmax, "%m-%d-%Y %T", localtime(&starttime)) != 0)
	{
		printf("Deaf Shell started on: %s\n", buffer);
	}

	printf(	"Welcome to %s, %s. Press <Ctrl+C> to exit.\n", hostname, username);

	while (loop == TRUE)
	{
		sleep(slpt);
		printf("#");
		fflush(stdout);
	}

	printf("\n");
	free(buffer);
	gettimeofday(&tstop, NULL);
	stoptime = tstop.tv_sec;
	difft = round(difftime(stoptime, starttime));
	days = difft / (60 * 60 * 24L);
	difft %= 60 * 60 * 24L;
	hours = difft / (60 * 60);
	difft %= 60 * 60;
	minutes = difft / 60 ;
	difft %= 60 ;
	seconds = difft;
	printf("Deaf Shell ran for %lu days, %lu hours, %lu minutes and %lu seconds. Farewell!\n", days, hours, minutes, seconds);
	exit(EXIT_SUCCESS);

}
