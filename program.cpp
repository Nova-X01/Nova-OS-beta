// ----- СИСТЕМНІ ПРОГРАМИ ----- // 
#include "config.h"
#include "system.h"

// ----- Зміна курсор для інших програм ----- //
int new_current = 0;
int x, y;
int n;   // Зміна для збереження даних про WiFi

bool WiFi_flag = true;
bool TEXT_flag = true;
bool NOTES_flag = true;
bool NOTES_LIST_flag = true;
int menu_list = 1;

String menuTXTnotes [] = {

};

char letter [50] = {};

// ----- Обща функція для кнопок для всіх програм ----- //
void button_setting() { // Функція дла обробки кнопок у програмі настройки
  if (millis() - time_button > time_react) {
    time_button = millis();

    if (digitalRead(button_UP) == LOW) { // Кнопка для підняття курсору вгору
      if (new_current > 0) {             
        new_current--;
      } else new_current = 0;
    }

    if (digitalRead(button_DOWN) == LOW) {  // Кнопка для упуш=щення курсору у низ
      if (new_current < 8) {
        new_current++;
      } else {
        new_current = 0;
      }
    }

    // ----- Функціональні кнопки для налаштувань та функцій
    if (digitalRead(button_LEFT) == LOW) {    // Кнопка для зменшення параметрів
      element(new_current, -1);
      
    }

    if (digitalRead(button_RIGHT) == LOW) {   // Кнопка для збільшення параметрів
      element(new_current, +1);
    }
    

    if (digitalRead(button_OK) == LOW) { // Кнопка для виходу з програм
      delay(100);
      if (state == APP_SETTINGS) {   // Якщо зараз у нас відкриті налаштування 
          prefs.begin("SetingUSER", false); // відкриваємо простір, false - означає записування даних

          // ----- Яскравість OLED ----- //
          prefs.putInt("oledContrast", brightness);  // Записуєм у EPPROM нове значення яскравості дисплею
          // ----- Розмір шрифту ----- //
          prefs.putInt("fontSize", fontSize);        // Записуєм у EPPROM нове значення розміру шрифту  
          // ----- Кількість видимих елементів у меню ----- //
          prefs.putInt("visibleItems", visibleItems);// записуєм у EPPROM нове значення для відображення елементів на одній сторінці  
          prefs.end();
          // ----- Оновлюєм параметри ----- //
          oled.setScale(fontSize);
          oled.setContrast(brightness);
      }
      if (state == APP__WiFiMANAGER) {
        WiFi_flag = true;
      }
      if (state = APP_NOTES) {
        menu_list = 1;
        NOTES_LIST_flag = true;
      }
      state = MENU;                      // Встановлюєм стан системи меню
    }
  }
}
void element(int index, int i) { // Функція для обробки різних елементів у різних програмах
  switch(index) {
    case 0: 
    if (state == APP__WiFiMANAGER) n = WiFi.scanNetworks(); // Шукаєм усі доступні мережі та записуєм їх у n
    // ----- Якщо вибрана програма notes ----- //
    if (state == APP_NOTES) menu_list = 2; NOTES_flag = false; new_current = 0;
    break;
    case 1: 
    if (state == APP_SETTINGS) {                    // Якщо стан APP_SETTINGS
      fontSize = constrain(fontSize + i, 1, 2);
      if (fontSize == 1) visibleItems = 8;
      if (fontSize == 2) visibleItems = 4;
      oled.setScale(fontSize);

    }
    // ----- Якщо вибрана програма WiFi Manager ----- //
    if (state == APP__WiFiMANAGER) {
      WiFiConected(index);          // Функція для підключення до WiFi index = new_current
    }

    // ----- Якщо вибрана програма notes ----- //
    if (state == APP_NOTES) menu_list = 2; NOTES_flag = true; new_current = 0;
    break;
    case 2:
    if (state == APP_SETTINGS) {                     // Якщо стан APP_SETTINGS
      brightness = constrain(brightness + i, 10, 255);
      oled.setContrast(brightness);
    } break;
  }

}


