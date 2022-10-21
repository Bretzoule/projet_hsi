/**
 * \file main.c
 * \brief Description breve
 * \details Details ou notes d’implementation (peut rester vide)
 * \author Mathilde HAMON <<hamonmathi@cy-tech.fr>>
 */

#include "drv_api.h"

/**
 * \brief Description breve de la fonction.
 * \details Details ou notes d’implementation (peut rester vide)
 * \param param1 : Description
 * \param param2 : Description
 * \return int32_t : main
 */
int32_t main(int argc, char const *argv[])
{
    int32_t drvFd;
    uint8_t udpFrame[DRV_UDP_10MS_FRAME_SIZE];
    int32_t drvClose;
    // Open connection with driver
    drvFd = drv_open();
    printf("drvFd = %d\n", drvFd);
    drv_read_udp_10ms(drvFd, udpFrame);
    for (int i = 0; i < DRV_UDP_10MS_FRAME_SIZE; i++)
    {
        printf("udpFrame[%d] = %d\n", i, udpFrame[i]);
    }
    
    // Close connection with driver
    drvClose = drv_close(drvFd);

    return (drvClose);
}