sort(all(vals));
vals.resize(unique(all(vals)) - vals.begin());

auto lb = [&](int x) -> int {
     return 1 + lower_bound(all(vals), x) - vals.begin();
};
