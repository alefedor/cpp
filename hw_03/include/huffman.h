#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <vector>
#include <ostream>
#include <istream>
#include <fstream>
#include <exception>
#include <map>

typedef std::runtime_error ArchiverException;

class Archiver{
 public:
    void pack(std::ifstream &in, std::ofstream &out);
    void unpack(std::ifstream &in, std::ofstream &out);
    void printStat();

 private:

    void readTable(std::ifstream &in, std::map<char, unsigned int> &freq);
    void writeTable(std::ofstream &out, const std::map<char, unsigned int> &freq);

    class HuffmanTree{
     public:
        class TreeNode{
         public:
            char c;
            unsigned int freq;
            TreeNode *left, *right;

            TreeNode(char c, unsigned int freq, TreeNode *l, TreeNode *r);
            bool isLeaf() const;
            bool canGo(bool bit) const;
            TreeNode* go(bool bit) const;

            void delNodes();
        };

        TreeNode *root;

        HuffmanTree(const std::map<char, unsigned int> &freq);
        ~HuffmanTree();
        void getCodes(std::map<char, std::vector<char> > &codes);

     private:
        void calcCodes(TreeNode *v, std::vector<char> &cur, std::map<char, std::vector<char> > &codes);

        HuffmanTree(const HuffmanTree &t);
        void operator=(const HuffmanTree &t);
    };

    class BitWriter{
     public:
        BitWriter(std::ofstream &out);
        ~BitWriter();
        int writeBit(bool bit);
        int flush();

     private:
        std::ofstream &out;
        std::vector<char> buf;
        BitWriter(const BitWriter &b);
        void operator=(const BitWriter &b);
    };

    unsigned int before_size_, after_size_, table_size_;
};

#endif
