#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "D-Link DSL-2640B";
const char* token = "6196944314:AAHuMxSecHvxWMdwApU7p_KGkGGiu1E-hKM";
//const char* chatid = "5763563368";
//const char* token = "7047158891:AAE7wsAzglUzdCyDSKSOEuW4qBbFewf9vFw";
const char* chatid = "1938434862";

WiFiClientSecure client;
UniversalTelegramBot bot(token, client);

const unsigned long BOT_TIMEOUT = 1000;
const long TIM = 5 * 60 * 100;
unsigned long t1 = 0;
unsigned long t2 = 0;
unsigned long t3 = 0;
unsigned long t4 = 0;
const int FRS = 32;
const int DHTPin = 14;
const int DHTTYPE = DHT11;

int umid;
int lux;
int temp;
float volt;

LiquidCrystal_I2C lcd(0x27,20,4);
DHT dht = DHT(DHTPin, DHTTYPE);

String insta = "https://www.instagram.com/green_symphony_?utm_source=qr&igsh=MWw2cGhxaXZzM2M2dg==";
String git = "https://github.com/Fraalloo/PCTO-Green_Symphony";
String web = "https://fraalloo.github.io/PCTO-Green_Symphony//";

void lcdStart();
void handleNewMessagesTelegram(int);

void setup() {
    Serial.begin(115200);

    lcd.init();
    lcd.backlight();
    lcdStart();
    delay(1000);

    Serial.println("Connessione al WiFi...");
    WiFi.begin(ssid);

    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connettendo...");
    }

    Serial.println("Connesso!!!");

    Serial.print("Indirizzo IP: ");
    Serial.println(WiFi.localIP());

    bot.sendMessage(chatid, "Sono connesso, Ciao!", "");
    bot.sendPhoto(chatid,"https://raw.githubusercontent.com/Fraalloo/PCTO-Green_Symphony/main/Logo/logo.png","");
    bot.sendMessage(chatid, "Ecco a te link utili su di noi:", "");
    bot.sendMessage(chatid, "Instagram: " + insta, "");
    bot.sendMessage(chatid, "GitHub: " + git, "");
    bot.sendMessage(chatid, "Sito Web: " + web, "");
    bot.sendMessage(chatid, "/help per informazioni su tutti i comandi di Tech Flora v1", "");
}


void loop(){
    umid = dht.readHumidity();
    lux = analogRead(FRS);
    volt = lux * (5./1023.0);
    lux = map(volt,0.0,5.0,0.0,1023.0);
    temp = dht.readTemperature();

    if(umid < 4 || umid > 8){
      if(millis() - t2 > TIM){
        t2 = millis();
        bot.sendMessage(chatid, "Umidità al di fuori della norma, dovresti controllare la tua pianta", "");
      }
    }
    if(lux < 500){
      if(millis() - t3 > TIM){
        t3 = millis();
        bot.sendMessage(chatid, "Luminosità al di fuori della norma, dovresti controllare la tua pianta", "");
      }
    }
    if(temp < 15 || temp > 40){
      if(millis() - t4 > TIM){
        t4 = millis();
        bot.sendMessage(chatid, "Temperatura al di fuori della norma, dovresti controllare la tua pianta", "");
      }
    }

    if(WiFi.status() != WL_CONNECTED){
        Serial.println("Connessione persa, ricollego...");
        WiFi.begin(ssid);
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Connettendo...");
        }
        Serial.println("Riconnesso alla rete WiFi");
    }

    if((millis() - t1) > BOT_TIMEOUT){
      t1 = millis();
      int n = bot.getUpdates(bot.last_message_received + 1);
    while(n){
      Serial.println("Ci sono messaggi");
      handleNewMessagesTelegram(n);
      n = bot.getUpdates(bot.last_message_received + 1);
    }
  }
}

