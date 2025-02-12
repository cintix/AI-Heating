#ifndef LIGHTING_CONTROLLER_H
#define LIGHTING_CONTROLLER_H

class LightingController {
private:
    int pin;
    bool activated;
public:
    LightingController(int pin);
    void activate();
    void deactivate();
    bool isActive();
};

#endif