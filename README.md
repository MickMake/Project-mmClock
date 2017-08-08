# The mmClock
Source code for my talking alarm clock. This alarm clock will:
- [x] Sync time from an NTP server.
- [x] Sync events from Google calendar.
- [x] Speak the time/date in many formats.
- [x] Annoy you with the alarm of your choice.

Features I'll be adding:
- [ ] Better security, (currently it's open).
- [ ] Select clock display style from Google calendar.
- [ ] Select MP3 alarm file to play from Google calendar.
- [ ] Select alarm volume level from Google calendar.
- [ ] Multiple calendar syncing.
- [ ] MQTT connectivity.
- [ ] Better web interface.

Check out [my tutorial video](https://www.youtube.com/watch?v=IoX6t03ULnc) on how I made it.
Also check out [my website](https://www.mickmake.com/archives/3375) for further details. 


## Support :+1:
If you want to support me, then head on over to [my Patreon page](http://patreon.com/MickMake).


## License
This source code is covered under the GPL!


## Source code - Clock/
Source code is under the [Clock/](Clock/) directory.
All the important defines are in the [common.h](Clock/common.h) file.
Make sure you update these to the correct settings.

## MP3 files - SDcard/
Copy all the files under [SDcard/](SDcard/) to an SD card. You can create your own, but make sure that you keep the same order as define in [ClockMP3defs.h](Clock/ClockMP3defs.h).

