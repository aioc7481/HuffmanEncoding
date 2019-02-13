#ifndef HUFF_HPP
#define HUFF_HPP

#include <iostream>
using namespace std;

struct letters{
  char letter;
  int count;
  letters *left;
  letters *right;
  letters *parent;

};

class HuffTree {

public:
  HuffTree(int size);
  ~HuffTree();

  void enqueue(char letter[], int count[]);
  letters* Huffman();
  letters* dequeue();
  void BuildTree(letters *parent);

  void repairUpward();
  void repairDownward(int index);

  void printq(string code);
  bool isFull();
  bool isLeaf(letters *root);

  letters* newletter(char let, int freq);

  void printCodes(letters *root, int array[], int space);
  //void storeCodes(letters *root, string str);
  string decode_file(letters *root, string str);
  int maxDepth(letters* root);
  string printArray(int array[], int length);
  int maxQueueSize;
  string codes[32];
  letters *root;

  int currentQueueSize;
  letters** priorityQueue;
  //char array3[32] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q','r','s', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', '"', '.', ',', '!', '?'};
  void FindCodes(letters* root, char letter);
  //void StoreCodes(letters* root, int i, char arr[]);
};

#endif
