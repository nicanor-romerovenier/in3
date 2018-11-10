#include <memory>

#include <Arduino.h>
#include <DHT.h>
#include <PID_v1.h>
#include <SPI.h>

#define FWversion "v1.12"

#include "IncubatorManager.h"


void setup() {
    Serial.begin(115200);
    Serial.print("IN3ATOR, VERSION ");
    Serial.println(FWversion);

    std::unique_ptr<IncubatorManager> incubator_manager = std::unique_ptr<IncubatorManager>(new IncubatorManager());
}
