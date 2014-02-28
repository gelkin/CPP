#ifndef SPLAY_TEST_H
#define SPLAY_TEST_H

#include "splay_tree.h"

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

/* SPLAY TEST */

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
       3         / 
        \       1   
         4
*/
typedef node<1, nil, node<2, nil, node<3, nil, node<4, nil, nil> > > > before_left_zigzig;
typedef node<3, node<2, node<1, nil, nil>, nil>, node<4, nil, nil> > after_left_zigzig;

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
typedef node<1, nil, node<4, node<2, nil, node<3, nil, nil> >, nil> > before_left_zigzag;
typedef node<2, node<1, nil, nil>, node<4, node<3, nil, nil>, nil> > after_left_zigzag;

/* General splay test ( Splay(5) )
    10                 5 
   /  \              /   \
  2    11           2     10
 / \        =>     / \    / \
1   4             1   4  6   11
   / \               / 
  3   6             3
     /
    5
*/
typedef node<10,
             node<2, node<1, nil, nil>, node<4, node<3, nil, nil>, node<6, node<5, nil, nil>, nil> > >,
             node<11, nil, nil>
            > before_splay;
typedef node<5,
            node<2, node<1, nil, nil>, node<4, node<3, nil, nil>, nil> >,
            node<10, node<6, nil, nil>, node<11, nil, nil> >
           > after_splay;

/* GET_MAX (= 4)
    1
     \
      4  => 4
     /
    2
     \
      3
*/
typedef node<1, nil, node<4, node<2, nil, node<3, nil, nil> >, nil> > before_get_max;

/* MERGE
  5        10             7
 / \         \           / \
4   7   +    11   =>    5   10
   /                   / \    \
  6                   4   6   11
*/
typedef node<5, node<4, nil, nil>, node<7, node<6, nil, nil>, nil> > before_merge1;
typedef node<10, nil, node<11, nil, nil> > before_merge2;
typedef node<7, node<5, node<4, nil, nil>, node<6, nil, nil> >, node<10, nil, node<11, nil, nil> > > after_merge;

/* SPLIT(4)
      5             4    5 
    /   \          /      \
   2     7   =>   2   +    7
  / \   /        / \      / 
 1   4 6        1   3    6
    /                     
   3                      
 */
typedef node<5, node<2, node<1, nil, nil>, node<4, node<3, nil, nil>, nil> >, node<7, node<6, nil, nil>, nil> > before_split;
typedef node<4, node<2, node<1, nil, nil>, node<3, nil, nil> >, nil> after_split1;
typedef node<5, nil, node<7, node<6, nil, nil>, nil> > after_split2;

/* INSERT(8)
    5              8
   / \            / \
  3   7  =>      7   10
     / \        /
    6  10      5
              / \
             3   6
 */
typedef node<5, node<3, nil, nil>, node<7, node<6, nil, nil>, node<10, nil, nil> > > before_insert;
typedef node<8, node<7, node<5, node<3, nil, nil>, node<6, nil, nil> >, nil>, node<10, nil, nil> > after_insert;

/* REMOVE(3)
    5              2
   / \              \
  3   6    =>        5
 / \   \            / \
2   4   7          4   6
                        \
                         7
 */
typedef node<5, node<3, node<2, nil, nil>, node<4, nil, nil> >, node<6, nil, node<7, nil, nil> > > before_remove;
typedef node<2, nil, node<5, node<4, nil, nil>, node<6, nil, node<7, nil, nil> > > > after_remove;

/* FIND(7)
    5
  /   \           7
 3     7    =>   / \
  \   / \       6   8
   4 6   8
 */
typedef node<5, node<3, nil, node<4, nil, nil> >, node<7, node<6, nil, nil>, node<8, nil, nil> > > before_find;
typedef node<7, node<6, nil, nil>, node<8, nil, nil> > after_find;

#endif
