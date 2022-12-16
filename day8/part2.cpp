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

int ctoi(char c){return (size_t)(c - '0');}

template<typename T>
class Array2d
{
public:
  vector<T> data_;
  size_t n1_=0;
  size_t n2_=0;
public:
  Array2d(){}
  Array2d(size_t n1, size_t n2){resize(n1,n2);}
  auto & operator()(size_t i, size_t j){return data_[n2_*i+j];}
  void  resize(size_t n1, size_t n2)
  {
    if(n1!=n1_ || n2!=n2_)
    {
      n1_=n1;
      n2_=n2;
      data_.resize(n1*n2);
    }
  }
  void fill(T v){for(auto & e : data_)e=v;}
  auto begin(){return data_.begin();}
  auto end(){return data_.end();}
  void print()
  {
    for(size_t i=0;i<n1_;i++)
    {
      for(size_t j=0;j<n2_;j++)
        cout << (*this)(i,j);
      cout << endl;
    }
  }
      
};

int score(Array2d<int> & hts, int i0, int j0)
{
  int n1 = hts.n1_;
  int n2 = hts.n2_;
  int ht = hts(i0,j0);
  int product = 1;
  int n, hlast, hnow;

  if(i0 == 0 || i0 == n1 - 1 || j0 == 0 || j0 == n2-1) return 0;

  n=0;
  for(int i = i0 + 1; i<n1; i++)
  {
    hnow = hts(i,j0);
    n++;
    if(hnow >= ht) break;
  }
  product *= n;
  n=0;
  for(int i = i0 - 1; i>-1; i--)
  {
    hnow = hts(i,j0);
    n++;
    if(hnow >= ht) break;
  }
  product *= n;
  n=0;
  for(int j = j0 + 1; j<n2; j++)
  {
    hnow = hts(i0,j);
    n++;
    if(hnow >= ht) break;
  }
  product *= n;
  n=0;
  for(int j = j0 - 1; j>-1; j--)
  {
    hnow = hts(i0,j);
    n++;
    if(hnow >= ht) break;
  }
  product *= n;

  return product;
}


void part2(string fn)
{
  auto ip = read_ip(fn);

  size_t n1 = ip.size();
  size_t n2 = ip[0].size();
  Array2d<int> scores(n1,n2);
  Array2d<int> hts(n1,n2);

  for(size_t i=0; i<n1; i++)
    for(size_t j=0; j<n2; j++)
      hts(i,j)=ctoi(ip[i][j]);

  for(int i=0; i<n1; i++)
    for(int j=0; j<n2; j++)
    {
      int n = score(hts,i,j);
      scores(i,j) = n;
    }
  
  int maxscore = *max_element(scores.begin(),scores.end());
  
  cout << fn << " Part 2 = " << maxscore << endl;
}

int main()
{
  part2("input.txt");
  part2("test.txt");

  return 0;
}
