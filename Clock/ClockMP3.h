
//#include "Arduino.h"
//#include "DFRobotDFPlayerMini.h"

bool WaitForIt();
bool SayTime(int hour, int minute, int second, bool Set24H);
bool SayDate(int year, int month, int day);
bool PlayTrack(int Track);
void SetupMP3();
void printDetail(uint8_t type, int value);
bool Play(int folder, int file);