void lcdStart(){
    lcd.home();
    lcd.print("+");
    lcd.setCursor(19,0);
    lcd.print("+");
    lcd.setCursor(0,3);
    lcd.print("+");
    lcd.setCursor(19,3);
    lcd.print("+");

    lcd.setCursor(0,1);
    lcd.print("|");
    lcd.setCursor(0,2);
    lcd.print("|");
    lcd.setCursor(19,1);
    lcd.print("|");
    lcd.setCursor(19,2);
    lcd.print("|");

    lcd.setCursor(1,0);
    for(int i = 0; i < 18; i++){
      lcd.print("-");
    }
    lcd.setCursor(1,3);
    for(int i = 0; i < 18; i++){
      lcd.print("-");
    }

    String msg1 = "Hello,";
    String msg2 = "User!!";
    int len1 = msg1.length();
    int len2 = msg2.length();
    lcd.setCursor(7,1);
    for(int i = 0; i < len1; i++){
        lcd.print(msg1[i]);
        delay(150);
    }
    lcd.setCursor(7,2);
    for(int i = 0; i < len2; i++){
        lcd.print(msg2[i]);
        delay(150);
    }
}

void handleNewMessagesTelegram(int n){
  for(int i = 0; i < n; i++){
    String msg = String(bot.messages[i].text);
    if(msg == "/info") {
      String messageText = "Umidita del terreno: " + String(umid) + "%\n" +
                          "Luminosita': " + String(lux) + " lm\n" +
                        "Temperatura: " + String(temp) + " C";

      bot.sendMessage(bot.messages[i].chat_id, messageText, "");
      Serial.println(messageText);
    }else if(msg == "/hello"){
      bot.sendMessage(bot.messages[i].chat_id, "Hello, World!", "");
    }else if(msg == "/help"){
       bot.sendMessage(bot.messages[i].chat_id, "Comandi:", "");
       bot.sendMessage(bot.messages[i].chat_id, "/info: Invia tutti i parametri sulla pianta", "");
       bot.sendMessage(bot.messages[i].chat_id, "/hello: Il bot invia la stringa 'Hello, World!'", "");
       bot.sendMessage(bot.messages[i].chat_id, "/clear: Pulisce lo schermo LCD", "");
       bot.sendMessage(bot.messages[i].chat_id, "/temp: Mostra sul display la temperatura della pianta", "");
       bot.sendMessage(bot.messages[i].chat_id, "/lux: Mostra sul display la luminosità sulla pianta", "");
       bot.sendMessage(bot.messages[i].chat_id, "/umid: Mostra sul display la percentuale di umidità della pianta", "");
       bot.sendMessage(bot.messages[i].chat_id, "/lcd: Mostra la schermata iniziale del display", "");
       bot.sendMessage(bot.messages[i].chat_id, "/insta: Fornisce il link del profilo Instagram di Green Symphony", "");
       bot.sendMessage(bot.messages[i].chat_id, "/git: Fornisce il link del profilo GitHub di Green Symphony", "");
       bot.sendMessage(bot.messages[i].chat_id, "/web: Fornisce il link del sito di Green Symphony", "");
    }else if(msg == "/clear"){
        Serial.println("Clear");
        lcd.clear();
        lcd.setCursor(0, 0);
    }else if(msg == "/temp"){
        Serial.println("Temp");
        lcd.clear();
        lcd.print("Temp.: ");
        lcd.print(String(temp));
        lcd.print(" C");
        lcd.setCursor(0, 1);
    }else if(msg == "/lux"){
        Serial.println("Lux");
        lcd.clear();
        lcd.print("Lumin.: ");
        lcd.print(String(lux));
        lcd.print(" lm");
        lcd.setCursor(0, 1);
    }else if(msg == "/umid"){
        Serial.println("Umid");
        lcd.clear();
        lcd.print("Umidita': ");
        lcd.print(String(umid));
        lcd.print("%");
        lcd.setCursor(0, 1);
    }else if(msg == "/lcd"){
        lcd.clear();
        lcdStart();
    }else if(msg == "/insta"){
        bot.sendMessage(chatid, "Instagram: " + insta, "");
    }else if(msg == "/git"){
        bot.sendMessage(chatid, "GitHub: " + git, "");
    }else if(msg == "/web"){
        bot.sendMessage(chatid, "Sito Web: " + web, "");
    }else{
        bot.sendMessage(bot.messages[i].chat_id, "Comando sconosciuto", "");
    }
  }
}
