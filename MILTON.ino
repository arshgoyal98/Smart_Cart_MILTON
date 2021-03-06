// Smart Shoping Card Prototype
// We can include more options, integrated with Navigation, which can be tracked by just putting some tracking sensors at different Locations of Mall,
//which will help staff and managers to track the cart, inside the store.

#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = 9;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 10;     // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
SoftwareSerial BTserial(3, 2); // RX, TX
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//*****************************************************************************************//
char bread = ' ';         // FOR BLUETOOTH VALUE
String name1 = " ";       // FOR READING NAME FROM RFID
char cmp = ' ';
char  cmpbuffer [20];
int total = 0;            // TOTAL AMOUNT INTEGER
char c = ' ';

int abhi1 = 0;
int abhi2 = 0;
int abhi3 = 0;
int abhi4 = 0;
int abhi5 = 0;
int abhi6 = 0;

void setup()
{
  lcd.begin(20, 4);
  Serial.begin(9600);              // Initialize serial communications with the PC
  BTserial.begin(9600 );
  SPI.begin();                    // Init SPI bus
  mfrc522.PCD_Init();          // Init MFRC522 card

  pinMode(4, OUTPUT);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART Cart SYSTEM");
  lcd.setCursor(0, 1);
  lcd.print("****Smart Cart System****");
  lcd.setCursor(0, 2);
    lcd.print("****Team MILTON****");
  lcd.setCursor(0, 2);
  lcd.print("*****NIT Jalandhar*****");
  lcd.setCursor(0, 3);
  lcd.print("LOADING..");
  lcd.setCursor(9, 3);
  lcd.print(".");
  delay(300);
  lcd.setCursor(10, 3);
  lcd.print(".");
  delay(300);
  lcd.setCursor (11, 3);
  lcd.print(".");
  delay(300);
  lcd.setCursor(12, 3);
  lcd.print(".");
  delay(300);
  lcd.setCursor(13, 3);
  lcd.print(".");
  delay(300);
  lcd.setCursor(14, 3);
  lcd.print(".");
  delay(300);
  lcd.setCursor(15, 3);
  lcd.print(".");
  delay(300);
  lcd.setCursor(16, 3);
  lcd.print(".");
  delay(300);
  lcd.setCursor(17, 3);
  lcd.print(".");
  delay(2500);
  lcd.clear();
}

//*******************************Main Loop Begins*************************************//
void loop()
{

  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**Card Detected:**"));

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  Serial.print(F("Name: "));

  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file

  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT FIRST NAME
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);
    }
  }

  //---------------------------------------- GET LAST NAME

  byte buffer2[18];
  block = 1;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT LAST NAME
  for (uint8_t i = 0; i < 16; i++)
  {
    Serial.write(buffer2[i] );
    cmpbuffer[i] = buffer2[i];
  }

  cmp = cmpbuffer[0];
  Serial.println(cmp);

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  //*****************************PRODUCT IDENTIFIER**********************************//

  if (cmp == '1' && abhi1 == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*****ADD TO CART****");
    lcd.setCursor(0, 1);
    lcd.print("TAPAL DANEDAAR 250mg");
    lcd.setCursor(0, 2);
    lcd.print("PRICE: 210 PKR");

    inn();
    delay(3000);
    lcd.clear();

    total += 210;
    cmp = ' ';
    abhi1 = 1;
  }

  if (cmp == '1' && abhi1 == 1) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("**REMOVE FROM CART**");
    lcd.setCursor(0, 1);
    lcd.print("TAPAL DANEDAAR 250mg");
    lcd.setCursor(0, 2);
    lcd.print("PRICE: 210 PKR --");

    out();
    delay(3000);
    lcd.clear();

    total = total - 210;
    cmp = ' ';
    abhi1 = 0;
  }

  if (cmp == '2' && abhi2 == 0) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*****ADD TO CART****");
    lcd.setCursor(0, 1);
    lcd.print("NIDO 1KG");
    lcd.setCursor(0, 2);
    lcd.print("PRICE: 910 PKR");

    inn();
    delay(3000);
    lcd.clear();

    total += 910;
    cmp = ' ';
    abhi2 = 1;
  }

  if (cmp == '2' && abhi2 == 1) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("**REMOVE FROM CART**");
    lcd.setCursor(0, 1);
    lcd.print("NIDO 1KG");
    lcd.setCursor(0, 2);
    lcd.print("PRICE: 910 PKR ");

    out();
    delay(3000);
    lcd.clear();

    total = total - 910;
    cmp = ' ';
    abhi2 = 0;
  }

  if (cmp == '3' && abhi3 == 0) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*****ADD TO CART****");
    lcd.setCursor(0, 1);
    lcd.print("COLGATE 250mg");
    lcd.setCursor(0, 2);
    lcd.print("PRICE: 180 PKR");

    inn();
    delay(3000);
    lcd.clear();

    total += 180;
    cmp = ' ';
    abhi3 = 1;
  }

  if (cmp == '3' && abhi3 == 1) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("**REMOVE FROM CART**");
    lcd.setCursor(0, 1);
    lcd.print("COLGATE 250mg");
    lcd.setCursor(0, 2);
    lcd.print("PRICE: 180 PKR ");

    out();
    delay(3000);
    lcd.clear();

    total = total - 180;
    cmp = ' ';
    abhi3 = 0;
  }

  if (cmp == '4' && abhi4 == 0) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*****ADD TO CART****");
    lcd.setCursor(0, 1);
    lcd.print("DALDA 5KG");
    lcd.setCursor(0, 2);
    lcd.print("PRICE: 950 PKR");

    inn();
    delay(3000);
    lcd.clear();

    total += 950;
    cmp = ' ';
    abhi4 = 1;
  }

  if (cmp == '4' && abhi4 == 1) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("**REMOVE FROM CART**");
    lcd.setCursor(0, 1);
    lcd.print("DALDA 5KG");
    lcd.setCursor(0, 2);
    lcd.print("PRICE: 950 PKR ");

    out();
    delay(3000);
    lcd.clear();

    total = total - 950;
    cmp = ' ';
    abhi4 = 0;
  }

  if (cmp == '5' && abhi5 == 0) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*****ADD TO CART****");
    lcd.setCursor(0, 1);
    lcd.print("BLUEBAND 250gm");
    lcd.setCursor(0, 2);
    lcd.print("PRICE: 145 PKR");

    inn();
    delay(3000);
    lcd.clear();

    total += 145;
    cmp = ' ';
    abhi5 = 1;
  }

  if (cmp == '5' && abhi5 == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("**REMOVE FROM CART**");
    lcd.setCursor(0, 1);
    lcd.print("BLUEBAND 250gm");
    lcd.setCursor(0, 2);
    lcd.print("PRICE: 145 PKR ");
    out();
    delay(3000);
    lcd.clear();

    total = total - 145;
    cmp = ' ';
    abhi5 = 0;
  }

  if (cmp == '6' && abhi6 == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*****ADD TO CART****");
    lcd.setCursor(0, 1);
    lcd.print("EVERYDAY 1KG");
    lcd.setCursor(0, 2);
    lcd.print("PRICE: 890 PKR");

    inn();
    delay(3000);
    lcd.clear();

    total += 890;
    cmp = ' ';
    flag6 = 1;
  }

  
