function doGet()
{
  var _calendarName = 'AlarmClock2'; // Calendar used.
  var _checkInRate = 172800; // Only look a week ahead.
  
  return ContentService.createTextOutput(getOutput(_calendarName, _checkInRate));
}

function getOutput(calendarName, offset)
{
  return JSON.stringify(getResponse(calendarName, offset));
}

function getResponse(calendarName, offset)
{
  var cal = CalendarApp.getCalendarsByName(calendarName)[0];
  //return {status:"OK","time":[1501974000000,1502974000000],"event":["Wake Up","Business Lunch"],"info":["",""]};
  
  if (cal)
  {
    var retEvent = [];
    var retTitle = [];
    var retInfo = [];
    var now = new Date();
    var later = new Date();

    later.setSeconds(now.getSeconds() + offset);
  
    var events = cal.getEvents(now, later);
    var count = events.length;
    
    if (events.length)
    {
      for(i in events)
      {
        retTitle[i] = events[i].getTitle();
        var date = events[i].getStartTime();
        retEvent[i] = date.getTime() / 1000;
        retInfo[i] = events[i].getDescription();
        // responses.push({"title" : title, "when" : epoch, "info" : info});
      }
      return {status: 'OK', event: retEvent, title: retTitle, info: retInfo};
    }
    else
      return {status: 'EMPTY'};
  }
  else
    return {status: 'NOK', error: 'Error, calendar "' + calendarName + '" does not exist.'};
}

