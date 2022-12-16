#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;

vector<string> read_ip(string s)
{
  vector<string> lines;
  string line;
  ifstream ip(s);
  while(getline(ip,line))
    lines.push_back(line);
  return lines;
}


class Dir
{
public:
  Dir * root = this;
  Dir * parent = nullptr;
  string address = "/";
  map<string,Dir> subs;
  map<string,size_t> files;

  Dir() {}
  Dir(Dir * r, Dir * p, string s) : root(r),parent(p),address(s){}

  void mkdir(string s)
  {
    if(subs.find(s) == subs.end())
    {
      Dir d(root,this,address+s);
      subs[s]=d;
    }
  }

  Dir * cd(string s)
  {
    if(s=="..") return parent;
    else if(s=="/") return root;
    else
    {
      try
      {
        return &(subs.at(s));
      }
      catch(...)
      {
        cout << "ERROR - no directory " << s << '\n';
        exit(1);
      }
    }
    return this;
  }

  void touch(string s, size_t n){files[s]=n;}

  size_t size(map<string,size_t> & sizes) const
  {
    size_t n=0;
    for(const auto & f : files) n+=f.second;
    for(const auto & d : subs)
    {
      size_t subsize = d.second.size(sizes);
      sizes[d.second.address] = subsize;
      n += subsize;
    }
    return n;
  }

  void print()
  {
    for(auto f : files) cout << f.first << " " << f.second << endl;
    for(auto d : subs)
    {
      cout << "/" << d.first << endl;
      d.second.print();
    }
  }
  
};

void parse(Dir & dir, string fn)
{
  auto ip = read_ip(fn);
  Dir * dir_ptr = &dir;
  for(string s : ip)
  {
    if(s[0]=='$')
    {
      string command = s.substr(2,2);
      if(command=="cd") dir_ptr=dir_ptr->cd(s.substr(5));
    }
    else
    {
      stringstream ss(s);
      string arg1, arg2;
      if(ss >> arg1 >> arg2)
      {
        if(arg1 == "dir")dir_ptr->mkdir(arg2);
        else
        {
          size_t sz = atoi(arg1.c_str());
          dir_ptr->touch(arg2,sz);
        }
      }
      else{cout << "ERROR " << s << endl;exit(1);}
    }
  }
}

void sum_less_than(string fn, size_t lim)
{
  //build directory structure
  Dir root_dir;
  parse(root_dir,fn);

  map<string,size_t> sizes;
  size_t root_size = root_dir.size(sizes);

  for(auto p : sizes)
    cout << p.first << ", " << p.second << endl;


  size_t sum=0;
  for(auto p : sizes)
    if(p.second <= lim) sum+=p.second;
  cout << "Part 1 = " << fn << " = " << sum << endl;

  size_t req_space = 30000000 - (70000000 - root_size);
  cout << "required space " << req_space << endl;
  vector<size_t> nlist;
  for(auto p : sizes) nlist.push_back(p.second);
  sort(nlist.begin(),nlist.end());

  for(size_t n : nlist)
  {
    if(n>=req_space)
    {
      cout << "Part 2 = " << n << endl;
      break;
    }
  }

}


int main()
{
  sum_less_than("input.txt",100000);
  sum_less_than("test.txt",100000);

  return 0;
}
