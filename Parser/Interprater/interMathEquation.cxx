#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <map>
#include <algorithm>

class Token
{
public:
  enum Type
  {
    Integer,
    Plus,
    minus,
    lparser,
    rparser
  } type;
  std::string text;

  Token(Type typ, std::string txt) : type(typ), text(txt)
  {
  }
};

class InterPreter
{
  std::string equation;

public:
  InterPreter(std::string equ) : equation(equ)
  {
  }

  void compute(int &result)
  {
  }

  std::vector<Token> lex()
  {
    std::vector<Token> tokens;
    for (int i = 0; i < equation.size(); i++)
    {
      switch (equation[i])
      {

      case '(':
        tokens.push_back(Token(Token::lparser, "("));
        break;

      case ')':
        tokens.push_back(Token(Token::rparser, ")"));
        break;

      case '-':
        tokens.push_back(Token(Token::minus, "-"));
        break;

      case '+':
        tokens.push_back(Token(Token::Plus, "+"));
        break;

      default:
        std::stringstream stream;
        stream << equation[i];

        for (int j = i + 1; j < equation.size();)
        {
          if (isdigit(equation[j]))
          {
            stream << equation[j];
            j++;
            i++;
          }
          else
          {
            tokens.push_back(Token(Token::Integer, stream.str()));
            break;
          }
        }

        break;
      }
    }
    return tokens;
  }
};

#include "Graph.hpp"

int CalculateBadTrip(int p, int q, int r)
{
  int count = 0;

  //if (p == q || q == r || p == r)

  auto sum = p + q + r;
  if (sum % p == 0 && sum % q != 0 && sum % r != 0 ||
      sum % p != 0 && sum % q == 0 && sum % r != 0 ||
      sum % p != 0 && sum % q != 0 && sum % r == 0)
  {
    return 1;
  }
  // if (sum % p == 0 && sum % q == 0 && sum % r == 0)
  // {
  //   return 1;
  // }
  // else if (sum % p == 0 && sum % q == 0 ||
  //          sum % q == 0 && sum % r == 0 ||
  //          sum % p == 0 && sum % r == 0)
  // {

  //   if (p == q || q == r || p == r)
  //   {
  //     return 1;
  //   }
  // }
  return 0;
}

int FindThree(std::vector<int> &Combi)
{
  std::map<int, bool> mapUnique;
  int count = 0;
  std::vector<std::vector<int>> triplet;
  std::vector<bool> v(Combi.size());
  std::vector<int> tmp;
  std::fill(v.end() - 3, v.end(), true);
  do
  {
    for (int i = 0; i < Combi.size(); i++)
    {
      if (v[i])
        tmp.push_back(Combi[i]);
        }
    std::cout << tmp[0] << "," << tmp[1] << "," << tmp[2] << std::endl;
    std::cout << tmp[0] + tmp[1] + tmp[2] << "\n";

    count += CalculateBadTrip(tmp[0], tmp[1], tmp[2]);
    tmp.clear();

  } while (std::next_permutation(Combi.begin(), Combi.end()));

  return count;
}

int main()
{
  std::string eque("1+2-3-(12-3)");
  InterPreter par(eque);
  auto tokens = par.lex();
  for (auto item : tokens)
  {
    std::cout << item.text << " "; //<< std::endl;
    ;
  }
  std::cout << "\n";
  std::vector<int> num{1, 2, 3, 1};
  std::cout << "Sum : " << FindThree(num) << std::endl;

  std::vector<bool> v(4);
  std::fill(v.end() - 3, v.end(), true);
  // int c = 0;
  // do
  // {
  //   for (int i = 0; i < 4; i++)
  //   {
  //     if (v[i])
  //       std::cout << " " << num[i] << " ";
  //   }
  //   c++;
  //   std::cout << std::endl;

  // } while (std::next_permutation(num.begin(), num.end()));
  // std::cout << c << std::endl;
  // std::cout << "-----------" << std::endl;
  // Graph<int> a(1);
  // Graph<int> b(2);
  // Graph<int> c(3);
  // Graph<int> d(4);
  // a.AddEdge(b);
  // b.AddEdge(c);
  // c.AddEdge(d);
  // b.AddEdge(d);

  // c.DFSTest(a);

  // std::cout << std::endl;

  // return 0;
}
