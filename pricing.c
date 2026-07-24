#include "pricing.h"

Tier tierOf(int row) {
   if (row <= 1) return TIER_REGULAR;
   if (row <= 3) return TIER_PREMIUM;
   return TIER_VIP;
}

const char *tierLabel(Tier t) {
   switch (t) {
       case TIER_REGULAR: return "Regular";
       case TIER_PREMIUM: return "Premium";
       default:           return "VIP";
    }
}
double basePrice(Tier t) {
   switch (t){
      case TIER_REGULAR: return 500.0;
      case TIER_PREMIUM: return 750.0;
      default:              return 1000.0;
   }
}
double priceFor(Tier t, int student, int senior, int group) {
    double price = basePrice(t);
    double cut = senior ? 0.20 : (student ? 0.10 : 0.0);
    if (group) cut += 0.10;
    return price * (1.0 - cut);
}
