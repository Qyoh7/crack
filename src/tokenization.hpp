#pragma once

#include "parser.hpp"
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
    semi,
    open_paren,
    close_paren,
    ident,
    let,
    eq
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
        [[nodiscard]] inline std::optional<char> peek(int offset = 0) const
        {
            if (m_index + offset >= m_src.length())
            {
                return {};
            }
            else 
            {
                return m_src.at(m_index + offset);
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
                    if (buf == "let")
                    {
                        tokens.push_back({.type = TokenType::let});
                        buf.clear();
                    }
                    else
                    {
                        tokens.push_back({.type = TokenType::ident, .value = buf});
                        buf.clear();
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
                else if (peek().value() == '(')
                {
                    consume();
                    tokens.push_back({.type = TokenType::open_paren});
                }
                else if (peek().value() == ')')
                {
                    consume();
                    tokens.push_back({.type = TokenType::close_paren});
                }
                else if (peek().value() == ';')
                {
                    consume();
                    tokens.push_back({.type = TokenType::semi});
                }
                else if (peek().value() == '=')
                {
                    consume();
                    tokens.push_back({.type = TokenType::eq});
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