// ----- Програма Настройки ----- //
void seting() { // Функція для відображення програми настройки
  const char* text = "SETTINGS";
  int textWidth = strlen(text);
  string_center(text, &x, &y); // ----- Функція для центрування тексту по центру

  // ----- Перевіряєм таймер ----- // 
  if (millis() - time_oled > 30) {
    time_oled = millis();
    oled.clear();         // Чистим дисплей
    oled.setCursor(x, 0); // встановлюєм кординати для тексту SETING
    oled.print("SETTINGS"); // Виводим надпись SETING на дисплей

    oled.setCursor(12, 2 * fontSize);
    oled.print("fontsize:");
    oled.println(fontSize);

    oled.setCursor(12, 3 * fontSize);
    oled.print("contrast:");
    oled.println(brightness);

    // ----- Виведення курсору на дисплей ----- //
    
    oled.setCursor(0, (new_current + 1) * fontSize); // налаштовуєм виведення так щоб автоматично підлаштовуватися під розмір шрифту
    oled.print(">");

    oled.update(); // оновлюєм дисплей
  }
}




// ----- Програма WiFi менеджер ----- //
void WiFiManager() {
  if (WiFi_flag == true) {
    new_current = 0;             // Ставим курсор на нольову кординату по y
    WiFi.mode(WIFI_STA);         // Вмикаєм режим STA клієнтьський режим WiFi
    WiFi.disconnect();           // Розриваєм з'єднання якщо WiFi вже був підключений  
    WiFi_flag = false;
    delay(100);                  // Пауза щоб драйвер перемкнувся у новий стан
  }
  

  if (millis() - time_oled > 30) { //
    time_oled = millis();                 
    oled.clear();
    
    if (n == 0) {
      oled.setCursor(12, 0);
      oled.print("WiFi not");
    } else {
      
      oled.setCursor(12, 0);
      oled.print("update ");
      if (WiFi.status() == WL_CONNECTED) {
        IPAddress ip = WiFi.localIP(); // Записуєм у об'єкт IP адресу ESP32 отриману від роутера
        oled.print(ip.toString());
      }
    }
    for (int i = 0; i < n; i++) {
      oled.setCursor(12, (i + 1) * fontSize);            // Встановлюєм кординати
      oled.print(i);                    // Виводим номер мережі
      oled.print(":");
      oled.print(WiFi.SSID(i).c_str()); // Виводим назву мережі або мереж
      oled.print(WiFi.RSSI(i));         // Виводим рівень сигналу мережі
    }
    oled.setCursor(0, new_current * fontSize);
    oled.print(">");



    oled.update();
  }
}




// ----- Програма годиник ----- //
void app_clock() {

}

 

// ----- Програма файловий менеджер SD ----- //
void fileexplorer() {

}


// ----- Програма для считування стану системи ----- //
void systemInfo() {
  if (millis() - time_oled > 30) {
    time_oled = millis();
    oled.clear();
    oled.setCursor(12, 0);            // Виводим назву чіпа
    oled.print("Name:");
    oled.print(ESP.getChipModel());

    oled.setCursor(12, 1 * fontSize); // Виводим версію чіпа
    oled.print("Ver:");
    oled.print(ESP.getChipRevision());

    oled.setCursor(12, 2 * fontSize); // Виводим кількість ядер
    oled.print("Core:");
    oled.print(ESP.getChipCores());

    oled.setCursor(12, 3 * fontSize); // Виводим частоту процесора
    oled.print("Freq:");
    oled.print(ESP.getCpuFreqMHz());
    oled.print("MHz");


    oled.setCursor(12, 4 * fontSize);
    oled.print("V.1");

    oled.setCursor(0, new_current * fontSize);    // Виводим курсор
    oled.print(">");

    oled.update();
    }
}


// ----- Програма oновлення прошивки OS ----- //
void systemUpdate() {
  if (millis() - time_oled > 30) {
    time_oled = millis();
    ERROR();
  }
}


