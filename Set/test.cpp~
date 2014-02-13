#define BOOST_TEST_MODULE set_testing
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "set.h"
#include <boost/test/unit_test.hpp>



// Внутри структуры Fixture иницализируется вспомогательная переменная
// "x" - дерево поиска - и 2 указателя на начало и конец этого дерева типа iterator.
struct Fixture {
	Fixture()
	{
		x = new set();

		x->insert(5);
		x->insert(10);
		x->insert(8);
		x->insert(3);
		x->insert(31);
		x->insert(2);
		x->insert(7);

		BOOST_TEST_MESSAGE("setup fixture");
	}

	~Fixture() {
		BOOST_TEST_MESSAGE("teardown fixture");
	}

	set* x;
};

// Проверка работы метода begin().
// Начальный элемент должен содержать ключ "2".
BOOST_FIXTURE_TEST_CASE(set_testing_Begin, Fixture) {
	set::iterator it = x->begin();
	BOOST_CHECK_EQUAL(*it, 2);
}


// Проверка работы метода end().
// Тест выводит все элементы.
BOOST_FIXTURE_TEST_CASE(set_testing_End, Fixture) {
	for (set::iterator it = x->begin(); it != x->end(); it++) {
		BOOST_TEST_MESSAGE(*it);
	}
}

// Проверка работы метода insert(int).
// Все ли ключи должны быть добавлены в дерево правильно.
BOOST_FIXTURE_TEST_CASE(set_testing_Insert, Fixture) {
	set::iterator it = x->begin();
	BOOST_CHECK_EQUAL(*it, 2);
	++it;
	BOOST_CHECK_EQUAL(*it, 3);
	++it;
	BOOST_CHECK_EQUAL(*it, 5);
	++it;
	BOOST_CHECK_EQUAL(*it, 7);
	++it;
	BOOST_CHECK_EQUAL(*it, 8);
	++it;
	BOOST_CHECK_EQUAL(*it, 10);
	++it;
	BOOST_CHECK_EQUAL(*it, 31);
}

// Проверка работы метода find(int).
// Обход дерева и проверка каждого на find.
// + тест для оператора сравнения "==" для элементов типа iterator.
BOOST_FIXTURE_TEST_CASE(set_testing_Find, Fixture) {
	for (set::iterator it = x->begin(); it != x->end(); it++) {
		BOOST_CHECK(x->find(*it) == it);
	}
}

// Проверка работы оператора присвоения для set.
// Создание копии дерева "x" - y. Далее, полный обход двух новых деревьев.
// + тест для оператора "!=" для элементов типа iterator.
BOOST_FIXTURE_TEST_CASE(set_testing_AssignmentOperator, Fixture) {
	set* y = x;
	for (set::iterator it = x->begin(); it != x->end(); it++) {
		BOOST_CHECK(!(y->find(*it) != x->find(*it)));
	}
}

// Проверка работы конструктора копирования set(set const&).
// Создание физической копии дерева "x" - y. Далее, полный обход двух новых деревьев.
BOOST_FIXTURE_TEST_CASE(set_testing_CopyConstructor, Fixture) {
	set* y = new set(*x);
	y->insert(1);
	BOOST_CHECK(*(y->begin()) != *(x->begin()));
}

// Проверка работы метода erase(iterator).
// Создание физической копии дерева "x" - y. Далее удаление
// элемента из начала проверкой.
BOOST_FIXTURE_TEST_CASE(set_testing_Erase, Fixture) {
	set* y = new set(*x);
	set::iterator it = y->begin();
	y->erase(it);
	BOOST_CHECK(*(y->begin()) == 3);
}

// Проверка работы инфиксного оператора operator ++(), для элементов типа iterator.
// Назначение элемента типа iterator на начало и проверка.
BOOST_FIXTURE_TEST_CASE(set_testing_IteratorInfixIncreaseKey, Fixture) {
	set::iterator it = (x->begin())++;
	BOOST_CHECK(*it == 2);
}

// Проверка работы инфиксного оператора operator --(), для элементов типа iterator.
// Назначение элемента типа iterator на элемент, следующий за x->begin(), и проверка.
BOOST_FIXTURE_TEST_CASE(set_testing_IteratorInfixDecreaseKey, Fixture) {
	set::iterator it = (++(x->begin()))--;
	BOOST_CHECK(*it == 3);
}
