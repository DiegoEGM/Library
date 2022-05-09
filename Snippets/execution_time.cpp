#ifdef LOCAL
    auto beg = std::chrono::high_resolution_clock::now();
#endif

#ifdef LOCAL
    auto en = std::chrono::high_resolution_clock::now();
    cerr << setprecision(4) << fixed;
    cerr << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(en - beg).count() << " seconds" << "\n";
#endif
