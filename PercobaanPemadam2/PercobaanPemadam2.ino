#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial   ///input libbrary
#include <BlynkSimpleEsp8266.h>  // input library blynk esp 8266

// Network SSID
const char* ssid = "DREV"; /////////ganti sesuai ssid klean
const char* pass = "ojoomong"; /////////ganti sesuai psswrd klean

//Kode Blynk
const char* auth = "QX9MEi97X5FBlmAJk18US94Mw_X-Izk_"; // kode blynk ganti sesuai blynk klean

#define sensormq2 A0     /// Sensor pin a0
#define sensorflame D3  /// sensor flame di pin d3
#define indikator D2  /// Indikator speaker
#define ledred D5        // led red di pin d5
#define ledyel D7        //led yellow di D7
#define relay D8

void setup() {
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  delay(10);
  
  ////////////////////////////////////////////////////Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("Drev"); /////////ganti sesuai ssid klean
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  //////////////////////////////////////////////////////////

  /////Sensor MQ 2 /////////////////////////////////////////
  pinMode(sensormq2, INPUT);   /// sensor sebagai input
  pinMode(indikator, OUTPUT); ///indikator speaker sebagai output
  pinMode(ledyel, OUTPUT);
  /////////////////////////////////////////////////////////

  /////Sensor Flame /////////////////////////////////////////
  pinMode(sensorflame, INPUT);   /// sensor sebagai input
  pinMode(indikator, OUTPUT); ///indikator speaker sebagai output
  pinMode(ledred, OUTPUT);
  /////////////////////////////////////////////////////////connect wifi
}
 
void loop() {
///////////////////////////////MQ 2////////////////////////////
int nilaimq2=(analogRead(sensormq2));
Serial.print("Nilai analog sensor GAS: ");
Serial.println(nilaimq2);
delay (500);
  
  if(nilaimq2>1000)                                  // sensor on
  {
    digitalWrite(indikator, HIGH);                    //Speaker On
    {
      digitalWrite(ledyel, HIGH);
      delay(500);
      digitalWrite(ledyel, LOW);
      delay(500);
    }
    Blynk.notify("LAPOR Boss... ADA gas bocorrr ^_^");  //send notify blynk
    Blynk.virtualWrite(V0, 255);
  }
  else
  {
    digitalWrite(indikator, LOW);            ///speaker off
    digitalWrite(ledyel, LOW);
  }
///////////////////////////////////////////////////////////////////////////////
 

/////////////////////////////////////FLAME/////////////////////////////////// 
int nilaiflame=digitalRead(sensorflame);
Serial.print("Nilai analog sensor API: ");
Serial.println(nilaiflame);
delay (1000);
  
  if(nilaiflame==0)                                  // sensor on
  {
    digitalWrite(indikator, HIGH);                    //Speaker On
    {
      digitalWrite(ledred, HIGH);
      delay(500);
      digitalWrite(ledred, LOW);
      delay(500);
    }
    Blynk.notify("LAPOR Boss... Ada API ^_^");  //send notify blynk
    Blynk.virtualWrite(V0, 255);
  }
  else
  {
    digitalWrite(indikator, LOW);            ///speaker off
    digitalWrite(ledred, LOW);
  }
  ///////////////////////////////////////////////////////////////////////////
  Blynk.run();
  }
