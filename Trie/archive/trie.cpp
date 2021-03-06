#include <iostream>
  #include <thread>
  #include <unistd.h>
  #include <cstdio>
  #include "trie.hpp"
  #pragma once
  /////////////////////////////////////////
  #define ASCII_CHAR(C) ((int)C - (int)'a')
  #define def 10
  #define ERAN 0
  ////////////////////////////////////

///////////////////////////////
  Trie::Trie()
  {
    root=new Node;
    root->isLeaf=true;
    wordCount=0;
    read_size=write_size=del_size=def;
    read_count=write_count=del_count=0;
  }
  ////////////////////////////////////
  void Trie::insert(string str,string url)
  {
    if(root==NULL)
    {
      write_count--;
      return /*false*/;
    }
    //wod.lock();
      Node* t=root;
      size_t length=str.length();
      for (size_t i = 0; i < length; i++)
       {
        int index=ASCII_CHAR(str.at(i));
        //std::cout << str.at(i) << "\n";
        // while(t->writeworkingHere || t->delworkingHere){}//std::cout << "waiting on insert" << '\n';}
        // cout << "line 39, i = " << i << << ", "+str << "[i] = " << str[i] << endl;
         //t->writeworkingHere=true;
        if(t->isLeaf)
        {
          t->isLeaf=false;
          t->children[index]=new Node;
        }
        if(t->children[index]==NULL)t->children[index]=new Node;
        t->writeworkingHere=false;
        t=t->children[index];
      }
      // while(t->writeworkingHere || t->delworkingHere){}//std::cout << "waiting on insert" << '\n';}
      //t->writeworkingHere=true;
      if(!(t->isWord))
      {
     // std::cout << "TRYING TO OPEN " << "\n";
      t->file.open("../trie/archive/"+str+".txt");
      //std::cout << "OPENED " << "\n";
      t->file_name="../trie/archive/"+str+".txt";
      //std::cout << "GOT " << "\n";
      t->isWord=true;
      wordCount++;
      }
      t->file<<url<<endl;
      write_count--;
      t->writeworkingHere=false;

     // wod.unlock();
  }
  ////////////////////////////////////
Node* Trie::find(string str)
  {
  if(root==NULL) return NULL;
  Node* t=new Node;
  t=root;
  size_t length=str.length();

  wod.lock();
  for (size_t i = 0; i < length; i++)
   {
    int index=ASCII_CHAR(str.at(i));
    // while(t->delworkingHere || t->writeworkingHere){}//std::cout << "waiting on find" << '\n';}
    // t->delworkingHere=true;
    if(t==NULL || t->isLeaf || t->children[index]==NULL)
    {
      t->delworkingHere=false;
      return NULL;
    }
    t->delworkingHere=false;
    t=t->children[index];
  }
  wod.unlock();
  return t;
}
  ////////////////////////////////////
  void Trie::del(string str)
  {
    Node* n=find(str);
    if(n==NULL)
    {
    del_count--;
    return /*false*/;
    }
    if(n->isWord)
    {
    std::cout <<"removing "<< n->file_name << '\n';
    //n->file.close();
    remove(n->file_name.c_str());
    n->isWord=false;
    wordCount--;
    del_count--;
    return /*true*/;
    }
    del_count--;
    return /*false*/;
  }
  ////////////////////////////////////
  Node* Trie::search(string str)
  {
    Node* n=find(str);
    if(n==NULL || (n!=NULL && n->isWord==false))
    {
      read_count--;
      std::cout << "ERR_404"<< '\n';
      return NULL;
    }
    read_count--;
    std::cout <<str<< '\n';
    return n;
  }
  ///////////////////////////////////
  void Trie::go(SYNC type, string str,string url)
  {
    switch(type)
    {

          case READ:
          {
            while(read_count==read_size)
            {
            // std::this_thread::sleep_for(std::chrono::milliseconds(10));
            // std::cout << "to manny threads waiting.." << '\n';
            }
            {
            std::thread (&Trie::search,this,str).detach();
              read_count++;
              return;
            }
          }

          case WRITE:
          {
            while(write_count==write_size)
            {
            // std::this_thread::sleep_for(std::chrono::milliseconds(10));
            // std::cout << "to manny threads waiting.." << '\n';
            }
            {
              if(url=="NULL")
              {
                std::cout << "invalid url" << '\n';
                return;
              }
                //std::thread (&Trie::insert,this,str,url).detach();
                //std::cout << "ENTERING INSERT" << "\n";
                insert(str,url);
                //std::cout << "RETURNING FROM INSERT" << "\n";
                //write_count++;
                return;
            }
          }

          case DELETE:
          {
            while(del_count==del_size)
            {
            // std::this_thread::sleep_for(std::chrono::milliseconds(10));
            // std::cout << "to manny threads waiting.." << '\n';
            }
            {
              std::thread (&Trie::del,this,str).detach();
              del_count++;
              return;
            }
          }
          default:
          return;
    }
 }
  ////////////////////////////////////
    void Trie::setSize(SYNC type, size_t size)
    {
      switch(type)
      {

          case READ:
          {
              read_count=size;
          }

          case WRITE:
          {
              write_count=size;
          }

          case DELETE:
          {
              del_count=size;
          }
      }
   }
/////////////////////////////////////////////


///////////////////////////////////////

////////////////////////////////////////
  // int main(int argc, char const *argv[])
  //  {
  //     Trie t2;
  //     t2.go(WRITE,"eran","www.eran 1.com" );
  //     t2.go(WRITE,"dima","www.dima 1.com" );
  //     t2.go(WRITE,"shai","www.shai.com" );
  //     t2.go(WRITE,"damir","www.damir.com");
  //     t2.go(WRITE,"eran" ,"www.eran 2.com");
  //     t2.go(WRITE,"ernan","www.ernan.com");
  //     t2.go(WRITE,"eran" ,"www.eran 3.com");
  //     t2.go(WRITE,"dima" ,"www.dima 2.com");
  //     t2.go(WRITE,"eran" ,"www.eran 4.com");
  //     t2.go(WRITE,"eran" ,"www.eran 5.com");
  //     t2.go(WRITE,"dima");
  //     //////////////////////////////////
  //     t2.go(READ,"ernan");
  //     t2.go(READ,"damir");
  //     t2.go(READ,"eran");
  //     t2.go(READ,"shai");
  //     t2.go(READ,"dima");
  //     t2.go(READ,"eteg");
  //     ////////////////////////////////////
  //     sleep(1);
  //     // t2.go(DELETE,"damir");
  //     // t2.go(DELETE,"damir");
  //     // t2.go(DELETE,"jgjgjfjf");
  //     // t2.go(DELETE,"shai");
  //     /////////////////////////////////////
  //     sleep(1);
  //     std::cout << "t2 count ="<<t2.wordCount << '\n';
  //     }