void notes() {
  if (millis() - time_oled > 30) {
    time_oled = millis();
    oled.clear();
    
    // ----- Меню: 1 ----- //
    if (menu_list == 1) {
      oled.setCursor(12, 0);
      oled.print("Read notes");

      oled.setCursor(12, 1 * fontSize);
      oled.print("Enable notes");
    }
    if (menu_list == 2) { // Меню зі всіма нотатками для читання
      listTextFiles(notes_txt, 1); // Викликаєм функцію для виведення текстових документів нотаток на дисплей
                                   // notes_txt - Путь до файлів нотаток     1 - скфльки можна відкривати під папок
      const int menuTXTnotess = sizeof(menuTXTnotes) / sizeof(menuTXTnotes[0]);
      for (int i = 0; i < menuTXTnotess; i++) {
        oled.setCursor(12, i);
        oled.print(menuTXTnotes[i]);
      }  

    }                    
    
                  
    

    // ----- Курсор ----- //
    oled.setCursor(0, new_current * fontSize);
    oled.print(">");

    oled.update();
  
  }
}
void listTextFiles(const char * dirname, uint8_t levels) {
  if (NOTES_LIST_flag) {
    File root = SD.open(dirname); // Відкриваєм папку за вказаним шляхом dirname

    if (!root) {  // Перевіряєм чи відкрилася тека
      Serial.println("❌ Не можу відкрити теку");
      state = MENU;
    }
    if (!root.isDirectory()) { // Перевіряєм чи ми точно відкриваєм папку
      Serial.println("❌ Це не тека");
      state = MENU;
    }
    File file = root.openNextFile(); // відкриваєм перший файл або папку яка містиця за вказаним шляхом dirname

    oled.clear();
    int i = 0;
    while (file) {
      // ----- Читання файлів ----- //
                        // Якщо це не папка а файл
      String name = file.name(); // Считуєм ім'я файла та записуєм у зміну name
      if (name.endsWith(".txt")) {

        menuTXTnotes [i] = name;

        oled.setCursor(12, i);
        oled.print(name);
        i++;   
      }
      
    file.close();              // Закриваєм старий файл
    file = root.openNextFile();// Відкриваєм наступний файл
    }
    oled.update();
    NOTES_LIST_flag = false;
  }
}



int let = 0;
int x_text = 0;
int y_text = 4;
// ----- Програма термінал ----- //
void terminal_button() {
  if (millis() - time_button > time_react) {
    time_button = millis();

    if (digitalRead(button_UP) == LOW) { // UP
      if (y_text != 4) {
        y_text--;
      } 
    }
    if (digitalRead(button_DOWN) == LOW) {
      if (y_text < 7) {
        y_text++;
      } else y_text = 7;
    }
    if (digitalRead(button_LEFT) == LOW) {
      if (x_text > 0) {
        x_text -= 12;
      } else x_text = 0;
    }
    if (digitalRead(button_RIGHT) == LOW) {
      if (x_text < 120) {
        x_text += 12;
      } else x_text = 120;
    }
    if (digitalRead(button_OK) == LOW) {
      switch (y_text) {
        case 4:
        if (x_text == 0) letter[let] = 'q';
        else if (x_text == 12) letter[let] = 'w';
        else if (x_text == 24) letter[let] = 'e';
        else if (x_text == 36) letter[let] = 'r';
        else if (x_text == 48) letter[let] = 't';
        else if (x_text == 60) letter[let] = 'y';
        else if (x_text == 72) letter[let] = 'u';
        else if (x_text == 84) letter[let] = 'i';
        else if (x_text == 96) letter[let] = 'o';
        else if (x_text == 108) letter[let] = 'p';
        else if (x_text == 120) letter[let] = 'a';
        break;
        case 5:
        if (x_text == 0) letter[let] = 's';
        else if (x_text == 12) letter[let] = 'd';
        else if (x_text == 24) letter[let] = 'f';
        else if (x_text == 36) letter[let] = 'g';
        else if (x_text == 48) letter[let] = 'h';
        else if (x_text == 60) letter[let] = 'j';
        else if (x_text == 72) letter[let] = 'k';
        else if (x_text == 84) letter[let] = 'l';
        else if (x_text == 96) letter[let] = ';';
        else if (x_text == 108) letter[let] = '`';
        else if (x_text == 120) letter[let] = '[';
        break;
        case 6:
        if (x_text == 0) letter[let] = '[';
        else if (x_text == 12) letter[let] = '{';
        else if (x_text == 24) letter[let] = '}';
        else if (x_text == 36) letter[let] = 'z';
        else if (x_text == 48) letter[let] = 'x';
        else if (x_text == 60) letter[let] = 'c';
        else if (x_text == 72) letter[let] = 'v';
        else if (x_text == 84) letter[let] = 'b';
        else if (x_text == 96) letter[let] = 'n';
        else if (x_text == 108) letter[let] = 'm';
        else if (x_text == 120) letter[let] = ',';
        break;
        case 7:
        if (x_text == 0) letter[let] = '.';
        else if (x_text == 12) letter[let] = '/';
        else if (x_text == 24) letter[let] = '|';
        break;
      }
      char_x += 6;
    let++;
    letter[let] = '\0';   // ← важливо!
    }

  }
}


