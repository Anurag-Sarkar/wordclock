#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define NUM_LEDS 256  // Total number of LEDs
#define DATA_PIN 5  // Data pin for the LED strip
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

const char* ssid = "Sheryians_Office_2.4GHZ";
const char* password = "Sherythelab@0007";

unsigned long lastAnimationUpdate = 0;
const unsigned long animationInterval = 50; // Adjust as needed


CRGB leds[NUM_LEDS];

//words
const int half[] = { 207, 208, 239, 240 };             // Indices for "half"
const int past[] = { 136, 151, 168, 183 };             // Indices for "past"
const int minute[] = { 8, 23, 40, 55, 72, 87 };        // Indices for "past"
const int OClock[] = { 4, 27, 36, 59, 68, 91 };        // Indices for "past"
const int quater[] = { 14, 17, 46, 49, 78, 81, 110 };  // Indices for "past"
const int to[] = { 183, 200 };                         // Indices for "past"
const int in[] = { 123, 132 };                         // Indices for "past"
const int at[] = { 155, 164 };                         // Indices for "past"

//time of Day
const int morning[] = { 131, 156, 163, 188, 195, 220, 227 };              // Indices for "past"
const int night[] = { 3, 28, 35, 60, 67, 67 };                            // Indices for "past"
const int afternoon[] = { 125, 130, 157, 162, 189, 194, 221, 226, 253 };  // Indices for "past"
const int evening[] = { 2, 29, 34, 61, 66, 93, 98 };                      // Indices for "past"

//seconds
const int zeroSeconds[] = { 0, 96 };
const int oneSeconds[] = { 0, 127 };
const int twoSeconds[] = { 0, 128 };
const int threeSeconds[] = { 0, 159 };
const int fourSeconds[] = { 0, 160 };
const int fiveSeconds[] = { 0, 191 };
const int sixSeconds[] = { 0, 192 };
const int sevenSeconds[] = { 0, 223 };
const int eightSeconds[] = { 0, 224 };
const int nineSeconds[] = { 0, 255 };
const int tenSeconds[] = { 31, 96 };
const int elevenSeconds[] = { 31, 127 };
const int twelveSeconds[] = { 31, 128 };
const int thirteenSeconds[] = { 31, 159 };
const int fourteenSeconds[] = { 31, 160 };
const int fifteenSeconds[] = { 31, 191 };
const int sixteenSeconds[] = { 31, 192 };
const int seventeenSeconds[] = { 31, 223 };
const int eighteenSeconds[] = { 31, 224 };
const int nineteenSeconds[] = { 31, 255 };
const int twentySeconds[] = { 32, 96 };
const int twentyOneSeconds[] = { 32, 127 };
const int twentyTwoSeconds[] = { 32, 128 };
const int twentyThreeSeconds[] = { 32, 159 };
const int twentyFourSeconds[] = { 32, 160 };
const int twentyFiveSeconds[] = { 32, 191 };
const int twentySixSeconds[] = { 32, 192 };
const int twentySevenSeconds[] = { 32, 223 };
const int twentyEightSeconds[] = { 32, 224 };
const int twentyNineSeconds[] = { 32, 255 };
const int thirtySeconds[] = { 63, 96 };
const int thirtyOneSeconds[] = { 63, 127 };
const int thirtyTwoSeconds[] = { 63, 128 };
const int thirtyThreeSeconds[] = { 63, 159 };
const int thirtyFourSeconds[] = { 63, 160 };
const int thirtyFiveSeconds[] = { 63, 191 };
const int thirtySixSeconds[] = { 63, 192 };
const int thirtySevenSeconds[] = { 63, 223 };
const int thirtyEightSeconds[] = { 63, 224 };
const int thirtyNineSeconds[] = { 63, 255 };
const int fortySeconds[] = { 64, 96 };
const int fortyOneSeconds[] = { 64, 127 };
const int fortyTwoSeconds[] = { 64, 128 };
const int fortyThreeSeconds[] = { 64, 159 };
const int fortyFourSeconds[] = { 64, 160 };
const int fortyFiveSeconds[] = { 64, 191 };
const int fortySixSeconds[] = { 64, 192 };
const int fortySevenSeconds[] = { 64, 223 };
const int fortyEightSeconds[] = { 64, 224 };
const int fortyNineSeconds[] = { 64, 255 };
const int fiftySeconds[] = { 95, 96 };
const int fiftyOneSeconds[] = { 95, 127 };
const int fiftyTwoSeconds[] = { 95, 128 };
const int fiftyThreeSeconds[] = { 95, 159 };
const int fiftyFourSeconds[] = { 95, 160 };
const int fiftyFiveSeconds[] = { 95, 191 };
const int fiftySixSeconds[] = { 95, 192 };
const int fiftySevenSeconds[] = { 95, 223 };
const int fiftyEightSeconds[] = { 95, 224 };
const int fiftyNineSeconds[] = { 95, 255 };

