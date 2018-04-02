/*
 * Time_NTP.pde
 * Example showing time sync to NTP time source
 *
 * This sketch uses the ESP8266WiFi library
 */
 
#include <TimeLib.h> 
#include <time.h> 
#include <WiFi.h>
#include <ESP32WebServer.h>
#include "DFRobot_HT1632C.h" // https://github.com/Chocho2017/FireBeetleLEDMatrix
#include <Thread.h>
#include <ThreadController.h>
#include <ArduinoJson.h>

// Import my own headers.
#include "common.h"
#include "Debug.h"
#include "HTML.h"
#include "ClockNTP.h"
#include "ClockMP3.h"
#include "GoogleCal.h"


const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASSWD;
const char hostname[] = WIFI_HOSTNAME;

// ThreadController that will ThreadControl all threads
ThreadController ThreadControl = ThreadController();
Thread* updateThread = new Thread();
Thread* wifiThread = new Thread();
Thread* keyThread = new Thread();
Thread* htmlThread = new Thread();
Thread* ntpThread = new Thread();
Thread* brgThread = new Thread();
Thread* gcalThread = new Thread();
Thread* alarmThread = new Thread();


ESP32WebServer server(WWW_PORT);


DFRobot_HT1632C ht1632c = DFRobot_HT1632C(FBD_DATA, FBD_WR, FBD_CS);
#define UPDATE	100		// Refresh rate of display in mS.
#define ITERATE 5		// Number of iterations before blinking.
signed int sensorLight = 0;


bool ModeSB = 1;
int ModeBRG = 1;
int BlinkDelay = 0;
bool BlinkOn = 1;
int DispDelay = 0;
signed int ScrollPoint = 0;

bool debounceButt1 = 0;
bool debounceButt2 = 0;
bool debounceButt3 = 0;

enum enumDM
{
	dmTime24,
	dmTime12,
	dmDateYMD,
	dmDateMDY,
	dmDateFull,
	dmTDYMD24,
	dmTDYMD12,
	dmTDMDY24,
	dmTDMDY12,
	dmTDFull24,
	dmTDFull12,
	dmBlank
};
enumDM DispMode;

struct DMstruct
{
	char *name;
	bool time24;
	bool time12;
	bool date;
	char *format;
};

// When changing these make sure you update enumDM!
// The number of elements in both have to match.
DMstruct dm[] =
{
	{"Time (24H)",		1, 0, 0,	"%H:%M"},
	{"Time (12h)",		0, 1, 0,	"%l:%M"},
	{"Date (YMD)",		0, 0, 1,	"%Y/%m/%d"},
	{"Date (MDY)",		0, 0, 1,	"%m/%d/%Y"},
	{"Date (full)",		0, 0, 1,	"%a, %d %b %Y"},
	{"Date/Time (YMD/24H)",	1, 0, 1,	"%Y/%m/%d  %H:%M:%S"},
	{"Date/Time (YMD/12h)",	0, 1, 1,	"%Y/%m/%d  %l:%M %P"},
	{"Date/Time (MDY/24H)",	1, 0, 1,	"%m/%d/%Y  %H:%M:%S"},
	{"Date/Time (MDY/12h)",	0, 1, 1,	"%m/%d/%Y  %l:%M %P"},
	{"Date/Time (full/24H)",1, 0, 1,	"%a, %d %b %Y  %H:%M:%S"},
	{"Date/Time (full/12h)",0, 1, 1,	"%a, %d %b %Y  %l:%M %P"},
	{"Display off",		0, 0, 0,	""},
};


enum enumStatus
{
	stateWiFi,
	stateNTP,
	stateOK,
	stateAlarm,
};
enumStatus Status;

#define JSONBUFF 512		// 512byts should be enough.
#define GCALSIZE 16		// Limit to only 16 calendar entries.
struct Events {
   unsigned long event;
   const char* title;
   const char* info;
};
Events GCAL[GCALSIZE];


