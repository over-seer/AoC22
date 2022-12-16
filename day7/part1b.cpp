#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
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


void parse(string fn, set<string> & dirs, vector<string> & paths, vector<size_t> & sizes )
{
  auto ip = read_ip(fn);
  std::vector<string> path;
  path.push_back("/");
  for(string s : ip)
  {
    if(s[0]=='$')
    {
      string command = s.substr(2,2);
      if(command=="cd")
      {
        string arg = s.substr(5);
        if(arg=="/")
        {
          path.clear();
          path.push_back("/");
        }
        else if(arg=="..")
          path.pop_back();
        else
          path.push_back(arg);
      }
    }
    else
    {
      stringstream ss(s);
      string arg1, arg2;
      if(ss >> arg1 >> arg2)
      {
        if(arg1 == "dir")
        {
          string addr;
          for(string str : path)
            addr = addr + str + "/";
          dirs.insert(addr+arg2);
        }
        else
        {
          string addr;
          for(string str : path)
            addr = addr + str + "/";
          addr += arg2;
          paths.push_back(addr);
          sizes.push_back(atoi(arg1.c_str()));
        }
      }
      else{cout << "ERROR " << s << endl;exit(1);}
    }
  }
}

void sum_less_than(string fn, size_t lim)
{
  //build directory structure
  vector<string> paths;
  vector<size_t> sizes;
  set<string> dirs;
  parse(fn,dirs,paths,sizes);
  
  ofstream file(fn+".csv");
  for(size_t i=0; i<paths.size(); i++)
    file << paths[i] << ", " << sizes[i] << endl;
  file.close();

  size_t sum =0;
  vector<size_t> dirsizes;
  for(string dir : dirs)
  {
    cout << dir << endl;
    size_t sz=0;
    for(size_t i=0; i<paths.size(); i++)
    {
      if (paths[i].find(dir) != string::npos)
        sz+=sizes[i];
    }
    if(sz <= 100000) sum+=sz;
    dirsizes.push_back(sz);
  }
  cout << "Part 1 " << fn << " = " << sum << endl;

  size_t root_size = accumulate(sizes.begin(),sizes.end(),0);
  size_t unused = 70000000 - root_size;
  size_t req_space = 30000000 - unused;

  cout << "required space " << req_space << endl;

  sort(dirsizes.begin(),dirsizes.end());

  for(size_t n : dirsizes)
  {
    if(n>=req_space)
    {
      cout << "Part 2 " << fn << " = " << n << endl;
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
