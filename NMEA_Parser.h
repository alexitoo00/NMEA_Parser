// Clase para convertir los datos del GPS en latitud y longitud
template<class T> class NMEA_Parser {
  public:
    NMEA_Parser(T& stream) : stream(stream) {}
    void begin(unsigned long baud) {
      stream.begin(baud);
    }
    float lat;
    float lon;
    String hora;
    String fecha;
    float offsetCoord[2] = {0.15689683, -0.27937788};

    bool fix = false;
    bool datos;

    void parseHour(String hour) {
      hora = String((String(hour[0]) + String(hour[1])).toInt() + GMT) + ":" + String(hour[2]) + String(hour[3]) + ":" + String(hour[4]) + String(hour[5]);
    }
    void parseDate(String date) {
      fecha = String(date[0]) + String(date[1]) + "/" + String(date[2]) + String(date[3]) + "/" + String(date[4]) + String(date[5]);
    }
    bool Parse(String msg)
    {
      int index = 0;
      String vectorStr[40];
      memset(vectorStr, 0, sizeof(vectorStr));
      for (int i = msg.indexOf("GPRMC"); i < msg.length(); i++)
      {
        if (index > 9) break;
        if (msg[i] == '\n')
          continue;
        if (msg[i] == ',')
        {
          index++;
          continue;
        }
        vectorStr[index] += msg[i];
      }
      if (!(vectorStr[0] == "GPRMC"))return false;

      if (vectorStr[1].length() == 9)parseHour(vectorStr[1]);
      if (vectorStr[9].length() == 6)parseDate(vectorStr[9]);


      datos = true;

      // Check for GPS signal
      if (vectorStr[2] == "V") {
        Serial.println("Dispositivo sin señal");
        fix = false;
        return false;
      }
      fix = true;
      lat = vectorStr[3].toFloat() * (vectorStr[4] == "N" ? 1 : -1) * 0.01f + offsetCoord[0];
      lon = vectorStr[5].toFloat() * (vectorStr[6] == "E" ? 1 : -1) * 0.01f + offsetCoord[1];
      return true;
    }
    bool serialRead()
    {
      for (unsigned long temp = millis(); millis() - temp < 3000;) {
        while (stream.available()) {
          String msg = stream.readStringUntil('\n');
          return Parse(msg);
        }
      }
      if (!stream.available())
      {
        Serial.println("Error recibiendo datos de GPS");
        delay(1000);
        return false;
      }
      datos = false;
    }
  private:
    T& stream;
    int GMT = 1; // +1 para España en invierno
};
