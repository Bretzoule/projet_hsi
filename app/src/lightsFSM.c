/*
 *  \file lightsFSM.c
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Sam 15 Octobre 2022 - 10:59:03
 *
 *  \brief Car idle lights fsm
 *
 *
 */

#include "fsm.h"

/*!
 *  \def NULL ((void *)0)
 *  \brief Creates a null function that returns nothing
 */
#define NULL ((void *)0)

/* States */
#define ST_ANY -1
#define ST_TERM 255
#define EV_NONE 0
#define EV_ANY -1
#define IDLE 1
#define LOWBEAM 2
#define HIGHBEAM 3

/*!
 *  \def ST_ERROR
 *  \brief Manages error state
 */
#define ST_ERROR -1

/*!
 *  \def ST_LIGHTS_OFF
 *  \brief Manages state of the lights when it's off
 */
#define ST_LIGHTS_OFF 0

/*!
 *  \def ST_LIGHTS_ON
 *  \brief Manages state of the low beam lights when it's on
 */
#define ST_LIGHTS_ON 1

/*!
 *  \def ST_ACQ
 *  \brief Manages state of the acq light
 */
#define ST_ACQ 2

/*!
 *  \def EV_TURN_LIGHTS_OFF
 *  \brief Event status when the lights turn off
 */
#define EV_TURN_LIGHTS_OFF 0

/*!
 *  \def EV_TURN_LIGHTS_ON
 *  \brief Event status when the lights turn on
 */
#define EV_TURN_LIGHTS_ON 1

/*!
 *  \def EV_ACQ_RECEIVED
 *  \brief Event status when the ACQ return has been received
 */
#define EV_ACQ_RECEIVED 2

/*!
 *  \def LIGHTS_MASK
 *  \brief mask to get the digit of idle lights indicator
 */
#define LIGHTS_MASK 0b01000000

typedef struct
{
    int state;
    int event;
    int (*callback)(void);
    int next_state;
} tTransition;

/* Transitions */
tTransition trans[] = {
    {ST_LIGHTS_OFF, EV_TURN_LIGHTS_ON, &lightsOff, ST_LIGHTS_ON},
    {ST_LIGHTS_OFF, EV_TURN_LIGHTS_OFF, NULL, ST_LIGHTS_OFF},
    {ST_LIGHTS_ON, EV_TURN_LIGHTS_ON, NULL, ST_LIGHTS_ON},
    {ST_LIGHTS_ON, EV_TURN_LIGHTS_OFF, &lightsOff, ST_LIGHTS_OFF},
    {ST_LIGHTS_ON, EV_NONE, &fsmError, ST_ERROR},
    {ST_LIGHTS_ON, EV_ACQ_RECEIVED, &notifyListeners, ST_ACQ},
    {ST_ACQ, EV_TURN_LIGHTS_OFF, &lightsOff, ST_LIGHTS_OFF},
    {ST_ACQ, EV_TURN_LIGHTS_ON, NULL, ST_ACQ}};

#define TRANS_COUNT (sizeof(trans) / sizeof(*trans))

/*!
 *  \fn static int lightsOff(int type)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Dim 23 Octobre 2022 - 17:41:18
 *  \brief handles lightOn states
 *  \return 0
 */
static int lightsOff(int type)
{
    switch (type)
    {
    case 1:
        setisActivateStateLight(0);
        break;
    case 2:
        setisActivateDippedBeam(0);
        break;
    case 3:
        setisActivateMainBeam(0);
        break;
    }
    return 0;
};

/*!
 *  \fn static int lightsOn(int type)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Dim 23 Octobre 2022 - 17:41:18
 *  \brief handles lightOn states
 *  \return 0
 */
static int LightsOn(int type)
{
    switch (type)
    {
    case 1:
        setisActivateStateLight(1);
        break;
    case 2:
        setisActivateDippedBeam(1);
        break;
    case 3:
        setisActivateMainBeam(1);
        break;
    }
    return 0;
};

/*!
 *  \fn static int error(void)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Dim 23 Octobre 2022 - 17:41:18
 *  \brief handles common error states
 *  \return 0
 */
static int error(void)
{
    printf("Error\n");
    return 0;
};

/*!
 *  \fn static int acquitted(int type)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Dim 23 Octobre 2022 - 17:41:18
 *  \brief handles acquitted states
 *  \return 0
 */
