#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <vector>
#include <deque>
#include <array>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <cmath>

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


template<typename T>
class Array2d
{
  vector<T> data_;
  size_t n1_=0;
  size_t n2_=0;
public:
  Array2d(){}
  Array2d(size_t n1, size_t n2){resize(n1,n2);}
  Array2d(size_t n1, size_t n2, T v){resize(n1,n2);fill(v);}

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
  size_t ni(){return n1_;}
  size_t nj(){return n2_;}
      
};


void dijkstra(int i, int j, int i1, int j1, Array2d<int> & hts, Array2d<int> & dists)
{
  int inew, jnew;

  int dist = dists(i,j);
  int ni = hts.ni();
  int nj = hts.nj();

  //cout << i << "," << j << " dist " << dist << endl;

  if(i==i1 && j==j1) return;

  //UP
  inew = i+1; jnew=j;
  if(dists(inew,jnew)>dist+1)
  {
    if(inew>=0 && inew < ni && jnew>=0 && jnew< nj && hts(inew,jnew) <= hts(i,j)+1)
    {
      dists(inew,jnew)=dist+1;
      dijkstra(inew,jnew,i1,j1,hts,dists);
    }
  }

  //RIGHT
  inew = i; jnew=j+1;
  if(dists(inew,jnew)>dist+1)
  {
    if(inew>=0 && inew < ni && jnew>=0 && jnew< nj && hts(inew,jnew) <= hts(i,j)+1)
    {
      dists(inew,jnew)=dist+1;
      dijkstra(inew,jnew,i1,j1,hts,dists);
    }
  }

  //DOWN
  inew = i-1; jnew=j;
  if(dists(inew,jnew)>dist+1)
  {
    if(inew>=0 && inew < ni && jnew>=0 && jnew< nj && hts(inew,jnew) <= hts(i,j)+1)
    {
      dists(inew,jnew)=dist+1;
      dijkstra(inew,jnew,i1,j1,hts,dists);
    }
  }

  //LEFT
  inew = i; jnew=j-1;
  if(dists(inew,jnew)>dist+1)
  {
    if(inew>=0 && inew < ni && jnew>=0 && jnew< nj && hts(inew,jnew) <= hts(i,j)+1)
    {
      dists(inew,jnew)=dist+1;
      dijkstra(inew,jnew,i1,j1,hts,dists);
    }
  }

}


void play(string fn)
{
  auto ip = read_ip(fn);

  int ni = ip.size();
  int nj = ip[0].size();

  Array2d<int> hts(ni,nj,0);
  Array2d<int> dists(ni,nj,ni*nj*2);

  int i0,j0,i1,j1;

  for(size_t i=0; i<ni; i++)
  {
    for(size_t j=0; j<nj; j++)
    {
      char c = ip[i][j];
      if(c=='S')
      {
        i0=i;j0=j;c='a';
      }
      else if(c=='E')
      {
        i1=i;j1=j;c='z';
      }
      int ht = (int)(c-'a');
      hts(i,j)=ht;
    }
  }

  dists(i0,j0)=0;

  dijkstra(i0,j0,i1,j1,hts,dists);

  int answer = dists(i1,j1);

  cout << fn << " Part 1 answer = " << answer << endl;

}

int main()
{
  play("input.txt");
  play("test.txt");

  return 0;
}
