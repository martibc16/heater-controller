void updateDate() {
  setTime(hora, minut, 0, dia, mes, any);
  RTC.set(now());

}


void getDate() {
  hora = hour();
  minut = minute();
  dia = day();
  mes = month();
  any = year();
}

TOGGLE(autoProgACS,ACSonoff,"Prog ACS: ",doNothing,noEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);

CHOOSE(progACS, triarProg, "Mode ACS:", doNothing, noEvent, noStyle
       , VALUE("Auto", 0, doNothing, noEvent)
       , VALUE("ON", 1, doNothing, noEvent)
       , VALUE("ON Perm", 2, doNothing, noEvent)
       , VALUE("OFF Perm", 3, doNothing, noEvent)
      );

MENU(canviarHora, "Ajustar Data", doNothing, noEvent, noStyle
     , OP("Obtenir hora", getDate, enterEvent)
     , FIELD(hora, "Hora ", "", 0, 23, 1, 0, doNothing, noEvent, wrapStyle)
     , FIELD(minut, "Minut ", "", 0, 59, 10, 1, doNothing, noEvent, wrapStyle)
     , FIELD(dia, "Dia ", "", 1, 31, 1, 0, doNothing, noEvent, wrapStyle)
     , FIELD(mes, "Mes ", "", 1, 12, 1, 0, doNothing, noEvent, wrapStyle)
     , FIELD(any, "Any ", "", 2018, 2022, 1, 0, doNothing, noEvent, wrapStyle)
     , OP("Guardar", updateDate, enterEvent)
     , EXIT("<Back")
    );

MENU(mainMenu, "Menu principal", doNothing, noEvent, wrapStyle
     , FIELD(tACS, "Temp ACS ", " C", 0, 100, 0, 0, doNothing, enterEvent, wrapStyle)
     , FIELD(tSetACS, "Set ACS ", " C", 10, 75, 10, 5, doNothing, enterEvent, wrapStyle)
     , FIELD(tTAIACS, "IMP ACS ", " C", 0, 100, 0, 0, doNothing, enterEvent, wrapStyle)
     , FIELD(tTAICal, "IMP Cal ", " C", 0, 100, 0, 0, doNothing, enterEvent, wrapStyle)
     , SUBMENU(triarProg)
     ,SUBMENU(ACSonoff)
     , FIELD(deltaT, "Delta ACS ", " C", 1, 8, 1, 1, doNothing, enterEvent, wrapStyle)
     , SUBMENU(canviarHora)
    // , EXIT("<Back")
    );



//describing a menu output device without macros
//define at least one panel for menu output
const panel panels[] MEMMODE = {{0, 0, 128 / fontW, 64 / fontH}};
navNode* nodes[sizeof(panels) / sizeof(panel)]; //navNodes to store navigation status
panelsList pList(panels, nodes, 1); //a list of panels and nodes
idx_t tops[MAX_DEPTH] = {0, 0}; //store cursor positions for each level

#ifdef LARGE_FONT
SSD1306AsciiOut outOLED(&oled, tops, pList, 8, 2); //oled output device menu driver

#else
SSD1306AsciiOut outOLED(&oled, tops, pList, 5, 1); //oled output device menu driver
#endif

menuOut* constMEM outputs[]  MEMMODE  = {&outOLED}; //list of output devices
outputsList out(outputs, 1); //outputs list

#ifdef NAV_BUTTONS_INPUT_PULLUP
//build a map of keys to menu commands
keyMap joystickBtn_map[] = {
  { -BTN_SEL, defaultNavCodes[enterCmd].ch} ,
  { -BTN_UP, defaultNavCodes[upCmd].ch} ,
  { -BTN_DOWN, defaultNavCodes[downCmd].ch}  ,
  { -BTN_ESC, defaultNavCodes[escCmd].ch}  ,
};
keyIn<TOTAL_NAV_BUTTONS> joystickBtns(joystickBtn_map);//the input driver
#else
//build a map of keys to menu commands
keyMap joystickBtn_map[] = {
  { BTN_SEL, defaultNavCodes[enterCmd].ch} ,
  { BTN_UP, defaultNavCodes[upCmd].ch} ,
  { BTN_DOWN, defaultNavCodes[downCmd].ch}  ,
  { BTN_ESC, defaultNavCodes[escCmd].ch},
};
keyIn<TOTAL_NAV_BUTTONS> joystickBtns(joystickBtn_map);//the input driver
#endif

NAVROOT(nav, mainMenu, MAX_DEPTH, joystickBtns, out);
