/*
 *  \file highBeamLightsFSM.c
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Sam 15 Octobre 2022 - 10:59:03
 *
 *  \brief Car highBeam lights fsm
 *
 *
 */

#include "fsm.h"

/*!
 *  \def NULL ((void *)0)
 *  \brief Creates a null function that returns nothing
 */
#define NULL ((void *)0)

/*!
 *  \def ST_BLINK_LIGHTS_OFF
 *  \brief Manage blink lights state when it's off
 */
#define ST_BLINK_LIGHTS_OFF 0

/*!
 *  \def ST_BLINK_LIGHTS_ENABLED_OFF
 *  \brief Manage blink lights state when it's enable and off
 */
#define ST_BLINK_LIGHTS_ENABLED_OFF 1

/*!
 *  \def ST_BLINK_LIGHTS_ENABLED_ON
 *  \brief Manage blink lights state when it's on and enabled
 */
#define ST_BLINK_LIGHTS_ENABLED_ON 2

/*!
 *  \def ST_BLINK_LIGHTS_ON_ACQ
 *  \brief Manages state of the acq for blinking lights when they're on
 */
#define ST_BLINK_LIGHTS_ON_ACQ 3

/*!
 *  \def ST_BLINK_LIGHTS_OFF_ACQ
 *  \brief Manages state of the acq for blinking lights when they're off
 */
#define ST_BLINK_LIGHTS_OFF_ACQ 4

/*!
 *  \def ST_ERROR
 *  \brief Manages error state
 */
#define ST_ERROR -1

/*!
 *  \def EV_TURN_BLINK_LIGHTS_OFF
 *  \brief Handles event of turning the lights off
 */
#define EV_TURN_BLINK_LIGHTS_OFF 0

/*!
 *  \def EV_TURN_BLINK_LIGHTS_ENABLED_ON
 *  \brief Handles event of turning the lights on when they are enabled
 */
#define EV_TURN_BLINK_LIGHTS_ENABLED_ON 1

/*!
 *  \def EV_TURN_BLINK_LIGHTS_ENABLED_OFF
 *  \brief Handles event of turning the lights off when they are enabled
 */
#define EV_TURN_BLINK_LIGHTS_ENABLED_OFF 2

/*!
 *  \def EV_ACQ_BLINK_LIGHTS_RECEIVED
 *  \brief Event status when the ACQ return has been received
 */
#define EV_ACQ_BLINK_LIGHTS_RECEIVED 3

/*!
 *  \def EV_ACQ_BLINK_LIGHTS_ENABLED_ON
 *  \brief Handles event of turning lights on when they are acquitted
 */
#define EV_ACQ_BLINK_LIGHTS_ENABLED_ON 4

/*!
 *  \def EV_ACQ_BLINK_LIGHTS_ENABLED_OFF
 *  \brief Handles event of turning lights off when they are acquitted
 */
#define EV_ACQ_BLINK_LIGHTS_ENABLED_OFF 5

/*!
 *  \def BLINK_LIGHTS_MASK
 *  \brief mask to get the digit of blink lights indicator
 */
#define BLINK_LIGHTS_MASK 0b10000000

/*!
 *  \def LEFT
 *  \brief left side for lights
 */
#define LEFT 0

/*!
 *  \def RIGHT
 *  \brief right side for lights
 */
#define RIGHT 1

/* States */
#define ST_ANY -1
#define ST_TERM 255
#define EV_NONE 0
#define EV_ANY -1

typedef struct
{
    int state;
    int event;
    int (*callback)(void);
    int next_state;
} tTransition;

typedef struct currentHandledState
{
    int left;
    int right;
    int warnings;
} currentHandledState;

static currentHandledState savedState = {ST_BLINK_LIGHTS_OFF, ST_BLINK_LIGHTS_OFF, ST_BLINK_LIGHTS_OFF};

/*!
 *  \fn static int turnLightOff(int side)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 25 Octobre 2022 - 22:00:40
 *  \brief Handles lights off state
 *  \param int side: the side of the light to turn on
 *  \return 0
 */
static int turnLightOff(int side)
{
    switch (side)
    {
    case LEFT:
        setIsActivateLeftBlinker(0);
        break;
    case RIGHT:
        setIsActivateRightBlinker(0);
        break;
    default:
        setIsActivateRightBlinker(0);
        setIsActivateLeftBlinker(0);
    }
    return 0;
}
/*!
 *  \fn static int turnLightEnabledOn(int side)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 25 Octobre 2022 - 22:00:40
 *  \brief Handles lights on and enabled state
 *  \param int side: the side of the light to turn on
 *  \return 0
 */
