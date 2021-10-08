#include "types.h"


WORD xmul(WORD a, WORD b, WORD c)
{
    return static_cast<WORD>((static_cast<LONG>(a)*b)/c);
}
