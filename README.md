[![voltNik YouTube](http://voltnik.ru/voltnik-banner.jpg)](https://www.youtube.com/channel/UC4s13gPVOMQVX3P1ZpdUwjA?sub_confirmation=1)
![ПРЕВЬЮ](https://github.com/voltNik/AltMeter/blob/master/baro-almeter.jpg)
# Высотомер на Arduino своими руками
* [Описание проекта](#chapter-0)
* [Папки проекта](#chapter-1)
* [Схемы подключения](#chapter-2)
* [Материалы и компоненты](#chapter-3)
* [Как скачать и прошить](#chapter-4)
* [FAQ](#chapter-5)
* [Полезная информация](#chapter-6)

<a id="chapter-0"></a>
## Описание проекта
Цифровой высотомер с экраном
- Используется OLED экран 128 на 64 точкек
- Используется модуль барометра BMP-280
- На дисплее отображается, давление, высота, температура с датчика
- Работает от одной батарейки АА
- Подробности в видео: https://youtu.be/q__ANYfkhVY

<a id="chapter-1"></a>
## Папки
- **libraries** - типовые библиотеки с настройкой адресов I2C, использовать не обязательно. Используются: Adafruit_BMP280, Adafruit_Sensor, Adafruit_SSD1306, Adafruit-GFX, EEPROMEx.
- **barometer280** - прошивка для Arduino
- **i2c-scaner** - сканер адресов I2C
- **3d-model** - модель корпуса .stl для 3D печати

<a id="chapter-2"></a>
## Схема
![СХЕМА](https://github.com/voltNik/AltMeter/blob/master/scheme_altmeter.jpg)

<a id="chapter-3"></a>
## Материалы и компоненты
- Arduino NANO: http://ali.pub/2351o1
- OLED дисплей: http://ali.pub/2351lp
- Барометр BMP-280: http://ali.pub/2351u2
- Батарейный отсек AA: http://ali.pub/2352id
- Выключатели 20шт: http://ali.pub/2352gf
- Кнопки 25шт: http://ali.pub/235230
- Повышающий преобразователь 10шт: http://ali.pub/23528u
- Корпус печатаем на принтере или используем такой: http://ali.pub/2352la 

<a id="chapter-4"></a>
## Как скачать и прошить
* Скачать архив с проектом
> На этой странице сверху справа зелёная кнопка **Clone or download**, жми её, там будет **Download ZIP**
* Установить библиотеки в:  
`C:\Program Files (x86)\Arduino\libraries\` (Windows x64)  
`C:\Program Files\Arduino\libraries\` (Windows x86) 
* Подключить Ардуино к компьютеру
* Запустить файл прошивки .ino
* Настроить COM порт и модель Arduino
* Настроить что нужно по проекту в файле прошивке
* Нажать загрузить

## Настройки в коде
    не требуются

<a id="chapter-5"></a>
## FAQ
### Основные вопросы
В: Как скачать с этого сайта?  
О: Вверху вверху справа зелёная кнопка **Clone or download**, её жми, там будет **Download ZIP**  

В: Скачался какой то файл .zip, куда его теперь?  
О: Это архив. Надо распаковать.  

В: Компьютер никак не реагирует на подключение Ардуины!  
О: Возможно у тебя зарядный USB кабель, а нужен именно data-кабель, по которому можно данные передавать  

В: Сколько стоит?  
О: Модель бесценна и не продается. Можно только сделать самому по инструкции и видеогайду.  

### Вопросы по этому проекту
В: На сколько хватит батарейки?  
О: Около 20 часов работы.  

<a id="chapter-6"></a>
## Полезная информация
* [Мой сайт VOLTNIK.RU](http://voltnik.ru/)
* [Мой YouTube канал VOLTNIK](https://www.youtube.com/channel/UC4s13gPVOMQVX3P1ZpdUwjA?sub_confirmation=1)