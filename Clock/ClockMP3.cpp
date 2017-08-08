#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

// Import my own headers.
#include "common.h"
#include "Debug.h"
#include "ClockMP3.h"
#include "ClockMP3defs.h"

DFRobotDFPlayerMini myDFPlayer;
HardwareSerial Serial1(1);
HardwareSerial Serial2(2);
//void printDetail(uint8_t type, int value);


bool WaitForIt()
{
	int Response = 0;

	//while(!(myDFPlayer.available() || digitalRead(BUSY_PIN)))
	while(!myDFPlayer.available())
	{
		// MP3_PRINT(digitalRead(BUSY_PIN));
		// myDFPlayer.readState();
		// Response = myDFPlayer.read();
		// MP3_PRINT(" R:"); MP3_PRINT(Response);
		// MP3_PRINT("Z");
		delay(20);
	}
	// MP3_PRINTLN("");

	// MP3_PRINTLN(myDFPlayer.readType());
	// MP3_PRINTLN(myDFPlayer.read());
	myDFPlayer.readState();
	Response = myDFPlayer.readType();
/*
	MP3_PRINT("R: "); MP3_PRINTLN(Response);
	MP3_PRINT("V: "); MP3_PRINTLN(myDFPlayer.read());
	while(Response >= DFPlayerError)
	{
		MP3_PRINT("z");
		delay(10);
		myDFPlayer.readState();
		Response = myDFPlayer.readType();
		MP3_PRINT("Response: "); MP3_PRINTLN(Response);
	}
*/

	if (Response == DFPlayerPlayFinished)
		return(0);
	else
		return(1);
}


bool PlayTrack(int Track)
{
	/*
	MP3_PRINT("Wait:");
	while(!digitalRead(BUSY_PIN))
	{
		MP3_PRINT(".");
	}
	MP3_PRINTLN("");
	*/

	MP3_PRINT("MP3:Track:");
	MP3_PRINTLN(Track);
	myDFPlayer.playMp3Folder(Track);
	return(WaitForIt());
}


bool SayTime(int hour, int minute, int second, bool Set24H)
{
	PlayTrack(vfTheTimeIs);

	if (Set24H)
	{
		for(int index = 0; Hour24[hour][index]; index++)
			PlayTrack(Hour24[hour][index]);
		if (minute)
			for(int index = 0; Numbers[minute][index]; index++)
				PlayTrack(Numbers[minute][index]);
		else
			PlayTrack(vfHundred);
	}
	else
	{
		for(int index = 0; Hour[hour][index]; index++)
			PlayTrack(Hour[hour][index]);
		if (minute)
			for(int index = 0; Numbers[minute][index]; index++)
				PlayTrack(Numbers[minute][index]);
		if (hour > 12)
			PlayTrack(vfPM);
		else
			PlayTrack(vfAM);
	}
}


bool SayDate(int year, int month, int day)
{
	PlayTrack(vfTheDateIs);

	for(int index = 0; Month[month][index]; index++)
		PlayTrack(Month[month][index]);

	for(int index = 0; Numbers[day][index]; index++)
		PlayTrack(Numbers[day][index]);

	// Hackety hack - good for another 83 years!
	PlayTrack(vfTwo);
	PlayTrack(vfThousand);
	PlayTrack(vfAnd);

	for(int index = 0; Numbers[year-2000][index]; index++)
		PlayTrack(Numbers[year-2000][index]);
}


bool Play(int folder, int file)
{
	MP3_PRINT("MP3:Track:");
	MP3_PRINT(folder);
	MP3_PRINT(":");
	MP3_PRINTLN(file);
	myDFPlayer.playFolder(folder, file);
	// return(myDFPlayer.playFolder(folder, file));
}


void SetupMP3()
{
	pinMode(BUSY_PIN, INPUT);
 
	MP3_PRINT(F("MP3:Init"));
	Serial2.begin(9600, SERIAL_8N1, SERIAL2_RXPIN, SERIAL2_TXPIN);
	while (!Serial2)
		MP3_PRINT(".");
	MP3_PRINT("OK ");

	if (!myDFPlayer.begin(Serial2))
	{
		int count = 10;
		while(count--)
		{
			MP3_PRINT(".");
			delay(500);
		}
	}
	MP3_PRINT(F("OK "));
	MP3_PRINTLN(myDFPlayer.readState());
  
	MP3_PRINTLN("MP3:Config");
	myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
	//----Set volume----
	myDFPlayer.volume(30);  //Set volume value (0~30).
	myDFPlayer.outputSetting(true, 31);
	//myDFPlayer.volumeUp(); //Volume Up
	//myDFPlayer.volumeDown(); //Volume Down
  
	//----Set different EQ----
	myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
	//  myDFPlayer.EQ(DFPLAYER_EQ_POP);
	//  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
	//  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
	//  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
	//  myDFPlayer.EQ(DFPLAYER_EQ_BASS);
  
	//----Set device we use SD as default----
	//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_U_DISK);
	myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
	//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_AUX);
	//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SLEEP);
	//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_FLASH);
  
	//----Mp3 control----
	//  myDFPlayer.sleep();     //sleep
	//  myDFPlayer.reset();     //Reset the module
	//  myDFPlayer.enableDAC();  //Enable On-chip DAC
	//  myDFPlayer.disableDAC();  //Disable On-chip DAC
	//  myDFPlayer.outputSetting(true, 15); //output setting, enable the output and set the gain to 15

	//----Read imformation----
	MP3_PRINT("MP3:readState:");
	MP3_PRINTLN(myDFPlayer.readState()); //read mp3 state
	MP3_PRINT("MP3:readVolume:");
	MP3_PRINTLN(myDFPlayer.readVolume()); //read current volume
	MP3_PRINT("MP3:readEQ:");
	MP3_PRINTLN(myDFPlayer.readEQ()); //read EQ setting
	MP3_PRINT("MP3:readFC:");
	MP3_PRINTLN(myDFPlayer.readFileCounts()); //read all file counts in SD card
	MP3_PRINT("MP3:readCFN:");
	MP3_PRINTLN(myDFPlayer.readCurrentFileNumber()); //read current play file number
	MP3_PRINT("MP3:readFCIF:");
	MP3_PRINTLN(myDFPlayer.readFileCountsInFolder(1)); //read fill counts in folder SD:/03
}


void printDetail(uint8_t type, int value)
{
  switch (type) {
    case TimeOut:
      MP3_PRINTLN(F("MP3:Time Out"));
      break;
    case WrongStack:
      MP3_PRINTLN(F("MP3:Stack Wrong"));
      break;
    case DFPlayerCardInserted:
      MP3_PRINTLN(F("MP3:Card Inserted"));
      break;
    case DFPlayerCardRemoved:
      MP3_PRINTLN(F("MP3:Card Removed"));
      break;
    case DFPlayerCardOnline:
      MP3_PRINTLN(F("MP3:Card Online"));
      break;
    case DFPlayerPlayFinished:
      MP3_PRINT(F("MP3:Number:"));
      MP3_PRINT(value);
      MP3_PRINTLN(F("Finished"));
      break;
    case DFPlayerError:
      MP3_PRINT(F("MP3:DFPlayerError:"));
      switch (value) {
        case Busy:
          MP3_PRINTLN(F("Card not found"));
          break;
        case Sleeping:
          MP3_PRINTLN(F("Sleeping"));
          break;
        case SerialWrongStack:
          MP3_PRINTLN(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          MP3_PRINTLN(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          MP3_PRINTLN(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          MP3_PRINTLN(F("Cannot Find File"));
          break;
        case Advertise:
          MP3_PRINTLN(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}