void keyBounce()
{
	if (Status == stateAlarm)
	{
		if (!digitalRead(BUTTON1) || !digitalRead(BUTTON1) || !digitalRead(BUTTON1))
		{
			Status = stateOK;
			UpdateDisplay();

			if (dm[DispMode].time24)
				SayTime(hour(), minute(), second(), 1);
			else if (dm[DispMode].time12)
				SayTime(hour(), minute(), second(), 0);

			if (dm[DispMode].date)
				SayDate(year(), month(), day());
		}
	}
	else
	{
		// BUTTON1 is the mode button.
		if ((digitalRead(BUTTON1) == 0) && !debounceButt1)
		{
			debounceButt1 = 1;
			CLK_PRINTLN("KEY:Button:1");

			if (dm[DispMode].time24)
				SayTime(hour(), minute(), second(), 1);
			else if (dm[DispMode].time12)
				SayTime(hour(), minute(), second(), 0);

			if (dm[DispMode].date)
				SayDate(year(), month(), day());
		}

		// BUTTON2 select display types.
		else if ((digitalRead(BUTTON2) == 0) && !debounceButt2)
		{
			debounceButt2 = 1;
			CLK_PRINTLN("KEY:Button:2");

			// Toggle through modes.
			int temp = DispMode;
			temp++;
			if (temp > dmBlank)
				temp = 0;
			DispMode = (enumDM)temp;
			CLK_PRINT("DM:"); CLK_PRINT(dm[DispMode].name); CLK_PRINT(":"); CLK_PRINTLN(dm[DispMode].format);

			char str[80];
			mmStrftime(str, 80, dm[DispMode].format);
			//CLK_PRINT("Now:"); CLK_PRINT(str); CLK_PRINT("  "); CLK_PRINTLN(time());
			ScrollPoint = 0;
			BlinkOn = 1;
			// handleGCAL();
			/*
			if (digitalRead(BUSY_PIN))
			{
				Play(1,1);
				// Play(1,2);
				delay(100);
			}
			// SayDate(year(), month(), day());
			*/
		}

		// BUTTON3 is refresh Google calendar
		else if ((digitalRead(BUTTON3) == 0) && !debounceButt3)
		{
			debounceButt3 = 1;
			CLK_PRINTLN("KEY:Button:3");

			handleBRG();
			displayText("NTP");
			handleNTP();
			displayText("Gcal");
			handleGCAL();
			displayText("Alrm");
			handleAlarm();
			ht1632c.inLowpower(0);
		}

		// Make sure we release before we accept a new button press.
		else if ((digitalRead(BUTTON1) == 1) && debounceButt1)
			debounceButt1 = 0;
		else if ((digitalRead(BUTTON2) == 1) && debounceButt2)
			debounceButt2 = 0;
		else if ((digitalRead(BUTTON3) == 1) && debounceButt3)
			debounceButt3 = 0;
	}
}


void connectWiFi()
{
	int Count = 10;

	// Setup WiFi.
	while ((WiFi.status() != WL_CONNECTED) && Count)
	{
		delay(100);
		WIFI_PRINT(".");
		Count--;
	}
	if (WiFi.status() != WL_CONNECTED)
	{
		WIFI_PRINTLN("WiFi:Connecting.");
		displayText("WiFi");
		WiFi.begin(ssid, pass);
	}
}


void mmStrftime(char *str, int size, char *format)
{
	time_t timeNow = now();
	tm *tmNow = localtime(&timeNow);
	strftime(str, size, format, tmNow);
}


void displayText(char *Text)
{
	ht1632c.clearScreen();
	ht1632c.drawText(Text, 0, 0, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);
	ht1632c.writeScreen();
}


void UpdateDisplay()
{
	char str[80];
	char dPM[2] = " ";

	ht1632c.clearScreen();
	BlinkDelay++;
	if (BlinkDelay > ITERATE)
	{
		BlinkDelay = 0;
		BlinkOn = !BlinkOn;
	}

	if (Status == stateWiFi)
	{
		if (BlinkOn)
			strcpy(str, "WiFi");
		else
			strcpy(str, "");
		// ht1632c.drawText(str, 0, 0, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);
	}

	else if (Status == stateNTP)
	{
		if (BlinkOn)
			strcpy(str, "NTP");
		else
			strcpy(str, "");
		// ht1632c.drawText(str, 0, 0, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);
	}

	else if (Status == stateAlarm)
	{
		if (BlinkOn)
			strcpy(str, "Alarm");
		else
			strcpy(str, "");
		// ht1632c.drawText(str, 0, 0, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);
	}

	else
	{
		// Create time/date string.
		mmStrftime(str, 80, dm[DispMode].format);
	}

	// Remove any colons - for blinking the display.
	int index;
	for(index=0; (index<80) && str[index]; index++)
	{
		if ((str[index] == ':') && !BlinkOn)
			str[index] = ' ';
	}

	// If we have a long time/date string the scroll it.
	if (index > 5)
	{
		ht1632c.drawText(str, ScrollPoint, 0, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);
		ScrollPoint--;
		if (ScrollPoint<-(index*4))
			ScrollPoint = 24;
		// Serial.println(ScrollPoint);
	}
	else
		ht1632c.drawText(str, 0, 0, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);

	/*
		if (dPM)
		{
			// ht1632c.setPixel(x, y);
			ht1632c.drawText(dPM, 21, 0, FONT_5X4, FONT_5X4_END, FONT_5X4_HEIGHT);
		}
	*/

	ht1632c.writeScreen();
}


