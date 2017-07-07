#pragma once
//#include <mutex>
#include <string>
#include <thread>
#include <iostream>
#include <fstream>
#include <mutex>
using namespace std;

# define ALPHABET 26

enum SYNC
{
    DELETE,WRITE,READ
};
class Node
{
public:
  //Node* parent;
  Node* children[ALPHABET];
  string word;
  size_t count;
  bool sync[3];
  bool isLeaf;
  bool isWord;
  bool readworkingHere;
  bool writeworkingHere;
  bool delworkingHere;
  ofstream file;
  string file_name;
  Node()
  {
    //file=NULL;
    count=1;
    sync[DELETE]=false;
    sync[WRITE]=false;
    sync[READ]=false;
    isLeaf=true;
    readworkingHere=false;
    writeworkingHere=false;
    delworkingHere=false;
  }
};

class Trie
{
  mutex wod; // write or delete
  size_t read_size;
  size_t write_size;
  size_t del_size;
  size_t read_count;
  size_t write_count;
  size_t del_count;
  void insert(string str,string url);
  void del(string str);
  Node* find(string str);
  Node* search(string str);
//  mutex mu;
//  ostream stream //
public:
//  friend class threadPool;
  Node* root;
  //threadPool *tp;
  size_t wordCount;
  Trie();
  // ~Trie()
  // {
  //   Node* n=root;
  //   Node* next=n;
  // }
  void go(SYNC type, string str,string url="NULL");
  void setSize(SYNC type, size_t size);
};
