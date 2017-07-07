//This program takes spider files and puts it in the archive
//"WORDS.RECORD.URL: "

#include <iostream>
#include <fstream>
#include <string>
#include "trie.cpp"

#pragma once

#define PREF "WORDS.RECORD.URL: "

using namespace std;

class Convert {
  ifstream file;
  string pref = PREF;
  size_t pref_len = pref.length();
public:
  Convert(string fname);
  void write();
};

Convert::Convert(string fname)
{
  file.open(fname);
}


void Convert::write()
{
  string line;
  string url;
  getline(file,line);
  if((line.substr(0,pref_len)).compare(pref) == 0) {
    url = line.substr(pref_len,line.length()-1);
    cout << "\nThe obtained url is: " << url << "\n" << endl;
  }
  else
  {
    cout << PREF << " not found!" << endl;
    return;
  }
  Trie t;
  // t.go(WRITE,line,url);
  // while((line.substr(0,pref_len)).compare(pref) != 0)
  // {
  //   cout << "Writing :" << line << endl;
  //   t.go(WRITE,line,url);
  // }
  while(line != "")
  {
    getline(file,line);
    // sleep(1);
    if((line.substr(0,pref_len)).compare(pref) == 0) {
      url = line.substr(pref_len,line.length()-1);
      cout << "\nThe obtained url is: " << url << "\n" << endl;
      continue;
    }
    else if(line == "") break;
    // sleep(1);
    t.go(WRITE,line,url);
    cout << "adding " << url << " --> " << line << ".txt" << endl;
  }
}

int main()
{
  Convert con("doc.txt");
  con.write();

  while(true){}
  return 0;
}