void htmlRadio(String *Result, char *Name, int Selected, int Value, char *Item)
{
	char Temp[256];
	if (Selected == Value)
	{
		sprintf(Temp, radio_html, Name, Value, "checked", Item);
	}
	else
	{
		sprintf(Temp, radio_html, Name, Value, "", Item);
	}

	Result->concat(Temp);
}


void htmlSlider(String *Result, char *Name, int Value, int Min, int Max, int Step)
{
	char Temp[256];
	sprintf(Temp, slider_html, Name, Name, Value, Min, Max, Step, Name);
	Result->concat(Temp);
}


void htmlButton(String *Result, char *Name, int Value)
{
	char Temp[256];

	if (Value)
		sprintf(Temp, button_html, Name, "checked", Name);
	else
		sprintf(Temp, button_html, Name, "", Name);

	Result->concat(Temp);
}


void handleSubmit(void)
{
	// Handle toggles.
	ModeSB = 0;

	if (server.args() > 0 )
	{
		for ( uint8_t i = 0; i < server.args(); i++ )
		{
			if (server.argName(i) == optDispMode)
			{
				DispMode = (enumDM) server.arg(i).toInt();
			}
			else if (server.argName(i) == optSB)
			{
				ModeSB = 1;
			}
			else if (server.argName(i) == optBRG)
			{
				ModeBRG = server.arg(i).toInt();
				ht1632c.setPwm(ModeBRG);
				if (ModeBRG)
				{
					ht1632c.isLedOn(true);
				}
				else
				{
					ht1632c.isLedOn(false);
				}
			}

			HTML_PRINT("HTML:");
			HTML_PRINT(server.argName(i));
			HTML_PRINT(" = ");
			HTML_PRINTLN(server.arg(i));
		}
	}
}


void handleRoot(void)
{
	if (server.method() == HTTP_POST)
	{
		handleSubmit();
	}

	String Response;
	Response = Response + header_html;
	Response = Response + CSS_html;

	if (Status == stateNTP)
	{
		Response = Response + "<p>Status: <b>No NTP!</b></p>";
	}

	Response = Response + "<form action=\"/\" method=\"POST\">";

	Response = Response + "Display Mode:<br />";
	htmlRadio(&Response, (char*)optDispMode, DispMode, dmTime24, dm[dmTime24].name);
	htmlRadio(&Response, (char*)optDispMode, DispMode, dmTime12, dm[dmTime12].name);
	htmlRadio(&Response, (char*)optDispMode, DispMode, dmDateYMD, dm[dmDateYMD].name);
	htmlRadio(&Response, (char*)optDispMode, DispMode, dmDateMDY, dm[dmDateMDY].name);
	htmlRadio(&Response, (char*)optDispMode, DispMode, dmTDYMD24, dm[dmTDYMD24].name);
	htmlRadio(&Response, (char*)optDispMode, DispMode, dmTDYMD12, dm[dmTDYMD12].name);
	htmlRadio(&Response, (char*)optDispMode, DispMode, dmTDMDY24, dm[dmTDMDY24].name);
	htmlRadio(&Response, (char*)optDispMode, DispMode, dmTDMDY12, dm[dmTDMDY12].name);
	htmlRadio(&Response, (char*)optDispMode, DispMode, dmBlank, dm[dmBlank].name);

	Response = Response + "<br /><hr />";

	htmlButton(&Response, (char*)optSB, ModeSB);
	htmlSlider(&Response, (char*)optBRG, ModeBRG, 0, 15, 1);

	Response = Response + "<input type = \"submit\" name = \"submit\" value = \"Submit\" /></form>";

	Response = Response + footer_html;
	server.send(200, "text/html", Response);

	// close the connection:
	// HTML_PRINTLN("Client Response:");
	// HTML_PRINTLN(Response);
}


