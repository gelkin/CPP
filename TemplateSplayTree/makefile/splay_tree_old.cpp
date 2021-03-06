// TODO: CHECKOUT en.wiki.com/splay_tree
#include <cstdlib>
template <typename Tree, int key>
struct splay;

struct nil
{};

template <bool condition, typename IfTrue, typename IfFalse>
struct conditional {
    typedef IfFalse result;
};

template <typename IfTrue, typename IfFalse>
struct conditional <true, IfTrue, IfFalse> {
    typedef IfTrue result;
};

// Checks are two types equal or not 
template <typename A, typename B>
struct is_same {
    static const bool result = false;
};

template <typename T>
struct is_same <T,T> {
    static const bool result = true;
};

// equals
template <int key1, int key2>
struct is_equal {
    static const bool result = (key1 == key2);
};

// compareTo
// 0 - key1 == key2
// 1 - key1 < key2
// 2 - key1 > key2
template <int key1, int key2>
struct compare_to {
    static const int result = (key1 <= key2)? !(is_equal<key1, key2>::result) : 2;
};

// Node of tree itself
template <int kkey, typename Left, typename Right>
struct node {
    static const int key = kkey;
    typedef Left left;
    typedef Right right;
};

// left rotate
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

// right rotate
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



//////////
///SPLAY
//////////

///////////////CASE_1

// if (Tree.left != null)
template <typename Tree, bool condition>
struct splay_case1_helper {
    typedef Tree result;
};

// if (Tree.left == null)
template <typename Tree>
struct splay_case1_helper<Tree, false> {
    typedef 
	    typename right_rotate<Tree>::result
    result;
};


template <typename Tree>
struct splay_case1 {
    typedef
	typename splay_case1_helper<Tree, is_same<typename Tree::left, nil>::result>::result
    result;
};

