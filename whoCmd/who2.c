#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h> /* the new added item compared to who1.c */

#define SHOWHOST	/* include remote machine on output */

void showtime(long); /* the new added item compared to who1.c */
void show_info (struct utmp*);

int main () {
	struct utmp current_record; /* read info into this variable */
	int utmpfd; /* just a file descriptor */
	int reclen = sizeof(current_record);
	
	if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
		perror(UTMP_FILE); /* UTMP_FILE is in utmp.h */
		exit(1);
	}
	while (read(utmpfd, &current_record, reclen) == reclen) {
		show_info(&current_record);
	}
	close(utmpfd);
	return 0;
}

void show_info (struct utmp* utbufp) {
	if (utbufp->ut_type != USER_PROCESS) return ;
	
	printf("%-8.8s", utbufp->ut_name);
	printf(" ");
	printf("%-8.8s", utbufp->ut_line);
	printf(" ");
	showtime(utbufp->ut_time);	
#ifdef SHOWHOST
	if (utbufp->ut_host[0] != '\0') /* read info into this variable */
		printf("(%s)", utbufp->ut_host);
#endif
	printf("\n");
}

void showtime(long timeval) {
	char* cp = ctime(&timeval);
	printf("%12.12s", cp+4);
}
