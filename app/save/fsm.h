#ifndef FSM_H
#define FSM_H
/*!
 *  \file fsm.h
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 18 Octobre 2022 - 20:21:54
 *
 *  \brief Manages every FSM function
 *
 *
 */

// Including library headers
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
/*!
 \def EXIT_SUCCESS
 \brief Exit code confirming program proper execution
*/
#define EXIT_SUCCESS 0

/*!
 \def RW_ERROR
 \brief Exit code stating that an error occured in a read/write process (stdin/out)
*/
#define RW_ERROR -1

/*!
 *  \fn int lightsFSM(int lightType, int acqTimer)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 18 Octobre 2022 - 20:27:14
 *  \param int lightType : manage selected Light type
 *  \param int acqTimer : timer that handle current deadline for acq status
 *  \brief manages fsm for the lights
 *  \return 0 if everything is fine
 */
int lightsFSM(int lightType, int acqTimer);

/*!
 *  \fn int warningLightsFSM(int side, int acqTimer)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 18 Octobre 2022 - 20:27:14
 *  \param int side : manage side of the selected light type
 *  \param int acqTimer : timer that handle current deadline for acq status
 *  \brief manages fsm for the blinking lights
 *  \return 0 if everything is fine
 */
int blinkLightsFSM(int side, int acqTimer);

#endif