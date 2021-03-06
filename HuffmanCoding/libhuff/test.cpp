#define BOOST_TEST_MODULE Huff_testing
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "Huff.h"
#include <boost/test/unit_test.hpp>



// Внутри структуры Fixture иницализируются вспомогательные переменные.
struct Fixture {
	friend class Huff;
	Fixture()
		: x("/home/vladimir/CPP/HuffArchive/materials/test.txt",
			"/home/vladimir/CPP/HuffArchive/materials/test.txt.huff")
		, y("/home/vladimir/CPP/HuffArchive/materials/test.txt.huff",
			"/home/vladimir/CPP/HuffArchive/materials/test.txt.orig")
	{
		// real_stats initialization
		real_stats['\n'] = 1;
		real_stats['a'] = 2;
		real_stats['b'] = 3;
		real_stats['c'] = 4;
		real_stats['d'] = 4;

		// real_table initialization
		std::vector<bool> code;
		code.push_back(0); code.push_back(0);
		real_table['b'] = code;

		code.pop_back(); code.push_back(1); code.push_back(0);
		real_table['\n'] = code;

		code.pop_back(); code.push_back(1);
		real_table['a'] = code;

		code.pop_back(); code.pop_back(); code.pop_back(); code.push_back(1); code.push_back(0);
		real_table['c'] = code;

		code.pop_back(); code.push_back(1);
		real_table['d'] = code;

		// real_out initialization
		bool arr [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					  0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
					  0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1,
					  1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
					  0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0};

		std::vector<bool> tmp (arr, arr + sizeof(arr) / sizeof(bool) );
		real_out = tmp;

		BOOST_TEST_MESSAGE("setup fixture");
	}

	~Fixture() {
		BOOST_TEST_MESSAGE("teardown fixture");
	}
	Huff x; // для архивации
	Huff y; // для разархивации
	std::map<unsigned char, size_t> real_stats;
	std::map<unsigned char, std::vector<bool> > real_table;
	std::vector<bool> real_out;
};



// Проверка работы метода init_map(std::map<unsigned char, size_t> *).
// После выполнения init_map(stats), stats должен быть равен real_stats.
BOOST_FIXTURE_TEST_CASE(Huff_testing_init_map, Fixture) {
	x.in = new Huff::BufferedReader(x.in_file_name);
	std::map<unsigned char, size_t> stats;
	x.init_map(&stats);
	std::map<unsigned char, size_t>::iterator it;
	for (it = real_stats.begin(); it != real_stats.end(); ++it) {
		BOOST_CHECK_EQUAL(stats[it->first], it->second);
	}

	delete x.in;
}

// Проверка работы метода build_huff_tree(std::map<unsigned char, size_t> *).
// Тест проверяет порядок "листьев" дерева (считая слева на право).
BOOST_FIXTURE_TEST_CASE(Huff_testing_build_huff_tree, Fixture) {
	Huff::Node* root = x.build_huff_tree(&real_stats);
	Huff::Node* root_tmp_1 = root;
	Huff::Node* root_tmp_2 = root;
	std::vector<unsigned char> bytes;
	while (root_tmp_1->left != nullptr) {
		root_tmp_1 = root_tmp_1->left;
	}
	while (root_tmp_2->left != nullptr) {
		root_tmp_2 = root_tmp_2->right;
	}

	BOOST_CHECK_EQUAL(root->freq, 14);
	BOOST_CHECK_EQUAL(root_tmp_1->val, 'b');
	BOOST_CHECK_EQUAL(root_tmp_2->val, 'd');

	delete root;
}

//  Проверка работы метода build_huff_table(Node*, std::map<unsigned char, std::vector<bool> > *,
//											std::vector<bool> *)
//	Тест проверяет соответствие "байт" <-> "код хаффмана для этого байта"
BOOST_FIXTURE_TEST_CASE(Huff_testing_build_huff_table, Fixture) {
	Huff::Node* root = x.build_huff_tree(&real_stats);
	std::vector<bool> code;
	std::map<unsigned char, std::vector<bool> > table;
	x.build_huff_table(root, &table, &code);
	std::map<unsigned char, std::vector<bool> >::iterator it;
	for (it = real_table.begin(); it != real_table.end(); ++it) {
		BOOST_CHECK(std::equal(it->second.begin(),
							   it->second.begin() + it->second.size(),
							   table[it->first].begin()));
	}

	delete root;
}

// Проверка работы методов: encode_file(), encode_tree(Node*), encode_size(int).
// Тест проверяет соответствие действительного заархивированного файла (real_out)
// и того, что генерируется методом encode_file().
BOOST_FIXTURE_TEST_CASE(Huff_testing_encode_file, Fixture) {
	x.encode_file();
	Huff::BitReader* out = new Huff::BitReader("/home/vladimir/CPP/HuffArchive/materials/test.txt.huff");
	int size = real_out.size();
	while (size > 0) {
		BOOST_CHECK(real_out[real_out.size() - size] == out->read_bit());
		size--;
	}

	delete out;
}

// Проверка работы методов: decode_file(), decode_tree(), decode_size(int).
// Тест проверяет соответствие входного файла (real_in) и файла,
// разархивированного методом decode_file().
BOOST_FIXTURE_TEST_CASE(Huff_testing_decode_file, Fixture) {
	y.decode_file();
	std::ifstream old_in("/home/vladimir/CPP/HuffArchive/materials/test.txt", std::ios::binary);
	std::ifstream new_in("/home/vladimir/CPP/HuffArchive/materials/test.txt.orig", std::ios::binary);

	unsigned ch1 = old_in.get();
	unsigned ch2 = new_in.get();
	while(!old_in.eof()) {
		BOOST_CHECK(ch1 == ch2);
		ch1 = old_in.get();
		ch2 = new_in.get();
	}
}