void handleNotFound()
{
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";

	for (uint8_t i = 0; i < server.args(); i++)
	{
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}

	// HTML_PRINTLN(message);
	server.send ( 404, "text/plain", message );
}


void WiFiEvent(WiFiEvent_t event)
{
	switch(event)
	{
		case SYSTEM_EVENT_AP_START:
			// WiFi.softAPsetHostname(hostname);
			WIFI_PRINTLN("WiFi:STA AP START:");
			break;

		case SYSTEM_EVENT_STA_START:
			WiFi.setHostname(hostname);
			WIFI_PRINT("WiFi:STA START:");
			WIFI_PRINTLN(hostname);
			break;

		case SYSTEM_EVENT_STA_CONNECTED:
			WIFI_PRINT("WiFi:STA CONNECT:");
			WIFI_PRINTLN(ssid);
			break;

		case SYSTEM_EVENT_AP_STA_GOT_IP6:
			WIFI_PRINTLN("WiFi:STA AP IP6:");
			WIFI_PRINTLN(WiFi.localIPv6());
			break;

		case SYSTEM_EVENT_STA_GOT_IP:
			Status = stateNTP;
			WIFI_PRINT("WiFi:STA IP:");
			WIFI_PRINTLN(WiFi.localIP());
			break;

		case SYSTEM_EVENT_STA_DISCONNECTED:
			Status = stateWiFi;
			WIFI_PRINTLN("WiFi:STA DISCONNECT.");
			break;

		default:
			break;
	}
}


void handleHTML()
{
	server.handleClient();
}


void handleNTP()
{
	if (timeStatus() == timeNotSet)
	{
		NTP_PRINTLN("NTP:Lost.");
		Status = stateNTP;
		//getNtpTime();
	}
	else
		Status = stateOK;
}


void handleBRG()
{
	// The LEDs emit too much light, turn em off.
	displayText("");
	delay(500);

	// Adjust brightness
	sensorLight = analogRead(LDR);
	// ModeBRG = sensorLight / 256;
	ModeBRG = map(sensorLight, 0, 3000, 16, 1);
	if (ModeBRG < 0)
		ModeBRG = 0;

	CLK_PRINT("BRG:"); CLK_PRINT(sensorLight); CLK_PRINT(" : "); CLK_PRINTLN(ModeBRG);
	ht1632c.setPwm(ModeBRG);
	ht1632c.inLowpower(0);
	UpdateDisplay();
}


void handleSay()
{
	SayTime(hour(), minute(), second(), 1);
	SayDate(year(), month(), day());
}


void handleAlarm(void)
{
	// foo
	CLK_PRINTLN("Alarm check:");
	time_t Now = getNow();

	unsigned long Target = Now - (Now % 60);
	for (int i=0; (i<GCALSIZE) && GCAL[i].event; i++)
	{
		unsigned long Check = GCAL[i].event - (GCAL[i].event % 60);
		// CLK_PRINT("T:"); CLK_PRINT(Now); CLK_PRINT(" / "); CLK_PRINTLN(Target);
		// CLK_PRINT("C:"); CLK_PRINT(GCAL[i].event); CLK_PRINT(" / "); CLK_PRINTLN(Check);
		if (Check == Target)
		{
			Status = stateAlarm;
			CLK_PRINTLN("Alarm!");
			Play(1,1);
		}
	}
}


void handleGCAL(void)
{
	if (WiFi.status() == WL_CONNECTED)
	{
		String response = FetchGCal(GCALURL);
		GCAL_PRINT("GCAL:"); GCAL_PRINTLN(response);
		process(response);
	}
}


