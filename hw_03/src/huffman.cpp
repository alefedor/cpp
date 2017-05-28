#include "huffman.h"
#include <iostream>
#include <set>

using namespace std;

Archiver::BitWriter::BitWriter(ofstream &out):out(out){}

int Archiver::BitWriter::flush(){
    if (buf.empty())
        return 0;
    while (buf.size() % 8 != 0)
        buf.push_back(0);
    unsigned int num = buf.size() / 8;
    unsigned char c[num];
    for (unsigned int i = 0; i < num; i++){
        c[i] = 0;
        for (unsigned int j = 0; j < 8; j++)
            c[i] += buf[8 * i + j] << j;
    }
    out.write((char*)c, num);
    buf.clear();
    return num;
}

int Archiver::BitWriter::writeBit(bool b){
    buf.push_back(b);
    if (buf.size() == (1 << 15))
        return flush();
    return 0;
}

Archiver::BitWriter::~BitWriter(){
    flush();
}

void Archiver::pack(std::ifstream &in, std::ofstream &out){
    in.seekg(0, in.end);
    unsigned int len = in.tellg();
    before_size_ = len;
    after_size_ = 0;
    in.seekg(0, in.beg);
    char c;
    std::map<char, unsigned int> freq;
    for (unsigned int i = 0; i < len; i++){
        in.read(&c, 1);
        freq[c]++;
    }

    writeTable(out, freq);
    if (freq.size() == 0){
        printStat();
        return;
    }
    HuffmanTree t(freq);

    out.write((char*)&len, 4);
    table_size_ += 4;

    std::map<char, std::vector<char> > codes;
    BitWriter bw(out);
    t.getCodes(codes);
    in.seekg(0, in.beg);

    vector<char> gt[256];
    for (std::map<char, vector<char> >::iterator it = codes.begin(); it != codes.end(); it++)
        gt[it -> first + 128] = it -> second;

    for (unsigned int i = 0; i < len; i++){
        in.read(&c, 1);
        std::vector<char> &code = gt[c + 128];
        for (unsigned int j = 0; j < code.size(); j++)
            after_size_ += bw.writeBit(code[j]);
    }
    after_size_ += bw.flush();

    if (!in.good())
        throw ArchiverException("Error: can not read file");
    if (!out.good())
        throw ArchiverException("Error: can not write in file");

    printStat();
}

void Archiver::unpack(std::ifstream &in, std::ofstream &out){
    after_size_ = before_size_ = 0;
    std::map<char, unsigned int> freq;
    readTable(in, freq);
    if (freq.size() == 0){
        before_size_ = after_size_ = 0;
        printStat();
        return;
    }

    HuffmanTree t(freq);
    HuffmanTree::TreeNode *v = t.root;

    unsigned int len;
    in.read((char*)&len, 4);
    table_size_ += 4;
    if (!in.good())
            throw ArchiverException("Error on reading archive");
    char c;
    bool bit;
    while (len){
        in.read(&c, 1);
        if (!in.good())
            throw ArchiverException("Error on reading archive");
        before_size_++;
        for (unsigned int j = 0; len && j < 8; j++){
            bit = (((unsigned char)c) & (1 << j));
            if (!v -> canGo(bit))
                throw ArchiverException("Error on reading archive3");
            v = v -> go(bit);
            if (v -> isLeaf()){
                after_size_++;
                out.write(&(v -> c), 1);
                v = t.root;
                len--;
            }
        }
    }

    if (v != t.root || !in.good())
        throw ArchiverException("Error on reading archive");
    if (!out.good())
        throw ArchiverException("Error: can not write in file");

    printStat();
}

void Archiver::printStat(){
    cout << before_size_ << "\n";
    cout << after_size_ << "\n";
    cout << table_size_ << "\n";
}

