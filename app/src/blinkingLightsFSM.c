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
 *  \def EV_ACQ_BLINK_LIGHTS_NOT_RECEIVED
 *  \brief Event status when the ACQ return has not been received
 */
#define EV_ACQ_BLINK_LIGHTS_NOT_RECEIVED 4

/*!
 *  \def EV_ACQ_BLINK_LIGHTS_ENABLED_ON
 *  \brief Handles event of turning lights on when they are acquitted
 */
#define EV_ACQ_BLINK_LIGHTS_ENABLED_ON 5

/*!
 *  \def EV_ACQ_BLINK_LIGHTS_ENABLED_OFF
 *  \brief Handles event of turning lights off when they are acquitted
 */
#define EV_ACQ_BLINK_LIGHTS_ENABLED_OFF 6

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

/* Cmd status */
#define CMD_ON 1
#define CMD_OFF 0

/* Acq status */
#define ACQ_ON 1
#define ACQ_OFF 0

typedef struct
{
    int state;
    int event;
    int (*callback)(int);
    int next_state;
} tTransition;

typedef struct currentHandledState
{
    int left;
    int right;
    int warnings;
    int blinkingTimer;
} currentHandledState;

static currentHandledState savedState = {ST_BLINK_LIGHTS_OFF, ST_BLINK_LIGHTS_OFF, ST_BLINK_LIGHTS_OFF, 0};

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
    {ST_BLINK_LIGHTS_ENABLED_ON, EV_ACQ_BLINK_LIGHTS_NOT_RECEIVED, &fsmError, ST_ERROR},
    {ST_BLINK_LIGHTS_ENABLED_OFF, EV_ACQ_BLINK_LIGHTS_NOT_RECEIVED, &fsmError, ST_ERROR},
    {ST_BLINK_LIGHTS_ENABLED_ON, EV_ACQ_BLINK_LIGHTS_RECEIVED, &turnLightEnabledAndACQOn, ST_BLINK_LIGHTS_ON_ACQ},
    {ST_BLINK_LIGHTS_ENABLED_OFF, EV_ACQ_BLINK_LIGHTS_RECEIVED, &turnLightEnabledAndACQOff, ST_BLINK_LIGHTS_OFF_ACQ},
    {ST_BLINK_LIGHTS_ON_ACQ, EV_ACQ_BLINK_LIGHTS_ENABLED_ON, NULL, ST_BLINK_LIGHTS_ON_ACQ},
    {ST_BLINK_LIGHTS_ON_ACQ, EV_TURN_BLINK_LIGHTS_OFF, &turnLightOff, ST_BLINK_LIGHTS_OFF},
    {ST_BLINK_LIGHTS_OFF_ACQ, EV_TURN_BLINK_LIGHTS_OFF, &turnLightOff, ST_BLINK_LIGHTS_OFF},
    {ST_BLINK_LIGHTS_OFF_ACQ, EV_ACQ_BLINK_LIGHTS_ENABLED_OFF, NULL, ST_BLINK_LIGHTS_OFF_ACQ},
    {ST_BLINK_LIGHTS_ON_ACQ, EV_TURN_BLINK_LIGHTS_ENABLED_OFF, &turnLightEnabledOff, ST_BLINK_LIGHTS_ENABLED_OFF},
    {ST_BLINK_LIGHTS_OFF_ACQ, EV_TURN_BLINK_LIGHTS_ENABLED_ON, &turnLightEnabledOn, ST_BLINK_LIGHTS_ENABLED_ON}};

#define TRANS_COUNT (sizeof(trans) / sizeof(*trans))
/*!
 *  \fn static int GetNextEvent(int current_state, int side, int acqTimer)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 18 Octobre 2022 - 20:23:29
 *  \brief gets next event for the fms
 *  \param int current_state: current fsm state
 *  \param int side: side of the light to turn on
 *  \param int acqTimer : timer that checks if acq has been received or not
 *  \return event : an event that will trigger a callback or not
 */
