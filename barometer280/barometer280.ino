/*********************************************************************
HELLO WORLD! ANYBODY HOME?
Высотомер на модуле барометра BMP-280

SITE: http://voltnik.ru/
YOUTUBE: https://www.youtube.com/channel/UC4s13gPVOMQVX3P1ZpdUwjA
Креатед бай voltNik 2017
*********************************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define OLED_RESET 4
#define but1 2                    // пин кнопки1
#define but2 3                    // пин кнопки2

#define screen_ref 300            // обновление экрана каждые милисекунд
#define but_protect 100           // защита дребегза кнопки
#define mass_l 20                 // длинна массива средних

Adafruit_SSD1306 display(OLED_RESET);
Adafruit_BMP280 bmp; // I2C

long now_millis, last_millis, last_but1, last_but2;       // миллисекунды для отсчета
byte num_ekr = 0 ;                        // номер отображения экрана
float pressure_zero = 1005.00;           // нулевая точка давления

float pressure[mass_l];  // массив давления
float temp[mass_l];      // массив температуры
float alt[mass_l];      // массив температуры
float cur_pres = 0, pres_sr = 0, temp_sr = 0, alt_sr = 0; // среднее давление и температура
byte pos = 0;

//=====================================
void setup()   {                
  Serial.begin(9600);

  pinMode(but1, INPUT_PULLUP);
  pinMode(but2, INPUT_PULLUP);

  pinMode(5, OUTPUT);  // использую контакт как массу для одной из кнопок
  digitalWrite(5, 0);
    
  if (!bmp.begin()) {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.cp437(true);
  display.clearDisplay();  
  testdrawrect();
  delay(200);
  
  // начальное заполнение массива
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(30,40);
  display.println("Loading...");
  pres_sr = 0;
  temp_sr = 0;
  for (byte i=0; i<mass_l; i++) {
    pressure[i] = bmp.readPressure();
    temp[i] = bmp.readTemperature();
    pres_sr = pres_sr + pressure[i];
    temp_sr = temp_sr + temp[i];
    //display.print(i);
    display.drawRect(0, 30, i*8, 5, WHITE);
    display.display();
    delay(50);
  }
  pres_sr /= mass_l;
  temp_sr /= mass_l;
}
//=====================================
void loop() {
  byte sensorVal1 = digitalRead(but1);
  byte sensorVal2 = digitalRead(but2);
    
  now_millis = millis();  // разово на цикл запоминаем старт милисекунд

 // обработка нажатия кнопки 1
  if ((sensorVal1 == LOW) & (now_millis - last_but1)> but_protect) { 
    num_ekr = (num_ekr+1) % 4; 
    last_but1 = now_millis + 500;  // +500мс задержка следующего нажатия кнопки 1
  }
// обработка нажатия кнопки 2
  if ((sensorVal2 == LOW) & (now_millis - last_but2)> but_protect) { 
    pressure_zero = pres_sr / 100;
    last_but2 = now_millis + 500;  // +500мс задержка следующего нажатия кнопки 2
  }

  if (now_millis - last_millis > screen_ref) {
    
    //цикл обновления массива температуры и давления
    pos = (pos + 1) % mass_l;
    pressure[pos] = bmp.readPressure();
    temp[pos] = bmp.readTemperature();
    
    // пересчет средних значений
    pres_sr = 0; 
    temp_sr = 0;
    // пересчет средних значений
    for (byte i=0; i<mass_l; i++) {
      //Serial.print(pressure[i]); Serial.print(" ");
      pres_sr = pres_sr + pressure[i];
      temp_sr = temp_sr + temp[i];
    }
    pres_sr /= mass_l;
    temp_sr /= mass_l;
    
  // вывод на экран
  switch (num_ekr) {
  case 0:
    display.clearDisplay();  
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("     Baro-280"); display.println();    
    display.print("Press: "); display.println(pressure[pos]);
    display.print("P_SR : "); display.println(pres_sr);
    display.print("Alt  : "); display.println(bmp.readAltitude());
    display.print("Alt Z: "); display.println(bmp.readAltitude(pressure_zero));
    display.print("Calc : "); display.println(calcAltitude(pressure_zero, pres_sr));
    display.print("Temp : "); display.println(temp_sr);
    display.display();
    break;
  case 1:
    display.clearDisplay();  
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Pressure");
    display.setCursor(0,24);
    display.println(bmp.readPressure());
    display.println(pressure_zero);
    display.display();
    break;
  case 2:
    display.clearDisplay();  
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Alt");
    display.setCursor(0,24);
    display.println(bmp.readAltitude(pressure_zero));
    display.println(calcAltitude(pressure_zero, pres_sr));
    display.display();
    break;
  case 3:   
    display.clearDisplay();  
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Temp");
    display.setCursor(0,24);
    display.println(bmp.readTemperature());
    display.display();
    break;
  }
    
   last_millis = now_millis;
  }
  
}
//===================================== квадратики на старте
void testdrawrect(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display();
    delay(1);
  }
}
//===================================== расчет высоты
float calcAltitude(float seaLevelhPa, float pressure) {
  float altitude;
  pressure /= 100;
  altitude = 44330 * (1.0 - pow(pressure / seaLevelhPa, 0.1903));
  return altitude;
}
//=====================================
