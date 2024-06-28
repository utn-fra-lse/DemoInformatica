#include <L2.h>
/* System clock frequency. */
extern uint32_t SystemCoreClock;
//---------------------------------------------------------------//
void ClockFRO18M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut18M);   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOsc); /*!< Set FRO clock source */
    POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);       /*!< Ensure Main osc is on */
    CLOCK_Select(kEXT_Clk_From_SysOsc);         /*!<select external clock source to sys_osc */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);  /*!< select fro for main clock */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = CLOCKFRO18M_CORE_CLOCK;
}
//---------------------------------------------------------------//
void ClockFRO24M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut24M);   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOsc); /*!< Set FRO clock source */
    POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);       /*!< Ensure Main osc is on */
    CLOCK_Select(kEXT_Clk_From_SysOsc);         /*!<select external clock source to sys_osc */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);  /*!< select fro for main clock */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = CLOCKFRO24M_CORE_CLOCK;
}
//---------------------------------------------------------------//
void ClockFRO30M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut30M);   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOsc); /*!< Set FRO clock source */
    POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);       /*!< Ensure Main osc is on */
    CLOCK_Select(kEXT_Clk_From_SysOsc);         /*!<select external clock source to sys_osc */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);  /*!< select fro for main clock */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = CLOCKFRO30M_CORE_CLOCK;
}
//---------------------------------------------------------------//
