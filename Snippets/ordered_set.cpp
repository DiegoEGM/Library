#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//.find_by_order(k) -> k-th smallest, 0-index (use *, its an iterator)
//.order_of_key(x) -> number of elements strictly < x
//+ insert, lower_bound and other stuff that set does...