void Archiver::readTable(std::ifstream &in, std::map<char, unsigned int> &freq){
    unsigned int num;
    in.read((char*)&num, 4);
    char c;
    unsigned int f;
    for (unsigned int i = 0; i < num; i++){
        in.read(&c, 1);
        in.read((char*)&f, 4);
        freq[c] = f;
    }
    table_size_ = 5 * num + 4;
}

void Archiver::writeTable(std::ofstream &out, const std::map<char, unsigned int> &freq){
    unsigned int num = freq.size();
    out.write((char*)&num, 4);
    unsigned int f;
    char c;
    for (std::map<char, unsigned int>::const_iterator it = freq.begin(); it != freq.end(); it++){
        c = it -> first;
        f = it -> second;
        out.write(&c, 1);
        out.write((char*)&f, 4);
    }
    table_size_ = 5 * num + 4;
}

Archiver::HuffmanTree::HuffmanTree(const std::map<char, unsigned int> &freq){

    if (freq.size() == 1){
        TreeNode *v = new TreeNode(freq.begin() -> first, freq.begin() -> second, NULL, NULL);
        root = new TreeNode(0, 0, v, NULL);
        return;
    }

    std::vector<char> chars;
    std::vector<TreeNode*> nodes;
    std::set<pair<unsigned int, unsigned int> > st;
    for (std::map<char, unsigned int>::const_iterator it = freq.begin(); it != freq.end(); it++){
        st.insert(make_pair(it -> second, chars.size()));
        chars.push_back(it -> first);
        nodes.push_back(new TreeNode (it -> first, it -> second, NULL, NULL));
    }

    while (st.size() != 2){
        pair<unsigned int, unsigned int> fst = *st.begin();
        st.erase(st.begin());
        pair<unsigned int, unsigned int> sec = *st.begin();
        st.erase(st.begin());
        st.insert(make_pair(fst.first + sec.first, nodes.size()));
        nodes.push_back(new TreeNode(0, fst.first + sec.first, nodes[fst.second], nodes[sec.second]));
    }

    pair<unsigned int, unsigned int> fst = *st.begin();
    st.erase(st.begin());
    pair<unsigned int, unsigned int> sec = *st.begin();
    root = new TreeNode(0, 0, nodes[fst.second], nodes[sec.second]);
}

Archiver::HuffmanTree::~HuffmanTree(){
    if (root)
        root -> delNodes();
}

void Archiver::HuffmanTree::getCodes(std::map<char, std::vector<char> > &codes){
    if (root -> isLeaf()){
        codes[root -> c].push_back(0);
        return;
    }
    std::vector<char> cur;
    calcCodes(root, cur, codes);
}

void Archiver::HuffmanTree::calcCodes(TreeNode *v, std::vector<char> &cur, std::map<char, std::vector<char> > &codes){
    if (v -> isLeaf()){
        codes[v -> c] = std::vector<char>();
        codes[v -> c].insert(codes[v -> c].end(), cur.begin(), cur.end());
        return;
    }
    if (v -> left){
        cur.push_back(0);
        calcCodes(v -> left, cur, codes);
        cur.pop_back();
    }
    if (v -> right){
        cur.push_back(1);
        calcCodes(v -> right, cur, codes);
        cur.pop_back();
    }
}

Archiver::HuffmanTree::TreeNode::TreeNode(char c, unsigned int freq, TreeNode *l, TreeNode *r):
                                                                c(c), freq(freq), left(l), right(r){}

bool Archiver::HuffmanTree::TreeNode::isLeaf() const{
    return (left == NULL && right == NULL);
}

bool Archiver::HuffmanTree::TreeNode::canGo(bool bit) const{
    if (bit == 0)
        return (left != NULL);
    else
        return (right != NULL);
}

Archiver::HuffmanTree::TreeNode* Archiver::HuffmanTree::TreeNode::go(bool bit) const{
    if (bit == 0)
        return left;
    else
        return right;
}

void Archiver::HuffmanTree::TreeNode::delNodes(){
    if (left)
        left -> delNodes();
    if (right)
        right -> delNodes();
    delete this;
}
