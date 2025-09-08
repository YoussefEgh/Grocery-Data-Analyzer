#pragma once
#define _USE_MATH_DEFINES
#include <math.h>


double distance(double lat1, double lon1, double lat2, double lon2) {
        // Switch to latidue and longitude in radians
        lat1 = M_PI / 180;
        lon1= M_PI / 180;
        lat2 = M_PI / 180;
        lon2= M_PI / 180;

        double distanceInRadians = 2 * asin(sqrt( pow((sin((lat1 - lat2) / 2)), 2) +  cos(lat1) * cos(lat2) * pow((sin((lon1 - lon2) / 2)), 2)));
        
        // Convert to nautical miles, then multiply by 1.1508 to get regular miles
        return distanceInRadians * 180 * 60 / M_PI * 1.1508;
}