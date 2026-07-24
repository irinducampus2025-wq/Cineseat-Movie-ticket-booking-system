#include "pricing.h"

Tier tierOf(int row) {
   if (row <= 1) return TIER_REGULAR; // A,B
   if (row <= 3) return TIER_PREMIUM; // C,D
   return TIER_VIP;                   // E
}

<<<<<<< HEAD
const char *teirLabel(Tier t) {
=======
const char *teirLabal(Tier t) {
>>>>>>> 1d97df2508271a2477d838aa65cf172f3a75760b
   switch (t) {
       case TIER_REGULAR: return "Regular";
       case TIER_PREMIUM: return "Premium";
       default:           return "VIP";
    }
}
double basePrice(Tier t) {
   switch (t){
      case TIER_REGULAR: return 500.0;
<<<<<<< HEAD
      case TIER_PREMIUM: return 750.0;
=======
      case TIER_PREMIUM; return 750.0;
>>>>>>> 1d97df2508271a2477d838aa65cf172f3a75760b
      default:              return 1000.0;
   }
}
double priceFor(Tier t, int student, int senior, int group) {
    double price = basePrice(t);
<<<<<<< HEAD
    double cut = senior ? 0.20 : (student ? 0.10 : 0.0;)
=======
    double cut = senior ? 0.20 : (student ? 0.10 : 0.0;
>>>>>>> 1d97df2508271a2477d838aa65cf172f3a75760b
    if (group) cut += 0.10;
    return price * (1.0 - cut);
}
