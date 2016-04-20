#include <DS1302.h>



DS1302 rtcc;
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  

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
