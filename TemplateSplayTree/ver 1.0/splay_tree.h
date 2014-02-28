#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <cstdlib>

// null-pointer analogue
struct nil {};

// if-operator analogue
template <bool condition, typename IfTrue, typename IfFalse>
struct conditional {
    typedef IfFalse result;
};

template <typename IfTrue, typename IfFalse>
struct conditional <true, IfTrue, IfFalse> {
    typedef IfTrue result;
};

// Equals for typesp
template <typename A, typename B>
struct is_same {
    static const bool result = false;
};

template <typename T>
struct is_same <T,T> {
    static const bool result = true;
};

// Equals for ints
template <int key1, int key2>
struct is_equal {
    static const bool result = (key1 == key2);
};

/* Compare_to for ints. Definition:
 * 0 - key1 == key2
 * 1 - key1 < key2
 * 2 - key1 > key2
 */
template <int key1, int key2>
struct compare_to {
    static const int result = (key1 <= key2)? !(is_equal<key1, key2>::result): 2;
};

// Node of tree itself
template <int kkey, typename Left, typename Right>
struct node {
    static const int key = kkey;
    typedef Left left;
    typedef Right right;
};


/* Left rotate */
template <typename Tree>
struct left_rotate {
    typedef
            node<Tree::right::key,
                 node<Tree::key,
                      typename Tree::left,
                      typename Tree::right::left
                     >,
                 typename Tree::right::right
                >
    result;
};


/* Right rotate */
template <typename Tree>
struct right_rotate {
    typedef
            node<Tree::left::key,
                 typename Tree::left::left,
                 node<Tree::key,
                      typename Tree::left::right,
                      typename Tree::right
                     >
                >
    result;
};


/****************
 * Splay_left
 ****************/

template <typename Tree, int key>
struct splay;

// if (Tree.left != null)
template <typename Tree, bool condition>
struct splay_left_zig_helper {
    typedef Tree result;
};

// if (Tree.left == null)
template <typename Tree>
struct splay_left_zig_helper<Tree, false> {
    typedef 
	    typename right_rotate<Tree>::result
    result;
};

template <typename Tree>
struct splay_left_zig {
    typedef
	typename splay_left_zig_helper<Tree, is_same<typename Tree::left, nil>::result>::result
    result;
};

// if (Tree.left.left == null)
template <typename Tree, int key, bool condition>
struct splay_left_zig_zig_helper {
    typedef Tree result;
};

template <typename Tree, int key>
struct splay_left_zig_zig_helper<Tree, key, false> {
    typedef
    typename right_rotate<node<Tree::key,
                               node<Tree::left::key,
                                    typename splay<typename Tree::left::left, key>::result,
                                    typename Tree::left::right>,
                               typename Tree::right
                              >
                         >::result
    result;
};

// case: key < Tree.left.key
template <typename Tree, int key>
struct splay_left_zig_zig {
    typedef
    typename splay_left_zig_zig_helper<Tree, key, is_same<typename Tree::left::left, nil>::result>::result
    result;
};

template <typename Tree, int key, bool condition>
struct splay_left_zig_zag_helper {
    typedef Tree result;
};

template <typename Tree, int key>
struct splay_left_zig_zag_helper<Tree, key, false> {
    typedef
	node<Tree::key,
         typename left_rotate<node<Tree::left::key,
                                   typename Tree::left::left,
                                   typename splay<typename Tree::left::right, key>::result>
                             >::result,
          typename Tree::right
        >
    result;
};

// case: key > Tree.left.key
template <typename Tree, int key>
struct splay_left_zig_zag {
    typedef
    typename splay_left_zig_zag_helper<Tree, key, is_same<typename Tree::left::right, nil>::result>::result
    result;
};

// if key == Tree::left::key
template <typename Tree, int key, int condition>
struct splay_left_helper {
    typedef
    	typename splay_left_zig<Tree>::result
    result;
};

// key < Tree::left::key
template <typename Tree, int key>
struct splay_left_helper<Tree, key, 1> {
    typedef
    	typename splay_left_zig<typename splay_left_zig_zig<Tree, key>::result >::result 
    result;
};

