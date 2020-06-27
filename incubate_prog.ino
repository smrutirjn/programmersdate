#include<HX711.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial gsm(9,10);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#define DT A0
#define SCK A1
#define sw 9
#define LED 13
#define buzzer 12

long sample = 0;
float val = 0;
long count = 0;
int k=0;




#include <ESP8266WiFi.h">
#include <<span class="TextRun Highlight BCX0 SCXW174472232" lang="EN-US" xml:lang="EN-US" data-contrast="auto"><span class="SpellingError BCX0 SCXW174472232">FirebaseArduino.h></span></span>
 
// Set these to run example. 
#define FIREBASE_HOST "example.firebaseio.com" 
#define FIREBASE_AUTH "token_or_secret" 
#define WIFI_SSID "SSID" 
#define WIFI_PASSWORD "PASSWORD" 

 
unsigned long readCount(void)
{
  unsigned long Count;
  unsigned char i;
  pinMode(DT, OUTPUT);
  digitalWrite(DT, HIGH);
  digitalWrite(SCK, LOW);
  Count = 0;
  pinMode(DT, INPUT);
  while (digitalRead(DT));
  for (i = 0; i < 24; i++)
  {
    digitalWrite(SCK, HIGH);
    Count = Count << 1;
    digitalWrite(SCK, LOW);
    if (digitalRead(DT))
      Count++;
  }
  digitalWrite(SCK, HIGH);
  Count = Count ^ 0x800000;
  digitalWrite(SCK, LOW);
  return (Count);
}

void setup()
{
  pinMode(SCK, OUTPUT);
  pinMode (buzzer,OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  lcd.begin(16, 2);
  lcd.print(" Weight ");
  lcd.setCursor(0, 1);
  lcd.print(" Measurement ");
  Serial.print("weight measure");
  delay(1000);
  //lcd.clear();
  calibrate();



Serial.begin(9600); 
 
  // connect to wifi. 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  Serial.print("connecting"); 
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print("."); 
    delay(500); 
  } 
  Serial.println(); 
  Serial.print("connected: "); 
  Serial.println(WiFi.localIP()); 
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
} 
 

}

void loop()
{
  Serial.begin(9600);
  count = readCount();
  int w = (((count - sample) / val) - 2 * ((count - sample) / val));
  lcd.setCursor(0, 0);
  lcd.print("BED NUMBER 7");
  lcd.setCursor(0, 1);
 
  //Serial.print(w);
  lcd.print("ALL IS WELL");
   Serial.print(w);
  delay(1000);

  if (digitalRead(sw) == 0)
  {
    val = 0;
    sample = 0;
    w = 0;
    count = 0;
    calibrate();
  }
  if (w <30)
  {
   Serial.begin(9600);
  Serial.print(w);
  
   // if(k<1)
    
    alert();
    
    horn();
   }

  }


void calibrate()
{
  lcd.clear();
  //Serial.print("Calibrating...");
  lcd.setCursor(0, 1);
  lcd.print("CALIBRATING...");
  for (int i = 0; i < 100; i++)//CHANGE CODE
  {
    count = readCount();
    sample += count;
  }
  sample /= 100;
  lcd.clear();
  lcd.print("Put IV & wait");
  count = 0;
  while (count < 1000)
  {
    count = readCount();
    count = sample - count;
  }
  lcd.clear();
  lcd.print("Please Wait....");
  delay(2000);
  for (int i = 0; i < 100; i++)
  {
    count = readCount();
    val += sample - count;
  }
  val = val / 100.0;
  val = val / 100.0; // put here your calibrating weight
  v=String(val);

   if (Firebase.failed()) { 
      Serial.print("setting /truth failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 

  else{
    
    Firebase.setString("value", v); 
    
    }
  
  lcd.clear();
}

void alert()
{
    lcd.setCursor(0, 0);
  Serial.print("calling");
 lcd.print("BED NUMBER 7");
   lcd.setCursor(0, 1);
  lcd.print("PLEASE REFILL...");
    lcd.setCursor(0, 1);
    digitalWrite(13, HIGH);
  Serial.println("OK");
  delay(1000);
 //lcd.print("Calling...");
   Serial.begin(9600);
  gsm.begin(9600);
  gsm.println("ATD6370870484;");//add target mobile number in place of xxxxxxxxxx
  delay(10000);
  gsm.println("ATH");
   //Serial.begin(9600);
 delay(1000);
 Serial.begin(9600);
 gsm.begin(9600);
  gsm.println("ATD7377745402;");
   delay(10000);
  gsm.println("ATH");
   //delay(10000);
   k++;
 }
void horn()
{
 
     for(int y=0;y<5;y++)
  {
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  }
   digitalWrite(13, LOW);
  digitalWrite(buzzer, LOW);
   lcd.clear();
  
}
