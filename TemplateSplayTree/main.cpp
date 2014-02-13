#include "SplayTree.cpp"
#include <cstdlib>
#include <iostream>

/* Left rotate test
    1             2
     \           / \
      2    =>   1   3
       \
        3
*/
typedef node<1, nil, node<2, nil, node<3, nil, nil> > > before_left_rotate;
typedef node<2, node<1, nil, nil>, node<3, nil, nil> > after_left_rotate;

/* Right rotate test
       3          2
      /          / \
     2    =>    1   3
    /
   1
*/
typedef node<3, node<2, node<1, nil, nil>, nil>, nil> before_right_rotate;
typedef node<2, node<1, nil, nil>, node<3, nil, nil> > after_right_rotate;

// SPLAY TEST

/* Right Zig ( Splay(2) )
        4          2
       / \        / \
      2   5  =>  1   4
     / \            / \
    1   3          3   5
*/
typedef node<4, node<2, node<1, nil, nil>, node<3, nil, nil> >, node<5, nil, nil> > before_right_zig;
typedef node<2, node<1, nil, nil>, node<4, node<3, nil, nil>, node<5, nil, nil> > > after_right_zig;

/* Left Zig ( Splay (4) )
        2            4
       / \          / \
      1   4   =>   2   5
         / \      / \
        3   5    1   3
*/
typedef node<2, node<1, nil, nil>, node<4, node<3, nil, nil>, node<5, nil, nil> > > before_left_zig;
typedef node<4, node<2, node<1, nil, nil>, node<3, nil, nil> >, node<5, nil, nil> > after_left_zig;

/* Right Zig-Zig ( Splay(2) )
         4
        /           2
       3           / \
      /     =>    1   3
     2                 \
    /                   4
   1
*/
typedef node<4, node<3, node<2, node<1, nil, nil>, nil>, nil>, nil> before_right_zigzig;
typedef node<2, node<1, nil, nil>, node<3, nil, node<4, nil, nil> > > after_right_zigzig;

/* Left Zig-Zig ( Splay(3) )
   1
    \               3
     2             / \
      \     =>    2   4
       3         / \
        \       1   3
         4
*/
typedef node<1, nil, node<2, nil, node<3, nil, node<4, nil, nil> > > > before_left_zigzig;
typedef node<3, node<2, node<1, nil, nil>, node<3, nil, nil> >, node<4, nil, nil> > after_left_zigzig;

/* Right Zig-Zag ( Splay(3) )
     4
    /          3
   1    =>    / \
    \        1   4
     3        \
    /          2
   2
*/
typedef node<4, node<1, nil, node<3, node<2, nil, nil>, nil> >, nil> before_right_zigzag;
typedef node<3, node<1, nil, node<2, nil, nil> >, node<4, nil, nil> > after_right_zigzag;

/* Left Zig-Zag ( Splay(2) )
    1
     \         2
      4  =>   / \
     /       1   4
    2           /
     \         3
      3
*/
typedef node<1, node<4, node<2, nil, node<3, nil, nil> >, nil>, nil> before_left_zigzag;
typedef node<2, node<1, nil, nil>, node<4, node<3, nil, nil>, nil> > after_left_zigzag;


// TODO::::
// МНОГО СПЕЦИАЛИЗАЦИЙ, ИНАЧЕ НЕ СМОЖЕТ ПРОИНИЦИАЛИЗИРОВАТЬ ШАБЛОНЧИК

int main() {

    bool b;

    // Left rotate test
    b = is_same<typename left_rotate<before_left_rotate>::result, after_left_rotate>::result;
    std::cout << b;

    // Right rotate test
    b = is_same<typename right_rotate<before_right_rotate>::result, after_right_rotate>::result;
    std::cout << b;

    // SPLAY TEST

    // Right Zig ( Splay(2) )
    b = is_same<typename splay<before_right_zig, 2>::result, after_right_zig>::result;
    std::cout << b;

    // Left Zig ( Splay(4) )
    b = is_same<typename splay<before_left_zig, 4>::result, after_left_zig>::result;
    std::cout << b;

    // Right Zig-Zig ( Splay(2) )
    b = is_same<typename splay<before_right_zigzig, 2>::result, after_right_zigzig>::result;
    std::cout << b;

    // Left Zig-Zig ( Splay(3) )
    b = is_same<typename splay<before_left_zigzig, 3>::result, after_left_zigzig>::result;
    std::cout << b;

    // Right Zig-Zag ( Splay(3) )
    b = is_same<typename splay<before_right_zigzag, 3>::result, after_right_zigzag>::result;
    std::cout << b;

    // Left Zig-Zag ( Splay(2) )
    b = is_same<typename splay<before_left_zigzag, 2>::result, after_left_zigzag>::result;
    std::cout << b;

    return 0;
}
