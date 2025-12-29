void readSerialCommands() {
  while (Serial.available() > 0) {
    char c = Serial.read();

    if (c == '\n' || c == '\r') {
      if (serialBuffer.length() > 0) {
        handleCommand(serialBuffer);
        serialBuffer = "";
      }
    } else {
      serialBuffer += c;
    }
  }
}

void handleCommand(const String& rawCmd) {
  String cmd = rawCmd;
  cmd.trim(); 

  if (cmd.length() == 0) return;

  if (cmd.charAt(0) == 't') {
    if (setTimeFromString(cmd)) {
      Serial.println("Cas nastaveny.");
      vypisAktualnyCas();
    } else {
      Serial.println("Chybny format casu. tHH:MM:SSdDD.MM.RRRR");
    }
  }
  else if (cmd.equalsIgnoreCase("a")) {
    vypisAktualnyCas();
  }
  else {
    Serial.print("Neznamy prikaz: ");
    Serial.println(cmd);
  }
}

bool setTimeFromString(const String& cmd) {
  int tIndex   = 1;
  int colon1   = cmd.indexOf(':', tIndex);
  int colon2   = cmd.indexOf(':', colon1 + 1);
  int dIndex   = cmd.indexOf('d', colon2 + 1);

  if (colon1 < 0 || colon2 < 0 || dIndex < 0) return false;

  int hour   = cmd.substring(tIndex, colon1).toInt();
  int minute = cmd.substring(colon1 + 1, colon2).toInt();
  int second = cmd.substring(colon2 + 1, dIndex).toInt();

  String datePart = cmd.substring(dIndex + 1);
  int dot1 = datePart.indexOf('.');
  int dot2 = datePart.indexOf('.', dot1 + 1);
  if (dot1 < 0 || dot2 < 0) return false;

  int day   = datePart.substring(0, dot1).toInt();
  int month = datePart.substring(dot1 + 1, dot2).toInt();
  int year  = datePart.substring(dot2 + 1).toInt();

  if (hour   < 0 || hour > 23) return false;
  if (minute < 0 || minute > 59) return false;
  if (second < 0 || second > 59) return false;
  if (day    < 1 || day > 31)   return false;
  if (month  < 1 || month > 12) return false;
  if (year   < 2000 || year > 2099) return false;

  rtc.adjust(DateTime(year, month, day, hour, minute, second));
  return true;
}

// =================== RTC – VYPISY ====================
void vypisCas(const char* tlacidloName) {
  DateTime now = rtc.now();

  Serial.print("Udalost ");
  Serial.print(tlacidloName);
  Serial.print(" – cas: ");

  if (now.day() < 10) Serial.print('0');
  Serial.print(now.day());
  Serial.print('.');
  if (now.month() < 10) Serial.print('0');
  Serial.print(now.month());
  Serial.print('.');
  Serial.print(now.year());
  Serial.print(' ');

  if (now.hour() < 10) Serial.print('0');
  Serial.print(now.hour());
  Serial.print(':');
  if (now.minute() < 10) Serial.print('0');
  Serial.print(now.minute());
  Serial.print(':');
  if (now.second() < 10) Serial.print('0');
  Serial.println(now.second());
}

void vypisAktualnyCas() {
  DateTime now = rtc.now();

  Serial.print("Aktualny cas: ");

  if (now.day() < 10) Serial.print('0');
  Serial.print(now.day());
  Serial.print('.');
  if (now.month() < 10) Serial.print('0');
  Serial.print(now.month());
  Serial.print('.');
  Serial.print(now.year());
  Serial.print(' ');

  if (now.hour() < 10) Serial.print('0');
  Serial.print(now.hour());
  Serial.print(':');
  if (now.minute() < 10) Serial.print('0');
  Serial.print(now.minute());
  Serial.print(':');
  if (now.second() < 10) Serial.print('0');
  Serial.println(now.second());
}