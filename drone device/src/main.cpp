/* WiFi scan Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sdkconfig.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <HTTPClient.h>
#include "NetworkDroneController.h"

int pin = 2;
void connectAp(String ap, String password) 
{
  WiFi.begin(ap.c_str(), password.c_str());
  while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(200);

       
    }
 
  
  Serial.println("Wifi connected to "+ap+"!" );
  NetworkDroneController* networkDroneController = new NetworkDroneController();
  networkDroneController->Connect("192.168.178.177");
}


int motion = LOW;

void setup() {
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
  
    Serial.begin(9600);
    

    pinMode(25, OUTPUT);
    
    connectAp("Ziggo6562938", "m7wCrnf3yypg");
    delay(110);
}

void loop() {
    // Wait a bit before scanning again
   
    
    

}


