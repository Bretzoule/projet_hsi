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

/* Cmd status */
#define CMD_ON 1
#define CMD_OFF 0

/* Acq status */
#define ACQ_ON 1
#define ACQ_OFF 0

/* Lights type */
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
#define EV_TURN_LIGHTS_OFF 1

/*!
 *  \def EV_TURN_LIGHTS_ON
 *  \brief Event status when the lights turn on
 */
#define EV_TURN_LIGHTS_ON 2

/*!
 *  \def EV_ACQ_RECEIVED
 *  \brief Event status when the ACQ return has been received
 */
#define EV_ACQ_RECEIVED 3

/*!
 *  \def EV_ACQ_NOT_RECEIVED
 *  \brief Event status when the ACQ return has not been received
 */
#define EV_ACQ_NOT_RECEIVED 4

typedef struct
{
    int state;
    int event;
    int (*callback)(int);
    int next_state;
} tTransition;

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
    case IDLE:
        setIsActivateStateLight(0);
        break;
    case LOWBEAM:
        setIsActivateDippedBeam(0);
        break;
    case HIGHBEAM:
        setIsActivateMainBeam(0);
        break;
    }
    return 0;
}

/*!
 *  \fn static int lightsOn(int type)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Dim 23 Octobre 2022 - 17:41:18
 *  \brief handles lightOn states
 *  \return 0
 */
static int lightsOn(int type)
{
    switch (type)
    {
    case IDLE:
        setIsActivateStateLight(1);
        break;
    case LOWBEAM:
        setIsActivateDippedBeam(1);
        break;
    case HIGHBEAM:
        setIsActivateMainBeam(1);
        break;
    }
    return 0;
}

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
}

/*!
 *  \fn static int acquitted(int type)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Dim 23 Octobre 2022 - 17:41:18
 *  \brief handles acquitted states
 *  \return 0
 */
static int acquittedLights(int type)
{
    switch (type)
    {
    case IDLE:
        setIdleIsAcquited(1);
        break;
    case LOWBEAM:
        setHighBeamIsAcquited(1);
        break;
    case HIGHBEAM:
        setLowBeamIsAcquited(1);
        break;
    }
    return 0;
}

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

/* Transitions */
tTransition trans[] = {
    {ST_LIGHTS_OFF, EV_TURN_LIGHTS_ON, &lightsOn, ST_LIGHTS_ON},
    {ST_LIGHTS_OFF, EV_TURN_LIGHTS_OFF, NULL, ST_LIGHTS_OFF},
    {ST_LIGHTS_ON, EV_TURN_LIGHTS_ON, NULL, ST_LIGHTS_ON},
    {ST_LIGHTS_ON, EV_TURN_LIGHTS_OFF, &lightsOff, ST_LIGHTS_OFF},
    {ST_LIGHTS_ON, EV_ACQ_NOT_RECEIVED, &fsmError, ST_ERROR},
    {ST_LIGHTS_ON, EV_ACQ_RECEIVED, &acquittedLights, ST_ACQ},
    {ST_ACQ, EV_TURN_LIGHTS_OFF, &lightsOff, ST_LIGHTS_OFF},
    {ST_ACQ, EV_TURN_LIGHTS_ON, NULL, ST_ACQ}};
/*!
 *  \fn static int GetNextEvent(int current_staten int lightType, int acqTimer)
 *  \author LEFLOCH Thomas <leflochtho@eisti.eu>
 *  \version 0.1
 *  \date Mar 18 Octobre 2022 - 20:23:29
 *  \brief gets next event for the fms
 *  \param int current_state: current fsm state
 *  \param int lightType: type of light
 *  \param int acqTimer: timer to check if the acq deadline hasnt been missed
 *  \return event : an event that will trigger a callback or not
 */
static int GetNextEvent(int current_state, int lightType, int acqTimer)
{
    int event = EV_NONE;
    int acqStatus;
    int cmdStatus;

    switch (lightType)
    {
    case IDLE:
        acqStatus = getIdleIsAcquited();
        cmdStatus = getisActivateStateLight();
        break;
    case LOWBEAM:
        acqStatus = getHighBeamIsAcquited();
        cmdStatus = getIsActivateDippedBeam();
        break;
    case HIGHBEAM:
        acqStatus = getLowBeamIsAcquited();
        cmdStatus = getIsActivateMainBeam();
        break;
    }

    switch (current_state)
    {

    /* switch case on states */
    case ST_LIGHTS_OFF:
        event = (cmdStatus == CMD_ON) ? EV_TURN_LIGHTS_ON : EV_TURN_LIGHTS_OFF;
        break;
    case ST_LIGHTS_ON:
        if (cmdStatus == CMD_ON)
        {
            event = EV_TURN_LIGHTS_ON;
            if (acqStatus != ACQ_ON && acqTimer > 100)
            {
                event = EV_ACQ_NOT_RECEIVED;
            }
            else
            {
                if (acqStatus == cmdStatus)
                {
                    event = EV_ACQ_RECEIVED;
                }
            }
        }
        else
        {
            event = EV_TURN_LIGHTS_OFF;
        }
        break;
    case ST_ACQ:
        event = (cmdStatus == CMD_OFF) ? EV_TURN_LIGHTS_OFF : EV_TURN_LIGHTS_ON;
        break;
    }
    return event;
}

int lightsFSM(int lightType, int acqTimer)
{
    int i = 0;
    int ret = 0;
    int event = EV_NONE;
    int state = ST_LIGHTS_OFF;

    /* Get event */
    event = GetNextEvent(state, lightType, acqTimer);
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
                ret = (trans[i].callback(lightType));
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}
