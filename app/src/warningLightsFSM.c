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
 *  \def ST_WARNING_LIGHTS_OFF
 *  \brief Manage warning lights state when it's off
 */
#define ST_WARNING_LIGHTS_OFF 0

/*!
 *  \def ST_WARNING_LIGHTS_ENABLED_OFF
 *  \brief Manage warning lights state when it's enable and off
 */
#define ST_WARNING_LIGHTS_ENABLED_OFF 1

/*!
 *  \def ST_WARNING_LIGHTS_ENABLED_ON
 *  \brief Manage warning lights state when it's on and enabled
 */
#define ST_WARNING_LIGHTS_ENABLED_ON 2

/*!
 *  \def ST_WARNING_LIGHTS_ON_ACQ
 *  \brief Manages state of the acq light for warnings when they're on
 */
#define ST_WARNING_LIGHTS_ON_ACQ 3

/*!
 *  \def ST_WARNING_LIGHTS_OFF_ACQ
 *  \brief Manages state of the acq light for warnings when they're off
 */
#define ST_WARNING_LIGHTS_OFF_ACQ 4

/*!
 *  \def ST_ERROR
 *  \brief Manages error state
 */
#define ST_ERROR -1

/*!
 *  \def EV_TURN_WARNING_LIGHTS_OFF
 *  \brief Handles event of turning the lights off
 */
#define EV_TURN_WARNING_LIGHTS_OFF 0

/*!
 *  \def EV_TURN_WARNING_LIGHTS_ENABLED_ON
 *  \brief Handles event of turning the lights on when they are enabled
 */
#define EV_TURN_WARNING_LIGHTS_ENABLED_ON 1

/*!
 *  \def EV_TURN_WARNING_LIGHTS_ENABLED_OFF
 *  \brief Handles event of turning the lights off when they are enabled
 */
#define EV_TURN_WARNING_LIGHTS_ENABLED_OFF 2

/*!
 *  \def EV_ACQ_WARNING_LIGHTS_RECEIVED
 *  \brief Event status when the ACQ return has been received
 */
#define EV_ACQ_WARNING_LIGHTS_RECEIVED 3

/*!
 *  \def EV_ACQ_WARNING_LIGHTS_ENABLED_ON
 *  \brief Handles event of turning lights on when they are acquitted
 */
#define EV_ACQ_WARNING_LIGHTS_ENABLED_ON 4

/*!
 *  \def EV_ACQ_WARNING_LIGHTS_ENABLED_OFF
 *  \brief Handles event of turning lights off when they are acquitted
 */
#define EV_ACQ_WARNING_LIGHTS_ENABLED_OFF 5

/*!
 *  \def WARNING_LIGHTS_MASK
 *  \brief mask to get the digit of warning lights indicator
 */
#define WARNING_LIGHTS_MASK 0b10000000

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

static int turnWarningLightsEnabledOff(void);
static int turnWarningLightsEnabledOn(void);
static int turnWarningLightsEnabledAndACQOff(void);
static int turnWarningLightsEnabledAndACQOn(void);
static int turnWarningLightsOff(void);
static int fsmError(void);
static int notifyListeners(void);

/* Transitions */
tTransition trans[] = {
    {ST_WARNING_LIGHTS_OFF, EV_TURN_WARNING_LIGHTS_OFF, NULL, ST_WARNING_LIGHTS_OFF},
    {ST_WARNING_LIGHTS_OFF, EV_TURN_WARNING_LIGHTS_ENABLED_ON, &turnWarningLightsEnabledOn, ST_WARNING_LIGHTS_ENABLED_ON},
    {ST_WARNING_LIGHTS_ENABLED_ON, EV_TURN_WARNING_LIGHTS_ENABLED_ON, NULL, ST_WARNING_LIGHTS_ENABLED_ON},
    {ST_WARNING_LIGHTS_ENABLED_ON, EV_TURN_WARNING_LIGHTS_ENABLED_OFF, &turnWarningLightsEnabledOff, ST_WARNING_LIGHTS_ENABLED_ON},
    {ST_WARNING_LIGHTS_ENABLED_ON, EV_TURN_WARNING_LIGHTS_OFF, &turnWarningLightsOff, ST_WARNING_LIGHTS_OFF},
    {ST_WARNING_LIGHTS_ENABLED_OFF, EV_TURN_WARNING_LIGHTS_OFF, &turnWarningLightsOff, ST_WARNING_LIGHTS_OFF},
    {ST_WARNING_LIGHTS_ENABLED_OFF, EV_TURN_WARNING_LIGHTS_ENABLED_OFF, NULL, ST_WARNING_LIGHTS_ENABLED_OFF},
    {ST_WARNING_LIGHTS_ENABLED_OFF, EV_TURN_WARNING_LIGHTS_ENABLED_ON, &turnWarningLightsEnabledOn, ST_WARNING_LIGHTS_ENABLED_ON},
    {ST_WARNING_LIGHTS_ENABLED_ON, EV_NONE, &fsmError, ST_ERROR},
    {ST_WARNING_LIGHTS_ENABLED_OFF, EV_NONE, &fsmError, ST_ERROR},
    {ST_WARNING_LIGHTS_ENABLED_ON, EV_ACQ_WARNING_LIGHTS_RECEIVED, &notifyListeners, ST_WARNING_LIGHTS_ON_ACQ},
    {ST_WARNING_LIGHTS_ENABLED_OFF, EV_ACQ_WARNING_LIGHTS_RECEIVED, &notifyListeners, ST_WARNING_LIGHTS_OFF_ACQ},
    {ST_WARNING_LIGHTS_ON_ACQ, EV_ACQ_WARNING_LIGHTS_ENABLED_ON, NULL, ST_WARNING_LIGHTS_OFF_ACQ},
    {ST_WARNING_LIGHTS_OFF_ACQ, EV_ACQ_WARNING_LIGHTS_ENABLED_OFF, &turnWarningLightsEnabledAndACQOff, ST_WARNING_LIGHTS_ON_ACQ},
    {ST_WARNING_LIGHTS_ON_ACQ, EV_ACQ_WARNING_LIGHTS_ENABLED_OFF, &turnWarningLightsEnabledAndACQOn, ST_WARNING_LIGHTS_OFF_ACQ}};

#define TRANS_COUNT (sizeof(trans) / sizeof(*trans))

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
    u_int8_t time = getTime();
    u_int8_t decodedACQLNS = getACQLNS();

    /* Build all the events */
    switch (current_state)
    {
    case ST_WARNING_LIGHTS_OFF:
    if((decodedLNS & WARNING_LIGHTS_MASK) == 0b10000000)
        event = EV_TURN_WARNING_LIGHTS_ENABLED_ON;
    //TODO: Complete states and conditions
        break;
    }
    return event;
}

int warningLightsFSM(void)
{
    int i = 0;
    int ret = 0;
    int event = EV_NONE;
    int state = ST_WARNING_LIGHTS_OFF;

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
                    ret = (trans[i].callback)();
                    break;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}
