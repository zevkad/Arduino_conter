//  NANO_Counter_LCD
#include <LiquidCrystal.h>
#include <EEPROM.h>
// , E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int address = 0; // адрес ячейки
int i;
long value;
long value0, value1, value2; // значение данных
long val, val0, val1, val2; // значение данных
int stan = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const long interval = 4800;

void setup()
{
  pinMode(12, OUTPUT); // RS
  pinMode(11, OUTPUT); // E
  pinMode(2, OUTPUT);  // DB4
  pinMode(3, OUTPUT);  // DB5
  pinMode(4, OUTPUT);  // DB6
  pinMode(5, OUTPUT);  // DB7
  pinMode(10, OUTPUT); // PWM - яркость LCD
  pinMode(7, INPUT_PULLUP);  // Reset
  pinMode(8, INPUT_PULLUP);  // bonbon start
  pinMode(9, OUTPUT);  // buzzer

  analogWrite(10, 5); // PWM - яркость LCD
  stan = HIGH;

  /* Valera DELETE me */
  /* Инициализируем дисплей: 2 строки по 16 символов */
  lcd.begin(16, 2);
  // Выводим на дисплей фразу приветствия

  lcd.print("   Hello!!!");
  lcd.setCursor(0, 1);
  delay(500);
  lcd.print("Bombon counter");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("www.newcom.cv.ua");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("      2016     ");
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("  -- Counter -- ");
  lcd.setCursor(0, 1);
  lcd.print("Piese =         ");

  // Чтение EEPROM
  value0 = EEPROM.read(address);
  delay(5);
  value1 = EEPROM.read(address + 1);
  delay(5);
  value2 = EEPROM.read(address + 2);
  delay(5);

  lcd.setCursor(8, 1);
  lcd.print(value2, DEC);
  lcd.print(value1, DEC);
  lcd.print(value0, DEC);
  value = value2 * 10000 + value1 * 100 * value0;
  if (value > 99999) {
    value = 0;
  }
  //  value = 1;
}

void loop()
{
 // lcd.setCursor(0, 0);
 // lcd.print("  -- Counter -- ");

  if (digitalRead(8) == LOW && stan == HIGH) {
    value = value + 1;
    stan = LOW;

    value0 = value % 100;
    val = value / 100;
    val0 = byte(value0);

    value1 = val % 100;
    val = val / 100;
    val1 = byte(value1);

    value2 = val % 100;
    val2 = byte(value2);

    delay (10);
    EEPROM.write(address, val0);  // Запись в EEPROM
    delay (10);
    EEPROM.write(address + 1, val1); // Запись в EEPROM
    delay (10);
    EEPROM.write(address + 2, val2); // Запись в EEPROM
    delay (10);
    for (i == 0; i <= 16; i++) {
      delay(300);
      lcd.setCursor(i, 0);
      lcd.print(">");
    }
    i = 0;
    lcd.setCursor(0, 0);
    lcd.print("  -- Counter -- ");
    lcd.setCursor(0, 1);
    lcd.print("Piese =            ");
    lcd.setCursor(8, 1);
    lcd.print(value);

    delay(1000);
  }

  if (digitalRead(8) == HIGH) {
    stan = HIGH;
  }
  // Сброс показаний счетчика нажатием кнопки в течении 5 сек.
  currentMillis = millis();
  if (digitalRead(7) == HIGH) {
    previousMillis = currentMillis;
    lcd.setCursor(0, 0);
    lcd.print("  -- Counter -- ");    
  }
  else {
    
    lcd.setCursor((int(currentMillis - previousMillis) / 300), 0);
    lcd.print("*");
  }

  if (digitalRead(7) == LOW && currentMillis - previousMillis >= interval ) {
    value = 0;
    delay (10);
    EEPROM.write(address, 0);  // Запись в EEPROM
    delay (10);
    EEPROM.write(address + 1, 0); // Запись в EEPROM
    delay (10);
    EEPROM.write(address + 2, 0); // Запись в EEPROM
    delay (10);
//    for (i == 0; i <= 16; i++) {
 //     delay(300);
//      lcd.setCursor(i, 0);
//      lcd.print("<");
//    }
//     i = 0;
    // Выводим на дисплей фразу приветствия
    lcd.setCursor(0, 0);
    lcd.print("   Hello!!!");
    lcd.setCursor(0, 1);
    delay(500);
    lcd.print("Bombon counter");
    delay(2000);
    lcd.setCursor(0, 0);
    lcd.print("www.newcom.cv.ua");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("      2016     ");
    delay(3000);
    lcd.setCursor(0, 0);
    lcd.print("  -- Counter -- ");
    lcd.setCursor(0, 1);
    lcd.print("Piese =         ");
    lcd.setCursor(8, 1);
    lcd.print(0, DEC);
    value = 0;
    delay(1000);
  }
}


