# NMEA_Parser

Librería creada con el fin de convertir datos procedentes de módulos GPS comerciales en formato NMEA ([National Marine Electronics Association](https://www.nmea.org/)), estándar utilizado para la comunicación de información GPS, en concreto, esta librería analiza el mensaje recibido y extrae los datos de latitud, longitud, fecha y hora del mensaje comenzado en GPRMC (Posición, velocidad y tiempo)

## Cómo usarla

  Para utilizar esta librería basta con añadir su único archivo en la misma dependencia que el programa de Arduino en el que lo queremos utilizar e incluir la librería en el comienzo del script y crear una instancia indicando si el puerto UART utilizado es del tipo HardwareSerial, como el de los propios pines RX y TX de cada Arduino, o si se trata del tipo SoftwareSerial, el cual permite utilizar otros dos pines de nuestro dispositivo de la siguiente forma:
```C++
  #include <SoftwareSerial.h>
  #include "NMEA_Parser.h" // Librería GPS

  SoftwareSerial ss(32, 33); // RX TX
  NMEA_Parser<SoftwareSerial> gps(ss);
```
En este caso nuestro módulo gps está conectado en los pines 32 y 33, por lo que utilizamos la librería SoftwareSerial para utilizarlos como RX y TX, respectivamente y creamos una instancia de nuestra librería llamada __gps__.


## Funciones y variables

- **begin()**
  En el ```void setup()``` de nuestro script de Arduino debemos dar la orden de recibir los datos a nuestro dispositivo GPS mediante la función ```begin()``` junto con la tasa de baudios a la que deseamos recibir los mensajes de nuestro módulo:
```C++
  gps.begin(9600);
```

- **serialRead()**
  Cuando necesitemos leer los datos del GPS debemos indicarlo con la función ```serialRead()```. Esta función devuelve un valor booleano de __true__ si es capaz de encontrar los datos de latitud y longitud y un valor de __false__ si no los encuentra, lo que la hace muy útil para evaluar esta situación en una declaración if como se muestra en el ejemplo:
```C++
  if (gps.serialRead()){ // Si se encuentra señal GPS
    // Ejecuta el código de aquí
  }
```

- **Parse(String datosNMEA)**
  Si lo deseamos también podemos interpretar los datos en formato NMEA pasandole a la función ```Parse()``` una cadena de caracteres como parámetro:
 ```C++
   String datosNMEA = "$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A";
   Parse(datosNMEA);
 ```
 
- **lat**
  Variable que devuelve el valor de tipo float correspondiente a la latitud
```C++
  float latitud = gps.lat;
```
  
- **lon**
  Variable que devuelve el valor de tipo float correspondiente a la longitud
```C++
  float longitud = gps.lon;
```  
  
- **hora**
  Variable que devuelve el valor de tipo String correspondiente a la hora en formato HH:MM:SS
```C++
  String horaGPS = gps.hora;
```  
  
- fecha
  Variable que devuelve el valor de tipo String correspondiente a la fecha en formato DD/MM/AA
```C++
  String fechaGPS = gps.fecha;
```  
  
