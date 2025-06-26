#pragma once

#include <cstddef>
#include <cstdlib>
#include <vector>

#include "tokenization.hpp"

struct NodeExpr
{
    Token int_lit;
};

struct NodeExit
{
    NodeExpr expr;
};


class Parser
{
        const std::vector<Token> m_tokens;
        size_t m_index = 0;

        [[nodiscard]] std::optional<Token> peek(int ahead = 0) const
        {
            if (m_index + ahead > m_tokens.size())
            {
                return {};
            }
            return m_tokens.at(m_index + ahead);
        }
        Token consume()
        {
            if (m_index >= m_tokens.size())
            {
                std::cerr << "Tried to consume out of bounds\n";
                exit(EXIT_FAILURE);
            }
            return m_tokens.at(m_index++);
        }
    public:
        explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)) {}

        std::optional<NodeExpr> parse_expr()
        {
            auto next = peek();
            if (next.has_value() && next.value().type == TokenType::int_lit)
            {
                return NodeExpr
                {
                    .int_lit = consume()
                };
            }
            return {};
        }

        std::optional<NodeExit> parse()
        {
            std::optional<NodeExit> exit_node;
            while (peek().has_value())
            {
                if (peek().value().type == TokenType::exit)
                {
                    consume();
                    if (auto node_expr = parse_expr())
                    {
                        exit_node = NodeExit{.expr = node_expr.value()};
                    }
                    else {
                        std::cerr << "Invalid Expression" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    if (peek().has_value() && peek().value().type == TokenType::semi)
                    {
                        consume();
                    }
                    else {
                        std::cerr << "Invalid Expression" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }
            m_index = 0;
            return exit_node;
        }
        
};
