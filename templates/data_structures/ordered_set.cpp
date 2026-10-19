// policy based ordered set. the pb_ds #includes MUST stay above "#define int ll" (uncomment them in the base template),
// otherwise the library breaks. paste only the two lines below.
// os.order_of_key(x) = number of elements < x, *os.find_by_order(k) = k-th smallest (0-based)
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> using ordered_multiset = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>; // {value, unique id}
