#ifndef FRAMEUTILS_H
#define FRAMEUTILS_H
/*!
 *  \file frameUtils.h
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 01 Novembre 2022 - 19:08:25
 *
 *  \brief Manages functions for frameUtils.c file.
 *
 *
 */

// Including library headers
#include <stdlib.h>
#include <stdio.h>
#include "drv_api.h"
#include "types.h"

/*!
 \def EXIT_SUCCESS
 \brief Exit code confirming program proper execution
*/
#define EXIT_SUCCESS 0
/*!
 \def ERREUR_SAISIE
 \brief Exit code stating that an error occured
*/
#define ERREUR_SAISIE -1

/*!
 *  \def DECODE_SUCCESS
 *  \brief Exit code when decoding was a success
 */
#define DECODE_SUCCESS 0

/*!
 *  \def DECODE_ERR
 *  \brief Exit code when an error happened during decoding
 */
#define DECODE_ERR -1

/*!
 *  \def WARNING_LIGHTS_MASK
 *  \brief Mask the value in the frame for WARNING LIGHTS
 */
#define WARNING_LIGHTS_MASK 0x80

/*!
 *  \def IDLE_LIGHTS_MASK
 *  \brief Mask the value in the frame for IDLE LIGHTS
 */
#define IDLE_LIGHTS_MASK 0x40

/*!
 *  \def LOWBEAM_LIGHTS_MASK
 *  \brief Mask the value in the frame for LOWBEAM LIGHTS
 */
#define LOWBEAM_LIGHTS_MASK 0x20

/*!
 *  \def HIGHBEAM_LIGHTS_MASK
 *  \brief Mask the value in the frame for HIGHBEAM LIGHTS
 */
#define HIGHBEAM_LIGHTS_MASK 0x10

/*!
 *  \def RIGHT_BLINKER_MASK
 *  \brief Mask the value in the frame for RIGHT BLINKER
 */
#define RIGHT_BLINKER_MASK 0x08

/*!
 *  \def LEFT_BLINKER_MASK
 *  \brief Mask the value in the frame for LEFT BLINKER
 */
#define LEFT_BLINKER_MASK 0x04

/*!
 *  \def WIPERS_MASK
 *  \brief Mask the value in the frame for WIPERS
 */
#define WIPERS_MASK 0x02

/*!
 *  \def ICE_WASHER_MASK
 *  \brief Mask the value in the frame for ICE WASHER
 */
#define ICE_WASHER_MASK 0x01

/*!
 *  \fn int decodeLNS(lns_frame_t lnsFrame)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 01 Novembre 2022 - 19:04:48
 *  \brief decodes LNS frame
 *  \param lns_frame_t lnsFrame: lnsFrame to decode
 *  \return DECODE_SUCCESS if everything was fine, DECODE_ERR otherwise
 */
int decodeLNS(lns_frame_t lnsFrame);

/*!
 *  \fn int decodeUDP(uint8_t *udpFrame)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 01 Novembre 2022 - 19:04:48
 *  \brief decodes UDP frame
 *  \param lns_frame_t udpFrame: udpFrame to decode
 *  \return DECODE_SUCCESS if everything was fine, DECODE_ERR otherwise
 */
int decodeUDP(uint8_t *udpFrame);

/*!
 *  \fn void debugBCGV()
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mer 02 Novembre 2022 - 23:08:54
 *  \brief Debugs data from BCGV
 */
void debugBCGV();

/*!
 *  \fn void debugFrameLNS(lns_frame_t lnsFrame)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mer 02 Novembre 2022 - 23:08:54
 *  \param lns_frame_t lnsFrame : LNS Frame to debug
 *  \brief Debugs data from LNS frame
 */
void debugFrameLNS(lns_frame_t lnsFrame);

/*!
 *  \fn void debugFrameLNS(uint8_t* udpFrame)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mer 02 Novembre 2022 - 23:08:54
 *  \param uint8_t* udpFrame : UDP Frame to debug
 *  \brief Debugs data from UDP frame
 */
void debugFrameUDP(uint8_t *udpFrame);

#endif