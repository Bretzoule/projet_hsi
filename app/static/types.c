
/*! 
*  \file types.c
*  \author LEFLOCH Thomas <leflochtho@eisti.eu>
*/
#include "types.h"
static data_t data = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
isActivate_t getisActivateWarning() {
    return (data.isActivateWarning);
}

    
void setisActivateWarning(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateWarning = val;
    } else {
        printf("Error, value not in domain isActivateWarning doesnt accept : %d\n", val);
    }
}
    
    
isActivate_t getisActivateIdleLight() {
    return (data.isActivateIdleLight);
}

    
void setisActivateIdleLight(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateIdleLight = val;
    } else {
        printf("Error, value not in domain isActivateIdleLight doesnt accept : %d\n", val);
    }
}
    
    
isActivate_t getisActivateLowBeam() {
    return (data.isActivateLowBeam);
}

    
void setisActivateLowBeam(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateLowBeam = val;
    } else {
        printf("Error, value not in domain isActivateLowBeam doesnt accept : %d\n", val);
    }
}
    
    
isActivate_t getisActivateHighBeam() {
    return (data.isActivateHighBeam);
}

    
void setisActivateHighBeam(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateHighBeam = val;
    } else {
        printf("Error, value not in domain isActivateHighBeam doesnt accept : %d\n", val);
    }
}
    
    
isActivate_t getisActivateRightBlinker() {
    return (data.isActivateRightBlinker);
}

    
void setisActivateRightBlinker(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateRightBlinker = val;
    } else {
        printf("Error, value not in domain isActivateRightBlinker doesnt accept : %d\n", val);
    }
}
    
    
isActivate_t getisActivateLeftBlinker() {
    return (data.isActivateLeftBlinker);
}

    
void setisActivateLeftBlinker(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateLeftBlinker = val;
    } else {
        printf("Error, value not in domain isActivateLeftBlinker doesnt accept : %d\n", val);
    }
}
    
    
isActivate_t getisActivateWindshieldWiper() {
    return (data.isActivateWindshieldWiper);
}

    
void setisActivateWindshieldWiper(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateWindshieldWiper = val;
    } else {
        printf("Error, value not in domain isActivateWindshieldWiper doesnt accept : %d\n", val);
    }
}
    
    
isActivate_t getisActivateIceWasher() {
    return (data.isActivateIceWasher);
}

    
void setisActivateIceWasher(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateIceWasher = val;
    } else {
        printf("Error, value not in domain isActivateIceWasher doesnt accept : %d\n", val);
    }
}
    
    
km_t getkm() {
    return (data.km);
}

    
void setkm(km_t val) {
    if(val >= 0) {
    data.km = val;
    } else {
        printf("Error, value not in domain km doesnt accept : %d\n", val);
    }
}
    
    
speed_t getspeed() {
    return (data.speed);
}

    
void setspeed(speed_t val) {
    if(val <= 255 && val >= 0) {
    data.speed = val;
    } else {
        printf("Error, value not in domain speed doesnt accept : %d\n", val);
    }
}
    
    
frameissue_t getframeIssue() {
    return (data.frameIssue);
}

    
void setframeIssue(frameissue_t val) {
    if(val < 3 && val >= 0) {
    data.frameIssue = val;
    } else {
        printf("Error, value not in domain frameIssue doesnt accept : %d\n", val);
    }
}
    
    
engineissue_t getengineIssue() {
    return (data.engineIssue);
}

    
void setengineIssue(engineissue_t val) {
    if(val < 4 && val >= 0) {
    data.engineIssue = val;
    } else {
        printf("Error, value not in domain engineIssue doesnt accept : %d\n", val);
    }
}
    
    
fuellvl_t getfuelLevel() {
    return (data.fuelLevel);
}

    
void setfuelLevel(fuellvl_t val) {
    if(val >= 0 && val <= 40) {
    data.fuelLevel = val;
    } else {
        printf("Error, value not in domain fuelLevel doesnt accept : %d\n", val);
    }
}
    
    
rpm_t getrpm() {
    return (data.rpm);
}

    
void setrpm(rpm_t val) {
    if(val <= 10000) {
    data.rpm = val;
    } else {
        printf("Error, value not in domain rpm doesnt accept : %d\n", val);
    }
}
    
    
batteryissue_t getbatteryIssue() {
    return (data.batteryIssue);
}

    
void setbatteryIssue(batteryissue_t val) {
    if(val < 3 && val >= 0) {
    data.batteryIssue = val;
    } else {
        printf("Error, value not in domain batteryIssue doesnt accept : %d\n", val);
    }
}
    
    
isAcquited_t getidleIsAcquited() {
    return (data.idleIsAcquited);
}

    
void setidleIsAcquited(isAcquited_t val) {
    if(val == 0 || val == 1) {
    data.idleIsAcquited = val;
    } else {
        printf("Error, value not in domain idleIsAcquited doesnt accept : %d\n", val);
    }
}
    
    
isAcquited_t getlowBeamIsAcquited() {
    return (data.lowBeamIsAcquited);
}

    
void setlowBeamIsAcquited(isAcquited_t val) {
    if(val == 0 || val == 1) {
    data.lowBeamIsAcquited = val;
    } else {
        printf("Error, value not in domain lowBeamIsAcquited doesnt accept : %d\n", val);
    }
}
    
    
isAcquited_t gethighBeamIsAcquited() {
    return (data.highBeamIsAcquited);
}

    
void sethighBeamIsAcquited(isAcquited_t val) {
    if(val == 0 || val == 1) {
    data.highBeamIsAcquited = val;
    } else {
        printf("Error, value not in domain highBeamIsAcquited doesnt accept : %d\n", val);
    }
}
    
    
isActivate_t getisActivateAndEnabledLeftBlinker() {
    return (data.isActivateAndEnabledLeftBlinker);
}

    
void setisActivateAndEnabledLeftBlinker(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateAndEnabledLeftBlinker = val;
    } else {
        printf("Error, value not in domain isActivateAndEnabledLeftBlinker doesnt accept : %d\n", val);
    }
}
    
    
isActivate_t getisActivateAndEnabledRightBlinker() {
    return (data.isActivateAndEnabledRightBlinker);
}

    
void setisActivateAndEnabledRightBlinker(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateAndEnabledRightBlinker = val;
    } else {
        printf("Error, value not in domain isActivateAndEnabledRightBlinker doesnt accept : %d\n", val);
    }
}
    
    
isAcquited_t getisActivateAndEnabledAndAcquittedLeftBlinker() {
    return (data.isActivateAndEnabledAndAcquittedLeftBlinker);
}

    
void setisActivateAndEnabledAndAcquittedLeftBlinker(isAcquited_t val) {
    if(val == 0 || val == 1) {
    data.isActivateAndEnabledAndAcquittedLeftBlinker = val;
    } else {
        printf("Error, value not in domain isActivateAndEnabledAndAcquittedLeftBlinker doesnt accept : %d\n", val);
    }
}
    
    
isAcquited_t getisActivateAndEnabledAndAcquittedRightBlinker() {
    return (data.isActivateAndEnabledAndAcquittedRightBlinker);
}

    
void setisActivateAndEnabledAndAcquittedRightBlinker(isAcquited_t val) {
    if(val == 0 || val == 1) {
    data.isActivateAndEnabledAndAcquittedRightBlinker = val;
    } else {
        printf("Error, value not in domain isActivateAndEnabledAndAcquittedRightBlinker doesnt accept : %d\n", val);
    }
}
    