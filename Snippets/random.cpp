mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int unif(int l, int r) { return uniform_int_distribution(l, r)(rng); }
ll unif_ll(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }
//shuffle(all(a), rng); to randomly shuffle a vector a