// key > Tree::left::key
template <typename Tree, int key>
struct splay_left_helper<Tree, key, 2> {
    typedef
        typename splay_left_zig<typename splay_left_zig_zag<Tree, key>::result >::result 
    result;
};

// if Tree::left == nil
template <typename Tree, int key, bool condition>
struct splay_left {
    typedef Tree result;
};

template <typename Tree, int key>
struct splay_left<Tree, key, false> {
    typedef
    typename splay_left_helper<Tree, key, compare_to<key, Tree::left::key>::result >::result 
    result;
};

/****************
 * Splay_right
 ****************/

// if (Tree.right != null)
template <typename Tree, bool condition>
struct splay_right_zig_helper {
    typedef Tree result;
};

// if (Tree.right == null)
template <typename Tree>
struct splay_right_zig_helper<Tree, false> {
    typedef 
	    typename left_rotate<Tree>::result
    result;
};

// if (Tree.right == null)
template <typename Tree>
struct splay_right_zig {
    typedef
    typename splay_right_zig_helper<Tree, is_same<typename Tree::right, nil>::result>::result
    result;
};

// if Tree::right::left == nil
template <typename Tree, int key, bool condition>
struct splay_right_zig_zag_helper {
    typedef Tree result;
};

template <typename Tree, int key>
struct splay_right_zig_zag_helper<Tree, key, false> {
    typedef
	node<Tree::key,
         typename Tree::left,
         typename right_rotate<node<Tree::right::key,
                                    typename splay<typename Tree::right::left, key>::result,
                                    typename Tree::right::right>
                              >::result
	    >
    result;
};

// case: key < Tree.right.key
template <typename Tree, int key>
struct splay_right_zig_zag {
    typedef
    typename splay_right_zig_zag_helper<Tree, key, is_same<typename Tree::right::left, nil>::result>::result
    result;
};

template <typename Tree, int key, bool condition>
struct splay_right_zig_zig_helper {
    typedef Tree result;
};

// if (Tree.right.right != null)
template <typename Tree, int key>
struct splay_right_zig_zig_helper<Tree, key, false> {
    typedef
    typename left_rotate<node<Tree::key,
                              typename Tree::left,
                              node<Tree::right::key,
                                   typename Tree::right::left,
                                   typename splay<typename Tree::right::right, key>::result
                                  >
                             >
                        >::result
    result;
};

// case: key > Tree.right.key
template <typename Tree, int key>
struct splay_right_zig_zig {
    typedef
    typename splay_right_zig_zig_helper<Tree, key, is_same<typename Tree::right::right, nil>::result>::result
    result;
};

// if key == Tree::right::key
template <typename Tree, int key, int condition>
struct splay_right_helper {
    typedef
	    typename splay_right_zig<Tree>::result
    result;
};

// key < Tree::right::key
template <typename Tree, int key>
struct splay_right_helper<Tree, key, 1> {
    typedef
        typename splay_right_zig<typename splay_right_zig_zag<Tree, key>::result>::result
    result;
};

// key > Tree::right::key
template <typename Tree, int key>
struct splay_right_helper<Tree, key, 2> {
    typedef
      	typename splay_right_zig<typename splay_right_zig_zig<Tree, key>::result>::result
    result;
};

// if Tree::right == nil
template <typename Tree, int key, bool condition>
struct splay_right {
    typedef Tree result;
};

template <typename Tree, int key>
struct splay_right<Tree, key, false> {
    typedef
    typename splay_right_helper<Tree, key, compare_to<key, Tree::right::key>::result>::result
    result;
};

/****************
 * Splay_helper
 ****************/

// if key == Tree::key
template <typename Tree, int key, int condition>
struct splay_helper {
    typedef Tree result;
};

// if key < Tree::key
template <typename Tree, int key>
struct splay_helper<Tree, key, 1> {
    typedef
	typename splay_left<Tree, key, is_same<typename Tree::left, nil>::result>::result
    result;
};

