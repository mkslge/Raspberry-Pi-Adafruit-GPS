#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

//This function converts data from DMM format to degrees
double convertToDecimalDegrees(char *dmm) {
    int degrees;
    double minutes;
    char temp[10];  //temp string for minutes
    int negative = 0;
    if (dmm[0] == '-' || dmm[0] == '+') {
        //handles negative values (Southern hemisphere or Western longitude)
        degrees = atoi(dmm + 1); //skip -/+ sign
        negative = 1; //set negative to true
    } else {
        degrees = atoi(dmm); //normal positive case
    }

    //handle the minutes after degrees
    strncpy(temp, dmm + (dmm[0] == '-' || dmm[0] == '+' ? 4 : 2), 9); //get the minutes
    temp[9] = '\0'; //cut off minutes
    minutes = atof(temp);  //convert minutes to float

    //convert to decimal degrees
    return degrees + (minutes / 60.0);
}

int readGPSData(int fd) {
    char buffer[1024];
    ssize_t bytesRead;
    char *lineStart, *lineEnd;

    //use select() to wait for data
    fd_set readFDS;
    struct timeval timeout;
    
    FD_ZERO(&readFDS);
    FD_SET(fd, &readFDS);
    
    timeout.tv_sec = 1;  //set timeout to 1 second
    timeout.tv_usec = 0;
    
    int result = select(fd + 1, &readFDS, NULL, NULL, &timeout);
    if (result == -1) {
        perror("select\n");
        return -1;
    } else if (result == 0) {
        //something bad happened ): aka we had no data streaming for 1 second
        return 0;
    }
    
    //we need to read the data from where the GPS is
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        perror("Read error\n");
        return -1;
    }
    
    buffer[bytesRead] = '\0'; //turn buffer into string

    //only use sentence if its GPGGA or GNRMC
    lineStart = strstr(buffer, "$GPGGA");
    if(lineStart == NULL) {
        lineStart = strstr(buffer, "$GNRMC"); //get start of string
        if(lineStart != NULL) {
            char* longitudeStart = strstr(lineStart, ",N,"); //find start of ,N, coordinates

            if(longitudeStart != NULL) {
                //jump over ,N, that we found
                longitudeStart += 3;
                
                //go through until next comma or EOF
                int idx = 0;
                while (longitudeStart[idx] != ',' && longitudeStart[idx] != '\0') {
                    idx++;
                }
                
                //cut off string
                longitudeStart[idx] = '\0';

                
                //split the string into degrees and minutes
                int degrees = 0;
                double minutes = 0.0;

                //converts the first three digits before the decimal as degrees
                sscanf(longitudeStart, "%3d%lf", &degrees, &minutes);

                //convert to decimal degrees (DDD + MMM/60)
                double decimalDegrees = degrees + (minutes / 60.0);
                
                
                printf("Longitude: %.20lf\n", decimalDegrees);
            }

                char* latitudeStart = strstr(lineStart, ",A,"); //find where ,A, start 
                if(latitudeStart != NULL) {
                    latitudeStart += 3;  //skip past it to find start of coordinates
                    
                    //find end of coordiantes (or EOF)
                    int idx = 0;
                    while (latitudeStart[idx] != ',' && latitudeStart[idx] != '\0') {
                        idx++;
                    }
                    
                    //cut off coordinates at end
                    latitudeStart[idx] = '\0';

                    //split the string into degrees and minutes
                    int degrees = 0;
                    double minutes = 0.0;

                    //convert the first part before the decimal as degrees
                    sscanf(latitudeStart, "%2d%lf", &degrees, &minutes);

                    //convert to decimal degrees (DD + MM/60)
                    double decimalDegrees = degrees + (minutes / 60.0);
                    printf("Latitude: %.20lf\n\n", decimalDegrees);
                }

        }
    }

    return 0;
}

int main() {
    //open GPS port on raspi 5
    int gpsFD = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);
    if (gpsFD == -1) {
        perror("Unable to open serial port\n");
        return -1;
    }

    //infinite loop
    while (1) {
        //repeatedly read gps data
        if (readGPSData(gpsFD) == -1) {
            printf("Error or no fix\n");
            break;
        }
        sleep(1); //buffer for 1 second
    }

    //close our files
    close(gpsFD);
    
    return 0;
}
