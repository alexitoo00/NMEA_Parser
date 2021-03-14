# NMEA_Parser

Librería creada con el fin de convertir datos procedentes de módulos GPS comerciales en formato NMEA ([National Marine Electronics Association](https://www.nmea.org/)), estándar utilizado para la comunicación de información GPS, en concreto, esta librería analiza el mensaje recibido y extrae los datos de latitud, longitud, fecha y hora del mensaje comenzado en GPRMC (Posición, velocidad y tiempo)

## Cómo usarla

Para utilizar esta librería basta con añadir su único archivo en la misma dependencia que el programa de Arduino en el que lo queremos utilizar e incluir la librería en el comienzo del script y crear una instancia indicando si el puerto UART utilizado es del tipo HardwareSerial, como el de los propios pines RX y TX de cada Arduino, o si se trata del tipo SoftwareSerial, el cual permite utilizar otros dos pines de nuestro dispositivo de la siguiente forma:
```C++
  #include <SoftwareSerial.h>
  #include "NMEA_Parser.h" // Librería GPS

  SoftwareSerial ss(32, 33);
  NMEA_Parser<SoftwareSerial> gps(ss);
```
En este caso nuestro módulo gps está conectado en los pines 32 y 33, por lo que utilizamos la librería SoftwareSerial para utilizarlos como RX y TX, respectivamente y creamos una instancia de nuestra librería llamada **gps**.


## Funciones y variables

En el ```void setup()``` de nuestro script de Arduino debemos dar la orden de recibir los datos a nuestro dispositivo GPS mediante la función begin() junto con la tasa de baudios a la que deseamos recibir los mensajes de nuestro módulo:
```C++
  gps.begin(9600);
```
