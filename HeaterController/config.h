
/*config.h*/

/* List of Supported Fonts

  Arial14,
  Arial_bold_14,
  Callibri11,
  Callibri11_bold,
  Callibri11_italic,
  Callibri15,
  Corsiva_12,
  fixed_bold10x15,
  font5x7,    //Do not use in LARGE_FONT, can use as default font
  font8x8,
  Iain5x7,    //Do not use in LARGE_FONT, can use as default font
  lcd5x7,     //Do not use in LARGE_FONT, can use as default font
  Stang5x7,   //Do not use in LARGE_FONT, can use as default font
  System5x7,  //Do not use in LARGE_FONT, can use as default font
  TimesNewRoman16,
  TimesNewRoman16_bold,
  TimesNewRoman16_italic,
  utf8font10x16,
  Verdana12,
  Verdana12_bold,
  Verdana12_italic,
  X11fixed7x14,
  X11fixed7x14B,
  ZevvPeep8x16

*/


/*
   Incloem llibreries
*/

#include <menu.h>

#include <EEPROM.h>

#include <TimeLib.h>
#include <TimeAlarms.h>
#include <DS3232RTC.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <menu.h>
#include <menuIO/SSD1306AsciiOut.h>
#include <menuIO/keyIn.h>


/*
   Definim sortides a optoacopladors
*/
#define PINACS 33
#define PINCALE 37
#define PINFAT 32 //actuador Foc a Terra
#define PINCALDERA 41

/*
 * Definim entrades digitals
 */
#define PINTERMOSTAT 49
#define PINBOMBACIR 8
#define PINTERMOFAT 10


/*
   Definim variables calefaccio
*/
 short int tACS ;
unsigned short int tSetACS;
unsigned short int deltaT; //hysteresis for the DHW tank
bool ACSON;
unsigned short int progACS = 0; //0 auto, 1 on, 2 on-perm, 3 off-per
bool autoProgACS=false; //true-on false-off
short int tTAIACS;
short int tTAICal;
bool termostatActiu;
bool FATactiu;
bool canviEstat;

unsigned short int hora, minut, dia, mes;
unsigned short int any = 2019;

unsigned long int tempsStandby;
unsigned long int refreshEeprom;

/*
   OneWire Definitions
*/
const int pinDatosDQ = 5; //onewire
OneWire oneWireBus(pinDatosDQ);
DallasTemperature sensors(&oneWireBus);
DeviceAddress TAICal = {0x28, 0xFF, 0x6A, 0x1B, 0x32, 0x18, 0x02, 0xFF};
DeviceAddress TAIACS = {0x28, 0xD6, 0x08, 0x30, 0x0A, 0x00, 0x00, 0x74};
DeviceAddress ACS = {0x28, 0x24, 0xD2, 0x45, 0x92, 0x11, 0x02, 0x3B};
int  resolution = 12;
unsigned long lastTempRequest = 0;
int  delayInMillis = 0;

float RawHighACS = 100.37;
float RawLowACS = 0.44;
float RawHighTAIACS = 101.31;
float RawLowTAIACS = 1.06;
float RawHighTAICal=100;
float RawLowTAICal=0;

float ReferenceHigh = 99.8;
float ReferenceLow = 0;
float ReferenceRange = ReferenceHigh - ReferenceLow;

unsigned long tempsActiu=0;

#define OLED_I2C_ADDRESS 0x3C     
#define I2C_ADDRESS 0x3C
SSD1306AsciiWire oled;

// Define proper RST_PIN if required.
#define RST_PIN -1


/*
   Define your font from the list.
   Default font: lcd5x7
   Comment out the following for using the default font.
*/
#define LARGE_FONT TimesNewRoman16

//Navigate buttons
#define BTN_SEL     25                 // Select button
#define BTN_UP      24                 // Up Button
#define BTN_DOWN    26                 // Down Button
#define BTN_ESC     23                 // Exit Button
// Comment the following to disable internal pullup for Navigate buttons
#define NAV_BUTTONS_INPUT_PULLUP

#define TOTAL_NAV_BUTTONS 4       // Total Navigation Button used



#define MAX_DEPTH 2

#ifdef LOC
// #define LARGE_FONT
#define INV
#endif

/*Do not change the values(recomended)*/
#ifdef LARGE_FONT
#define menuFont LARGE_FONT
#define fontW 8
#define fontH 16
#else
// #define menuFont System5x7
#define menuFont lcd5x7
#define fontW 5
#define fontH 8
#endif
