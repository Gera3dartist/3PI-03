
#include <time.h> 
#include <stdio.h> 

int main() {
    const char *time_details = "2021/06/20 16:35:12";
    struct tm *tm;
    strptime(time_details, "%YYYY-%MM-%DD %H:%M:%S", tm);
    time_t t = mktime(&tm);  // t is now your desired time_t
    // timeinfo = localtime(&t);
    printf ("Current local time and date: %s", asctime(tm));
    return 0;
}