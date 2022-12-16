#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdio>

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

deque<uintmax_t> get_items(string s)
{
  deque<uintmax_t> items;
  stringstream ss(s.substr(18));
  string str1, str2;
  while(ss >> str1)
  {
    if(str1.find(",")!=string::npos) str1.pop_back();
     uintmax_t n = atoi(str1.c_str());
     items.push_back(n);
  }
  return items;
}

void get_operation(string s, char & op, string & n)
{
  op = s[23];
  n = s.substr(25);
}

void get_test(string s, uintmax_t & n)
{
  stringstream ss(s);
  string s1, s2, s3;
  ss >> s1 >> s2 >> s3 >> n;
}

void get_monkey(string s, uintmax_t & n)
{
  stringstream ss(s);
  string s1, s2, s3, s4, s5;
  ss >> s1 >> s2 >> s3 >> s4 >> s5 >> n;
}

class Monkey
{
public:
  deque<uintmax_t> items;
  char op = '+';
  string operand;
  uintmax_t test = 1;
  uintmax_t monkey_true = 0;
  uintmax_t monkey_false = 0;
  size_t inspected = 0;
  void parse(vector<string> & ip)
  {
    //for(string s : ip) cout << s << endl;
    items = get_items(ip[1]);
    get_operation(ip[2],op,operand);
    get_test(ip[3],test);
    get_monkey(ip[4],monkey_true);
    get_monkey(ip[5],monkey_false);
  }
};


void parse_ip(string fn, vector<Monkey> & monkeys)
{
  auto ip = read_ip(fn);
  Monkey m;
  for(size_t i=0; i<ip.size(); i+=7)
  {
    vector<string> section(6);
    copy(ip.begin()+i,ip.begin()+i+6,section.begin());
    m.parse(section);
    monkeys.push_back(m);
  }

  for(Monkey & m : monkeys)
  {
    for(uintmax_t i : m.items) cout << i << ", ";
    cout << " " << m.op << " " << m.operand << " " << m.test << " " << m.monkey_true << " " << m.monkey_false << endl;
  }

}

void round(vector<Monkey> & monkeys, uintmax_t factor)
{
  for(Monkey & m : monkeys)
  {
    m.inspected+=m.items.size();
    for(uintmax_t worry : m.items)
    {
      uintmax_t operand = m.operand=="old" ? worry : atoi(m.operand.c_str());
      if(m.op=='+') worry += operand;
      else worry *= operand;

      if(factor != 0) worry /= factor;

      uintmax_t recipient = worry%m.test == 0?  m.monkey_true : m.monkey_false;

      monkeys[recipient].items.push_back(worry);
    }
    m.items.clear();
  }
}

void play(string fn, size_t nrounds, uintmax_t factor)
{
  vector<Monkey> monkeys;
  parse_ip(fn,monkeys);
  for(size_t iturn=0; iturn<nrounds; iturn++)
    round(monkeys,factor);

  vector<size_t> inspected(monkeys.size(),0);
  for(size_t i = 0;i<monkeys.size();i++)
    inspected[i]=monkeys[i].inspected;

  sort(inspected.begin(),inspected.end());

  for(Monkey & m : monkeys) cout << m.inspected << endl;

  size_t monkey_business = *(inspected.end()-1) * *(inspected.end()-2);

  cout << fn << " after " << nrounds << " rounds and worry factor of " << factor << " monkey business = " << monkey_business << endl;

    
}

int main()
{
  play("input.txt",20,3);
  play("test.txt",20,3);

  play("input.txt",10000,1);
  play("test.txt",10000,1);

  return 0;
}
