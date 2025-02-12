#ifndef LIGHTING_CONTROLLER_H
#define LIGHTING_CONTROLLER_H

class LightingController {
private:
    int pin;
public:
    LightingController(int pin);
    void activate();
};

#endif