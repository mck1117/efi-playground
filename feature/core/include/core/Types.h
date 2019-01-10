#pragma once

#include <core/math/Quantity.h>

QUANTITY_TYPE(1, 0, -1, 0, massrate_t);

template <typename TBin, typename TValue, unsigned char TSize>
struct Table2Data
{
    const char* Name;
    TBin Bins[TSize];
    TValue Values[TSize];
};

template <typename TBin, typename TValue, unsigned char TSizeX, unsigned char TSizeY>
struct Table3Data
{
    const char* Name;
    TBin BinsX[TSizeX];
    TBin BinsY[TSizeY];
    TValue Values[TSizeX * TSizeY];
};

struct PhaseDurationScheduled
{

};