//Hours
const int oneHours[] = { 39, 56, 71 };
const int twoHours[] = { 7, 24, 39 };
const int threeHours[] = { 89, 102, 121, 134, 153 };
const int fourHours[] = { 5, 26, 37, 58 };
const int fiveHours[] = { 90, 101, 122, 133 };
const int sixHours[] = { 216, 231, 248 };
const int sevenHours[] = { 6, 25, 38, 57, 69 };
const int eightHours[] = { 133, 154, 165, 186, 197 };
const int nineHours[] = { 152, 167, 184, 199 };
const int tenHours[] = { 197, 218, 229 };
const int elevenHours[] = { 73, 88, 103, 120, 135, 152 };
const int twelveHours[] = { 166, 185, 198, 217, 230, 249 };

//minuites
const int oneMinute[] = { 205, 210, 237 };
const int twoMinutes[] = { 173, 178, 205 };
const int threeMinutes[] = { 182, 201, 214, 233, 246 };
const int fourMinutes[] = { 10, 21, 42, 53 };
const int fiveMinutes[] = { 140, 147, 172, 179 };
const int sixMinutes[] = { 50, 77, 82 };
const int sevenMinutes[] = { 11, 20, 43, 52, 75 };
const int eightMinutes[] = { 12, 19, 44, 51, 76 };
const int nineMinutes[] = { 139, 148, 171, 180 };
const int tenMinutes[] = { 13, 18, 45 };
const int elevenMinutes[] = { 86, 105, 118, 137, 150, 169 };
const int twelveMinutes[] = { 9, 22, 41, 54, 73, 86 };
const int thirteenMinutes[] = { 138, 149, 170, 181, 202, 213, 234, 245 };
const int fourteenMinutes[] = { 10, 21, 42, 53, 74, 85, 106, 117 };
const int fifteenMinutes[] = {140,147,172,179,204,212,235,244};
const int sixteenMinutes[] = { 50, 77, 82, 109, 114, 141, 146 };
const int seventeenMinutes[] = { 11, 20, 43, 52, 75, 84, 107, 116, 139 };
const int eighteenMinutes[] = { 12, 19, 44, 51, 76, 83, 108, 115 };
const int nineteenMinutes[] = { 139, 148, 171, 180, 203, 212, 235, 244 };
const int twentyMinutes[] = { 113, 142, 145, 174, 177, 206 };
const int twentyOneMinutes[] = { 113, 142, 145, 174, 177, 206, 205, 210, 237 };
const int twentyTwoMinutes[] = { 113, 142, 145, 174, 177, 206, 173, 178, 205 };
const int twentyThreeMinutes[] = { 113, 142, 145, 174, 177, 206, 182, 201, 214, 233, 246 };
const int twentyFourMinutes[] = { 113, 142, 145, 174, 177, 206, 10, 21, 42, 53 };
const int twentyFiveMinutes[] = { 113, 142, 145, 174, 177, 206, 140, 147, 172, 179 };
const int twentySixMinutes[] = { 113, 142, 145, 174, 177, 206, 50, 77, 82 };
const int twentySevenMinutes[] = { 113, 142, 145, 174, 177, 206, 11, 20, 43, 52, 75 };
const int twentyEightMinutes[] = { 113, 142, 145, 174, 177, 206, 12, 19, 44, 51, 76 };
const int twentyNineMinutes[] = { 113, 142, 145, 174, 177, 206, 139, 148, 171, 180 };

const char* ntpServer = "pool.ntp.org";
const long  utcOffsetInSeconds = 19800; // Example: UTC+1

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, utcOffsetInSeconds);

