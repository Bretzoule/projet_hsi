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
    printf("engineIssue : %x\n", getengineIssue());
    printf("rpm : %d\n", getrpm());
    printf("fuelLevel : %d\n", getfuelLevel());
    printf("batteryIssue : %x\n", getbatteryIssue());
    printf("-----------------------------------------------------------------------------------\n");
}

void debugFrameLNS(lns_frame_t lnsFrame)
{
    printf("------------------------------------ LNS Frame ------------------------------------\n");
    printf("frame[0] : %x\n", lnsFrame.frame[0]);
    printf("frame[1] : %x\n", lnsFrame.frame[1]);
    printf("-----------------------------------------------------------------------------------\n");
}

void debugFrameUDP(uint8_t *udpFrame, uint8_t frameSize)
{
    printf("------------------------------------ UDP Frame ------------------------------------\n");
    for (int i = 0; i < frameSize; i++)
    {
        printf("frame[%d] : %x\n", i, udpFrame[i]);
    }
    printf("-----------------------------------------------------------------------------------\n");
}

int decodeUDP(uint8_t *udpFrame)
{
    km_t kilometers = ((uint32_t)udpFrame[1]) << 24 | ((uint32_t)udpFrame[2] << 16) | ((uint32_t)udpFrame[3] << 8) | ((uint32_t)udpFrame[4]);
    rpm_t rpm = ((uint32_t)udpFrame[9] << 24) | ((uint32_t)udpFrame[10] << 16) | ((uint32_t)udpFrame[11] << 8) | ((uint32_t)udpFrame[12]);
    setkm(kilometers);
    setspeed(udpFrame[5]);
    setframeIssue(udpFrame[6]);
    setengineIssue(udpFrame[7]);
    setfuelLevel(udpFrame[8]);
    setrpm(rpm);
    setbatteryIssue(udpFrame[13]);
    return (DECODE_SUCCESS);
}

int buildAndSendUDPFrame(int32_t drvFd, uint8_t (*udpFrameToSend)[DRV_UDP_20MS_FRAME_SIZE])
{
    int32_t status;
    /* First byte */
    bool fuelLevelCritical = (getfuelLevel() <= 2);
    bool myEngineIssue = (getengineIssue() != noEngineIssue);
    bool myTirePressureStatus = (getframeIssue() == tirePressure);
    bool myBrakesStatus = (getframeIssue() == usedBrakes);
    bool myBatteryEmpty = (getbatteryIssue() == empty);
    /* Second byte */
    bool warningIndicator = (getisActivateAndEnabledAndAcquittedRightBlinker() && getisActivateAndEnabledAndAcquittedLeftBlinker());
    bool myBatteryDead = (getbatteryIssue() == failure);
    bool myCoolingLiquidIssue = (getengineIssue() == ldrTemperature);
    bool myEnginePressureIssue = (getengineIssue() == pressureError);
    bool myEngineOilOverheatIssue = (getengineIssue() == oilOverheat);
    /* Frame building */
    (*udpFrameToSend)[0] = getidleIsAcquited() << 7 | getlowBeamIsAcquited() << 6 | gethighBeamIsAcquited() << 5 | fuelLevelCritical << 4 | myEngineIssue << 3 | myTirePressureStatus << 2 | myBrakesStatus << 1 | myBatteryEmpty;
    (*udpFrameToSend)[1] = warningIndicator << 7 | myBatteryDead << 6 | myCoolingLiquidIssue << 5 | myEnginePressureIssue << 4 | myEngineOilOverheatIssue << 3 | getisActivateWindshieldWiper() << 2 | getisActivateIceWasher() << 1 | myBrakesStatus;
    // FIXME: Change getIsActivateWindshieldWipers() by the acq boolean (need to add the acq part in the struct)
    (*udpFrameToSend)[2] = getkm() >> 24;
    (*udpFrameToSend)[3] = getkm() >> 16;
    (*udpFrameToSend)[4] = getkm() >> 8;
    (*udpFrameToSend)[5] = getkm();
    (*udpFrameToSend)[6] = getspeed();
    (*udpFrameToSend)[7] = getfuelLevel();
    (*udpFrameToSend)[8] = getrpm() / (uint8_t)100;
    /* Frame sending */
    // debugFrameUDP(*udpFrameToSend, DRV_UDP_20MS_FRAME_SIZE);
    status = drv_write_udp_20ms(drvFd, *udpFrameToSend);

    return status;
}

int buildAndSendLNSFrame(int32_t drvFd, lns_frame_t (*frameToSend)[BCGV_BGF_MESSAGEQUEUE_SIZE])
{
    int32_t status;
    uint8_t bgf_bcgv_idleLights[LNS_MAX_FRAME_SIZE] = {
        0x01,
        getisActivateIdleLight()};
    uint8_t bgf_bcgv_lowBeam[LNS_MAX_FRAME_SIZE] = {
        0x02,
        getisActivateLowBeam()};
    uint8_t bgf_bcgv_highBeam[LNS_MAX_FRAME_SIZE] = {
        0x03,
        getisActivateHighBeam()};
    uint8_t bgf_bcgv_rightBlinker[LNS_MAX_FRAME_SIZE] = {
        0x04,
        getisActivateAndEnabledRightBlinker()};
    uint8_t bgf_bcgv_leftBlinker[LNS_MAX_FRAME_SIZE] = {
        0x05,
        getisActivateAndEnabledLeftBlinker()};

    memcpy((*frameToSend)[0].frame, bgf_bcgv_idleLights, LNS_MAX_FRAME_SIZE);
    memcpy((*frameToSend)[1].frame, bgf_bcgv_lowBeam, LNS_MAX_FRAME_SIZE);
    memcpy((*frameToSend)[2].frame, bgf_bcgv_highBeam, LNS_MAX_FRAME_SIZE);
    memcpy((*frameToSend)[3].frame, bgf_bcgv_rightBlinker, LNS_MAX_FRAME_SIZE);
    memcpy((*frameToSend)[4].frame, bgf_bcgv_leftBlinker, LNS_MAX_FRAME_SIZE);

    status = drv_write_lns(drvFd, *frameToSend, BCGV_BGF_MESSAGEQUEUE_SIZE);
    return status;
}

void lnsContentChecker(lns_frame_t *lnsFrame, uint32_t frameLength)
{
    char frameAsString[1];
    uint8_t crc8Check;

    for (int i = 0; i < frameLength; i++)
    {
        crc8Check = crc_8(&(lnsFrame[i]).frame[1], sizeof(frameAsString));
        // debugFrameLNS(lnsFrame[i]);
        if (crc8Check == (lnsFrame[i]).frame[0])
        {
            decodeLNS(lnsFrame[i]);
        }
        else
        {
            printf("Exception : CRC8 invalid. \r\n Received %d, expected %d for frame %d", (lnsFrame[i]).frame[i], crc8Check, i);
        }
    }
}

int lnsACQChecker(lns_frame_t *sentlnsFrame, lns_frame_t *lnsFrame, uint32_t frameLength)
{
    uint8_t acq = true;
    int i = 0;
    while (i < frameLength && acq)
    {
        acq = ((lnsFrame[i].frame[0] == sentlnsFrame[i].frame[0]) && (lnsFrame[i].frame[1] == sentlnsFrame[i].frame[1]));
        debugFrameLNS(lnsFrame[i]);
        printf("^ RECEIVED[%d] // v SENT[%d] \n ", i, i);
        debugFrameLNS(sentlnsFrame[i]);
        i++;
    }
    return acq;
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
