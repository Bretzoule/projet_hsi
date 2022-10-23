/*
 *  \file idleLightsFSM.c
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

/*!
 *  \def ST_ERROR
 *  \brief Manages error state
 */
#define ST_ERROR -1

/*!
 *  \def ST_IDLE_LIGHTS_OFF
 *  \brief Manages state of the lights when it's off
 */
#define ST_IDLE_LIGHTS_OFF 0

/*!
 *  \def ST_IDLE_LIGHTS_ON
 *  \brief Manages state of the low beam lights when it's on
 */
#define ST_IDLE_LIGHTS_ON 1

/*!
 *  \def ST_IDLE_ACQ
 *  \brief Manages state of the acq light
 */
#define ST_IDLE_ACQ 3

/*!
 *  \def EV_TURN_IDLE_LIGHTS_OFF
 *  \brief Event status when the lights turn off
 */
#define EV_TURN_IDLE_LIGHTS_OFF 0

/*!
 *  \def EV_TURN_IDLE_LIGHTS_ON
 *  \brief Event status when the lights turn on
 */
#define EV_TURN_IDLE_LIGHTS_ON 1

/*!
 *  \def EV_ACQ_IDLE_RECEIVED
 *  \brief Event status when the ACQ return has been received
 */
#define EV_ACQ_IDLE_RECEIVED 2


/*!
 *  \def IDLE_LIGHTS_MASK
 *  \brief mask to get the digit of idle lights indicator
 */
#define IDLE_LIGHTS_MASK 0b01000000


typedef struct
{
    int state;
    int event;
    int (*callback)(void);
    int next_state;
} tTransition;

static int idleLightsOff(void);
static int idleLightsOn(void);
static int fsmError(void);
static int notifyListeners(void);

/* Transitions */
tTransition trans[] = {
    {ST_IDLE_LIGHTS_OFF, EV_TURN_IDLE_LIGHTS_ON, &idleLightsOn, ST_IDLE_LIGHTS_ON},
    {ST_IDLE_LIGHTS_OFF, EV_TURN_IDLE_LIGHTS_OFF, NULL, ST_IDLE_LIGHTS_OFF},
    {ST_IDLE_LIGHTS_ON, EV_TURN_IDLE_LIGHTS_ON, NULL, ST_IDLE_LIGHTS_ON},
    {ST_IDLE_LIGHTS_ON, EV_TURN_IDLE_LIGHTS_OFF, &idleLightsOff, ST_IDLE_LIGHTS_OFF},
    {ST_IDLE_LIGHTS_ON, EV_NONE, &fsmError, ST_ERROR},
    {ST_IDLE_LIGHTS_ON, EV_ACQ_IDLE_RECEIVED, &notifyListeners, ST_IDLE_ACQ},
    {ST_IDLE_ACQ, EV_TURN_IDLE_LIGHTS_OFF, &idleLightsOff, ST_IDLE_LIGHTS_OFF},
    {ST_IDLE_ACQ, EV_TURN_IDLE_LIGHTS_ON, NULL, ST_IDLE_ACQ}};

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
    u_int8_t decodedACQLNS = getACQLNS();

    /* Build all the events */
    switch (current_state)
    {
    case ST_IDLE_LIGHTS_OFF:
        if ((decodedLNS & IDLE_LIGHTS_MASK) == 0b01000000)
            event = EV_TURN_IDLE_LIGHTS_ON;
        if ((decodedLNS & IDLE_LIGHTS_MASK) == 0b00000000)
            event = EV_TURN_IDLE_LIGHTS_OFF;
        break;

    case ST_IDLE_LIGHTS_ON:
        if ((decodedLNS & IDLE_LIGHTS_MASK) == 0b01000000)
            event = EV_TURN_IDLE_LIGHTS_ON;
        if ((decodedLNS & IDLE_LIGHTS_MASK) == 0b00000000)
            event = EV_TURN_IDLE_LIGHTS_OFF;
        if ((decodedACQLNS & IDLE_LIGHTS_MASK) == 0b01000000)
            event = EV_ACQ_IDLE_RECEIVED;
        // if(decodedACQLNS == 0) event = EV_NONE // ERROR
        break;
    case ST_IDLE_ACQ:
        if ((decodedLNS & IDLE_LIGHTS_MASK) == 0b01000000)
            event = EV_TURN_IDLE_LIGHTS_ON;
        if ((decodedLNS & IDLE_LIGHTS_MASK) == 0b00000000)
            event = EV_TURN_IDLE_LIGHTS_OFF;
        break;
    }
    return event;
}

int idleLightsFSM(void)
{
    int i = 0;
    int ret = 0;
    int event = EV_NONE;
    int state = ST_IDLE_LIGHTS_OFF;

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