// case: key < Tree.left.key
template <typename Tree, int key>
struct splay_case1_helper1 {
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


template <typename Tree, int key, bool condition>
struct splay_case1_helper2_helper {
    typedef
	node<Tree::key,
             nil,
             typename Tree::right
            >
    result;
};

template <typename Tree, int key>
struct splay_case1_helper2_helper<Tree, key, false> {
    typedef
	node<Tree::key,
             typename left_rotate<node<Tree::left::key,
                                       typename Tree::left::left,
                                       typename splay<typename Tree::left::right, key>::result
                                      >
                                 >::result,
             typename Tree::right
            >
    result;
};
   

// case: key > Tree.left.key
template <typename Tree, int key>
struct splay_case1_helper2 {
    typedef
    typename splay_case1_helper2_helper<Tree, key, is_same<typename splay<typename Tree::left::right, key>::result, nil>::result>::result
    result;
};

///////////////CASE_2

// if (Tree.right != null)
template <typename Tree, bool condition>
struct splay_case2_helper {
    typedef Tree result;
};

// if (Tree.right == null)
template <typename Tree>
struct splay_case2_helper<Tree, false> {
    typedef 
	    typename left_rotate<Tree>::result
    result;
};

// if (Tree.right == null)
template <typename Tree>
struct splay_case2 {
    typedef
    typename splay_case2_helper<Tree, is_same<typename Tree::right, nil>::result>::result
    result;
};

template <typename Tree, int key, bool condition>
struct splay_case2_helper1_helper {
    typedef
	node<Tree::key,
             typename Tree::left,
	     nil
            >
    result;
};

template <typename Tree, int key>
struct splay_case2_helper1_helper<Tree, key, false> {
    typedef
	node<Tree::key,
         typename Tree::left,
         typename right_rotate<typename Tree::right>::result
	    >
    result;
};

// case: key < Tree.right.key
template <typename Tree, int key>
struct splay_case2_helper1 {
    typedef
    typename splay_case2_helper1_helper<Tree, key, is_same<typename splay<typename Tree::right::left, key>::result, nil>::result>::result
    result;
};

// case: key > Tree.right.key
template <typename Tree, int key>
struct splay_case2_helper2 {
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


// if key == Tree::left::key
template <typename Tree, int key, int condition>
struct splay_left_helper {
    typedef
    	typename splay_case1<Tree>::result
    result;
};

// key < Tree::left::key
template <typename Tree, int key>
struct splay_left_helper<Tree, key, 1> {
    typedef
    	typename splay_case1<typename splay_case1_helper1<Tree, key>::result >::result 
    result;
};

// key > Tree::left::key
template <typename Tree, int key>
struct splay_left_helper<Tree, key, 2> {
    typedef
        typename splay_case1<typename splay_case1_helper2<Tree, key>::result >::result 
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


// if key == Tree::right::key
template <typename Tree, int key, int condition>
struct splay_right_helper {
    typedef
        typename splay_case2<Tree>::result
    result;
};

// key < Tree::right::key
template <typename Tree, int key>
struct splay_right_helper<Tree, key, 1> {
    typedef
        typename splay_case2<typename splay_case2_helper1<Tree, key>::result>::result
    result;
};

// key > Tree::right::key
template <typename Tree, int key>
struct splay_right_helper<Tree, key, 2> {
    typedef
      	typename splay_case2<typename splay_case2_helper2<Tree, key>::result>::result
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


//////
//INSERT
//////

// insert after splay
// key == Tree::key 
template <typename Tree, int key, int condition>
struct insert_splayed_helper {
    typedef Tree result;
};

// key < Tree::key 
template <typename Tree, int key>
struct insert_splayed_helper<Tree, key, 1> {
    typedef 
	node<key,
 	     typename Tree::left,
             node<Tree::key,
                  nil,
     		  typename Tree::right
	         >
            >		 
    result;
};

// key > Tree::key 
template <typename Tree, int key>
struct insert_splayed_helper<Tree, key, 2> {
    typedef 
	node<key,
             node<Tree::key,
                  typename Tree::left,
                  nil
                 >,
             typename Tree::right
            >
    result;
};

template <typename Tree, int key>
struct insert_splayed {
    typedef
	typename insert_splayed_helper<Tree, key, compare_to<key, Tree::key>::result>::result
    result;
};

template <typename Tree, int key>
struct insert {
    typedef typename insert_splayed<typename splay<Tree, key>::result, key>::result result;
};

template <int key>
struct insert <nil, key> {
    typedef node<key, nil, nil> result;
};


//////
//REMOVE
//////

// if Tree::left == nil
template <typename Tree, int key, bool condition>
struct remove_left {
    typedef
    typename Tree::right
    result;
};

template <typename Tree, int key>
struct remove_left<Tree, key, false> {
    typedef
    node<splay<typename Tree::left, key>::result::key,
         typename splay<typename Tree::left, key>::result::left,
         typename Tree::right
        >
    result;
};

// key == splay(Tree, key) (i.e. is key in Tree)
template <typename Tree, int key, bool condition>
struct remove_helper {
    typedef
    typename remove_left<Tree, key, is_same<typename Tree::left, nil>::result>::result
    result;
};

template <typename Tree, int key>
struct remove_helper<Tree, key, false> {
    typedef Tree result;
};

// if (key in Tree): make left subtree main (if it's not nil)
// else: return Tree 
template <typename Tree, int key>
struct remove {
    typedef
    typename remove_helper<typename splay<Tree, key>::result,
                                   key,
                                   is_equal<key, Tree::key>::result
                                  >::result
    result;
};

template <int key>
struct remove<nil, key> {
    typedef nil result;
};


//////
//FIND
//////

template <typename Tree, int key>
struct find_splayed {
    typedef
    typename conditional<is_equal<Tree::key, key>::result,
                         Tree,
                         nil
                        >::result
    result;
};

template <typename Tree, int key>
struct find {
    typedef
    typename find_splayed<Tree, key>::result
    result;
};

template <int key>
struct find<nil, key> {
    typedef nil result;
};

//////
//SIZE
//////

template <typename Tree>
struct size {
   static const int result = 1 + size<typename Tree::left>::result
                               + size<typename Tree::right>::result;
};

template <>
struct size<nil> {
    static const int result = 0;
};
