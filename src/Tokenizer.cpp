#include <cctype>
#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
class Tokenizer
{
    private:
        ifstream f;

        enum class TokenType
        {
            Number,
            Identifier,
            Equals,
            OpenParen,
            CloseParen,
            BinaryOp,
            Let,
        };
        struct Token
        {
            std::string value;
            TokenType type;
        };

        std::string shift(std::vector<std::string> &arr)
        {
            std::string ret = arr.front();
            arr.erase(arr.begin());
            return ret;
        }

        bool isNumber(std::string str)
        {
            for (const char &c : str)
            {
                if (!std::isdigit(c)) return false;
            }
            return true;
        }

    public:
        std::vector<std::string> splitString(std::string s)
        {
            std::string word;
            std::vector<std::string> words;
            
            for (const char &c : s)
            {
                if (c != ' ') word += c;
                else if (!word.empty())
                {
                    words.push_back(word);
                    word.clear();
                }
            }
            return words;
        }

        std::vector<Token> tokenize(std::string &code)
        {
            std::vector<Token> tokens;
            std::vector<std::string> src = splitString(code);
            while (!src.empty())
            {
                if (src.front() == "(")      tokens.push_back(Token{shift(src), TokenType::OpenParen});
                else if (src.front() == ")") tokens.push_back(Token{shift(src), TokenType::CloseParen});
                else if (src.front() == "=") tokens.push_back(Token{shift(src), TokenType::Equals});
                else if (src.front() == "let") tokens.push_back(Token{shift(src), TokenType::Let});
                if (isNumber(src.front()))
                {
                    std::string number;
                }
            }
            return tokens;
        }


};