void terminal() {
  
  if (millis() - time_oled > 30) {
    time_oled = millis();
    oled.clear();

    // ----- Вивід клавіатури ----- //
    oled.setCursor(0, 4);
    oled.print("q w e r t y u i o p a");
    oled.setCursor(0, 5);
    oled.print("s d f g h j k l ; ' ]");
    oled.setCursor(0, 6);
    oled.print("] { } z x c v b n m ,");
    oled.setCursor(0, 7);
    oled.print(". / | ");
    oled.setCursor(x_text, y_text);
    oled.print("_");
    // ----- Вивід тексту ----- //
    const int char_letter = sizeof(letter) / sizeof(letter[0]);
    for (int i = 0; i < char_letter; i++) {
      oled.setCursor(i * 6, 0);
      oled.print(letter[i]);
    }


    if (millis() - time_text > time_text_millis) { // Таймер відображення знаку _
      time_text = millis();
      TEXT_flag = !TEXT_flag;
    }
    oled.setCursor(char_x, char_y);
    if (TEXT_flag) oled.print("_"); // Відображаєм знак
    else oled.print("");            // не відображаєм знак

    oled.update();
  }
}


// ----- Пограма браузер ----- //
void broswer() {

}



// ----- Допоміжні функції для програм ----- //
// ----- Функція підключення до вайфай ----- //
void WiFiConected(int index_WiFi) {
  int selected = index_WiFi;   // вибрана мережа за курсором

  if (selected > 0 && selected <= n) {       // Перевіряєм чи мережа вибрана вірно
    String ssid = WiFi.SSID(selected - 1);   // Записуєм назву мережі по скільки ми використовуєм курсор потрібно віднімати 1
    if (ssid.length() == 0) {                // Якщо помилка при запусу назви мережі
      Serial.println("❌ Порожній SSID, пропускаю.");
      oled.clear();
      oled.home();
      oled.print("error ssid");
      oled.update();
      delay(1000);
      return;                                // Повертаємося назад в програму
    }

    String pass; // Створюєм зміну для храненія пароля
    if (WiFi.encryptionType(selected) != WIFI_AUTH_OPEN) {  // Перевіряєм чи закрита мережа
      pass = "12345678";                                    // тимчасово — пізніше буде введення користувачем
    }

    Serial.printf("🔗 Підключення до '%s'...\n", ssid.c_str());
    WiFi.begin(ssid.c_str(), pass.c_str());  // Пробуєм підключитися до иережі

    unsigned long start = millis();   
    while (millis() - start < 15000) {          // Даєм мікроконтролеру 15 сек. на підключення до мережі
      if (millis() - time_delay > 200) { 
        time_delay = millis(); 
        if (WiFi.status() == WL_CONNECTED) break; // Якщо підключилися виходим з циклу
      }
    }

    if (WiFi.status() == WL_CONNECTED) {        // Якщо підключилися до WiFi
      Serial.println("✅ Wi-Fi підключено!"); 
      prefs.begin("wifi", false);    //  Відкриваєм простір wifi
      prefs.putString("ssid", ssid); // Записуєм назву мережі ssid
      prefs.putString("pass", pass); // Записуєм пароль pass
      prefs.end();                   // Закриваємо EPRROM та зберігаєм

      IPAddress ip = WiFi.localIP(); // Записуєм у об'єкт IP адресу ESP32 отриману від роутера
      oled.clear();
      oled.home();
      oled.print("WiFi conected!");   // Виводим текст про успішне підключення до WiFi
      oled.setCursor(0, 1 * fontSize);
      oled.print(ip.toString());      // Виводим ip адресу на дисплей
      oled.update();
      delay(1500);
    } else {                          // Якщо не підключилися до WiFi 
      Serial.println("❌ Не вдалося підключитись");
      WiFi.disconnect();
      oled.clear();
      oled.home();
      oled.print("WiFi error");
      oled.update();
      delay(1000);
    }

  } else {
    Serial.println("Невірний індекс вибраної мережі!");
  }
}

