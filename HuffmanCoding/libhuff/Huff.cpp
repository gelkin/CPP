#include "Huff.h"

const size_t Huff::BufferedReader::M_BYTE;
const size_t Huff::BufferedWriter::M_BYTE;

//############################
//#### Huff::Node-methods
//############################
Huff::Node::Node () {
	this->val = 0;
	this->freq = 0;
	this->left = nullptr;
	this->right = nullptr;
}

Huff::Node::Node (unsigned char val, size_t freq, Node* left, Node* right)	{
	this->val = val;
	this->freq = freq;
	this->left = left;
	this->right = right;
}

Huff::Node::~Node () {
	delete left;
	delete right;
}

//############################
//#### Huff::Comparator-methods
//############################

bool Huff::Comparator::operator ()(Node* x, Node* y) const {
	return (x->freq < y->freq);
}

//############################
//#### Huff::BufferedReader-methods
//############################

Huff::BufferedReader::BufferedReader(const char* in_file_name) {
	in.open(in_file_name, std::ios::binary);

	// init "size"
	in.seekg(0, in.end);
	size = in.tellg();
	in.seekg(0, in.beg);

	counter = 0;
	current_data_size = std::min(M_BYTE, size);
	init_data_size = current_data_size;
	buffer = new char[current_data_size];
	in.read(buffer, current_data_size);
}

Huff::BufferedReader::~BufferedReader() {
	in.close();
	delete [] buffer;
}

unsigned char Huff::BufferedReader::get() {
	if (counter == current_data_size) {
		if (size == init_data_size) {
			return 0;
		}
		counter = 0;
		current_data_size = std::min(M_BYTE, size - init_data_size);
		init_data_size += current_data_size;
		delete [] buffer;
		buffer = new char[current_data_size];
		in.read(buffer, current_data_size);
	}
	counter++;
	return buffer[counter - 1];
}

size_t Huff::BufferedReader::get_size() {
	return this->size;
}

//############################
//#### Huff::BufferedWriter-methods
//############################

Huff::BufferedWriter::BufferedWriter(const char* out_file_name) {
	out.open(out_file_name, std::ios::binary);

	counter = 0;
	current_data_size = M_BYTE;
	buffer = new char[current_data_size];
}

Huff::BufferedWriter::~BufferedWriter() {
	flush();
	out.close();
	delete [] buffer;
}

void Huff::BufferedWriter::put(unsigned char ch) {
	if (counter == current_data_size) {
		out.write(buffer, current_data_size);
		counter = 0;
		current_data_size = M_BYTE;
		delete [] buffer;
		buffer = new char[current_data_size];
	}
	buffer[counter] = ch;
	counter++;
}

void Huff::BufferedWriter::flush() {
	out.write(buffer, counter);
}

//############################
//#### Huff::BitReader-methods
//############################
Huff::BitReader::BitReader(const char* in_file_name) {
	in = new BufferedReader(in_file_name);
	buf = in->get();
	counter = 7;
}

Huff::BitReader::~BitReader() {
	delete in;
}

bool Huff::BitReader::read_bit() {
	bool bit = 0;
	if ((buf >> counter) % 2 == 1) {
		bit = 1;
	}
	counter--;
	if (counter < 0) {
		buf = in->get();
		counter = 7;
	}
	return bit;
}

unsigned char Huff::BitReader::read_byte() {
	unsigned char byte = 0;
	int j = 7;
	while (counter > -1) {
		if ((buf >> counter) % 2 == 1) {
			byte += (int) pow(2.0, j);
		}
		counter--;
		j--;
	}
	buf = in->get();
	counter = 7;
	while (j > -1) {
		if ((buf >> counter) % 2 == 1) {
			byte += (int) pow(2.0, j);
		}
		counter--;
		j--;
	}
	return byte;
}

unsigned char* Huff::BitReader::read_code(Node* root) {
	while (true) {
		if (root->left == nullptr) {
			return &(root->val);
		} else if (read_bit() == 1) {
			root = root->right;
		} else {
			root = root->left;
		}
	}
}

//############################
//#### Huff::BitWriter-methods
//############################
Huff::BitWriter::BitWriter(const char* out_file_name_) {
	out = new BufferedWriter(out_file_name_);
	buf = 0;
	counter = 7;
}

Huff::BitWriter::~BitWriter() {
	flush();
	delete out;
}

void Huff::BitWriter::write_bit(bool bit) {
	if (bit == 1) {
		buf += (int) pow(2.0, counter);
	}
	counter--;
	if (counter < 0) {
		out->put(buf);
		buf = 0;
		counter = 7;
	}
}

