
const char CSS_html[] PROGMEM = "<style>.switch{position:relative;display:inline-block;width:60px;height:34px}.switch input{display:none}.slider{position:absolute;cursor:pointer;top:0;left:0;right:0;bottom:0;background-color:#ccc;-webkit-transition:.4s;transition:.4s}.slider:before{position:absolute;content:\"\";height:26px;width:26px;left:4px;bottom:4px;background-color:#fff;-webkit-transition:.4s;transition:.4s}input:checked+.slider{background-color:#2196F3}input:focus+.slider{box-shadow:0 0 1px #2196F3}input:checked+.slider:before{-webkit-transform:translateX(26px);-ms-transform:translateX(26px);transform:translateX(26px)}.slider.round{border-radius:34px}.slider.round:before{border-radius:50%}</style>";

const char header_html[] PROGMEM = "<html><head><META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\"></head><body>";
const char footer_html[] PROGMEM = "</body></html>";


const char radio_html[] PROGMEM = "<input type=\"radio\" name=\"%s\" value=\"%u\" %s>%s<br />";

const char slider_html[] PROGMEM = "<input id=\"%s\" type=\"range\" name=\"%s\" value=\"%u\" min=\"%u\" max=\"%u\" step=\"%u\" />%s<br />";

const char button_html[] PROGMEM = "<label class=\"switch\"><input type=\"checkbox\" name=\"%s\" %s><span class=\"slider round\"></span></label>%s<br />";

/*
<script>function printValue(e,n){var t=document.getElementById(n),l=document.getElementById(e);t.value=l.value}window.onload=function(){printValue("slider1","rangeValue1")};</script>
*/


const char optDispMode[] PROGMEM = "Display Mode";
const char optSB[] PROGMEM = "Second Blink";
const char optBRG[] PROGMEM = "Brightness";

