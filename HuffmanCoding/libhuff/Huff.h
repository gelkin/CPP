#ifndef HUFF_H
#define HUFF_H

#ifndef nullptr
#define nullptr NULL
#endif

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <list>

class Huff {
 public:
	class Node {
	 public:
		unsigned char val;
		size_t freq;
		Node* left;
		Node* right;

		Node();
		Node(unsigned char, size_t, Node*, Node*);
		~Node();
	};

	class Comparator {
	 public:
		bool operator()(Node*, Node*) const;
	};

	class BufferedReader {
		static const size_t M_BYTE = 1000000;
		std::ifstream in;
		size_t counter;
		size_t current_data_size;
		size_t init_data_size;
		char* buffer;
		size_t size;

	 public:
		BufferedReader(const char*);
		~BufferedReader();
		unsigned char get();
		size_t get_size();
	};

	class BufferedWriter {
		static const size_t M_BYTE = 1000000;
		std::ofstream out;
		size_t counter;
		size_t current_data_size;
		char* buffer;

	 public:
		BufferedWriter(const char*);
		~BufferedWriter();
		void put(unsigned char);

	 private:
		void flush();

	};

	class BitReader {
	 public:
		BufferedReader* in;
		unsigned char buf;
		int counter;

	 public:
		BitReader(const char*);
		~BitReader();
		bool read_bit();
		unsigned char read_byte();
		unsigned char* read_code(Node*);
	};

	class BitWriter {
		BufferedWriter* out;
		unsigned char buf;
		int counter;

	 public:
		BitWriter(const char*);
		~BitWriter();
		void write_bit(bool);
		void write_byte(unsigned char);
		void write_code(std::vector<bool> *);

	 private:
		void flush();
	};

	const char* in_file_name;
	const char* out_file_name;
	BufferedReader* in;
	BufferedWriter* out;
	BitReader* reader;
	BitWriter* writer;

	void init_map(std::map<unsigned char, size_t> *);
	Node* build_huff_tree(std::map<unsigned char, size_t> *);
	void build_huff_table(Node*, std::map<unsigned char, std::vector<bool> > *, std::vector<bool> *);
	void encode_size(int);
	void encode_tree(Node*);


	Node* decode_tree();
	int decode_size();

 // public:
	Huff(const char*, const char*);
	void encode_file();
	void decode_file();
};

#endif // HUFF_H
