/*!
 *  \file frameUtils.c
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 01 Novembre 2022 - 18:57:54
 *
 *  \brief Manages utils for encoding/decoding frames
 *
 *
 */

#include "frameUtils.h"

void debugBCGV()
{
    printf("------------------------------------ BCGV DATA ------------------------------------\n");
    printf("isActivateWarning : %d\n", getisActivateWarning());
    printf("isActivateIdleLight : %d\n", getisActivateIdleLight());
    printf("isActivateLowBeam : %d\n", getisActivateLowBeam());
    printf("isActivateHighBeam : %d\n", getisActivateHighBeam());
    printf("isActivateRightTurnSignal : %d\n", getisActivateRightBlinker());
    printf("isActivateLeftTurnSignal : %d\n", getisActivateLeftBlinker());
    printf("isActivateWindshieldWiper : %d\n", getisActivateWindshieldWiper());
    printf("isActivateIceWasher : %d\n", getisActivateIceWasher());
    printf("km : %d\n", getkm());
    printf("speed : %d\n", getspeed());
    printf("frameIssue : %x\n", getframeIssue());
    printf("-----------------------------------------------------------------------------------\n");
}

void debugFrameLNS(lns_frame_t lnsFrame)
{
    printf("------------------------------------ LNS Frame ------------------------------------\n");
    printf("frame[0] : %x\n", lnsFrame.frame[0]);
    printf("frame[1] : %x\n", lnsFrame.frame[1]);
    printf("-----------------------------------------------------------------------------------\n");
}

void debugFrameUDP(uint8_t *udpFrame)
{
    printf("------------------------------------ UDP Frame ------------------------------------\n");
    for (int i = 0; i < DRV_UDP_10MS_FRAME_SIZE; i++)
    {
        printf("frame[%d] : %x\n", i, udpFrame[i]);
    }
    printf("-----------------------------------------------------------------------------------\n");
}

int decodeUDP(uint8_t *udpFrame)
{
    km_t kilometers = ((uint32_t)udpFrame[1]) | ((uint32_t)udpFrame[2] << 8) | ((uint32_t)udpFrame[3] << 16) | ((uint32_t)udpFrame[4] << 24);
    rpm_t rpm = ((uint32_t)udpFrame[9]) | ((uint32_t)udpFrame[10] << 8) | ((uint32_t)udpFrame[11] << 16) | ((uint32_t)udpFrame[12] << 24);
    setkm(kilometers);
    setspeed(udpFrame[5]);
    setframeIssue(udpFrame[6]);
    setengineIssue(udpFrame[7]);
    setfuelLevel(udpFrame[8]);
    setrpm(rpm);
    setbatteryIssue(udpFrame[13]);
    return (DECODE_SUCCESS);
}

int decodeLNS(lns_frame_t lnsFrame)
{
    setisActivateWarning((lnsFrame.frame[1] & WARNING_LIGHTS_MASK) == WARNING_LIGHTS_MASK);
    setisActivateIdleLight((lnsFrame.frame[1] & IDLE_LIGHTS_MASK) == IDLE_LIGHTS_MASK);
    setisActivateLowBeam((lnsFrame.frame[1] & LOWBEAM_LIGHTS_MASK) == LOWBEAM_LIGHTS_MASK);
    setisActivateHighBeam((lnsFrame.frame[1] & HIGHBEAM_LIGHTS_MASK) == HIGHBEAM_LIGHTS_MASK);
    setisActivateAndEnabledRightBlinker((lnsFrame.frame[1] & RIGHT_BLINKER_MASK) == RIGHT_BLINKER_MASK);
    setisActivateAndEnabledLeftBlinker((lnsFrame.frame[1] & LEFT_BLINKER_MASK) == LEFT_BLINKER_MASK);
    setisActivateWindshieldWiper((lnsFrame.frame[1] & WIPERS_MASK) == WIPERS_MASK);
    setisActivateIceWasher((lnsFrame.frame[1] & ICE_WASHER_MASK) == ICE_WASHER_MASK);
    return (DECODE_SUCCESS);
}
