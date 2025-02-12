#ifndef HEATING_CONTROLLER_H
#define HEATING_CONTROLLER_H

class HeatingController {
private:
    int pin;
    bool activated;
public:
    HeatingController(int pin);
    void activate();
    void deactivate();
    bool isActive();
};

#endif