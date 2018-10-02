
#include "FS.h"
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "WebService.h"
#include "Queue.h"
#include "RelayController.h"
#include "ArduinoJson.h"

AsyncWebServer server(80);

String getSoil()
{
  uint8_t sreading[2];
   String returnStr;
   BaseType_t xStatus; 
   xStatus = xQueueReceive(soilQ, &sreading, pdMS_TO_TICKS(80)); 
   if(xStatus == pdPASS)   
   {
      returnStr =  (String)sreading[1];
    
   }
   else
      returnStr = "0";

  return returnStr;
}

String getTemp()
{
  uint8_t sreading[2];
   String returnStr;
   BaseType_t xStatus; 
   xStatus = xQueueReceive(tempQ, &sreading, pdMS_TO_TICKS(80)); 
   if(xStatus == pdPASS)   
   {
      returnStr =  (String)sreading[1];
    
   }
   else
      returnStr = "0";

  return returnStr;
}

String getHumid()
{
  uint8_t sreading[2];
   String returnStr;
   BaseType_t xStatus; 
   xStatus = xQueueReceive(humidQ, &sreading, pdMS_TO_TICKS(80)); 
   if(xStatus == pdPASS)   
   {
      returnStr =  (String)sreading[1];
    
   }
   else
      returnStr = "0";

  return returnStr;
}

String getLight()
{
  uint8_t sreading[2];
   String returnStr;
   BaseType_t xStatus; 
   xStatus = xQueueReceive(lightQ, &sreading, pdMS_TO_TICKS(80)); 
   if(xStatus == pdPASS)   
   {
      returnStr =  (String)sreading[1];
    
   }
   else
      returnStr = "0";

  return returnStr;
}

String createJsonResponse()
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["soil"] = getSoil();
  root["temperature"] = getTemp();
  root["humidity"] = getHumid();
  root["light"] =  getLight();
   
  String json;
  root.printTo(json);
  return json;
}

void webServiceSetup()
{
  server.on("/getdata", HTTP_GET, [](AsyncWebServerRequest *request)
        {
           String jsonData = createJsonResponse();
           request->send(200, "text/json",  jsonData);
       });

 
  // water relay on
   server.on("/put/wateron", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           waterControl();
        });

 // water relay off
  server.on("/put/wateroff", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           turnOffWater();
        });

  // water relay on
   server.on("/put/wateron2", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           waterControl2();
        });

 // water relay off
  server.on("/put/wateroff2", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           turnOffWater2();
        });

// fan relayd on
   server.on("/put/fanon", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           fanControl();
        });

// fan relay off
   server.on("/put/fanoff", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           turnOffFan();
        });


    server.on("/put/heaton", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           heatControl();
        });

// fan relay off
   server.on("/put/heatoff", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           turnOffHeat();
        });

  server.on("/put/heaton2", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           heatControl2();
        });

// fan relay off
   server.on("/put/heatoff2", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           turnOffHeat2();
        });

server.on("/put/humidon", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           humidControl();
        });

// fan relay off
   server.on("/put/humidoff", HTTP_PUT, [](AsyncWebServerRequest *request)
        {
           request->send(200, "text/plain", "");
           turnOffHumidifier();
        });

  server.begin();

}


