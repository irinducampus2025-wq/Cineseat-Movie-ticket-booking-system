#ifndef PRICING_H
#define PRICING_H

#include "types.h"

Tire tierof(int row);
const char *tierLabel(tier t);
double basePrice(Tier t);
double priceFor(Tire t, int student, int senior, int group);
endif /*PRICING_H*/
