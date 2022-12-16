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

void part1(string fn)
{
  auto ip = read_ip(fn);

  size_t n1 = ip.size();
  size_t n2 = ip[0].size();
  Array2d<int> bmap(n1,n2);
  Array2d<int> hts(n1,n2);
  bmap.fill(0);

  for(size_t i=0; i<n1; i++)
    for(size_t j=0; j<n2; j++)
      hts(i,j)=ctoi(ip[i][j]);


  for(size_t i=0; i<n1; i++)
  {
    //SIDE 1
    int maxht1 = -1;
    for(size_t j=0; j<n2; j++)
    {
      if(hts(i,j)>maxht1)
      {
        maxht1 = hts(i,j);
        bmap(i,j) = 1;
      }
    }
    //SIDE 2
    int maxht2 = -1;
    for(size_t j=0; j<n2; j++)
    {
      size_t j2 = n2 - j - 1;
      if(hts(i,j2)>maxht2)
      {
        maxht2 = hts(i,j2);
        bmap(i,j2) = 1;
      }
    }
  }
  
  for(size_t j=0; j<n2; j++)
  {
    //SIDE 3
    int maxht1 = -1;
    for(size_t i=0; i<n1; i++)
    {
      if(hts(i,j)>maxht1)
      {
        maxht1 = hts(i,j);
        bmap(i,j) = 1;
      }
    }
    //SIDE 4
    int maxht2 = -1;
    for(size_t i=0; i<n1; i++)
    {
      size_t i2 = n1 - i - 1;
      if(hts(i2,j)>maxht2)
      {
        maxht2 = hts(i2,j);
        bmap(i2,j) = 1;
      }
    }
  }
  size_t sum=0;
  bmap.print();
  for(auto b : bmap)
    if(b==1)sum++;
  

  cout << fn << " Part 1 = " << sum << endl;
}

int main()
{
  part1("input.txt");
  part1("test.txt");

  return 0;
}
