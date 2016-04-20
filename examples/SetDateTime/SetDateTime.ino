#include <DS1302.h>



DS1302 rtcc;
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  ds1302_struct rtc;
int seconds, minutes, hours, dayofweek, dayofmonth, month, year;


  seconds    = 0;
  minutes    = 8;
  hours      = 10;
  dayofweek  = 2;  // Day of week, any day can be first, counts 1...7
  dayofmonth = 15; // Day of month, 1...31
  month      = 4;  // month 1...12
  year       = 2013;

  
  memset ((char *) &rtc, 0, sizeof(rtc));

  rtc.Seconds    = bin2bcd_l( seconds);
  rtc.Seconds10  = bin2bcd_h( seconds);
  rtc.CH         = 0;      // 1 for Clock Halt, 0 to run;
  rtc.Minutes    = bin2bcd_l( minutes);
  rtc.Minutes10  = bin2bcd_h( minutes);

  rtc.h24.Hour   = bin2bcd_l( hours);
  rtc.h24.Hour10 = bin2bcd_h( hours);
  rtc.h24.hour_12_24 = 0; // 0 for 24 hour format
  rtc.Date       = bin2bcd_l( dayofmonth);
  rtc.Date10     = bin2bcd_h( dayofmonth);
  rtc.Month      = bin2bcd_l( month);
  rtc.Month10    = bin2bcd_h( month);
  rtc.Day        = dayofweek;
  rtc.Year       = bin2bcd_l( year - 2000);
  rtc.Year10     = bin2bcd_h( year - 2000);
  rtc.WP = 0;  

  rtcc.setDateTime( (uint8_t *) &rtc);
}

void loop() {
  ds1302_struct rtc;

  rtcc.readDateTime((uint8_t *) &rtc);
char buffer[80];
sprintf( buffer, "Time = %02d:%02d:%02d, ", \
    bcd2bin( rtc.h24.Hour10, rtc.h24.Hour), \
    bcd2bin( rtc.Minutes10, rtc.Minutes), \
    bcd2bin( rtc.Seconds10, rtc.Seconds));
  Serial.print(buffer);

  sprintf(buffer, "Date(day of month) = %d, Month = %d, " \
    "Day(day of week) = %d, Year = %d", \
    bcd2bin( rtc.Date10, rtc.Date), \
    bcd2bin( rtc.Month10, rtc.Month), \
    rtc.Day, \
    2000 + bcd2bin( rtc.Year10, rtc.Year));
  Serial.println( buffer);
  delay(2000);

}
