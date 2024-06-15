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
    coordinate_gps lat0;
    coordinate_gps longitude;
    coordinate_gps lon0;
    float velocity;
    float cog; //   course over ground
} GPS;

#endif // GPS_H
