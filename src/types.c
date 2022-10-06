
/*! 
*  \file types.c
*  \author LEFLOCH Thomas <leflochtho@eisti.eu>
*/
#include "types.h"
static data_t bcgvDATA = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    
isActivate_t getisActivateWarning() {
    return (bcgvDATA.isActivateWarning);
}

    
void setisActivateWarning(isActivate_t val) {
    if(val == 0 || val == 1) {
    bcgvDATA.isActivateWarning = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateStateLight() {
    return (bcgvDATA.isActivateStateLight);
}

    
void setisActivateStateLight(isActivate_t val) {
    if(val == 0 || val == 1) {
    bcgvDATA.isActivateStateLight = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateDippedBeam() {
    return (bcgvDATA.isActivateDippedBeam);
}

    
void setisActivateDippedBeam(isActivate_t val) {
    if(val == 0 || val == 1) {
    bcgvDATA.isActivateDippedBeam = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateMainBeam() {
    return (bcgvDATA.isActivateMainBeam);
}

    
void setisActivateMainBeam(isActivate_t val) {
    if(val == 0 || val == 1) {
    bcgvDATA.isActivateMainBeam = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateRightTurnSignal() {
    return (bcgvDATA.isActivateRightTurnSignal);
}

    
void setisActivateRightTurnSignal(isActivate_t val) {
    if(val == 0 || val == 1) {
    bcgvDATA.isActivateRightTurnSignal = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateLeftTurnSignal() {
    return (bcgvDATA.isActivateLeftTurnSignal);
}

    
void setisActivateLeftTurnSignal(isActivate_t val) {
    if(val == 0 || val == 1) {
    bcgvDATA.isActivateLeftTurnSignal = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateWindshieldWiper() {
    return (bcgvDATA.isActivateWindshieldWiper);
}

    
void setisActivateWindshieldWiper(isActivate_t val) {
    if(val == 0 || val == 1) {
    bcgvDATA.isActivateWindshieldWiper = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
isActivate_t getisActivateIceWasher() {
    return (bcgvDATA.isActivateIceWasher);
}

    
void setisActivateIceWasher(isActivate_t val) {
    if(val == 0 || val == 1) {
    bcgvDATA.isActivateIceWasher = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
crc8_t getcrc8() {
    return (bcgvDATA.crc8);
}

    
void setcrc8(crc8_t val) {
    if(val >= 0) {
    bcgvDATA.crc8 = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
tramenb_t gettrameNb() {
    return (bcgvDATA.trameNb);
}

    
void settrameNb(tramenb_t val) {
    if((val = val % 100) || 1) {
    bcgvDATA.trameNb = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
km_t getkm() {
    return (bcgvDATA.km);
}

    
void setkm(km_t val) {
    if(val >= 0) {
    bcgvDATA.km = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
speed_t getspeed() {
    return (bcgvDATA.speed);
}

    
void setspeed(speed_t val) {
    if(val <= 255 && val >= 0) {
    bcgvDATA.speed = val;
    } else {
        printf("Error, value not in domain");
    }
}
    
    
frameissue_t getframeIssue() {
    return (bcgvDATA.frameIssue);
}

    
void setframeIssue(frameissue_t val) {
    if(val < 3 && val >= 0) {
    bcgvDATA.frameIssue = val;
    } else {
        printf("Error, value not in domain");
    }
}
    