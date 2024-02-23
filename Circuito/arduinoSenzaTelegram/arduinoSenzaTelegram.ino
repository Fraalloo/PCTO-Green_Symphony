#include <LiquidCrystal.h>
#include <DHT.h>

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

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
}

void loop(){
  umid = dht.readHumidity();
  lux1 = analogRead(FRS1);
  lux2 = analogRead(FRS2);
  lux3 = analogRead(FRS3);
  temp = dht.readTemperature();

  percentualeLux = (map(lux1, 0, 1023, 0, 100) + map(lux2, 0, 1023, 0, 100) + map(lux3, 0, 1023, 0, 100))/3;

  if(Serial.available()){
    String inputString = "";

    while(Serial.available()){
      char incomingChar = Serial.read();

      if (incomingChar == '\n') {
        break;
      }
      inputString += incomingChar;
      delay(2);
    }

    if(inputString.equals("/read")){
      Serial.print("Umidita del terreno: ");
      Serial.print(umid);
      Serial.println("%");

      Serial.print("Luminosita': ");
      Serial.print(percentualeLux);
      Serial.println("%");

      Serial.print("Temperatura: ");
      Serial.print(temp);
      Serial.println("C");
    }else if(inputString.equals("/clear")) {
      lcd.clear();
      lcd.setCursor(0, 0);
    }else if(inputString.equals("/temp")) {
      lcd.clear();
      lcd.print("Temp.: ");
      lcd.print(String(temp));
      lcd.print("C");
      lcd.setCursor(0, 1);
    }else if(inputString.equals("/lux")){
      lcd.clear();
      lcd.print("Lumin.: ");
      lcd.print(String(percentualeLux));
      lcd.print("%");
      lcd.setCursor(0, 1);
    }else if(inputString.equals("/umid")){
      lcd.clear();
      lcd.print("Umidita': ");
      lcd.print(String(umid));
      lcd.print("%");
      lcd.setCursor(0, 1);
    }
  }

  delay(1000);
}
