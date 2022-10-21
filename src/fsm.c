/* States */
#define ST_ANY                             -1
#define ST_INIT                             0
#define ST_LIGHTS_OFF                       1
#define ST_LIGHTS_ON                        2
#define ST_ACQUITTED                        3
#define ST_ERROR                            4
#define ST_TERM                           255

/* Events */
#define EV_NONE                             0
#define EV_ANY                             -1
#define EV_CMD_ON                           1
#define EV_CMD_OFF                          2
#define EV_ACQUIT_RECEIVED                  3
#define EV_ACQUIT_NOT_RECEIVED              4                        

/* Functions called on transitions */
static int LightsOff(int type){ 
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

static int LightsOn(int type){ 
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

static int Error(void){ 
    printf("Error\n");
    return 0;
};

static int Acquitted(int type){ 
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

static int FsmError(void){ 
    printf("FsmError\n");
    return 0;
};

typedef struct {
    int state;
    int event;
    int (*callback)(void);
    int next_state;
} tTransition;

/* Transitions */
tTransition trans[] = {
    { ST_LIGHTS_OFF, EV_CMD_ON, &LightsOff, ST_LIGHTS_ON},
    { ST_LIGHTS_ON, EV_CMD_OFF, &LightsOn, ST_LIGHTS_OFF},
    { ST_LIGHTS_ON, EV_ACQUIT_NOT_RECEIVED, &Error, ST_ERROR},
    { ST_LIGHTS_ON, EV_ACQUIT_RECEIVED, &Acquitted, ST_ACQUITTED},
    { ST_ACQUITTED, EV_CMD_OFF, &Acquitted, ST_LIGHTS_OFF},
    { ST_ANY, EV_ANY, &FsmError, ST_TERM}
};

#define TRANS_COUNT (sizeof(trans)/sizeof(*trans))


int GetNextEvent(int current_state)
{
    int event = EV_NONE;

    /* Here, you can get the parameters of your FSM */
    
    /* Build all the events */
    switch (current_state) {

        /* switch case on states */
        case ST_LIGHTS_OFF :
            event = getisActivateStateLight();
        break;
        case ST_LIGHTS_ON :
            event = getidleIsAcquited();
        break;
        case ST_ACQUITTED:
            event = getidleIsAcquited();
        break;
        case ST_ERROR:
        break;
    }
    return event;
}

int main(void)
{
    int i = 0;
    int ret = 0; 
    int event = EV_NONE;
    int state = ST_INIT;
    
    /* While FSM hasn't reach end state */
    while (state != ST_TERM) {
        
        /* Get event */
        event = GetNextEvent(state);
        
        /* For each transitions */
        for (i = 0; i < TRANS_COUNT; i++) {
            /* If State is current state OR The transition applies to all states ...*/
            if ((state == trans[i].state) || (ST_ANY == trans[i].state)) {
                /* If event is the transition event OR the event applies to all */
                if ((event == trans[i].event) || (EV_ANY == trans[i].event)) {
                    /* Apply the new state */
                    state = trans[i].next_state;
                    /* Call the state function */
                    ret = (trans[i].callback)();
                    break;
                }
            }
        }
    }

    return 0;
}
