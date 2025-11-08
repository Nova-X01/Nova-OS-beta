#pragma once

// ---- PINOUT ---- //
#define PIN_LED 2            // Підключаєм системно_платний світлодіод
#define button_LEFT 13       // Підключаєм кнопку LEFT
#define button_RIGHT 12      // Підключаєм кнопку RIGHT
#define button_UP 14         // Підключаєм кнопку UP
#define button_DOWN 27       // Підключаєм кнопку DOWN
#define button_OK 33
#define SD_CS 5              // Підключаєм пін CS SD карти до 5 піна
#define SD_MOSI 23           // MOSI — передача даних
#define SD_MISO 19           // MISO — прийом даних
#define SD_CLK  18           // CLK — тактова лінія
#define BUFFER_SIZE 4096     // Ми будемо зчитувати файл по 4096 байт (4 КБ)
                             // Ми будемо за 1 заход считувати 4 кб. файла з SD
                             // І так ми будемо считувати поки не считаєм весь файл