static int turnLightEnabledOn(int side)
{
    switch (side)
    {
    case LEFT:
        setisActivateAndEnabledLeftBlinker(1);
        break;
    case RIGHT:
        setisActivateAndEnabledRightBlinker(1);
        break;
    default:
        setisActivateAndEnabledLeftBlinker(1);
        setisActivateAndEnabledRightBlinker(1);
    }
    return 0;
}
/*!
 *  \fn static int turnLightEnabledOff(int side)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 25 Octobre 2022 - 22:00:40
 *  \brief Handles lights off and enabled state
 *  \param int side: the side of the light to turn on
 *  \return 0
 */
static int turnLightEnabledOff(int side)
{
    switch (side)
    {
    case LEFT:
        setisActivateAndEnabledLeftBlinker(0);
        break;
    case RIGHT:
        setisActivateAndEnabledRightBlinker(0);
        break;
    default:
        setisActivateAndEnabledLeftBlinker(0);
        setisActivateAndEnabledRightBlinker(0);
    }
    return 0;
}

static int turnLightEnabledAndACQOn(int side);
// TODO: Implement the "lights enabled, on and aquited" function
static int turnLightEnabledAndACQOff(int side);
// TODO: Implement the "lights enabled, off and aquited" function

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
}

static int notifyListeners(void);
// TODO: Implement the notifyListeners function

/* Transitions */
tTransition trans[] = {
    {ST_BLINK_LIGHTS_OFF, EV_TURN_BLINK_LIGHTS_OFF, NULL, ST_BLINK_LIGHTS_OFF},
    {ST_BLINK_LIGHTS_OFF, EV_TURN_BLINK_LIGHTS_ENABLED_ON, &turnLightEnabledOn, ST_BLINK_LIGHTS_ENABLED_ON},
    {ST_BLINK_LIGHTS_ENABLED_ON, EV_TURN_BLINK_LIGHTS_ENABLED_ON, NULL, ST_BLINK_LIGHTS_ENABLED_ON},
    {ST_BLINK_LIGHTS_ENABLED_ON, EV_TURN_BLINK_LIGHTS_OFF, &turnLightOff, ST_BLINK_LIGHTS_OFF},
    {ST_BLINK_LIGHTS_ENABLED_OFF, EV_TURN_BLINK_LIGHTS_OFF, &turnLightOff, ST_BLINK_LIGHTS_OFF},
    {ST_BLINK_LIGHTS_ENABLED_OFF, EV_TURN_BLINK_LIGHTS_ENABLED_OFF, NULL, ST_BLINK_LIGHTS_ENABLED_OFF},
    {ST_BLINK_LIGHTS_ENABLED_ON, EV_NONE, &fsmError, ST_ERROR},
    {ST_BLINK_LIGHTS_ENABLED_OFF, EV_NONE, &fsmError, ST_ERROR},
    {ST_BLINK_LIGHTS_ENABLED_ON, EV_ACQ_BLINK_LIGHTS_RECEIVED, &notifyListeners, ST_BLINK_LIGHTS_ON_ACQ},
    {ST_BLINK_LIGHTS_ENABLED_OFF, EV_ACQ_BLINK_LIGHTS_RECEIVED, &notifyListeners, ST_BLINK_LIGHTS_OFF_ACQ},
    {ST_BLINK_LIGHTS_ON_ACQ, EV_ACQ_BLINK_LIGHTS_ENABLED_ON, NULL, ST_BLINK_LIGHTS_ON_ACQ},
    {ST_BLINK_LIGHTS_ON_ACQ, EV_TURN_BLINK_LIGHTS_OFF, &turnLightOff, ST_BLINK_LIGHTS_OFF},
    {ST_BLINK_LIGHTS_ENABLED_OFF, EV_TURN_BLINK_LIGHTS_OFF, &turnLightOff, ST_BLINK_LIGHTS_OFF},
    {ST_BLINK_LIGHTS_OFF_ACQ, EV_ACQ_BLINK_LIGHTS_ENABLED_OFF, &turnLightEnabledAndACQOff, ST_BLINK_LIGHTS_ON_ACQ},
    {ST_BLINK_LIGHTS_OFF_ACQ, EV_ACQ_BLINK_LIGHTS_ENABLED_OFF, NULL, ST_BLINK_LIGHTS_OFF_ACQ},
    {ST_BLINK_LIGHTS_ON_ACQ, EV_TURN_BLINK_LIGHTS_ENABLED_OFF, &turnLightEnabledOff, ST_BLINK_LIGHTS_ENABLED_OFF},
    {ST_BLINK_LIGHTS_OFF_ACQ, EV_TURN_BLINK_LIGHTS_ENABLED_ON, &turnLightEnabledOn, ST_BLINK_LIGHTS_ENABLED_ON}};

