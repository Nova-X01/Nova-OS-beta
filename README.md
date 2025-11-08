# Nova-OS-beta
🧠 Nova OS — вбудована операційна система для ESP32

Nova OS — це міні-операційна система для ESP32 із графічним інтерфейсом на OLED-дисплеї, файловою системою SD, підтримкою Wi-Fi та системою додатків.
Проєкт створено з метою розробити повноцінну модульну платформу, що дозволяє запускати різні програми без необхідності перепрошивки контролера.

⚙️ Можливості

📂 Файлова система SD із завантаженням додатків у форматі .bin

🧭 Меню з прокруткою та динамічним курсором

💾 EEPROM-збереження налаштувань (шрифт, яскравість, кількість пунктів меню)

🌐 Wi-Fi-менеджер із автоматичним підключенням

🧮 Вбудовані програми: Notes, Terminal, Settings, File Explorer

🕹 Зовнішні програми: Snake, Paint, Tetris, DoomMini, Music Player (завантажуються з SD-карти)

💡 Модульне ядро системи, написане на C++ (Arduino Framework)

🧱 Апаратна частина

ESP32 DevKit V1

OLED-дисплей SSD1306 (I2C або SPI)

Модуль SD-карти (SPI)

5 кнопок: UP, DOWN, LEFT, RIGHT, OK

(Додатково): динамік, Wi-Fi, світлодіоди, живлення від Li-ion акумулятора

🚧 Статус проєкту

На даний момент проєкт перебуває у стадії активної розробки (v0.8 Prototype).

Поточний стан:

🧾 Notes працює, але нестабільно — можливі зависання при читанні текстових файлів з SD.

💻 Більшість програм ще не завершені або знаходяться на етапі тестування.

⚙️ Основне ядро та система меню — стабільні.

💡 У планах — додати кольоровий дисплей, аудіосистему, графічні іконки та оптимізувати управління пам’яттю.

👨‍💻 Автор

Створено Nova-X — розробником апаратного та програмного забезпечення.
Слідкуй за моїм прогресом: [https://github.com/Nova-X01]




🧠 Nova OS — Embedded Operating System for ESP32

Nova OS is a mini operating system for the ESP32, featuring an OLED graphical interface, SD-based file system, Wi-Fi support, and a modular app system.
The project aims to create a lightweight yet functional embedded platform capable of running standalone applications without reflashing the controller.

⚙️ Features

📂 SD-based file system with .bin app loading

🧭 Scrollable menu navigation with dynamic cursor

💾 EEPROM-stored settings (font size, brightness, menu count)

🌐 Wi-Fi Manager with auto-connect support

🧮 Built-in apps: Notes, Terminal, Settings, File Explorer

🕹 External apps: Snake, Paint, Tetris, DoomMini, Music Player (loaded from SD card)

💡 Modular system core written in C++ (Arduino Framework)

🧱 Hardware

ESP32 DevKit V1

SSD1306 OLED display (I2C or SPI)

MicroSD card module (SPI)

5 buttons: UP, DOWN, LEFT, RIGHT, OK

(Optional): speaker, Wi-Fi, LEDs, Li-ion battery power module

🚧 Project Status

Currently in active development (v0.8 Prototype).

Current State:

🧾 Notes app works but is unstable — may freeze while reading text files from SD.

💻 Most apps are still unfinished or under testing.

⚙️ The core system and menu navigation are stable.

💡 Future plans: add color TFT display support, audio system, graphical icons, and improve memory management.

👨‍💻 Author

Created by Nova-X — hardware & software developer.
Follow my progress: [https://github.com/Nova-X01]