void process(String response)
{
	JSON_PRINT(F("JSON:")); JSON_PRINTLN(response);

	StaticJsonBuffer<JSONBUFF> jsonBuffer;
	JsonObject& JSON = jsonBuffer.parseObject(response, 2);
	if (JSON.success())
	{
		String status = JSON["status"];
		JSON_PRINT(F("JSON:")); JSON_PRINT(status); JSON_PRINT(F(":")); JSON_PRINTLN(getNow());
		if (status == "OK")
		{
			if (JSON["event"])
			{
				for (int i=0; (i<GCALSIZE) && JSON["event"][i]; i++)
				{
					GCAL[i].event = JSON["event"][i];
					GCAL[i].title = JSON["title"][i];
					GCAL[i].info = JSON["info"][i];
					JSON_PRINT(F("EVENT: ")); JSON_PRINT(GCAL[i].event); JSON_PRINT(F(" ")); JSON_PRINT(GCAL[i].title); JSON_PRINT(F(" ")); JSON_PRINTLN(GCAL[i].info);
				}
			}
		}
		else if (status == "EMPTY")
		{
			JSON_PRINTLN(F("JSON:EMPTY"));
		}
		else if (status == "NOK")
		{
			JSON_PRINT(F("JSON:")); JSON_PRINTLN((const char*)JSON["error"]);
		}
		else
		{
			JSON_PRINT(F("JSON:Unknown:")); JSON_PRINTLN(response);
		}
	}
	else
	{
		JSON_PRINT(F("JSON:Parse error:")); JSON_PRINTLN(response);
	}
}


void setup() 
{
	DispMode = dmTime24;
	Status = stateWiFi;

	pinMode(BUSY_PIN, INPUT_PULLUP);
	pinMode(BUTTON1, INPUT_PULLUP);
 	pinMode(BUTTON2, INPUT_PULLUP);
 	pinMode(BUTTON3, INPUT_PULLUP);
	// pinMode(D1, OUTPUT);
	// digitalWrite(D1, 0);


	Serial.begin(115200);
	//while (!Serial) ; // Needed for Leonardo only
	delay(250);
	INIT_PRINTLN("mmClock v0.9");


	// Setup LED display.
	ht1632c.begin();
	ht1632c.isLedOn(true);
	ht1632c.setPwm(ModeBRG);


	// Setup WiFi
	INIT_PRINTLN("WiFi:");
	displayText("WiFi");
	WiFi.begin(ssid, pass);
	WiFi.onEvent(WiFiEvent);


	// Setup NTP.
	INIT_PRINTLN("NTP:");
	displayText("NTP");
	SetupNTP();


	// Setup MP3 player.
	INIT_PRINTLN("MP3:");
	displayText("MP3");
	SetupMP3();


	// Setup web server.
	INIT_PRINTLN("HTML:");
	displayText("HTML");
	// server.on("/submit", handleSubmit);
	server.on("/", handleRoot);
	server.onNotFound(handleNotFound);
	server.begin();

	// Setup threads.
	INIT_PRINTLN("CPU:");
	displayText("CPU");
	updateThread->onRun(UpdateDisplay);	// Display update thread.
	updateThread->setInterval(UPDATE);
	wifiThread->onRun(connectWiFi);		// WiFi connection thread.
	wifiThread->setInterval(10000);
	keyThread->onRun(keyBounce);		// Key check thread.
	keyThread->setInterval(50);
	htmlThread->onRun(handleHTML);		// web server thread.
	htmlThread->setInterval(2000);
	ntpThread->onRun(handleNTP);		// NTP sync thread.
	ntpThread->setInterval(120000);
	brgThread->onRun(handleBRG);		// Regular time announcements.
	brgThread->setInterval(3600000);
	gcalThread->onRun(handleGCAL);		// Update Google Calendar data.
	gcalThread->setInterval(60000);
	alarmThread->onRun(handleAlarm);	// The Alarm thread.
	alarmThread->setInterval(60000);

	ThreadControl.add(updateThread);
	ThreadControl.add(wifiThread);
	ThreadControl.add(keyThread);
	ThreadControl.add(htmlThread);
	ThreadControl.add(ntpThread);
	ThreadControl.add(brgThread);
	ThreadControl.add(gcalThread);
	ThreadControl.add(alarmThread);

	INIT_PRINTLN("OK:");
	displayText("mmC 1");
}


void loop()
{
	// Manage running threads.
	ThreadControl.run();

/*	if (!digitalRead(BUSY_PIN))
	{
		MP3_PRINTLN("U");
	}
*/
}


