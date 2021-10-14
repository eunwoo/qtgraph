#include "types.h"

using namespace MY_DATA;

#define LONG MY_LONG
WORD xmul(WORD a, WORD b, WORD c)
{
    return static_cast<WORD>((static_cast<LONG>(a)*b)/c);
}
