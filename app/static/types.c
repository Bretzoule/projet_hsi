
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
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateIdleLight() {
    return (data.isActivateIdleLight);
}

    
void setisActivateIdleLight(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateIdleLight = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateLowBeam() {
    return (data.isActivateLowBeam);
}

    
void setisActivateLowBeam(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateLowBeam = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateHighBeam() {
    return (data.isActivateHighBeam);
}

    
void setisActivateHighBeam(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateHighBeam = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateRightBlinker() {
    return (data.isActivateRightBlinker);
}

    
void setisActivateRightBlinker(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateRightBlinker = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateLeftBlinker() {
    return (data.isActivateLeftBlinker);
}

    
void setisActivateLeftBlinker(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateLeftBlinker = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateWindshieldWiper() {
    return (data.isActivateWindshieldWiper);
}

    
void setisActivateWindshieldWiper(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateWindshieldWiper = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateIceWasher() {
    return (data.isActivateIceWasher);
}

    
void setisActivateIceWasher(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateIceWasher = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
km_t getkm() {
    return (data.km);
}

    
void setkm(km_t val) {
    if(val >= 0) {
    data.km = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
speed_t getspeed() {
    return (data.speed);
}

    
void setspeed(speed_t val) {
    if(val <= 255 && val >= 0) {
    data.speed = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
frameissue_t getframeIssue() {
    return (data.frameIssue);
}

    
void setframeIssue(frameissue_t val) {
    if(val < 3 && val >= 0) {
    data.frameIssue = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
engineissue_t getengineIssue() {
    return (data.engineIssue);
}

    
void setengineIssue(engineissue_t val) {
    if(val < 4 && val >= 0) {
    data.engineIssue = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
fuellvl_t getfuelLevel() {
    return (data.fuelLevel);
}

    
void setfuelLevel(fuellvl_t val) {
    if(val >= 0 && val <= 40) {
    data.fuelLevel = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
rpm_t getrpm() {
    return (data.rpm);
}

    
void setrpm(rpm_t val) {
    if(val <= 10000) {
    data.rpm = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
batteryissue_t getbatteryIssue() {
    return (data.batteryIssue);
}

    
void setbatteryIssue(batteryissue_t val) {
    if(val < 3 && val >= 0) {
    data.batteryIssue = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isAcquited_t getidleIsAcquited() {
    return (data.idleIsAcquited);
}

    
void setidleIsAcquited(isAcquited_t val) {
    if(val == 0 || val == 1) {
    data.idleIsAcquited = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isAcquited_t getlowBeamIsAcquited() {
    return (data.lowBeamIsAcquited);
}

    
void setlowBeamIsAcquited(isAcquited_t val) {
    if(val == 0 || val == 1) {
    data.lowBeamIsAcquited = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isAcquited_t gethighBeamIsAcquited() {
    return (data.highBeamIsAcquited);
}

    
void sethighBeamIsAcquited(isAcquited_t val) {
    if(val == 0 || val == 1) {
    data.highBeamIsAcquited = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateAndEnabledLeftBlinker() {
    return (data.isActivateAndEnabledLeftBlinker);
}

    
void setisActivateAndEnabledLeftBlinker(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateAndEnabledLeftBlinker = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateAndEnabledRightBlinker() {
    return (data.isActivateAndEnabledRightBlinker);
}

    
void setisActivateAndEnabledRightBlinker(isActivate_t val) {
    if(val == 0 || val == 1) {
    data.isActivateAndEnabledRightBlinker = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isAcquited_t getisActivateAndEnabledAndAcquittedLeftBlinker() {
    return (data.isActivateAndEnabledAndAcquittedLeftBlinker);
}

    
void setisActivateAndEnabledAndAcquittedLeftBlinker(isAcquited_t val) {
    if(val == 0 || val == 1) {
    data.isActivateAndEnabledAndAcquittedLeftBlinker = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isAcquited_t getisActivateAndEnabledAndAcquittedRightBlinker() {
    return (data.isActivateAndEnabledAndAcquittedRightBlinker);
}

    
void setisActivateAndEnabledAndAcquittedRightBlinker(isAcquited_t val) {
    if(val == 0 || val == 1) {
    data.isActivateAndEnabledAndAcquittedRightBlinker = val;
    } else {
        printf("Error, value not in domain");
    }
}
    