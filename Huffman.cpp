#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include "huff.hpp"

using namespace std;

map <char, string> codes;

HuffTree::HuffTree(int size)
{
  currentQueueSize = 0;

  maxQueueSize = size;
  priorityQueue = new letters*[maxQueueSize];

}

HuffTree::~HuffTree()
{
  delete [] priorityQueue;
}

bool HuffTree::isFull()
{
  if(currentQueueSize == 26)
  {
    cout << "Priority Queue full. File Ready to be Compressed" << endl;
    return true;
  }
  else
  {
    return false;
  }
}


void swap(letters **x, letters **y)
{
  letters *temp = *x;
  *x = *y;
  *y = temp;
}
letters* HuffTree::newletter(char let, int freq) {
  letters *temp = new letters();
  temp->letter = let;
  temp->count = freq;
  temp->left = temp->right = temp->parent = NULL;
  return temp;
}

void HuffTree::enqueue(char letter[], int count[])
{
  if(isFull())
  {
    return;
  }

  for (int i = 0; i < maxQueueSize; i++) {
    priorityQueue[i] = newletter(letter[i], count[i]);
    currentQueueSize++;
  }
  repairUpward();

  return;
}

void HuffTree::repairUpward() {

  int parent = maxQueueSize - 1;
  int i;
    for(i = (parent - 1) / 2; i >= 0; --i) {

      repairDownward(i);
    }


}
letters* HuffTree::dequeue() {
  letters *temp = priorityQueue[0];
  priorityQueue[0] = priorityQueue[currentQueueSize - 1];
  currentQueueSize--;

  repairDownward(0);
  return temp;

}

void HuffTree::repairDownward(int index) {


    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < currentQueueSize && priorityQueue[left]->count < priorityQueue[smallest]->count)
        smallest = left;

    if (right < currentQueueSize && priorityQueue[right]->count < priorityQueue[smallest]->count)
        smallest = right;

    if (smallest != index) {
        swap(&priorityQueue[smallest], &priorityQueue[index]);
        repairDownward(smallest);
    }

}


void HuffTree::BuildTree(letters *parent) {

  currentQueueSize++;
  int i = currentQueueSize - 1;

    while (i && parent->count < priorityQueue[(i - 1) / 2]->count) {

        priorityQueue[i] = priorityQueue[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    priorityQueue[i] = parent;

}



letters* HuffTree::Huffman(){
  letters *left;
  letters *right;
  letters *parent;


  while (currentQueueSize != 1) {


    left = dequeue();
    right = dequeue();

    parent = newletter('$', left->count + right->count);


    parent->left = left;
    parent->right = right;

    BuildTree(parent);


  }

  return dequeue();
}


void HuffTree::printCodes(letters *root, int array[], int space)
{

  if (root->left) {

        array[space] = 0;
        printCodes(root->left, array, space + 1);
    }


    if (root->right) {

        array[space] = 1;
        printCodes(root->right, array, space + 1);
    }

    if (isLeaf(root)) {


        cout << root->letter << ": ";

        printArray(array, space);



    }

}

string HuffTree::printArray(int array[], int length)
{

  string str;
    for (int i = 0; i < length; ++i){
        str += to_string(array[i]);
        cout << array[i];
      }
    cout << endl;


    return str;

}

bool HuffTree::isLeaf(letters *root)

{
    if (root->left == NULL && root->right == NULL) {
      return true;
    }
    else {
      return false;
    }

}

void storeCodes(letters *root, string str)
{
    if (root==NULL)
        return;
    if (root->letter != '$')
        codes[root->letter]=str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

int HuffTree::maxDepth(letters* root)
{
   if (root==NULL)
       return 0;
   else
   {

       int lDepth = maxDepth(root->left);
       int rDepth = maxDepth(root->right);


       if (lDepth > rDepth)
           return(lDepth+1);
       else return(rDepth+1);
   }
}

void HuffTree::printq(string code) {



  root = Huffman();

  int height = maxDepth(root);
  cout << height << endl;
  

  int array[height];
  printCodes(root, array, 0);
  storeCodes(root, "");
  return;

}


int main (int argc, char *argv[]) {
  char array[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', '"', '.', ',', '!', '?'};
  int array2[6] = {0};
  HuffTree ht(32);
  string filename = argv[1];
  ifstream data;
  data.open(filename.c_str());
  int letcount[32] = {0};
  string temp;
  string tarp[125];
  int i = 0;
  if(data.is_open()) {

      while (getline(data, temp)) {
          char eachletter;
          for(int i = 0; i < temp.length(); i++) {
            eachletter = char(temp[i]);

            if(eachletter >= 'a' && eachletter <= 'z') {
              letcount[int(eachletter)- 'a']++;

            }
            if (eachletter == ' '){
              array2[0]++;
            }
            if (eachletter == '"'){
              array2[1]++;
            }
            if (eachletter == '.'){
              array2[2]++;
            }
            if (eachletter == ','){
              array2[3]++;
            }
            if (eachletter == '!'){
              array2[4]++;
            }
            if (eachletter == '?'){
              array2[5]++;
            }


          }
          tarp[i] = temp;
          i++;

      }
      data.close();
    }

    letcount[26] = array2[0];
    letcount[27] = array2[1];
    letcount[28] = array2[2];
    letcount[29] = array2[3];
    letcount[30] = array2[4];
    letcount[31] = array2[5];

    string encodedString;
    ht.enqueue(array, letcount);

    cout << temp << endl;
    ht.printq(temp);

    //string encodedString[125];
    /*for (int j = 0; j < 125; j++) {
      for (int i = 0; i < tarp[j].length(); i++) {
        encodedString[j]+=codes[i];
        cout << encodedString[j] << endl;
      }
    }*/

    string part;
    data.open(filename.c_str());
    if(data.is_open()) {

        while (getline(data, part)) {
          for (auto i : part)
            encodedString += codes[i];

          cout << encodedString << endl;
          cout << part << endl;
        }

    data.close();
  }
}
