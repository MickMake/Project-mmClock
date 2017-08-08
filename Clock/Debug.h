// Variadic macros used to print information in de-bugging mode
// from LarryD, Arduino forum
#pragma once

// un-comment these lines to print debugging statements
// #define CLK_DEBUG	// Clock.ino debugging
// #define INIT_DEBUG	// Clock.ino initialization
// #define HTML_DEBUG	// Clock.ino HTML processing
// #define JSON_DEBUG	// Clock.ino JSON processing
// #define WIFI_DEBUG	// Clock.ino WiFi setup
// #define GCAL_DEBUG	// GoogleCal.cpp debugging
// #define MP3_DEBUG	// ClockMP3.cpp debugging
// #define NTP_DEBUG	// ClockNTP.cpp debugging


#ifdef CLK_DEBUG
  #define CLK_PRINT(...)    Serial.print(__VA_ARGS__)
  #define CLK_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
  #define CLK_PRINT(...)
  #define CLK_PRINTLN(...)
#endif

#ifdef INIT_DEBUG
  #define INIT_PRINT(...)    Serial.print(__VA_ARGS__)
  #define INIT_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
  #define INIT_PRINT(...)
  #define INIT_PRINTLN(...)
#endif

#ifdef HTML_DEBUG
  #define HTML_PRINT(...)    Serial.print(__VA_ARGS__)
  #define HTML_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
  #define HTML_PRINT(...)
  #define HTML_PRINTLN(...)
#endif

#ifdef JSON_DEBUG
  #define JSON_PRINT(...)    Serial.print(__VA_ARGS__)
  #define JSON_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
  #define JSON_PRINT(...)
  #define JSON_PRINTLN(...)
#endif

#ifdef WIFI_DEBUG
  #define WIFI_PRINT(...)    Serial.print(__VA_ARGS__)
  #define WIFI_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
  #define WIFI_PRINT(...)
  #define WIFI_PRINTLN(...)
#endif

#ifdef GCAL_DEBUG
  #define GCAL_PRINT(...)    Serial.print(__VA_ARGS__)
  #define GCAL_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
  #define GCAL_PRINT(...)
  #define GCAL_PRINTLN(...)
#endif

#ifdef MP3_DEBUG
  #define MP3_PRINT(...)    Serial.print(__VA_ARGS__)
  #define MP3_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
  #define MP3_PRINT(...)
  #define MP3_PRINTLN(...)
#endif

#ifdef NTP_DEBUG
  #define NTP_PRINT(...)    Serial.print(__VA_ARGS__)
  #define NTP_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
  #define NTP_PRINT(...)
  #define NTP_PRINTLN(...)
#endif

