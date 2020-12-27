/*
Ciabatta Bluetooth ver.2 
  
@author:  Daniele Tartaglia & Mauro Alfieri
@site: www.labdomotic.com & www.mauroalfieri.it
@youtube: https://www.youtube.com/user/edstarink
          https://www.youtube.com/user/doctoralma77
@created: March 2017
  
@Licence: CC Attribution Noncommercial Share Alike
@link:    https://creativecommons.org/licenses/by-nc-sa/3.0/it/
*/
 
#include <SoftwareSerial.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
 
/*********************************************************************/
 
#define BT_TX_PIN  7
#define BT_RX_PIN  8
 
/*********************************************************************/
 
SoftwareSerial mySerial(BT_TX_PIN, BT_RX_PIN);
RTC_DS1307 RTC;
LiquidCrystal_I2C lcd(0x3F,16,2);
 
/*********************************************************************/
 
char lettera;    //inizializzo carattere
char buffer[16];
 
byte rele1=2;
byte rele2=3;
byte rele3=4;
byte rele4=5;
 
int previousSec = 0;
 
uint8_t SPENTO[8] = {0x0E, 0x11, 0x11, 0x11, 0x0A, 0x0E, 0x0E, 0x04,};
uint8_t ACCESO[8] = {0x0E, 0x1F, 0x1F, 0x1F, 0x0E, 0x0E, 0x0E, 0x04,};
 
/*********************************************************************/
 
void setup() {
  lcd.backlight();
    Serial.begin(9600);
    mySerial.begin(9600);
    Wire.begin();
    RTC.begin();
    lcd.init(); 
     
    pinMode(rele1, OUTPUT);
    pinMode(rele2, OUTPUT);
    pinMode(rele3, OUTPUT);
    pinMode(rele4, OUTPUT);
     
    digitalWrite(rele1, HIGH);
    digitalWrite(rele2, HIGH);
    digitalWrite(rele3, HIGH);
    digitalWrite(rele4, HIGH);
     
    if (! RTC.isrunning()) {
      Serial.println("RTC is NOT running!");
      RTC.adjust(DateTime(__DATE__, __TIME__));
    }
     
    lcd.createChar(0, SPENTO);
    lcd.createChar(1, ACCESO);
    lcd.setCursor (0, 0);
    lcd.print("Ciabatta BT v.2");
    delay(2000);
    lcd.clear();
    lcd.setCursor (12, 0);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
    
}
 
/*********************************************************************/
  
void loop() {
  DateTime now = RTC.now();
     
  if(now.second() != previousSec) {
        lcd.setCursor( 0,0 );
        sprintf(buffer,  "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
        lcd.print( buffer );
        previousSec = now.second();
    }
     
    if(mySerial.available()) { // se il serial buffer contiene almeno un carattere
        lettera = mySerial.read(); // leggi il buffer
         
        switch (lettera) {
        case 'A':
            digitalWrite(rele1, LOW); // eccita il relay1
            Serial.println("relay 1 on");
            viewSocket( 1,true );
        break;
         
        case 'S':
            digitalWrite(rele1, HIGH); // diseccita il relay1
            Serial.println("relay 1 off");
            viewSocket( 1,false );
        break;
         
        case 'Q':
            digitalWrite(rele2, LOW); // eccita il relay2
            Serial.println("relay 2 on");
            viewSocket( 2,true );
        break;
         
        case 'W':
            digitalWrite(rele2, HIGH); // diseccita il relay2
            Serial.println("relay 2 off");
            viewSocket( 2,false );
        break;
         
        case 'E':
            digitalWrite(rele3, LOW); // eccita il relay3
            Serial.println("relay 3 on");
            viewSocket( 3,true );
        break;
         
        case 'R':
            digitalWrite(rele3, HIGH); // diseccita il relay3
            Serial.println("relay 3 off");
            viewSocket( 3,false );
        break;
         
        case 'T':
            digitalWrite(rele4, LOW); // eccita il relay4
            Serial.println("relay 4 on");
            viewSocket( 4,true );
        break;
         
        case 'Y':
            digitalWrite(rele4, HIGH); // diseccita il relay4
            Serial.println("relay 4 off");
            viewSocket( 4,false );
        break;
        }
    }   
}
 
void viewSocket(byte num, boolean status) {
  lcd.setCursor( ( 11+num ),0 );
  if ( status ) { 
     lcd.write(1); 
     lcd.setCursor ( 0,1 );
     lcd.print("Acceso rele "); 
  } else { 
    lcd.write(0);
    lcd.setCursor ( 0,1 );
    lcd.print("Spento rele ");
  }
  lcd.setCursor ( 12,1 );
  lcd.print(num);
}
