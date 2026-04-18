// seven block rush auton

#include "main.h"
#include "lemlib/api.hpp"
#include "../../../include/configs.h"
#include "../autons.h"

void swap(){
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0,-47,2000, {.forwards=false});
    chassis.turnToHeading(-90, 2000);
    chassis.moveToPoint(-1000,-47,2000);
    chassis.moveToPoint(1000,-47,2000, {.forwards=false});
    chassis.swingToHeading(0,2000);
    chassis.moveToPoint(23,48,2000);
    chassis.turnToHeading(-45,2000);  
    chassis.moveToPoint(0,56,2000);
    chassis.turnToHeading(-90,2000);
    chassis.moveToPoint(-2000,56,2000);
    chassis.moveToPoint(0,56,2000);
    chassis.moveToPoint(36,36,2000);
}