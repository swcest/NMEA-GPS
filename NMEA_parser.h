#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <time.h>
#include <stdlib.h>

extern int hex2int(char *c);
extern int checksum_valid(char *string);
extern int parse_comma_delimited_str(char *string, char **fields, int max_fields);
extern int debug_print_fields(int numfields, char **fields);
extern int OpenGPSPort(const char *devname);
// int SetTime(char *date, char *time);
extern double convertNMEA (const char *string);
