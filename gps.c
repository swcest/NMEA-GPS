#include "NMEA_parser.h"

int main(int argc, char **argv)
{
	int fd;
	char buffer[255];
	int nbytes;
	int i;
	char *field[20];
	int utc_time,  gps_fix, num_satellites;
    double latitude, longitude, altitude;
	double c_latitude, c_longitude, c_altitude;
	

	if ((fd = OpenGPSPort("/dev/ttyS0")) < 0)
	{
		printf("Cannot open GPS port\r\n.");
		return 0;
	}

	do {
		if ((nbytes = read(fd, &buffer, sizeof(buffer))) < 0) {
			perror("Read");
			return 1;
		} else {
			if (nbytes == 0) {
				printf("No communication from GPS module\r\n");
				sleep(1);
			} else {
				buffer[nbytes - 1] = '\0';
				if (checksum_valid(buffer)) {
					if (strncmp(buffer, "$GP", 3) == 0) {

						if (strncmp(&buffer[3], "GGA", 3) == 0) {
							i = parse_comma_delimited_str(buffer, field, 20);
							//debug_print_fields(i,field);
							utc_time = atoi (field[1]);
                            latitude = atof (field[2]);
                            longitude = atof (field[4]);
                            altitude = atof (field[9]);
                            gps_fix = atoi (field[6]);
                            num_satellites = atoi (field[7]);

							c_latitude = convertNMEA(field[2]);
							c_longitude = convertNMEA(field[4]);

							printf("Latitude  : %f, %f\r\n ", c_latitude, c_longitude);
							
    						printf("UTC Time  : %s\r\n",field[1]);
							printf("Latitude  : %s\r\n", field[2]);
							printf("Longitude : %s\r\n", field[4]);
							printf("Altitude  : %s\r\n",field[9]);
							printf("GNSS fix  : %s\r\n",field[6]);
							printf("Satellites: %s\r\n\n",field[7]);
						}
						// if (strncmp(&buffer[3], "RMC", 3) == 0) {
						// 	i = parse_comma_delimited_str(buffer, field, 20);
						// 	//debug_print_fields(i,field);
						// 	printf("Speed     :%s\r\n",field[7]);
						// 	printf("UTC Time  :%s\r\n",field[1]);
						// 	printf("Date      :%s\r\n",field[9]);

						// 	SetTime(field[9],field[1]);
						// }
					}
				}
			}
		}
	} while(1);

	if (close(fd) < 0) {
		perror("Close");
		return 1;
	}

	return (0);
}