// ----- Функція для встановлення тексту по центру на дисплеї ----- //
void string_center(const char *text, int *X, int *Y) { 
  int textWidth = strlen(text) * 6;  // 6 пікселів на символ
  *X = ((128 - textWidth) / 2) / fontSize;        // центр по ширині
  *Y = (8 / fontSize) + 1;           // фіксована висота (середина по Y)
}


// ----- Функція для виведення файлів нотаток на дисплей ----- //









void ERROR() {
  oled.clear();
  oled.home();
  oled.print("Server is");
  oled.setCursor(0, 1 * fontSize);
  oled.print("not working :(");
  oled.update();
}











// ----- Програми які потрібно завантажувати з SD ----- //
void loading_SD_program() {      // Функція для читання програм з SD картки за запуску їх
  if (!SD.exists(firmwarePath)) {// Перевіряєм чи існує файл який ми хочемо відкрити
    Serial.println("❌ Помилка: файл прошивки не знайдено!"); // Якщо такого не існую
    state = MENU; // Встановлюєм початковий стан системи
    oled.clear();
    oled.home();
    oled.print("ERROR");
    oled.update();// Виводим на дисплей повідомлення про помилку
    delay(2000);  // Чекаєм 2 секунди
    return;       // Виходимо з програми якщо файл не знайдено    
  }
  Serial.println("✅ Файл прошивки знайдено!");
  // Відкриваємо файл для читання
  File updateBin = SD.open(firmwarePath, FILE_READ);  // Відкриваєм файл у режимі читання 
  if (!updateBin) {                                   // Перевірка чи файл відкрився
    Serial.println("❌ Помилка: не вдалось відкрити файл!"); // Якщо файл не відкрився 
    state = MENU; // Встановлюєм початковий стан системи
    oled.clear();
    oled.home();
    oled.print("ERROR update");
    oled.update();// Виводим на дисплей повідомлення про помилку
    delay(2000);  // Чекаєм 2 секунди
    return;       // Виходимо з програми якщо файл не знайдено  
    
  }
  size_t updateSize = updateBin.size(); // Читаєм скільки займає програма у байтах за допомогою size та записуєм у uupdateSize
  Serial.println(updateSize);           // Виводим у ком порт скіль зацймає прошивка

  // Гатуємо ESP32 до запису нової прошивки
  if (!Update.begin(updateSize)) {   // updateSize — розмір файлу // Інцілізує ОТА модуль для запису прошивки у Флеш
    Serial.println("❌ Помилка під час підготовки Update.begin()"); // Якщо сталася помилка
    state = MENU; // Встановлюєм початковий стан системи
    oled.clear();
    oled.home();
    oled.print("ERROR update.0");
    oled.update();// Виводим на дисплей повідомлення про помилку
    delay(2000);  // Чекаєм 2 секунди
    return;       // Виходимо з програми 
  }
  // Лічильники для прогресу
  size_t written = 0; // скільки байт уже записано
  // Починаєм цикл зчитування та запису прошивки
  while(updateBin.available()) { // Цикл продовжується поки у файлі є ще дані
    size_t bytesRead = updateBin.read(buffer, BUFFER_SIZE); // читаємо 4096 байт з SD та записуєм у буфер
    Update.write(buffer, bytesRead);                        // Записуєм частину з buffer у флеш память ESP32
    written += bytesRead;                                   // Додаєм до личильника written скільки байт уже записано
    int progress = (written * 100) / updateSize;            // Тут обчислюєм прогрес у віцотки та виводимо у монітор Serial
    Serial.print("\rПрогрес: ");
    Serial.print(progress);
    Serial.print("%");
  }

  if (!Update.end(true)) {  // Завершуєм процес запису
    Serial.println("Помилка при завершені процесу запису");
    oled.clear();
    oled.home();
    oled.print("ERROR end");
    oled.update();
    delay(2000);
    return;
  }
  if (Update.hasError()) { // Перевіряєм чи були помилки під час оновлення (Запису у флеш)
    Serial.println("ERROR UPDATE"); // Пишем про помилку у Serial
  } else { // Якщо у се добре то виконуєм далі
    oled.clear();
    oled.home();
    oled.print("loading...");
    oled.update();
    delay(2000);
    ESP.restart(); // Перезапускаєм ESP32 для запуску нової прошивки
  }

}




