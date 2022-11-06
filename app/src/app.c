/**
 * \file app.c
 * \brief Entry point for the app
 * \details Main entry point
 * \author Mathilde HAMON <hamonmathi@cy-tech.fr>
 */

#include <unistd.h>
#include "frameUtils.h"
// #include "fsm.h"

/*!
 *  \fn int main (int argc, char** argv)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Dim 06 Novembre 2022 - 19:07:35
 *  \brief Main program
 *  \param argc : Number of params at runtime
 *  \param argv : Parameters
 *  \return int32_t : main
 */
int main(int argc, char const *argv[])
{
    uint8_t lnsTimer = 0;
    uint8_t udpFrame[DRV_UDP_10MS_FRAME_SIZE];
    uint8_t udpFrameToSend[DRV_UDP_20MS_FRAME_SIZE];
    lns_frame_t lnsFrame[DRV_MAX_FRAMES];
    lns_frame_t lnsFrameToSend[BCGV_BGF_MESSAGEQUEUE_SIZE];
    uint32_t frameLength;
    int32_t drvStatus;
    int32_t drvFd;
    bool udpTimer = false;
    int8_t acq = 0;
    int frameExpected = 1;

    // Open connection with driver
    drvFd = drv_open();
    while (drvFd != DRV_ERROR)
    {
        /* UDP FRAME READING */
        drvStatus = drv_read_udp_10ms(drvFd, udpFrame);
        if (drvStatus != DRV_ERROR)
        {
            if (udpFrame[0] != frameExpected)
            {
                printf("Exception : Frame number invalid - received %d, expected %d\n", udpFrame[0], frameExpected);
            }
            else
            {
                frameExpected = (frameExpected % 100) + 1;
                decodeUDP(udpFrame);
            }
        }

        /* UDP FRAME READING */
        if (drv_read_lns(drvFd, lnsFrame, &frameLength) != DRV_ERROR)
        {
            lnsContentChecker(lnsFrame, frameLength);
        }
        else
        {
            printf("En error happened during LNS frame reading...\n");
        }

        /* LNS FRAME SENDING */
        if (buildAndSendLNSFrame(drvFd, &lnsFrameToSend) != DRV_ERROR)
        {
            if (drv_read_lns(drvFd, lnsFrame, &frameLength) != DRV_ERROR)
            {
                printf("frameLenght = %d\n", frameLength);
                // FIXME:  Understand WHY the acq check doesnt work and why the lns doesnt answer properly
                acq = lnsACQChecker(lnsFrameToSend, lnsFrame, frameLength);
                printf("ACQ = %d\n", acq);
            }
        }
        else
        {
            printf("En error happened during LNS frame sending...\n");
        }
        /* UDP FRAME SENDING */
        if (buildAndSendUDPFrame(drvFd, &udpFrameToSend) == DRV_ERROR)
        {
            printf("En error happened during UDP frame sending...\n");
        }
    }
    return (drvFd);
}
