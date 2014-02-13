/*
    typedef node<5, nil, node<10, nil, nil> > afterInsert;
typedef insert<x, 5> x0;

typedef node<2, nil, afterInsert> y;
typedef insert<afterInsert, 2> x1;

typedef find<x, 10> xFind;
typedef remove<x, 10> xRemove;
typedef splay<x, 10> xSplay;
    // typedef insert<x, 7> x2;

    // x == splay(x) =D
    std::cout << is_same<typename xSplay::result, x>::result << "\n";

    // x.left == nil
    std::cout << is_same<typename x::left, nil>::result << "\n";

    // remove(x, 10) == nil
    std::cout << is_same<typename xRemove::result, typename x::right>::result << "\n";

    // insert(x, 5)
    std::cout << is_same<typename x0::result, afterInsert>::result << "\n";

    // size(x0)
    std::cout << "size: " << size<typename x0::result>::result << "\n";

    // insert(afterInsert, 2)
    std::cout << is_same<typename x1::result, y>::result << "\n";

    // size(x1)
    std::cout << "size: " << size<typename x1::result>::result << "\n";
*/
