
// empty
struct nil
{};

template <typename Data, typename Next>
struct node
{
    typedef Data data;
    typedef Next next;
};


// node<int,int>
// node<int, node<float, int> >

// how to writo methods: metamethods
template <typename List, typename Value>
struct push_back
{
    // typedef ... result;
    typedef node<typename List::data, typename push_back<typename List::next, Value>::result> result;

};

// as example:  push_back<a,float>::result

template <typename Value>
struct push_back<nil, Value>
{
    typedef node<Value, nil> result;
};


int main()
{
    return 0;
}

// Thisl is a list of types

//его заполняют вот этим классом чтобы хранить конкретные значения:
template <typename T, T Data>
struct constant
{};

//как сравнивать:
template <typename A, typename B>
struct is_same
{
    static const bool result = false;
};

template <typename T>
struct is_same <T,T>
{
    static const bool result = true;
};

//static_assert(condition, "message");

typedef node<int,nil> a;
typedef node <int, node<float, nil> > b;
static_assert(is_same<push_back<a,float>::result, b>::result, "error");


// еще чего-нибудь напишем

template <typename List>
struct pop_front
{
    typedef typename List::next result;
    // если дать nil, то не скомпилится
};

template <typename List>
struct pop_back
{
    typedef node <typename List::data, typename pop_back<typename List::next>::result> result;
};

template <typename Value>
struct pop_back<node <Value, nil> >
{
    typedef nil result;
};


// удаляем
// на этом месте уже все должно быть понятно
template <typename List, size_t N>
struct erase
{
    typedef node <typename List::data, typename erase<typename List::next, N-1>::result> result;
};

// erase от нуля - то же самое что pop_front
template <typename List>
struct erase <List, 0>
{
    typedef typename List::next result;
};



// обращение
template <typename Source, typename Target>
struct reverse_impl
{
    typedef typename reverse_impl<typename Source::next, node<typename Source::data, Target> >::result result;
};

template <typename Target>
struct reverse_impl<nil, Target>
{
    typedef Target result;
};

template <typename List>
struct reverse
{
    typedef typename reverse_impl<List, nil>::result result;
};



// а еще в компайл тайме можно распечатать, ибо дебагать это нельзя
// у нас список типов, как печатать типы?

template <typename T>
void print_type()
{
    std::cout<<typeid(T).name()<<std::endl; // это хитрый хак. можно было и специализацию делать
}

template <typename List>
void print_list()
{
    print_type<typename List::data>();
    print_list<typename List::next>();
}

template <>
void print_list<nil>()
{}







// надо написать любое сбалансированное дерево.
// по мнению Сорокина проще всего пишется сплей

//дерево ИНТОВ, чтобы было понятно как их сравнивать
// операции: вставка, удаление, поиск


//// если нет статик_ассерта, можно и руками:
//template <bool>
//struct
//{};
//
//template<>
//struct static_assert<false>;
//
////пользоваться так:
//static_assert<condition> a;




//----------------
// как можно немного сократить писанину
template <typename T>
struct f
{
    typedef typename g<typename T::next>::result result;
};
// g - должна быть описана. это как бы функция, но это класс

//// записывается короче:
//template<typename T>
//struct f: g<typename T::next>
//{};


//-----------------------
// полезно иметь аналог тернарника ни типах
template <bool condition, typename IfTrue, typename IfFalse>
struct conditional
{
    typedef IfFalse result;
};

template <typename IfTrue, typename IfFalse>
struct conditional <true, IfTrue, IfFalse>
{
    typedef IfTrue result;
};
