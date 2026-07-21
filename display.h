#ifndef PRICING_H
#define PRICING_H

#include "types.h"



Tier tierOf(int row);
const char *tierLabel(Tier t);
double basePrice(Tier t);


double priceFor(Tier t, int student, int senior, int group);

#endif
