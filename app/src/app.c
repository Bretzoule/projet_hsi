/**
 * \file main.c
 * \brief Description breve
 * \details Details ou notes d’implementation (peut rester vide)
 * \author Mathilde HAMON <hamonmathi@cy-tech.fr>
 */

#include <unistd.h>
#include "checksum.h"
#include "frameUtils.h"

/*!
 *  \fn void debugLNS(lns_frame_t lnsFrame, uint8_t crc8Check, uint32_t frameLength)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 01 Novembre 2022 - 18:11:47
 */
void debugLNS(lns_frame_t *lnsFrame, uint8_t crc8Check, uint32_t frameLength)
{
    printf("Print HEX : %x -- CRC8 : %x == %x || Frame Length : %d\r\n", (lnsFrame[0]).frame[1], (lnsFrame[0]).frame[0], crc8Check, frameLength);
}

/**
 * \brief Description breve de la fonction.
 * \details Details ou notes d’implementation (peut rester vide)
 * \param param1 : Description
 * \param param2 : Description
 * \return int32_t : main
 */
int32_t main(int argc, char const *argv[])
{
    uint8_t lnsTimer = 0;
    uint8_t udpFrame[DRV_UDP_10MS_FRAME_SIZE];
    lns_frame_t lnsFrame[DRV_MAX_FRAMES];
    uint32_t frameLength;
    uint8_t crc8Check;
    int32_t drvStatus;
    int32_t drvFd;
    int frameExpected = 1;
    char frameAsString[1];
    // Open connection with driver
    drvFd = drv_open();
    while (1)
    {
        drvStatus = drv_read_udp_10ms(drvFd, udpFrame);
        if (drvStatus != DRV_ERROR)
        {
            debugFrameUDP(udpFrame);
            if (udpFrame[0] != frameExpected)
            {
                printf("Exception : Frame number invalid. \r\n Received %d, expected %d", udpFrame[0], frameExpected);
            }
            else
            {
                frameExpected = (frameExpected % 100) + 1;
                decodeUDP(udpFrame);
            }
        }
        if (lnsTimer < 10)
        {
            lnsTimer++;
        }
        else
        {
            drvStatus = drv_read_lns(drvFd, lnsFrame, &frameLength);
            if (drvStatus != DRV_ERROR)
            {
                crc8Check = crc_8(&(lnsFrame[0]).frame[1], sizeof(frameAsString));
                debugFrameLNS(lnsFrame[0]);
                if (crc8Check == (lnsFrame[0]).frame[0])
                {
                    decodeLNS(lnsFrame[0]);
                }
                else
                {
                    printf("Exception : CRC8 invalid. \r\n Received %d, expected %d", (lnsFrame[0]).frame[0], crc8Check);
                }
            }
        }
        debugBCGV();
        // TODO: Call different state machines
        // TODO: Send UDP
        // TODO: Send LNS
        sleep(0.1);
    }
    return (EXIT_SUCCESS);
}
