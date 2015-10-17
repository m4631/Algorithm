bool check(int x) {
   return true;
}

int binary_search_first_yes(int lo, int hi) {
   while (lo < hi) {
      int mid = lo + (hi-lo)/2;
      if ( check(mid) )
         hi = mid;
      else
         lo = mid+1;
   }
// if (check(lo)) --lo;  // if searching for last no
   return lo;            // lo is the least x for which check(x) is true
}


// no no no no yes yes yes
int binary_search_last_no(int lo, int hi) {
   while (lo < hi) {
      int mid = lo + (hi-lo+1)/2;
      if ( check(mid) )
         hi = mid-1;
      else
         lo = mid;
   }
   return lo;             // lo is the greatest x for which check(x) is false
}

// continuous case
double binary_search_continuous(double lo, double hi) {
   for (int t = 1; t <= 100; ++t) {
      double mid = lo + (hi-lo)/2;
      if ( check(mid) )
         hi = mid;
      else
         lo = mid;
   }
   return lo;            // lo is close to the border between no and yes
}


double F(double x) {
   return x*x*x - 3*x*x + 2*x + 20;
}

// find maximum of function F
double ternary_search(double L, double R) {
// const double EPS = 1e-9;
   for (int t = 0; t < 200 /* && R-L > EPS */ ; ++t) {
      double L3 = (L*2 + R) / 3;
      double R3 = (L + R*2) / 3;
      if (F(L3) < F(R3))
         L = L3;
      else
         R = R3;
   }
   return (L+R)/2;
}
