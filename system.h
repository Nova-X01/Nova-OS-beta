#pragma once             // Захист від подвійного підключення

#include "config.h"
#include <Arduino.h>     // Підключаєм бібліотеку для роботи з Ардуіно функціями
#include <Preferences.h> // Підключаєм бібліотеку для роботи з EPRROM
#include <WiFi.h>        // Підключаєм бібліотеку для роботи з WiFi
#include <HTTPClient.h>  // Підключаєм бібліотеку для роботи з Серверами/HTTP-запитами (GET/POST)
#include <WiFiClientSecure.h>
#include <GyverOLED.h>   // Підключаєм бібліотеку для роботи з Дисплеєм 128х64
#include <GyverButton.h> // Підключаєм бібліотеку для роботи з Кнопками
// #include <GyverTimer.h>  // Підключаєм бібліотеку для роботи з таймерами
#include <Update.h>      // Підключаєм бібліотеку для оновлення прошивки за допомогою SD карти або WiFi
#include <SD.h>          // Підключаєм бібліотеку для роботи з SD картками через SPI шину
#include <SPI.h>         // Підключаєм бібліотеку для роботи з SPI-протоколом


// ----- Об'являєм усі наші функції ----- //
// ----- Системні функції ----- //
void handleButtons(); 
void drawingOLED();
void openProgram(int index);
void seting();
void element(int index, int i);
void button_setting();
void loading_SD_program();
// ----- Програми ----- //
void WiFiManager();
void app_clock();    
void fileexplorer();
void systemInfo();
void systemUpdate();
void notes();
void terminal_button();
void terminal();
void broswer();
// ----- Допоміжні функції для програм ----- //
void WiFiConected(int index_WiFi);  
void listTextFiles(const char * dirname, uint8_t levels);
void string_center(const char *text, int *X, int *Y);   
void ERROR();  

// ----- Файли шляки до програм на SD ----- //
extern const char* firmwarePath;  // Зміна для вказання шляху до ігор
extern const char* system_OS;     // Зміна для збереження шляху до прошивки OS
extern const char* system_version;// Зміна для збереженя шляху до версії прошивки
extern const char* notes_txt;     // Зміна для збереженя шляху до нотаток
extern uint8_t buffer[BUFFER_SIZE];  

// ----- Оголошення об'єктів ----- //
extern Preferences prefs;                           
extern GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
extern File file;                                  // Створюєм об'єкт для роботи з файлами SD карти

extern int visibleItems;

extern int fontSize;      // розмір шрифту
extern int brightness;    // яскравість
extern bool darkMode;     // тема (на майбутнє)


// ----- Оголошення глобальних кнопок ----- // 
extern GButton but_left;     // Підключаєм кнопку LEFT
extern GButton but_right;    // Підключаєм кнопку RIGHT
extern GButton but_up;       // Підключаєм кнопку UP
extern GButton but_down;     // Підключаєм кнопку DOWN
extern GButton but_ok;       // Підключаєм кнопку OK

// ----- Таймери ----- //
extern unsigned long time_button;         // тай мер для кнопок (Лише для одиночного натискання)
extern unsigned long time_menu_scrol;     // Таймер для скролу меню
extern unsigned long time_oled;           // Таймер для дисплея
extern unsigned long time_delay;          // Таймер для різних системних затримок
extern unsigned long time_text;           // Таймер для моргання знаку

// ----- Інтервали ----- // 
extern int time_react;         // Швидкісь обробки натискань кнопок (Лише для одиночного натискання)
extern int time_text_millis;          // Швидкіть моргання знаку

// ----- Курсор ----- //
extern int current;

// ----- Відкслідкування кординат букв ----- //
extern int char_x;
extern int char_y;

// ----- Стани Системи ----- //
enum SystemState {
  MENU,            // головне меню                0
  APP_SETTINGS,    // програма "Налаштування"     1
  APP__WiFiMANAGER,// програма "WiFi менеджер"    2
  APP_CLOCK,       // програма "Годинник"         3
  APP_FILEEXPLORER,// Програма керування SD       4
  APP_SYSTEMINFO,  // Програма перегляду системних характеристик та настройок                  5
  APP_UPDATER,     // Програма для оновлення системи за допомогою WiFi                         6
  APP_CALKULATOR,  // Програма калькулятор        7
  APP_NOTES,       // Програма нотатки            8
  APP_TERMINAL,    // Програма для управління всієї операційною системою                       7
  APP_BROSWER,     // Програма браузер 1 вбудована в систему, а росширена записана на SD карту 8
};
extern SystemState state;