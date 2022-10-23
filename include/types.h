
#ifndef TYPES_H
#define TYPES_H
/*! 
*  \file types.h
*  \author LEFLOCH Thomas <leflochtho@eisti.eu>
*/

// Inclusion des entetes de librairies
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
    
    
/**
* \typedef isActivate_t
* \brief undefined
*/
typedef bool isActivate_t;

/**
* \typedef crc8_t
* \brief undefined
*/
typedef uint8_t crc8_t;

/**
* \typedef tramenb_t
* \brief undefined
*/
typedef uint8_t tramenb_t;

/**
* \typedef km_t
* \brief undefined
*/
typedef uint32_t km_t;

/**
* \typedef speed_t
* \brief undefined
*/
typedef uint8_t speed_t;

/**
* \enum frameissue_t
* \brief undefined
*/
typedef enum frameissue_t {
    noFrameIssue,tirePressure,usedBrakes
}frameissue_t;

/**
* \enum motorissue_t
* \brief undefined
*/
typedef enum motorissue_t {
    noMotorIssue,pressureError,ldrTemperature,oilOverheat
}motorissue_t;

/**
* \typedef fuellvl_t
* \brief undefined
*/
typedef uint8_t fuellvl_t;

/**
* \typedef rpm_t
* \brief undefined
*/
typedef uint32_t rpm_t;

/**
* \enum batteryissue_t
* \brief undefined
*/
typedef enum batteryissue_t {
    noBatteryIssue,empty,failure
}batteryissue_t;

/**
* \typedef isOnIndicator
* \brief undefined
*/
typedef bool isOnIndicator;

    
/*!
*  \fn isActivate_t getisActivateWarning()
*  \brief 
*  \param 
*  \return isActivateWarning
*/
isActivate_t getisActivateWarning();

    
/*!
*  \proc void setisActivateWarning()
*  \brief 
*  \param 
*  \return isActivateWarning
*/
void setisActivateWarning(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateStateLight()
*  \brief 
*  \param 
*  \return isActivateStateLight
*/
isActivate_t getisActivateStateLight();

    
/*!
*  \proc void setisActivateStateLight()
*  \brief 
*  \param 
*  \return isActivateStateLight
*/
void setisActivateStateLight(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateDippedBeam()
*  \brief 
*  \param 
*  \return isActivateDippedBeam
*/
isActivate_t getisActivateDippedBeam();

    
/*!
*  \proc void setisActivateDippedBeam()
*  \brief 
*  \param 
*  \return isActivateDippedBeam
*/
void setisActivateDippedBeam(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateMainBeam()
*  \brief 
*  \param 
*  \return isActivateMainBeam
*/
isActivate_t getisActivateMainBeam();

    
/*!
*  \proc void setisActivateMainBeam()
*  \brief 
*  \param 
*  \return isActivateMainBeam
*/
void setisActivateMainBeam(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateRightTurnSignal()
*  \brief 
*  \param 
*  \return isActivateRightTurnSignal
*/
isActivate_t getisActivateRightTurnSignal();

    
/*!
*  \proc void setisActivateRightTurnSignal()
*  \brief 
*  \param 
*  \return isActivateRightTurnSignal
*/
void setisActivateRightTurnSignal(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateLeftTurnSignal()
*  \brief 
*  \param 
*  \return isActivateLeftTurnSignal
*/
isActivate_t getisActivateLeftTurnSignal();

    
/*!
*  \proc void setisActivateLeftTurnSignal()
*  \brief 
*  \param 
*  \return isActivateLeftTurnSignal
*/
void setisActivateLeftTurnSignal(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateWindshieldWiper()
*  \brief 
*  \param 
*  \return isActivateWindshieldWiper
*/
isActivate_t getisActivateWindshieldWiper();

    
/*!
*  \proc void setisActivateWindshieldWiper()
*  \brief 
*  \param 
*  \return isActivateWindshieldWiper
*/
void setisActivateWindshieldWiper(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateIceWasher()
*  \brief 
*  \param 
*  \return isActivateIceWasher
*/
isActivate_t getisActivateIceWasher();

    
/*!
*  \proc void setisActivateIceWasher()
*  \brief 
*  \param 
*  \return isActivateIceWasher
*/
void setisActivateIceWasher(isActivate_t val);
    
    
/*!
*  \fn crc8_t getcrc8()
*  \brief 
*  \param 
*  \return crc8
*/
crc8_t getcrc8();

    
/*!
*  \proc void setcrc8()
*  \brief 
*  \param 
*  \return crc8
*/
void setcrc8(crc8_t val);
    
    
/*!
*  \fn tramenb_t gettrameNb()
*  \brief 
*  \param 
*  \return trameNb
*/
tramenb_t gettrameNb();

    
/*!
*  \proc void settrameNb()
*  \brief 
*  \param 
*  \return trameNb
*/
void settrameNb(tramenb_t val);
    
    
/*!
*  \fn km_t getkm()
*  \brief 
*  \param 
*  \return km
*/
km_t getkm();

    
/*!
*  \proc void setkm()
*  \brief 
*  \param 
*  \return km
*/
void setkm(km_t val);
    
    
/*!
*  \fn speed_t getspeed()
*  \brief 
*  \param 
*  \return speed
*/
speed_t getspeed();

    
/*!
*  \proc void setspeed()
*  \brief 
*  \param 
*  \return speed
*/
void setspeed(speed_t val);
    
    
/*!
*  \fn frameissue_t getframeIssue()
*  \brief 
*  \param 
*  \return frameIssue
*/
frameissue_t getframeIssue();

    
/*!
*  \proc void setframeIssue()
*  \brief 
*  \param 
*  \return frameIssue
*/
void setframeIssue(frameissue_t val);
    
    /*!
 *  \struct data
 *  \brief Entire data of the program
 */

typedef struct data {
     isActivate_t isActivateWarning;
    isActivate_t isActivateStateLight;
    isActivate_t isActivateDippedBeam;
    isActivate_t isActivateMainBeam;
    isActivate_t isActivateRightTurnSignal;
    isActivate_t isActivateLeftTurnSignal;
    isActivate_t isActivateWindshieldWiper;
    isActivate_t isActivateIceWasher;
    crc8_t crc8;
    tramenb_t trameNb;
    km_t km;
    speed_t speed;
    frameissue_t frameIssue;
    
}data_t;

#endif
    