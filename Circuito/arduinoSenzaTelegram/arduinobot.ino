#include <LiquidCrystal.h>
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

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

const char* ssid = "ap-react";
const char* token = "6196944314:AAHuMxSecHvxWMdwApU7p_KGkGGiu1E-hKM";
const int httpsPort = 443;
const char* host = "api.telegram.org";

WiFiClientSecure client;
UniversalTelegramBot bot(token, client);

WiFiServer server(80);

void setup(){
  Serial.begin(115200);
  lcd.begin(16, 2);
  dht.begin();
  
  delay(100);

  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione alla rete WiFi...");
  }
  Serial.println("Connesso alla rete WiFi");

  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  server.begin();

  delay(1000);
}

void loop(){
  umid = dht.readHumidity();
  lux1 = analogRead(FRS1);
  lux2 = analogRead(FRS2);
  lux3 = analogRead(FRS3);
  temp = dht.readTemperature();

  percentualeLux = (map(lux1, 0, 1023, 0, 100) + map(lux2, 0, 1023, 0, 100) + map(lux3, 0, 1023, 0, 100))/3;

  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nuova connessione!");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<html><body><h1>Richiesta ricevuta!</h1></body></html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Connessione chiusa!");
  }
  
    message m=bot.getUpdates();//vede se ci sono nuovi messaggi
    if(m.chat_id != 0){
        Serial.println(m.text);
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