static int acquitted(int type)
{
    switch (type)
    {
    case 1:
        setidleIsAcquited(1);
        break;
    case 2:
        sethighBeamIsAcquited(1);
        break;
    case 3:
        setlowBeamIsAcquited(1);
        break;
    }
    return 0;
};

/*!
 *  \fn static int fsmError(void)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Dim 23 Octobre 2022 - 17:41:18
 *  \brief prints error on fsm error
 *  \return 0
 */
static int fsmError(void)
{
    printf("FsmError\n");
    return 0;
};
static int notifyListeners(void);

// /*!
//  *  \fn idleLightsEventHandler(int current_state, int decodedACQLNS, int decodedLNS)
//  *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
//  *  \version 0.1
//  *  \date Dim 23 Octobre 2022 - 17:21:36
//  *  \brief Computes event according to current lns values
//  *  \param current_state : current state
//  *  \param decodedACQLNS : decoded acq lns value
//  *  \param decodedLNS : decoded lns value
//  *  \return event value
//  */
// idleLightsEventHandler(int current_state, int decodedACQLNS, int decodedLNS)
// {
//     int event = EV_NONE;
//     switch (current_state)
//     {
//     case ST_LIGHTS_OFF:
//         if ((decodedLNS & LIGHTS_MASK) == 0b01000000)
//             event = EV_TURN_LIGHTS_ON;
//         if ((decodedLNS & LIGHTS_MASK) == 0b00000000)
//             event = EV_TURN_LIGHTS_OFF;
//         break;

//     case ST_LIGHTS_ON:
//         if ((decodedLNS & LIGHTS_MASK) == 0b01000000)
//             event = EV_TURN_LIGHTS_ON;
//         if ((decodedLNS & LIGHTS_MASK) == 0b00000000)
//             event = EV_TURN_LIGHTS_OFF;
//         if ((decodedACQLNS & LIGHTS_MASK) == 0b01000000)
//             event = EV_ACQ_RECEIVED;
//         // if(decodedACQLNS == 0) event = EV_NONE // ERROR
//         break;
//     case ST_ACQ:
//         if ((decodedLNS & LIGHTS_MASK) == 0b01000000)
//             event = EV_TURN_LIGHTS_ON;
//         if ((decodedLNS & LIGHTS_MASK) == 0b00000000)
//             event = EV_TURN_LIGHTS_OFF;
//         break;
//     }
//     return (event);
// }

/*!
 *  \fn static int GetNextEvent(int current_state)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 18 Octobre 2022 - 20:23:29
 *  \brief gets next event for the fms
 *  \param int current_state: current fsm state
 *  \return event : an event that will trigger a callback or not
 */
static int GetNextEvent(int current_state)
{
    int event = EV_NONE;

    u_int8_t decodedLNS = getLNS();
    u_int8_t decodedACQLNS = getACQLNS();

    switch (current_state)
    {

    /* switch case on states */
    case ST_LIGHTS_OFF:
        event = getisActivateStateLight();
        break;
    case ST_LIGHTS_ON:
        event = getidleIsAcquited();
        break;
    case ST_ACQ:
        event = getidleIsAcquited();
        break;
    case ST_ERROR:
        break;
    }
    // switch (selectedLight)
    // {
    // case IDLE:

    //     break;
    // case LOWBEAM:
    //     break;
    // case HIGHBEAM:
    //     break;
    // }

    return event;
}

int lightsFSM(int lightType)
{
    int i = 0;
    int ret = 0;
    int event = EV_NONE;
    int state = ST_LIGHTS_OFF;

    /* While FSM hasn't reach end state */
    while (state != ST_ERROR)
    {
        /* Get event */
        event = GetNextEvent(state);
        /* For each transitions */
        for (i = 0; i < TRANS_COUNT; i++)
        {
            /* If State is current state OR The transition applies to all states ...*/
            if ((state == trans[i].state) || (ST_ANY == trans[i].state))
            {
                /* If event is the transition event OR the event applies to all */
                if ((event == trans[i].event) || (EV_ANY == trans[i].event))
                {
                    /* Apply the new state */
                    state = trans[i].next_state;
                    /* Call the state function */
                    ret = (trans[i].callback)(lightType);
                    break;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}
