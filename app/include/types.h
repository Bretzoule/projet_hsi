
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
* \enum engineissue_t
* \brief undefined
*/
typedef enum engineissue_t {
    noEngineIssue,pressureError,ldrTemperature,oilOverheat
}engineissue_t;

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

/**
* \typedef isAcquited_t
* \brief undefined
*/
typedef bool isAcquited_t;

    
/*!
*  \fn isActivate_t getisActivateWarning()
*  \brief get param isActivateWarning
*  \return isActivateWarning isActivate_t
*/
isActivate_t getisActivateWarning();

    
/*!
*  \fn void setisActivateWarning(isActivate_t val)
*  \brief set param isActivateWarning 
*  \param isActivateWarning val : value to be setted
*/
void setisActivateWarning(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateIdleLight()
*  \brief get param isActivateIdleLight
*  \return isActivateIdleLight isActivate_t
*/
isActivate_t getisActivateIdleLight();

    
/*!
*  \fn void setisActivateIdleLight(isActivate_t val)
*  \brief set param isActivateIdleLight 
*  \param isActivateIdleLight val : value to be setted
*/
void setisActivateIdleLight(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateLowBeam()
*  \brief get param isActivateLowBeam
*  \return isActivateLowBeam isActivate_t
*/
isActivate_t getisActivateLowBeam();

    
/*!
*  \fn void setisActivateLowBeam(isActivate_t val)
*  \brief set param isActivateLowBeam 
*  \param isActivateLowBeam val : value to be setted
*/
void setisActivateLowBeam(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateHighBeam()
*  \brief get param isActivateHighBeam
*  \return isActivateHighBeam isActivate_t
*/
isActivate_t getisActivateHighBeam();

    
/*!
*  \fn void setisActivateHighBeam(isActivate_t val)
*  \brief set param isActivateHighBeam 
*  \param isActivateHighBeam val : value to be setted
*/
void setisActivateHighBeam(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateRightBlinker()
*  \brief get param isActivateRightBlinker
*  \return isActivateRightBlinker isActivate_t
*/
isActivate_t getisActivateRightBlinker();

    
/*!
*  \fn void setisActivateRightBlinker(isActivate_t val)
*  \brief set param isActivateRightBlinker 
*  \param isActivateRightBlinker val : value to be setted
*/
void setisActivateRightBlinker(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateLeftBlinker()
*  \brief get param isActivateLeftBlinker
*  \return isActivateLeftBlinker isActivate_t
*/
isActivate_t getisActivateLeftBlinker();

    
/*!
*  \fn void setisActivateLeftBlinker(isActivate_t val)
*  \brief set param isActivateLeftBlinker 
*  \param isActivateLeftBlinker val : value to be setted
*/
void setisActivateLeftBlinker(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateWindshieldWiper()
*  \brief get param isActivateWindshieldWiper
*  \return isActivateWindshieldWiper isActivate_t
*/
isActivate_t getisActivateWindshieldWiper();

    
/*!
*  \fn void setisActivateWindshieldWiper(isActivate_t val)
*  \brief set param isActivateWindshieldWiper 
*  \param isActivateWindshieldWiper val : value to be setted
*/
void setisActivateWindshieldWiper(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateIceWasher()
*  \brief get param isActivateIceWasher
*  \return isActivateIceWasher isActivate_t
*/
isActivate_t getisActivateIceWasher();

    
/*!
*  \fn void setisActivateIceWasher(isActivate_t val)
*  \brief set param isActivateIceWasher 
*  \param isActivateIceWasher val : value to be setted
*/
void setisActivateIceWasher(isActivate_t val);
    
    
/*!
*  \fn km_t getkm()
*  \brief get param km
*  \return km km_t
*/
km_t getkm();

    
/*!
*  \fn void setkm(km_t val)
*  \brief set param km 
*  \param km val : value to be setted
*/
void setkm(km_t val);
    
    
/*!
*  \fn speed_t getspeed()
*  \brief get param speed
*  \return speed speed_t
*/
speed_t getspeed();

    
/*!
*  \fn void setspeed(speed_t val)
*  \brief set param speed 
*  \param speed val : value to be setted
*/
void setspeed(speed_t val);
    
    
/*!
*  \fn frameissue_t getframeIssue()
*  \brief get param frameIssue
*  \return frameIssue frameissue_t
*/
frameissue_t getframeIssue();

    
/*!
*  \fn void setframeIssue(frameissue_t val)
*  \brief set param frameIssue 
*  \param frameIssue val : value to be setted
*/
void setframeIssue(frameissue_t val);
    
    
/*!
*  \fn engineissue_t getengineIssue()
*  \brief get param engineIssue
*  \return engineIssue engineissue_t
*/
engineissue_t getengineIssue();

    
/*!
*  \fn void setengineIssue(engineissue_t val)
*  \brief set param engineIssue 
*  \param engineIssue val : value to be setted
*/
void setengineIssue(engineissue_t val);
    
    
/*!
*  \fn fuellvl_t getfuelLevel()
*  \brief get param fuelLevel
*  \return fuelLevel fuellvl_t
*/
fuellvl_t getfuelLevel();

    
/*!
*  \fn void setfuelLevel(fuellvl_t val)
*  \brief set param fuelLevel 
*  \param fuelLevel val : value to be setted
*/
void setfuelLevel(fuellvl_t val);
    
    
/*!
*  \fn rpm_t getrpm()
*  \brief get param rpm
*  \return rpm rpm_t
*/
rpm_t getrpm();

    
/*!
*  \fn void setrpm(rpm_t val)
*  \brief set param rpm 
*  \param rpm val : value to be setted
*/
void setrpm(rpm_t val);
    
    
/*!
*  \fn batteryissue_t getbatteryIssue()
*  \brief get param batteryIssue
*  \return batteryIssue batteryissue_t
*/
batteryissue_t getbatteryIssue();

    
/*!
*  \fn void setbatteryIssue(batteryissue_t val)
*  \brief set param batteryIssue 
*  \param batteryIssue val : value to be setted
*/
void setbatteryIssue(batteryissue_t val);
    
    
/*!
*  \fn isAcquited_t getidleIsAcquited()
*  \brief get param idleIsAcquited
*  \return idleIsAcquited isAcquited_t
*/
isAcquited_t getidleIsAcquited();

    
/*!
*  \fn void setidleIsAcquited(isAcquited_t val)
*  \brief set param idleIsAcquited 
*  \param idleIsAcquited val : value to be setted
*/
void setidleIsAcquited(isAcquited_t val);
    
    
/*!
*  \fn isAcquited_t getlowBeamIsAcquited()
*  \brief get param lowBeamIsAcquited
*  \return lowBeamIsAcquited isAcquited_t
*/
isAcquited_t getlowBeamIsAcquited();

    
/*!
*  \fn void setlowBeamIsAcquited(isAcquited_t val)
*  \brief set param lowBeamIsAcquited 
*  \param lowBeamIsAcquited val : value to be setted
*/
void setlowBeamIsAcquited(isAcquited_t val);
    
    
/*!
*  \fn isAcquited_t gethighBeamIsAcquited()
*  \brief get param highBeamIsAcquited
*  \return highBeamIsAcquited isAcquited_t
*/
isAcquited_t gethighBeamIsAcquited();

    
/*!
*  \fn void sethighBeamIsAcquited(isAcquited_t val)
*  \brief set param highBeamIsAcquited 
*  \param highBeamIsAcquited val : value to be setted
*/
void sethighBeamIsAcquited(isAcquited_t val);
    
    
/*!
*  \fn isActivate_t getisActivateAndEnabledLeftBlinker()
*  \brief get param isActivateAndEnabledLeftBlinker
*  \return isActivateAndEnabledLeftBlinker isActivate_t
*/
isActivate_t getisActivateAndEnabledLeftBlinker();

    
/*!
*  \fn void setisActivateAndEnabledLeftBlinker(isActivate_t val)
*  \brief set param isActivateAndEnabledLeftBlinker 
*  \param isActivateAndEnabledLeftBlinker val : value to be setted
*/
void setisActivateAndEnabledLeftBlinker(isActivate_t val);
    
    
/*!
*  \fn isActivate_t getisActivateAndEnabledRightBlinker()
*  \brief get param isActivateAndEnabledRightBlinker
*  \return isActivateAndEnabledRightBlinker isActivate_t
*/
isActivate_t getisActivateAndEnabledRightBlinker();

    
/*!
*  \fn void setisActivateAndEnabledRightBlinker(isActivate_t val)
*  \brief set param isActivateAndEnabledRightBlinker 
*  \param isActivateAndEnabledRightBlinker val : value to be setted
*/
void setisActivateAndEnabledRightBlinker(isActivate_t val);
    
    
/*!
*  \fn isAcquited_t getisActivateAndEnabledAndAcquittedLeftBlinker()
*  \brief get param isActivateAndEnabledAndAcquittedLeftBlinker
*  \return isActivateAndEnabledAndAcquittedLeftBlinker isAcquited_t
*/
isAcquited_t getisActivateAndEnabledAndAcquittedLeftBlinker();

    
/*!
*  \fn void setisActivateAndEnabledAndAcquittedLeftBlinker(isAcquited_t val)
*  \brief set param isActivateAndEnabledAndAcquittedLeftBlinker 
*  \param isActivateAndEnabledAndAcquittedLeftBlinker val : value to be setted
*/
void setisActivateAndEnabledAndAcquittedLeftBlinker(isAcquited_t val);
    
    
/*!
*  \fn isAcquited_t getisActivateAndEnabledAndAcquittedRightBlinker()
*  \brief get param isActivateAndEnabledAndAcquittedRightBlinker
*  \return isActivateAndEnabledAndAcquittedRightBlinker isAcquited_t
*/
isAcquited_t getisActivateAndEnabledAndAcquittedRightBlinker();

    
/*!
*  \fn void setisActivateAndEnabledAndAcquittedRightBlinker(isAcquited_t val)
*  \brief set param isActivateAndEnabledAndAcquittedRightBlinker 
*  \param isActivateAndEnabledAndAcquittedRightBlinker val : value to be setted
*/
void setisActivateAndEnabledAndAcquittedRightBlinker(isAcquited_t val);
    
    /*!
 *  \struct data
 *  \brief Struct to hold entire data of the BCGV
 */
typedef struct data {
     isActivate_t isActivateWarning;
    isActivate_t isActivateIdleLight;
    isActivate_t isActivateLowBeam;
    isActivate_t isActivateHighBeam;
    isActivate_t isActivateRightBlinker;
    isActivate_t isActivateLeftBlinker;
    isActivate_t isActivateWindshieldWiper;
    isActivate_t isActivateIceWasher;
    km_t km;
    speed_t speed;
    frameissue_t frameIssue;
    engineissue_t engineIssue;
    fuellvl_t fuelLevel;
    rpm_t rpm;
    batteryissue_t batteryIssue;
    isAcquited_t idleIsAcquited;
    isAcquited_t lowBeamIsAcquited;
    isAcquited_t highBeamIsAcquited;
    isActivate_t isActivateAndEnabledLeftBlinker;
    isActivate_t isActivateAndEnabledRightBlinker;
    isAcquited_t isActivateAndEnabledAndAcquittedLeftBlinker;
    isAcquited_t isActivateAndEnabledAndAcquittedRightBlinker;
    
}data_t;

#endif
    