include <SPI.h>
include <MFRC522.h>
include <LiquidCrystal.h>

define SS_PIN 10
define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  SPI.begin();
  rfid.PCD_Init();
  lcd.begin(16, 2);
  lcd.print("Scan Card");
  Serial.begin(9600);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (!rfid.PICC_ReadCardSerial())
    return;

  lcd.clear();
  lcd.print("ID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(rfid.uid.uidByte[i], HEX);
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  delay(2000);
  lcd.clear();
  lcd.print("Attendance OK");
}
