#include "public/library.h"

int GetApproxAngle(int X, int Y)
{
    if (X == 0 && Y == 0)
    {
        return 0;
    }

    if (ABS(X) > ABS(Y))
    {
        return (X > 0) ? ((Y > 0) ? 315 : ((Y < 0) ? 45 : 0)) : ((Y > 0) ? 225 : ((Y < 0) ? 135 : 180));
    }
    else
    {
        return (Y > 0) ? ((X > 0) ? 270 : ((X < 0) ? 225 : 270)) : ((X > 0) ? 90 : ((X < 0) ? 135 : 90));
    }

    return 0;
}