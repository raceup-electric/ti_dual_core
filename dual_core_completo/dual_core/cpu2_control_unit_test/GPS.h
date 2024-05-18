#ifndef GPS_H
#define GPS_H

typedef struct
{
    float second;
    char minute;
    char hour;
    char day;
    char month;
    short year;
} time_gps;

typedef struct
{
    short grad;
    float minutes;
    char direction;

} coordinate_gps;

typedef struct
{
    time_gps time;
    coordinate_gps latitude;
    coordinate_gps longitude;
    float velocity;
    float cog; //   course over ground
} GPS;


// true if the parsing is successful
char parse_NMEA_buffer(char *buffer, GPS *gps);

// 1 error
char readGPSMessage(char* buffer);

// degree, dec, sec to double
float degreeToFloat(coordinate_gps* coord);

#endif // GPS_H
