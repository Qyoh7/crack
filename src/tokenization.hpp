#pragma once

#include <cctype>
#include <cstdlib>
#include <string> 
#include <optional> 
#include <vector> 
#include <iostream>
#include <string>
#include <vector>


enum class TokenType
{
    exit,
    int_lit,
    semi
};

struct Token
{
    TokenType type;
    std::optional<std::string> value {};
};

class Tokenizer
{
    private:
        const std::string m_src;
        size_t m_index = 0;
        [[nodiscard]] inline std::optional<char> peek(int ahead = 1) const
        {
            if (m_index + ahead > m_src.length())
            {
                return {};
            }
            else 
            {
                return m_src.at(m_index);
            }
        }
        char consume()
        {
            return m_src.at(m_index++);
        }
        

    public:
        explicit Tokenizer(const std::string& src) : m_src(std::move(src)) {}

        std::vector<Token> tokenize()
        {
            std::vector<Token> tokens;
            std::string buf;
            while (peek().has_value())
            {
                if (std::isalpha(peek().value()))
                {
                    buf.push_back(consume());
                    while(peek().has_value() && std::isalnum(peek().value()))
                    {
                        buf.push_back(consume());
                    }
                    if (buf == "exit")
                    {
                        tokens.push_back({.type = TokenType::exit});
                        buf.clear();
                    }
                    else
                    {
                        std::cerr << "Invalid Syntax, use better words next time" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
                else if (std::isdigit(peek().value()))
                {
                    buf.push_back(consume());
                    while (peek().has_value() && std::isdigit(peek().value()))
                    {
                        buf.push_back(consume());
                    }
                    tokens.push_back({.type = TokenType::int_lit, .value = buf});
                    buf.clear();
                }
                else if (peek().value() == ';')
                {
                    consume();
                    tokens.push_back({.type = TokenType::semi});

                }
                else if (std::isspace(peek().value()))
                {
                    consume();
                }
                else
                {
                    std::cerr << "Invalid Syntax, use better words next time" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            m_index = 0;
            return tokens;   
        }

};
