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
 *  \fn int idleLightsFSM(void)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 18 Octobre 2022 - 20:27:14
 *  \brief manages fsm for the idle lights
 *  \return 0 if everything is fine
 */
int idleLightsFSM(void);
/*!
 *  \fn int highBeamLightsFSM(void)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 18 Octobre 2022 - 20:27:14
 *  \brief manages fsm for the high beam lights
 *  \return 0 if everything is fine
 */
int highBeamLightsFSM(void);
/*!
 *  \fn int lowBeamLightsFSM(void)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 18 Octobre 2022 - 20:27:14
 *  \brief manages fsm for the Low beam lights
 *  \return 0 if everything is fine
 */
int lowBeamLightsFSM(void);

#endif