[![Board Status](https://dev.azure.com/dbarrett91/3ea5f265-5884-44a2-8bbc-5e6abca5e398/8b739305-d302-44d9-884c-b12cf36360cc/_apis/work/boardbadge/ea2f6b3c-fc64-4a11-8c89-fde38236f9d9)](https://dev.azure.com/dbarrett91/3ea5f265-5884-44a2-8bbc-5e6abca5e398/_boards/board/t/8b739305-d302-44d9-884c-b12cf36360cc/Microsoft.RequirementCategory)
# APRemote
Web based autopilot control using ESP32 and Seatalk1

Seatalk 1 is a 9bit protocol with 9th bit being set to indicate a command byte. Decoding is done using the ESPSoftwareSerial library.
INitialise the software port as 8 bit and Space parity. Test the parity bit before reading data if it is set then the byte
being read is a command bit.

ESP32 sketch on Arduino IDE. Reads and writes Seatalk1 to display data and send AP commannds to control X10 smart pilot.

Seatalk processing in Core 0 on ESP32.

HTML/CSS files for web page uploaded via SPIFFS.

More details to follow.
