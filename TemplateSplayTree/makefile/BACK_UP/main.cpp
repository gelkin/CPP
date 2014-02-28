#include "splay_tree.h"
#include "splay_test.h"
#include <iostream>

void print_msg(bool b) {
    std::cout << ":: ";
    if (b)
        std::cout << "OK";
    else
       std::cout << "FAIL";
    std::cout << "\n";
}

int main() {

    bool b;

    // Left rotate test
    b = is_same<typename left_rotate<before_left_rotate>::result, after_left_rotate>::result;
    std::cout << "Left rotate test";
    print_msg(b);

    // Right rotate test
    b = is_same<typename right_rotate<before_right_rotate>::result, after_right_rotate>::result;
    std::cout << "Right rotate test";
    print_msg(b);

    // Right Zig ( Splay(2) )
    b = is_same<typename splay<before_right_zig, 2>::result, after_right_zig>::result;
    std::cout << "Right zig test";
    print_msg(b);

    // Left Zig ( Splay(4) )
    b = is_same<typename splay<before_left_zig, 4>::result, after_left_zig>::result;
    std::cout << "Left zig test";
    print_msg(b);

    // Right Zig-Zig ( Splay(2) )
    b = is_same<typename splay<before_right_zigzig, 2>::result, after_right_zigzig>::result;
    std::cout << "Right zig-zig test";
    print_msg(b);

    // Left Zig-Zig ( Splay(3) )
    b = is_same<typename splay<before_left_zigzig, 3>::result, after_left_zigzig>::result;
    std::cout << "Left zig-zig test";
    print_msg(b);

    // Right Zig-Zag ( Splay(3) )
    b = is_same<typename splay<before_right_zigzag, 3>::result, after_right_zigzag>::result;
    std::cout << "Right zig-zag test";
    print_msg(b);

    // Left Zig-Zag ( Splay(2) )
    b = is_same<typename splay<before_left_zigzag, 2>::result, after_left_zigzag>::result;
    std::cout << "Left zig-zag test";
    print_msg(b);
    
    // General splay test ( Splay(5) )
    b = is_same<typename splay<before_splay, 5>::result, after_splay>::result;
    std::cout << "General splay test";
    print_msg(b);
    
    // Get max element test
    b = (get_max<before_get_max>::value == 4)? true: false;
    std::cout << "Get max element test";
    print_msg(b);
    
    // Merge test
    b = is_same<typename merge<before_merge1, before_merge2>::result, after_merge>::result;
    std::cout << "Merge test";
    print_msg(b);
 
    // Split(4) test
    b = (is_same<typename split<before_split, 4>::subtree1, after_split1>::result
    + is_same<typename split<before_split, 4>::subtree2, after_split2>::result);
    std::cout << "Split test";
    print_msg(b);
 
    // Insert(8) test
    b = is_same<typename insert<before_insert, 8>::result, after_insert>::result;
    std::cout << "Insert test";
    print_msg(b);

    // Remove(3) test
    b = is_same<typename remove<before_remove, 3>::result, after_remove>::result;
    std::cout << "Remove test";
    print_msg(b);

    // Find(7) test
    b = is_same<typename find<before_find, 7>::result, after_find>::result;
    std::cout << "Find test";
    print_msg(b);

    return 0;
}