static int GetNextEvent(int current_state, int side, int acqTimer)
{
    int event = EV_NONE;
    int acqStatus;
    int cmdStatus;

    switch (side)
    {
    case LEFT:
        acqStatus = getLeftBlinkerIsAcquited();
        cmdStatus = getisActivateLeftBlinker();
        break;
    case RIGHT:
        acqStatus = getRightBlinkerIsAcquited();
        cmdStatus = getIsActivateRightBlinker();
        break;
    default:
        acqStatus = getWarningsIsAcquited();
        cmdStatus = getIsActivateWarnings();
        break;
    }

    /* Build all the events */
    switch (current_state)
    {
    case ST_BLINK_LIGHTS_OFF:
        event = (cmdStatus == CMD_ON) ? EV_TURN_BLINK_LIGHTS_ENABLED_ON : EV_TURN_BLINK_LIGHTS_OFF;
        break;
    case ST_BLINK_LIGHTS_ENABLED_ON:
        if (cmdStatus == CMD_ON)
        {
            event = EV_TURN_BLINK_LIGHTS_ENABLED_ON;
            if (acqStatus != ACQ_ON && acqTimer > 100)
            {
                event = EV_ACQ_BLINK_LIGHTS_NOT_RECEIVED;
            }
            else
            {
                if (acqStatus == cmdStatus)
                {
                    event = EV_ACQ_BLINK_LIGHTS_RECEIVED;
                    savedState.blinkingTimer++;
                }
            }
        }
        else
        {
            event = EV_TURN_BLINK_LIGHTS_OFF;
            savedState.blinkingTimer = 0;
        }
        break;
    case ST_BLINK_LIGHTS_ENABLED_OFF:
        if (cmdStatus == CMD_ON)
        {
            event = EV_TURN_BLINK_LIGHTS_ENABLED_OFF;
            if (acqStatus != ACQ_ON && acqTimer >= 100)
            {
                event = EV_ACQ_BLINK_LIGHTS_NOT_RECEIVED;
            }
            else
            {
                if (acqStatus == cmdStatus)
                {
                    event = EV_ACQ_BLINK_LIGHTS_RECEIVED;
                    savedState.blinkingTimer++;
                }
            }
        }
        else
        {
            event = EV_TURN_BLINK_LIGHTS_OFF;
            savedState.blinkingTimer = 0;
        }
        break;
    case ST_BLINK_LIGHTS_OFF_ACQ:
        if (cmdStatus == CMD_ON)
        {
            event = EV_ACQ_BLINK_LIGHTS_ENABLED_OFF;
            if (savedState.blinkingTimer >= 100)
            {
                event = EV_ACQ_BLINK_LIGHTS_ENABLED_ON;
                savedState.blinkingTimer = 0;
            }
        }
        else
        {
            event = EV_TURN_BLINK_LIGHTS_OFF;
        }
        break;
    case ST_BLINK_LIGHTS_ON_ACQ:
        if (cmdStatus == CMD_ON)
        {
            event = EV_ACQ_BLINK_LIGHTS_ENABLED_ON;
            if (savedState.blinkingTimer >= 100)
            {
                event = EV_ACQ_BLINK_LIGHTS_ENABLED_OFF;
                savedState.blinkingTimer = 0;
            }
        }
        else
        {
            event = EV_TURN_BLINK_LIGHTS_OFF;
            savedState.blinkingTimer = 0;
        }
        break;
    case ST_ERROR:
        printf("Fatal error, the lights wont work anymore.\r\n");
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

int blinkLightsFSM(int side, int acqTimer)
{
    int i = 0;
    int ret = 0;
    int event = EV_NONE;
    int state = getCurrentState(side);
    // TODO: Check if using a state handler is a good thing. :: Something to store fsm state between runs

    /* Get event */
    event = GetNextEvent(state, side, acqTimer);
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
                ret = (trans[i].callback)(side);
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}
