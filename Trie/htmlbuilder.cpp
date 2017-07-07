#include <iostream>
#include <fstream>

#include "trie.cpp"

using namespace std;

class Builder
{
  ofstream* _out;
  ifstream* _in;
  // Trie _t;
  string _str;
public:
  // Builder(ofstream out, ifstream in): _out(out), _in(in) {}
  Builder(string str);
  void build();
};

Builder::Builder(string str): _str(str)
{
  _in = new ifstream(str+".txt");
  if(!_in->is_open())
  {
    // _t.go(WRITE,str,"");
    return;
  }
  _in = new ifstream(str+".txt");
}

void Builder::build()
{
  _out = new ofstream("html/ret.html");
  ifstream stream("html/start.txt");
  stream.seekg(0, std::ios::end);
  size_t size = stream.tellg();
  string buffer(size, ' ');
  stream.seekg(0);
  stream.read(&buffer[0], size);

  (*_out) << buffer << endl;
  (*_out) << _str << endl;

  ifstream stream2("html/cont1.txt");

  stream2.seekg(0, std::ios::end);
  size = stream2.tellg();
  stream2.seekg(0);
  string buffer2(size, ' ');
  stream2.read(&buffer2[0], size);

  (*_out) << buffer2 << endl;

  string astart = "<a href =";
  string acont = ">";
  string aend = "</a>";

  ifstream name(_str);
  (*_out) << "<h1>Showing results for \"" << _str << "\":<br><br><br></h1>" << endl;
  string line;
  int i = 1;
  while(getline(*_in,line))
  {
    string insert = line.substr(3, line.length());
    (*_out) << astart << insert << acont << "Result number " << i++
    << "  is:                        " << insert << "<br><br>" << aend << endl;
  }

  (*_out) << "</body> </html>" << endl;

  delete _out;
  delete _in;
}

int main()
{
  Builder b("eran");
  b.build();
  return 0;
}
