#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

// Import my own headers.
#include "common.h"
#include "Debug.h"

WiFiClientSecure client;

String WebFetch(String url)
{
	const char *strURL;
	String Response;
	char server[80];
	bool Redirect = 0;

	strURL = url.c_str();
	GCAL_PRINT("GCAL:URL:"); GCAL_PRINTLN(strURL);

	if (memcmp("https://", strURL, 8) == 0)
	{
		int i;
		for(i=0; i<80; i++)
		{
			if (strURL[i+8] == '/')
				break;
			server[i] = strURL[i+8];
		}
		server[i] = 0;
	}

	GCAL_PRINT("GCAL:server:"); GCAL_PRINTLN(server);
	if (!client.connect(server, 443))
		GCAL_PRINTLN("GCAL:No connection");
	else
	{
		GCAL_PRINTLN("GCAL:Connect");
		// Make a HTTP request:
		client.print("GET ");
		client.print(url);
		client.println(" HTTP/1.0");

		client.print("Host: ");
		client.println(server);
		client.println("Connection: close");
		client.println();

		String header;
		while (client.connected())
		{
			String line = client.readStringUntil('\n');
			header = header + line + "\n";
			if (line.startsWith("Location: "))
			{
				Redirect = 1;
				Response = line.substring(line.indexOf("http"));
				GCAL_PRINT("GCAL:REDIRECT:"); GCAL_PRINTLN(Response);
			}
			if (line == "\r")
				break;
		}
		GCAL_PRINTLN("GCAL:HEADER:"); GCAL_PRINTLN(header);

		String body;
		while (client.available())
		{
			String line = client.readStringUntil('\n');
			body = body + line + "\n";
			if (line == "\r")
				break;
		}

		if (!Redirect)
		{
			GCAL_PRINTLN("GCAL:BODY:"); GCAL_PRINTLN(body);
			Response = body;
		}

		client.stop();
	}

	return(Response);
}


String FetchGCal(String url)
{
	String Return1;
	String Return2;
	Return1 = WebFetch(url);
	Return2 = WebFetch(Return1);

	return(Return2);
}