void Huff::BitWriter::write_byte(unsigned char byte) {
	int j = 7;
	while(counter > -1) {
		if ((byte >> j) % 2 == 1) {
			buf += (int) pow(2.0, counter);
		}
		counter--;
		j--;
	}

	out->put(buf);
	buf = 0;
	counter = 7;
	while (j > -1) {
		if ((byte >> j) % 2 == 1) {
			buf += (int) pow(2.0, counter);
		}
		counter--;
		j--;
	}
}

void Huff::BitWriter::write_code(std::vector<bool>* code) {
	for (std::vector<bool>::iterator it = (*code).begin(); it != (*code).end(); it++) {
		write_bit(*it);
	}
}

void Huff::BitWriter::flush() {
	if (counter != 7) {
		out->put(buf);
	}
}

//############################
//#### Huff-methods
//############################
Huff::Huff(const char* in_file_name_, const char* out_file_name_) {
	in_file_name = in_file_name_;
	out_file_name = out_file_name_;
}

void Huff::encode_file() {
	in = new BufferedReader(in_file_name);
	int size = in->get_size();

	std::map<unsigned char, size_t> stats;
	init_map(&stats);
	delete in;

	Node* root = build_huff_tree(&stats);
	stats.clear();

	std::vector<bool> code;
	std::map<unsigned char, std::vector<bool> > table;

	// if (there are more than 1 element in tree)?
	// fill the table: put one element from the tree in table with code '0'
	if (root->left != nullptr) {
		build_huff_table(root, &table, &code);
	} else {
		code.push_back(0);
		table[root->val] = code;
	}

	writer = new BitWriter(out_file_name);
	encode_size(size);
	encode_tree(root);

	in = new BufferedReader(in_file_name);
	while(size > 0) {
		writer->write_code(&table[in->get()]);
		size--;
	}

	delete root;
	table.clear();
	code.clear();
	delete in;
	delete writer;
}

void Huff::decode_file() {
	reader = new BitReader(in_file_name);
	int size = decode_size();
	Node* root = decode_tree();

	out = new BufferedWriter(out_file_name);
	unsigned char* ch;
	while (size > 0) {
		ch = reader->read_code(root);
		out->put(*ch);
		size--;
	}

	delete root;
	delete out;
	delete reader;
}

// It parses in_file and return map: byte <-> appearing frequency
void Huff::init_map(std::map<unsigned char, size_t> *stats) {
	size_t size = in->get_size();
	while (size > 0) {
		(*stats)[in->get()]++;
		size--;
	}
}

// It takes statistics of frequencies and builds Huffman tree
Huff::Node* Huff::build_huff_tree(std::map<unsigned char, size_t>* stats) {
	std::list<Node*> tree;
	std::map<unsigned char, size_t>::iterator it;
	for (it = (*stats).begin(); it != (*stats).end(); ++it) {
		Node* p = new Node;
		p->val = it->first;
		p->freq = it->second;
		tree.push_back(p);
	}

	while (tree.size() != 1) {
		tree.sort(Comparator());

		Node* left = tree.front();
		tree.pop_front();
		Node* right = tree.front();
		tree.pop_front();

		Node* parent = new Node(0, left->freq + right->freq, left, right);
		tree.push_back(parent);
	}
	Node* root = tree.front();
	tree.clear();
	return root;
}


// After running, "table" consists of pairs: byte <-> huffman_code
void Huff::build_huff_table(Node* root, std::map<unsigned char, std::vector<bool> > *table,
						  std::vector<bool> *code) {
	if (root->left != nullptr) {
		(*code).push_back(0);
		build_huff_table(root->left, table, code);

		(*code).push_back(1);
		build_huff_table(root->right, table, code);
	} else {
		(*table)[root->val] = *code;
	}
	(*code).pop_back();
}

void Huff::encode_size(int size) {
	unsigned char ch;
	for (int i = 24; i >= 0; i -= 8) {
		ch = size >> i;
		writer->write_byte(ch);
	}
}

void Huff::encode_tree(Node* root) {
	if (root->left == nullptr) {
		writer->write_bit(1);
		writer->write_byte(root->val);
	}
	else {
		writer->write_bit(0);
		encode_tree(root->left);
		encode_tree(root->right);
	}
}

int Huff::decode_size() {
	int size = 0;
	for (int i = 0; i < 3; i++) {
		size += reader->read_byte();
		size <<= 8;
	}
	size += reader->read_byte();
	return size;
}

Huff::Node* Huff::decode_tree() {
	if (reader->read_bit() == 1) {
		return new Node(reader->read_byte(), 1, nullptr, nullptr);
	} else {
		Node* left = decode_tree();
		Node* right = decode_tree();
		return new Node(0, 0, left, right);
	}
}