void setup() {
 FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(255);  // Set brightness (0-255)
  //
  FastLED.show();
  delay(10);
  Serial.begin(115200);
  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  // int count = 0;
  // int row = 0;
  

  int diagonalIndex = 0;

  while (WiFi.status() != WL_CONNECTED) {
    static uint8_t wavePosition = 0;
  static uint8_t hueOffset = 0;

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((wavePosition + (i * 8)) % 256 + hueOffset, 255, 255);
  }

  wavePosition++;
  hueOffset++;

  delay(20); // Adjust speed here
  FastLED.show();
  }
 
 // Adjust speed here
  

  
  // while (WiFi.status() != WL_CONNECTED) {
  //   Serial.print(".");
  //   CRGB color = CHSV((row * 30) % 256, 255, 255); // Change 30 to adjust hue increment
  //   for (int i = row * 16; i < (row + 1) * 16; i++) {
  //     leds[i] = color;
  //     delay(30);
  //     FastLED.show();
  //   }
  //   count += 16;
  //   row++;
  // }

  Serial.println("");
  Serial.println("Wi-Fi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
  


void loop() { 
  timeClient.begin();
  timeClient.update();
  unsigned long currentTime = millis();
  static unsigned long previousUpdateTime = 0;
  const unsigned long updateInterval = 1000;  // Update every 1000 milliseconds (1 second)
  timeClient.update();

  if (currentTime - previousUpdateTime >= updateInterval) {
    previousUpdateTime = currentTime;

    // Calculate time and update LEDs
    int hours = timeClient.getHours();
    int minutes = timeClient.getMinutes();
    int seconds = timeClient.getSeconds();
    int dayOfWeek = timeClient.getDay();
    
    if(minutes > 30) hours++;
    
    // Update word clock
    updateWordClock(hours, minutes, seconds, dayOfWeek);

    // Additional LED settings
    leds[15] = CRGB::White;
    leds[16] = CRGB::White;
    leds[47] = CRGB::White;
    leds[79] = CRGB::White;
    leds[80] = CRGB::White;
    leds[111] = CRGB::White;
    leds[112] = CRGB::White;
    leds[144] = CRGB::White;
    leds[175] = CRGB::White;

    FastLED.show();  // Update LEDs
  }

}

void updateWordClock(int hour, int minutes, int second, int week) {
  // Turn off all LEDs
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  
  // Determine which LEDs to turn on based on the current time
  //Update Hour
    if(hour == 0){
      turnOnLEDs(twelveHours, sizeof(twelveHours) / sizeof(twelveHours[0]));
    } 
    else if(hour == 1){
      turnOnLEDs(oneHours, sizeof(oneHours) / sizeof(oneHours[0]));
    } 
    else if(hour == 2){
      turnOnLEDs(twoHours, sizeof(twoHours) / sizeof(twoHours[0]));
    } 
    else if(hour == 3){
      turnOnLEDs(threeHours, sizeof(threeHours) / sizeof(threeHours[0]));
    } 
    else if(hour == 4){
      turnOnLEDs(fourHours, sizeof(fourHours) / sizeof(fourHours[0]));
    } 
    else if(hour == 5){
      turnOnLEDs(fiveHours, sizeof(fiveHours) / sizeof(fiveHours[0]));
    } 
    else if(hour == 6){
      turnOnLEDs(sixHours, sizeof(sixHours) / sizeof(sixHours[0]));
    } 
    else if(hour == 7){
      turnOnLEDs(sevenHours, sizeof(sevenHours) / sizeof(sevenHours[0]));
    } 
    else if(hour == 8){
      turnOnLEDs(eightHours, sizeof(eightHours) / sizeof(eightHours[0]));
    } 
    else if(hour == 9){
      turnOnLEDs(nineHours, sizeof(nineHours) / sizeof(nineHours[0]));
    } 
    else if(hour == 10){
      turnOnLEDs(tenHours, sizeof(tenHours) / sizeof(tenHours[0]));
    } 
    else if(hour == 11){
      turnOnLEDs(elevenHours, sizeof(elevenHours) / sizeof(elevenHours[0]));
    } 
    else if(hour == 12){
      turnOnLEDs(twelveHours, sizeof(twelveHours) / sizeof(twelveHours[0]));
    } 
    else if(hour == 24){
      turnOnLEDs(twelveHours, sizeof(twelveHours) / sizeof(twelveHours[0]));
    } 
    else if(hour == 13){
      turnOnLEDs(oneHours, sizeof(oneHours) / sizeof(oneHours[0]));
    } 
    else if(hour == 14){
      turnOnLEDs(twoHours, sizeof(twoHours) / sizeof(twoHours[0]));
    } 
    else if(hour == 15){
      turnOnLEDs(threeHours, sizeof(threeHours) / sizeof(threeHours[0]));
    } 
    else if(hour == 16){
      turnOnLEDs(fourHours, sizeof(fourHours) / sizeof(fourHours[0]));
    } 
    else if(hour == 17){
      turnOnLEDs(fiveHours, sizeof(fiveHours) / sizeof(fiveHours[0]));
    } 
    else if(hour == 18){
      turnOnLEDs(sixHours, sizeof(sixHours) / sizeof(sixHours[0]));
    } 
    else if(hour == 19){
      turnOnLEDs(sevenHours, sizeof(sevenHours) / sizeof(sevenHours[0]));
    } 
    else if(hour == 20){
      turnOnLEDs(eightHours, sizeof(eightHours) / sizeof(eightHours[0]));
    } 
    else if(hour == 21){
      turnOnLEDs(nineHours, sizeof(nineHours) / sizeof(nineHours[0]));
    } 
    else if(hour == 22){
      turnOnLEDs(tenHours, sizeof(tenHours) / sizeof(tenHours[0]));
    } 
    else if(hour == 23){
      turnOnLEDs(elevenHours, sizeof(elevenHours) / sizeof(elevenHours[0]));
    } 
  //minute
 
    if(minutes == 0){
      turnOnLEDs(OClock, sizeof(OClock) / sizeof(OClock[0]));
    }
    else if(minutes == 1){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(oneMinute, sizeof(oneMinute) / sizeof(oneMinute[0]));
    }
    else if(minutes == 2){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(twoMinutes, sizeof(twoMinutes) / sizeof(twoMinutes[0]));
    }
    else if(minutes == 3){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(threeMinutes, sizeof(threeMinutes) / sizeof(threeMinutes[0]));
    }
    else if(minutes == 4){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(fourMinutes, sizeof(fourMinutes) / sizeof(fourMinutes[0]));
    }
    else if(minutes == 5){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(fiveMinutes, sizeof(fiveMinutes) / sizeof(fiveMinutes[0]));
    }
    else if(minutes == 6){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(sixMinutes, sizeof(sixMinutes) / sizeof(sixMinutes[0]));
    }
    else if(minutes == 7){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(sevenMinutes, sizeof(sevenMinutes) / sizeof(sevenMinutes[0]));
    }
    else if(minutes == 8){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(eightMinutes, sizeof(eightMinutes) / sizeof(eightMinutes[0]));
    }
    else if(minutes == 9){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(nineMinutes, sizeof(nineMinutes) / sizeof(nineMinutes[0]));
    }
    else if(minutes == 10){
      turnOnLEDs(tenMinutes, sizeof(tenMinutes) / sizeof(tenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 11){
      turnOnLEDs(elevenMinutes, sizeof(elevenMinutes) / sizeof(elevenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 12){
      turnOnLEDs(twelveMinutes, sizeof(twelveMinutes) / sizeof(twelveMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 13){
      turnOnLEDs(thirteenMinutes, sizeof(thirteenMinutes) / sizeof(thirteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 14){
      turnOnLEDs(fourteenMinutes, sizeof(fourteenMinutes) / sizeof(fourteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 15){
      turnOnLEDs(fifteenMinutes, sizeof(fifteenMinutes) / sizeof(fifteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 16){
      turnOnLEDs(sixteenMinutes, sizeof(sixteenMinutes) / sizeof(sixteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 17){
      turnOnLEDs(seventeenMinutes, sizeof(seventeenMinutes) / sizeof(seventeenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 18){
      turnOnLEDs(eighteenMinutes, sizeof(eighteenMinutes) / sizeof(eighteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 19){
      turnOnLEDs(nineteenMinutes, sizeof(nineteenMinutes) / sizeof(nineteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 20){
      turnOnLEDs(twentyMinutes, sizeof(twentyMinutes) / sizeof(twentyMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 21){
      turnOnLEDs(twentyOneMinutes, sizeof(twentyOneMinutes) / sizeof(twentyOneMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 22){
      turnOnLEDs(twentyTwoMinutes, sizeof(twentyTwoMinutes) / sizeof(twentyTwoMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 23){
      turnOnLEDs(twentyThreeMinutes, sizeof(twentyThreeMinutes) / sizeof(twentyThreeMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 24){
      turnOnLEDs(twentyFourMinutes, sizeof(twentyFourMinutes) / sizeof(twentyFourMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 25){
      turnOnLEDs(twentyFiveMinutes, sizeof(twentyFiveMinutes) / sizeof(twentyFiveMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 26){
      turnOnLEDs(twentySixMinutes, sizeof(twentySixMinutes) / sizeof(twentySixMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 27){
      turnOnLEDs(twentySevenMinutes, sizeof(twentySevenMinutes) / sizeof(twentySevenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 28){
      turnOnLEDs(twentyEightMinutes, sizeof(twentyEightMinutes) / sizeof(twentyEightMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 29){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(twentyNineMinutes, sizeof(twentyNineMinutes) / sizeof(twentyNineMinutes[0]));
    }
    else if(minutes == 30){
      turnOnLEDs(half, sizeof(half) / sizeof(half[0]));
    }

    else if(minutes == 59){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(oneMinute, sizeof(oneMinute) / sizeof(oneMinute[0]));
    }
    else if(minutes == 58){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(twoMinutes, sizeof(twoMinutes) / sizeof(twoMinutes[0]));
    }
    else if(minutes == 57){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(threeMinutes, sizeof(threeMinutes) / sizeof(threeMinutes[0]));
    }
    else if(minutes == 56){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(fourMinutes, sizeof(fourMinutes) / sizeof(fourMinutes[0]));
    }
    else if(minutes == 55){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(fiveMinutes, sizeof(fiveMinutes) / sizeof(fiveMinutes[0]));
    }
    else if(minutes == 54){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(sixMinutes, sizeof(sixMinutes) / sizeof(sixMinutes[0]));
    }
    else if(minutes == 53){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(sevenMinutes, sizeof(sevenMinutes) / sizeof(sevenMinutes[0]));
    }
    else if(minutes == 52){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(eightMinutes, sizeof(eightMinutes) / sizeof(eightMinutes[0]));
    }
    else if(minutes == 51){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(nineMinutes, sizeof(nineMinutes) / sizeof(nineMinutes[0]));
    }
    else if(minutes == 50){
      turnOnLEDs(tenMinutes, sizeof(tenMinutes) / sizeof(tenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 49){
      turnOnLEDs(elevenMinutes, sizeof(elevenMinutes) / sizeof(elevenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 48){
      turnOnLEDs(twelveMinutes, sizeof(twelveMinutes) / sizeof(twelveMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 47){
      turnOnLEDs(thirteenMinutes, sizeof(thirteenMinutes) / sizeof(thirteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 46){
      turnOnLEDs(fourteenMinutes, sizeof(fourteenMinutes) / sizeof(fourteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 45){
      turnOnLEDs(fifteenMinutes, sizeof(fifteenMinutes) / sizeof(fifteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 44){
      turnOnLEDs(sixteenMinutes, sizeof(sixteenMinutes) / sizeof(sixteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 43){
      turnOnLEDs(seventeenMinutes, sizeof(seventeenMinutes) / sizeof(seventeenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 42){
      turnOnLEDs(eighteenMinutes, sizeof(eighteenMinutes) / sizeof(eighteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 41){
      turnOnLEDs(nineteenMinutes, sizeof(nineteenMinutes) / sizeof(nineteenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 40){
      turnOnLEDs(twentyMinutes, sizeof(twentyMinutes) / sizeof(twentyMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 39){
      turnOnLEDs(twentyOneMinutes, sizeof(twentyOneMinutes) / sizeof(twentyOneMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 38){
      turnOnLEDs(twentyTwoMinutes, sizeof(twentyTwoMinutes) / sizeof(twentyTwoMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 37){
      turnOnLEDs(twentyThreeMinutes, sizeof(twentyThreeMinutes) / sizeof(twentyThreeMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 36){
      turnOnLEDs(twentyFourMinutes, sizeof(twentyFourMinutes) / sizeof(twentyFourMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 35){
      turnOnLEDs(twentyFiveMinutes, sizeof(twentyFiveMinutes) / sizeof(twentyFiveMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 34){
      turnOnLEDs(twentySixMinutes, sizeof(twentySixMinutes) / sizeof(twentySixMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 33){
      turnOnLEDs(twentySevenMinutes, sizeof(twentySevenMinutes) / sizeof(twentySevenMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 32){
      turnOnLEDs(twentyEightMinutes, sizeof(twentyEightMinutes) / sizeof(twentyEightMinutes[0]));
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
    }
    else if(minutes == 31){
      turnOnLEDs(minute, sizeof(minute) / sizeof(minute[0]));
      turnOnLEDs(twentyNineMinutes, sizeof(twentyNineMinutes) / sizeof(twentyNineMinutes[0]));
    }

  //seconds
    if(second == 0){
      turnOnLEDs(zeroSeconds, sizeof(zeroSeconds) / sizeof(zeroSeconds[0]));
    }
    else if(second == 1){
      turnOnLEDs(oneSeconds, sizeof(oneSeconds) / sizeof(oneSeconds[0]));
    }
    else if(second == 2){
      turnOnLEDs(twoSeconds, sizeof(twoSeconds) / sizeof(twoSeconds[0]));
    }
    else if(second == 3){
      turnOnLEDs(threeSeconds, sizeof(threeSeconds) / sizeof(threeSeconds[0]));
    }
    else if(second == 4){
      turnOnLEDs(fourSeconds, sizeof(fourSeconds) / sizeof(fourSeconds[0]));
    }
    else if(second == 5){
      turnOnLEDs(fiveSeconds, sizeof(fiveSeconds) / sizeof(fiveSeconds[0]));
    }
    else if(second == 6){
      turnOnLEDs(sixSeconds, sizeof(sixSeconds) / sizeof(sixSeconds[0]));
    }
    else if(second == 7){
      turnOnLEDs(sevenSeconds, sizeof(sevenSeconds) / sizeof(sevenSeconds[0]));
    }
    else if(second == 8){
      turnOnLEDs(eightSeconds, sizeof(eightSeconds) / sizeof(eightSeconds[0]));
    }
    else if(second == 9){
      turnOnLEDs(nineSeconds, sizeof(nineSeconds) / sizeof(nineSeconds[0]));
    }
    else if(second == 10){
      turnOnLEDs(tenSeconds, sizeof(tenSeconds) / sizeof(tenSeconds[0]));
    }
    else if(second == 11){
      turnOnLEDs(elevenSeconds, sizeof(elevenSeconds) / sizeof(elevenSeconds[0]));
    }
    else if(second == 12){
      turnOnLEDs(twelveSeconds, sizeof(twelveSeconds) / sizeof(twelveSeconds[0]));
    }
    else if(second == 13){
      turnOnLEDs(thirteenSeconds, sizeof(thirteenSeconds) / sizeof(thirteenSeconds[0]));
    }
    else if(second == 14){
      turnOnLEDs(fourteenSeconds, sizeof(fourteenSeconds) / sizeof(fourteenSeconds[0]));
    }
    else if(second == 15){
      turnOnLEDs(fifteenSeconds, sizeof(fifteenSeconds) / sizeof(fifteenSeconds[0]));
    }
    else if(second == 16){
      turnOnLEDs(sixteenSeconds, sizeof(sixteenSeconds) / sizeof(sixteenSeconds[0]));
    }
    else if(second == 17){
      turnOnLEDs(seventeenSeconds, sizeof(seventeenSeconds) / sizeof(seventeenSeconds[0]));
    }
    else if(second == 18){
      turnOnLEDs(eighteenSeconds, sizeof(eighteenSeconds) / sizeof(eighteenSeconds[0]));
    }
    else if(second == 19){
      turnOnLEDs(nineteenSeconds, sizeof(nineteenSeconds) / sizeof(nineteenSeconds[0]));
    }
    else if(second == 20){
      turnOnLEDs(twentySeconds, sizeof(twentySeconds) / sizeof(twentySeconds[0]));
    }
    else if(second == 21){
      turnOnLEDs(twentyOneSeconds, sizeof(twentyOneSeconds) / sizeof(twentyOneSeconds[0]));
    }
    else if(second == 22){
      turnOnLEDs(twentyTwoSeconds, sizeof(twentyTwoSeconds) / sizeof(twentyTwoSeconds[0]));
    }
    else if(second == 23){
      turnOnLEDs(twentyThreeSeconds, sizeof(twentyThreeSeconds) / sizeof(twentyThreeSeconds[0]));
    }
    else if(second == 24){
      turnOnLEDs(twentyFourSeconds, sizeof(twentyFourSeconds) / sizeof(twentyFourSeconds[0]));
    }
    else if(second == 25){
      turnOnLEDs(twentyFiveSeconds, sizeof(twentyFiveSeconds) / sizeof(twentyFiveSeconds[0]));
    }
    else if(second == 26){
      turnOnLEDs(twentySixSeconds, sizeof(twentySixSeconds) / sizeof(twentySixSeconds[0]));
    }
    else if(second == 27){
      turnOnLEDs(twentySevenSeconds, sizeof(twentySevenSeconds) / sizeof(twentySevenSeconds[0]));
    }
    else if(second == 28){
      turnOnLEDs(twentyEightSeconds, sizeof(twentyEightSeconds) / sizeof(twentyEightSeconds[0]));
    }
    else if(second == 29){
      turnOnLEDs(twentyNineSeconds, sizeof(twentyNineSeconds) / sizeof(twentyNineSeconds[0]));
    }
    else if(second == 30){
      turnOnLEDs(thirtySeconds, sizeof(thirtySeconds) / sizeof(thirtySeconds[0]));
    }
    else if(second == 31){
      turnOnLEDs(thirtyOneSeconds, sizeof(thirtyOneSeconds) / sizeof(thirtyOneSeconds[0]));
    }
    else if(second == 32){
      turnOnLEDs(thirtyTwoSeconds, sizeof(thirtyTwoSeconds) / sizeof(thirtyTwoSeconds[0]));
    }
    else if(second == 33){
      turnOnLEDs(thirtyThreeSeconds, sizeof(thirtyThreeSeconds) / sizeof(thirtyThreeSeconds[0]));
    }
    else if(second == 34){
      turnOnLEDs(thirtyFourSeconds, sizeof(thirtyFourSeconds) / sizeof(thirtyFourSeconds[0]));
    }
    else if(second == 35){
      turnOnLEDs(thirtyFiveSeconds, sizeof(thirtyFiveSeconds) / sizeof(thirtyFiveSeconds[0]));
    }
    else if(second == 36){
      turnOnLEDs(thirtySixSeconds, sizeof(thirtySixSeconds) / sizeof(thirtySixSeconds[0]));
    }
    else if(second == 37){
      turnOnLEDs(thirtySevenSeconds, sizeof(thirtySevenSeconds) / sizeof(thirtySevenSeconds[0]));
    }
    else if(second == 38){
      turnOnLEDs(thirtyEightSeconds, sizeof(thirtyEightSeconds) / sizeof(thirtyEightSeconds[0]));
    }
    else if(second == 39){
      turnOnLEDs(thirtyNineSeconds, sizeof(thirtyNineSeconds) / sizeof(thirtyNineSeconds[0]));
    }
    else if(second == 40){
      turnOnLEDs(fortySeconds, sizeof(fortySeconds) / sizeof(fortySeconds[0]));
    }
    else if(second == 41){
      turnOnLEDs(fortyOneSeconds, sizeof(fortyOneSeconds) / sizeof(fortyOneSeconds[0]));
    }
    else if(second == 42){
      turnOnLEDs(fortyTwoSeconds, sizeof(fortyTwoSeconds) / sizeof(fortyTwoSeconds[0]));
    }
    else if(second == 43){
      turnOnLEDs(fortyThreeSeconds, sizeof(fortyThreeSeconds) / sizeof(fortyThreeSeconds[0]));
    }
    else if(second == 44){
      turnOnLEDs(fortyFourSeconds, sizeof(fortyFourSeconds) / sizeof(fortyFourSeconds[0]));
    }
    else if(second == 45){
      turnOnLEDs(fortyFiveSeconds, sizeof(fortyFiveSeconds) / sizeof(fortyFiveSeconds[0]));
    }
    else if(second == 46){
      turnOnLEDs(fortySixSeconds, sizeof(fortySixSeconds) / sizeof(fortySixSeconds[0]));
    }
    else if(second == 47){
      turnOnLEDs(fortySevenSeconds, sizeof(fortySevenSeconds) / sizeof(fortySevenSeconds[0]));
    }
    else if(second == 48){
      turnOnLEDs(fortyEightSeconds, sizeof(fortyEightSeconds) / sizeof(fortyEightSeconds[0]));
    }
    else if(second == 49){
      turnOnLEDs(fortyNineSeconds, sizeof(fortyNineSeconds) / sizeof(fortyNineSeconds[0]));
    }
    else if(second == 50){
      turnOnLEDs(fiftySeconds, sizeof(fiftySeconds) / sizeof(fiftySeconds[0]));
    }
    else if(second == 51){
      turnOnLEDs(fiftyOneSeconds, sizeof(fiftyOneSeconds) / sizeof(fiftyOneSeconds[0]));
    }
    else if(second == 52){
      turnOnLEDs(fiftyTwoSeconds, sizeof(fiftyTwoSeconds) / sizeof(fiftyTwoSeconds[0]));
    }
    else if(second == 53){
      turnOnLEDs(fiftyThreeSeconds, sizeof(fiftyThreeSeconds) / sizeof(fiftyThreeSeconds[0]));
    }
    else if(second == 54){
      turnOnLEDs(fiftyFourSeconds, sizeof(fiftyFourSeconds) / sizeof(fiftyFourSeconds[0]));
    }
    else if(second == 55){
      turnOnLEDs(fiftyFiveSeconds, sizeof(fiftyFiveSeconds) / sizeof(fiftyFiveSeconds[0]));
    }
    else if(second == 56){
      turnOnLEDs(fiftySixSeconds, sizeof(fiftySixSeconds) / sizeof(fiftySixSeconds[0]));
    }
    else if(second == 57){
      turnOnLEDs(fiftySevenSeconds, sizeof(fiftySevenSeconds) / sizeof(fiftySevenSeconds[0]));
    }
    else if(second == 58){
      turnOnLEDs(fiftyEightSeconds, sizeof(fiftyEightSeconds) / sizeof(fiftyEightSeconds[0]));
    }
    else if(second == 59){
      turnOnLEDs(fiftyNineSeconds, sizeof(fiftyNineSeconds) / sizeof(fiftyNineSeconds[0]));
    }

  if(minutes > 0 && minutes <= 30){
    turnOnLEDs(past, sizeof(past) / sizeof(past[0]));
  }else if(minutes <= 59 && minutes > 30){
    turnOnLEDs(to, sizeof(to) / sizeof(to[0]));
  }

  if(hour >= 4 && hour < 12){
    turnOnLEDs(in, sizeof(in) / sizeof(in[0]));
    turnOnLEDs(morning, sizeof(morning) / sizeof(morning[0]));
  }else if(hour >= 12 && hour < 16){
    turnOnLEDs(in, sizeof(in) / sizeof(in[0]));
    turnOnLEDs(afternoon, sizeof(afternoon) / sizeof(afternoon[0]));
  }else if(hour >= 16 && hour < 19){
    turnOnLEDs(in, sizeof(in) / sizeof(in[0]));
    turnOnLEDs(evening, sizeof(evening) / sizeof(evening[0]));
  }else if(hour >= 19 || hour < 4){
    turnOnLEDs(at, sizeof(at) / sizeof(at[0]));
    turnOnLEDs(night, sizeof(night) / sizeof(night[0]));
  }

    if(week == 0){
      leds[1] = CRGB::Green;
      leds[30] = CRGB::Green;
      leds[33] = CRGB::Green;
      leds[62] = CRGB::Green;
      leds[65] = CRGB::Green;
      leds[94] = CRGB::Green;
      leds[97] = CRGB::Red;
    }
    if(week == 1){
      leds[1] = CRGB::Red;
      leds[30] = CRGB::Green;
      leds[33] = CRGB::Green;
      leds[62] = CRGB::Green;
      leds[65] = CRGB::Green;
      leds[94] = CRGB::Green;
      leds[97] = CRGB::Green;
    }
    if(week == 2){
      leds[1] = CRGB::Green;
      leds[30] = CRGB::Red;
      leds[33] = CRGB::Green;
      leds[62] = CRGB::Green;
      leds[65] = CRGB::Green;
      leds[94] = CRGB::Green;
      leds[97] = CRGB::Green;
    }
    if(week == 3){
      leds[1] = CRGB::Green;
      leds[30] = CRGB::Green;
      leds[33] = CRGB::Red;
      leds[62] = CRGB::Green;
      leds[65] = CRGB::Green;
      leds[94] = CRGB::Green;
      leds[97] = CRGB::Green;
    }
    if(week == 4){
      leds[1] = CRGB::Green;
      leds[30] = CRGB::Green;
      leds[33] = CRGB::Green;
      leds[62] = CRGB::Red;
      leds[65] = CRGB::Green;
      leds[94] = CRGB::Green;
      leds[97] = CRGB::Green;
    }
    if(week == 5){
      leds[1] = CRGB::Green;
      leds[30] = CRGB::Green;
      leds[33] = CRGB::Green;
      leds[62] = CRGB::Green;
      leds[65] = CRGB::Red;
      leds[94] = CRGB::Green;
      leds[97] = CRGB::Green;
    }
    if(week == 6){
      leds[1] = CRGB::Green;
      leds[30] = CRGB::Green;
      leds[33] = CRGB::Green;
      leds[62] = CRGB::Green;
      leds[65] = CRGB::Green;
      leds[94] = CRGB::Red;
      leds[97] = CRGB::Green;
    }
    

  Serial.print("Current time: ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.print(second);
  Serial.print("-");
  Serial.println(week);

  // Add more conditions for other times
}
void turnOnLEDs(const int* ledIndices, int numLEDs) {
  for (int i = 0; i < numLEDs; i++) {
    leds[ledIndices[i]] = CRGB::White;
  }

}