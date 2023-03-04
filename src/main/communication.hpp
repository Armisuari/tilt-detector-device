#pragma once

#include <ThingESP.h>

ThingESP32 thing("BossHQ", "botwasaja", "botwasaja12");

struct thingESP
{
    bool begin(const char *ssid, const char *pass)
    {
        thing.SetWiFi(ssid, pass);
        return true;
    }
};

void setup_thingESP()
{
    thing.initDevice();
}