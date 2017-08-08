#include <TimeLib.h> 
#include <WiFiUdp.h>

// Import my own headers.
#include "common.h"
#include "Debug.h"

IPAddress timeServer(NTP_SERVER);
unsigned int localPort = NTP_PORT;
const int timeZone = TIMEZONE;

WiFiUDP Udp;

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:                 
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}


time_t getNtpTime()
{
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  NTP_PRINTLN("NTP:Tx");
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 3000)
  {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE)
    {
      NTP_PRINTLN("NTP:Rx");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  NTP_PRINTLN("NTP:NACK");
  return 0; // return 0 if unable to get the time
}


void SetupNTP(void)
{
  NTP_PRINT("NTP:Listen:");
  NTP_PRINTLN(localPort);
  Udp.begin(localPort);
  setSyncProvider(getNtpTime);
  setSyncInterval(NTP_SYNC);
}


void SetSyncEvent(void)
{
	//onNTPSyncEvent(TimeOK);
}


time_t getNow()
{
      return(now() - (timeZone * SECS_PER_HOUR));
}


