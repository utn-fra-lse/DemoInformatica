#include <L2.h>


//------------------------------------------------------------------------
//------------------------------------------------------------------------
/* Match Configuration for Channel 0-4 */
static ctimer_match_config_t matchConfig0, matchConfig1, matchConfig2, matchConfig3;
/* Array of function pointers for callback for each channel */
ctimer_callback_t ctimer_callback_table[] = {
    ctimer_match0_callback, ctimer_match1_callback, ctimer_match2_callback, ctimer_match4_callback, NULL, NULL, NULL, NULL
};

//------------------------------------------------------------------------
//------------------------------------------------------------------------
void ctimer_match0_callback(uint32_t flags)
{
	ctimer_match0_interrupt();
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
void ctimer_match1_callback(uint32_t flags)
{
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
void ctimer_match2_callback(uint32_t flags)
{
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
void ctimer_match3_callback(uint32_t flags)
{
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
void Init_Ctimer_Match0(uint16_t freq){
    ctimer_config_t config;
    CTIMER_StopTimer(CTIMER0);

    CTIMER_GetDefaultConfig(&config);
    CTIMER_Init(CTIMER0, &config);

    /* Configuration 0 */
    matchConfig0.enableCounterReset = true;
    matchConfig0.enableCounterStop  = false;
    matchConfig0.matchValue         = CLOCK_GetFreq(kCLOCK_CoreSysClk) / freq;
    matchConfig0.outControl         = kCTIMER_Output_NoAction;
    matchConfig0.outPinInitState    = false;
    matchConfig0.enableInterrupt    = true;

    CTIMER_RegisterCallBack(CTIMER0, &ctimer_callback_table[0], kCTIMER_MultipleCallback);
    CTIMER_SetupMatch(CTIMER0, kCTIMER_Match_0, &matchConfig0);
    //CTIMER_SetupMatch(CTIMER0, kCTIMER_Match_1, &matchConfig1);
    CTIMER_StartTimer(CTIMER0);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