// key > Tree::key
template <typename Tree, int key>
struct splay_helper<Tree, key, 2> {
    typedef
    	typename splay_right<Tree, key, is_same<typename Tree::right, nil>::result>::result
    result;
};

template <typename Tree, int key>
struct splay {
    typedef
	typename splay_helper<Tree, key, compare_to<key, Tree::key>::result>::result
    result;
};

template <int key>
struct splay <nil, key> {
    typedef nil result;
};


/* GET MAX ELEMENT */
template <typename Tree>
struct get_max {
    static const int value = (is_same<typename Tree::right, nil>::result )? Tree::key: get_max<typename Tree::right>::value;
};

template <>
struct get_max<nil> {
   // We decided that value = 0, when Tree == nil
   static const int value = 0;
};


/* MERGE TWO TREES */
template <typename Tree1, typename Tree2>
struct merge_splayed {
    typedef
    node<Tree1::key,
         typename Tree1::left,
         Tree2
        >
    result;
};

template <typename Tree1, typename Tree2>
struct merge {
    typedef
    typename merge_splayed<typename splay<Tree1, get_max<Tree1>::value>::result, Tree2>::result
    result;
};

template <typename Tree1>
struct merge<Tree1, nil> {
    typedef Tree1 result;
};

template <typename Tree2>
struct merge<nil, Tree2> {
    typedef Tree2 result;
};


/* SPLIT TREE BY KEY */
template <typename Tree, int key, int condition>
struct split_helper {
    typedef
        node<Tree::key,
             typename Tree::left,
             nil
            >
    subtree1;
    typedef typename Tree::right subtree2;
};
// key < Tree::key
template <typename Tree, int key>
struct split_helper<Tree, key, 1> {
    typedef typename Tree::left subtree1;
    typedef
        node<Tree::key,
             nil,
             typename Tree::right
            >
    subtree2;
};

template <typename Tree, int key>
struct split {
    typedef typename splay<Tree, key>::result splayed_tree;
    typedef split_helper<splayed_tree, key, compare_to<key, splayed_tree::key>::result> splitted_tree;

    typedef typename splitted_tree::subtree1 subtree1;
    typedef typename splitted_tree::subtree2 subtree2;
};


/* INSERT KEY */
template <typename Tree, int key>
struct insert {
    typedef typename split<Tree, key>::splitted_tree splitted_tree;

    typedef 
    typename conditional<is_equal<splitted_tree::subtree1::key, key>::result,
                         Tree, 
                         node<key, typename splitted_tree::subtree1, typename splitted_tree::subtree2>
                        >::result
    result;
};

template <int key>
struct insert<nil, key> {
    typedef node<key, nil, nil> result;
};


/* REMOVE KEY */
template <typename Tree, int key>
struct remove {
    typedef typename splay<Tree, key>::result splayed_tree;

    typedef
    typename merge<typename splayed_tree::left, typename splayed_tree::right>::result
    result;
};

template <int key>
struct remove<nil, key> {
    typedef nil result;
};


/* FIND KEY */
template <typename Tree, int key>
struct find;

template <typename Tree, int key, int condition>
struct find_helper {
    typedef Tree result;
};

// key < Tree::key
template <typename Tree, int key>
struct find_helper<Tree, key, 1> {
    typedef 
    typename find<typename Tree::left, key>::result
    result;
};

// key > Tree::key
template <typename Tree, int key>
struct find_helper<Tree, key, 2> {
    typedef 
    typename find<typename Tree::right, key>::result
    result;
};

template <typename Tree, int key>
struct find {
    typedef 
    typename find_helper<Tree, key, compare_to<key, Tree::key>::result>::result
    result; 
};

template <int key>
struct find<nil, key> {
    typedef nil result;
};


/* GET SIZE OF TREE */
template <typename Tree>
struct size {
   static const int result = 1 + size<typename Tree::left>::result
                               + size<typename Tree::right>::result;
};

template <>
struct size<nil> {
    static const int result = 0;
};

#endif