#define TRANS_COUNT (sizeof(trans) / sizeof(*trans))

// case ST_BLINK_LIGHTS_OFF:
//     if ((decodedLNS & BLINK_LIGHTS_MASK) == 0b10000000)
//         event = EV_TURN_BLINK_LIGHTS_ENABLED_ON;
//     if ((decodedLNS & BLINK_LIGHTS_MASK) == 0b00000000)
//         event = EV_TURN_BLINK_LIGHTS_OFF;
//     break;
// case ST_BLINK_LIGHTS_ENABLED_ON:
//     if ((decodedLNS & BLINK_LIGHTS_MASK) == 0b10000000)
//         event = EV_TURN_BLINK_LIGHTS_ENABLED_ON;
//     // TODO: À vérifier si on doit utiliser un event pour faire le passage entre enabled_on et enabled_off après 1scd
//     if ((decodedLNS & BLINK_LIGHTS_MASK) == 0b00000000)
//         event = EV_TURN_BLINK_LIGHTS_OFF;
//     if ((decodedACQLNS & BLINK_LIGHTS_MASK) == 0b10000000)
//         event = EV_ACQ_BLINK_LIGHTS_RECEIVED;
//     if (((decodedACQLNS & BLINK_LIGHTS_MASK) != 0b10000000) && time >= 1000)
//         event = EV_NONE;
//     break;
// case ST_BLINK_LIGHTS_ENABLED_OFF:
//     if ((decodedLNS & BLINK_LIGHTS_MASK) == 0b10000000)
//         event = ST_BLINK_LIGHTS_ENABLED_OFF;
//     // TODO: À vérifier si on doit utiliser un event pour faire le passage entre enabled_on et enabled_off après 1scd
//     if ((decodedLNS & BLINK_LIGHTS_MASK) == 0b00000000)
//         event = EV_TURN_BLINK_LIGHTS_OFF;
//     if ((decodedACQLNS & BLINK_LIGHTS_MASK) == 0b10000000)
//         event = EV_ACQ_BLINK_LIGHTS_RECEIVED;
//     if (((decodedACQLNS & BLINK_LIGHTS_MASK) != 0b10000000) && time >= 1000)
//         event = EV_NONE;
//     break;
// case ST_BLINK_LIGHTS_OFF_ACQ:
//     if ((decodedLNS & BLINK_LIGHTS_MASK) == 0b10000000)
//         event = EV_ACQ_BLINK_LIGHTS_ENABLED_OFF;
//     // TODO: À vérifier si on doit utiliser un event pour faire le passage entre acq_enabled_on et acq_enabled_on après 1scd
//     if ((decodedLNS & BLINK_LIGHTS_MASK) == 0b00000000)
//         event = EV_TURN_BLINK_LIGHTS_OFF;
//     break;

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

    uint8_t decodedLNS = getLNS();
    uint8_t time = getTime();
    uint8_t decodedACQLNS = getACQLNS();

    /* Build all the events */
    switch (current_state)
    {
    case ST_BLINK_LIGHTS_OFF:
        // TODO: Implement different blinkers "STATES" and "SIDES" !
        break;
    case ST_ERROR:
        break;
    }
    return event;
}

/*!
 *  \fn getCurrentState(int side)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Ven 28 Octobre 2022 - 18:05:09
 *  \brief getter for each light state
 *  \param int side : side of the light to get
 *  \return current light state for the side
 */
getCurrentState(int side)
{
    int state;
    switch (side)
    {
    case LEFT:
        state = savedState.left;
        break;
    case RIGHT:
        state = savedState.right;
        break;
    default:
        state = savedState.warnings;
        break;
    }
    return (state);
}

/*!
 *  \fn void setCurrentState(int side, int state)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Ven 28 Octobre 2022 - 18:25:56
 *  \brief saves state to a global var
 *  \param int side: side of the light
 *  \param int state: state of the light
 */
void setCurrentState(int side, int state)
{
    switch (side)
    {
    case LEFT:
        savedState.left = state;
        break;
    case RIGHT:
        savedState.right = state;
        break;
    default:
        savedState.warnings = state;
        break;
    }
}

int blinkLightsFSM(int side)
{
    int i = 0;
    int ret = 0;
    int event = EV_NONE;
    int state = getCurrentState(side);

    /* While FSM hasn't reach end state */
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
                setCurrentState(side, state);
                /* Call the state function */
                ret = (trans[i].callback)();
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}
