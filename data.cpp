#include "types.h"
#include "util.h"
#include "globals.h"
#include "point.h"
#include <vector>

#define INVERTER_MODEL_IS7

#if defined(INVERTER_MODEL_IS7)
/* Define the system frequency (Hz) */
#define SYSCLKOUT	150e6
#define HISPCP_DIV_FACTOR	(2)
#define HSPCLOCK			(SYSCLKOUT/HISPCP_DIV_FACTOR)
#define TIMER_DIV_FACTOR_X_1  	(0)
#define TIMER1_DIV_FACTOR		(TIMER_DIV_FACTOR_X_1)
#define T1CLOCK		(HSPCLOCK / (0x0001 << TIMER1_DIV_FACTOR))
#define	GET_PWM_CONST	(static_cast<Uint32>(T1CLOCK * 10000/1e6/2/2))
#define	GET_PWM_VAL(x)	( static_cast<Uint16>( GET_PWM_CONST / (x) ) )
#elif defined(INVERTER_MODEL_H100)
#endif

enum {
    DATA_TYPE_WORD
};


void GenerateData(std::vector<Point<WORD>> &data)
{

    WORD wSwitchingFreq;
    WORD wTemp, wAsrKgainFactor;

    for (wSwitchingFreq = 20; wSwitchingFreq <= 150; wSwitchingFreq++) {
        wPwmAmp2 = GET_PWM_VAL(wSwitchingFreq);

        wTemp = xmul(GET_PWM_VAL(50), 500, wPwmAmp2);
        if(wTemp < 500) {
            wAsrKgainFactor = xmul((wTemp - 100), 500, 400) + 500;		//5KHz -> 100%, 1KHz -> 50%
        }
        else {
            wAsrKgainFactor = 1000;
        }
        data.emplace_back(wPwmAmp2, wAsrKgainFactor);
    }

}

