/*********

  Руи Сантос

  Более подробно о проекте на: https://randomnerdtutorials.com  

*********/


// Импортируем необходимые библиотеки:

#include "WiFi.h"

#include "ESPAsyncWebServer.h"

#include "SPIFFS.h"

//#include <AsyncJson.h>

#include <ArduinoJson.h>


// Вставьте ниже SSID и пароль для своей WiFi-сети:

const char* ssid = "TechLan";

const char* password = "IbNhAtTaB1986_";


// Задаем GPIO-контакт, к которому подключен светодиод:

const int ledPin = 2;


// Создаем экземпляр класса «AsyncWebServer»

// под названием «server» и задаем ему номер порта «80»:

AsyncWebServer server(80);


// Меняем заглушку на текущее состояние светодиода:

String processor(const String& var){

  // Создаем переменную для хранения состояния светодиода:

  String ledState;


  Serial.println(var);

  if(var == "STATE"){

    if(digitalRead(ledPin)){

      ledState = "ON";

    }

    else{

      ledState = "OFF";

    }
    Serial.print(ledState);
    return ledState;
  }

  return String();

}

uint16_t potValue = 0;
uint16_t threshold = 0;
const uint8_t potPin = 34;

 

void setup(){
  // Включаем последовательную коммуникацию (для отладки):

  Serial.begin(9600);
  Serial2.begin(115200);

  pinMode(ledPin, OUTPUT);


  // Инициализируем SPIFFS:

  if(!SPIFFS.begin(true)){

    Serial.println("An Error has occurred while mounting SPIFFS");

               //  "При монтировании SPIFFS произошла ошибка"
    return;
  }

  // Подключаемся к WiFi:

  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);

    Serial.println("Connecting to WiFi..");

               //  "Подключаемся к WiFi..."
  }

  // Печатаем в мониторе порта локальный IP-адрес ESP32:

  Serial.println(WiFi.localIP());


  // URL для корневой страницы веб-сервера:
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasArg("threshold")) {
      AsyncWebParameter* p = request->getParam("threshold");
       threshold = p->value().toInt();
       Serial2.println(threshold);
       Serial.println(String(threshold));
     request->send(204);
     return;
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
// Расшарим файл стилей
  server.on("/css/style.css", HTTP_GET, [](AsyncWebServerRequest *request){

    request->send(SPIFFS, "/css/style.css", "text/css");

  });

  //Расшарим скрипт js

  server.on("/js/jquery.js", HTTP_GET, [](AsyncWebServerRequest *request){

    request->send(SPIFFS, "/js/jquery.js", "text/javascript");

  });

   server.on("/illumination", HTTP_GET, [](AsyncWebServerRequest *request){
     AsyncResponseStream *response = request->beginResponseStream("text/json");
     DynamicJsonBuffer jsonBuffer;
     JsonObject &root = jsonBuffer.createObject();
     root["illumination"] = potValue;
     root["threshold"] = threshold;
     root.printTo(*response);
     request->send(response);
  });

  // Запускаем сервер:

  server.begin();

}

void loop(){
  
  //potValue = analogRead(potPin);
  if (Serial2.available()) {
    String str = Serial2.readString();
    //str = str.substring(0,str.length()-1);
    Serial.println(str);
   // potValue = str.toInt();
    //Serial.println(str.toInt());
  }
  //Serial2.println("Hello");
  
}