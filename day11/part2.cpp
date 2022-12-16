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

deque<uint64_t> get_items(string s)
{
  deque<uint64_t> items;
  stringstream ss(s.substr(18));
  string str1, str2;
  while(ss >> str1)
  {
    if(str1.find(",")!=string::npos) str1.pop_back();
     uint64_t n = atoi(str1.c_str());
     items.push_back(n);
  }
  return items;
}

void get_operation(string s, char & op, string & n)
{
  op = s[23];
  n = s.substr(25);
}

void get_test(string s, uint64_t & n)
{
  stringstream ss(s);
  string s1, s2, s3;
  ss >> s1 >> s2 >> s3 >> n;
}

void get_monkey(string s, uint64_t & n)
{
  stringstream ss(s);
  string s1, s2, s3, s4, s5;
  ss >> s1 >> s2 >> s3 >> s4 >> s5 >> n;
}

class Monkey
{
public:
  deque<uint64_t> items;
  char op = '+';
  string operand;
  uint64_t test = 1;
  uint64_t monkey_true = 0;
  uint64_t monkey_false = 0;
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


uint64_t parse_ip(string fn, vector<Monkey> & monkeys)
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

  uint64_t test_product = 1;
  for(Monkey & m : monkeys)
  {
    test_product *= m.test;
    for(uint64_t i : m.items) cout << i << ", ";
    cout << " " << m.op << " " << m.operand << " " << m.test << " " << m.monkey_true << " " << m.monkey_false << endl;
  }
  return test_product;
}

void round(vector<Monkey> & monkeys, uint64_t test_product, uint64_t factor)
{
  for(Monkey & m : monkeys)
  {
    m.inspected+=m.items.size();
    for(uint64_t worry : m.items)
    {
      uint64_t operand = m.operand=="old" ? worry : atoi(m.operand.c_str());
      if(m.op=='+') worry += operand;
      else worry *= operand;

      if(factor != 0) worry /= factor;

      uint64_t recipient = worry%m.test == 0?  m.monkey_true : m.monkey_false;

      monkeys[recipient].items.push_back(worry);
    }
    m.items.clear();
  }
  for(Monkey & m : monkeys)
    for(uint64_t & item : m.items)
      item%=test_product;
}

void play(string fn, size_t nrounds, uint64_t factor)
{
  vector<Monkey> monkeys;
  uint64_t test_product = factor*parse_ip(fn,monkeys);
  for(size_t iturn=0; iturn<nrounds; iturn++)
    round(monkeys,test_product,factor);

  vector<size_t> inspected(monkeys.size(),0);
  for(size_t i = 0;i<monkeys.size();i++)
    inspected[i]=monkeys[i].inspected;

  sort(inspected.begin(),inspected.end());

  for(Monkey & m : monkeys) cout << m.inspected << endl;

  uint64_t mb1 = *(inspected.end()-1);
  uint64_t mb2 = *(inspected.end()-2);

  uint64_t monkey_business = mb1 * mb2;

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
