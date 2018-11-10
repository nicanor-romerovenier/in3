#include <memory>

#include <Arduino.h>
#include <Adafruit_ILI9341_STM.h> // STM32 DMA Hardware-specific library
#include <Adafruit_GFX_AS.h>
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
