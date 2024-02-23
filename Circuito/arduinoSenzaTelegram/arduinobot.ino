#include <LiquidCrystal.h>
#include <DHT.h>
#include<SPI.h>
#include<WiFiNINA.h>
#include<TelegramBot.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int DHTPin = 7;
const int FRS1 = A0;
const int FRS2 = A1;
const int FRS3 = A2;
const int DHTTYPE = DHT11;

DHT dht = DHT(DHTPin, DHTTYPE);

int umid;
int lux1;
int lux2;
int lux3;
int temp;

float percentualeLux;

char ssid[]="nomewifi";
char pass[]="pass";//password del wifi

int status=WL_IDLE_STATUS;
WiFiSSLClient client;

const char* BotToken="/inserire token di arduino/";
TelegramBot bot(BotToken, client);

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
  Serial.begin(9600);
    while(!Serial){
        ;
    }
    if(WiFi.status()==WL_NOMODULE){//trova il modulo Wifi
        Serial.printfln("Communication with WiFi module failed");

        while(true);
    }
    while(status!=WL_CONNECTED){
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);

        status=WiFi.begin(ssid, pass);

        delay(2000);
    }
    Serial.println("Connected to WiFi");
    bot.begin();
    Serial.println("Bot started");
}

void loop(){
  umid = dht.readHumidity();
  lux1 = analogRead(FRS1);
  lux2 = analogRead(FRS2);
  lux3 = analogRead(FRS3);
  temp = dht.readTemperature();

  percentualeLux = (map(lux1, 0, 1023, 0, 100) + map(lux2, 0, 1023, 0, 100) + map(lux3, 0, 1023, 0, 100))/3;
  
    message m=bot.getUpdates();//vede se ci sono nuovi messaggi
    if(m.chat_id != 0){
        Serial-println(m.text);
        String msg=String(m.text);
        if(msg=="/read"){
            Serial.print("Umidita del terreno: ");
            Serial.print(umid);
            Serial.println("%");

            Serial.print("Luminosita': ");
            Serial.print(percentualeLux);
            Serial.println("%");

            Serial.print("Temperatura: ");
            Serial.print(temp);
            Serial.println("C");      
        }
        else if(msg=="/clear"){
            lcd.clear();
            lcd.setCursor(0, 0);  
        }
        else if(msg=="/temp"){
            lcd.clear();
            lcd.print("Temp.: ");
            lcd.print(String(temp));
            lcd.print("C");
            lcd.setCursor(0, 1);  
        }
        else if(msg=="/lux"){
            lcd.clear();
            lcd.print("Lumin.: ");
            lcd.print(String(percentualeLux));
            lcd.print("%");
            lcd.setCursor(0, 1);  
        }
        else if(msg=="/umid"){
            lcd.clear();
            lcd.print("Umidita': ");
            lcd.print(String(umid));
            lcd.print("%");
            lcd.setCursor(0, 1);  
        }
    }

  delay(1000);
}
