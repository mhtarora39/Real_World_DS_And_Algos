#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

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

int main()
{
  std::string eque("1+2-3-(12-3)");
  InterPreter par(eque);
  auto tokens = par.lex();
  for (auto item : tokens)
  {
    std::cout << item.text << " ";
  }

  std::cout << std::endl;

  return 0;
}
