#pragma once

#include <cstddef>
#include <cstdlib>
#include <vector>
#include <variant>

#include "tokenization.hpp"

struct NodeExprIntLit
{
    Token int_lit;
};

struct NodeExprIdent
{
    Token ident;
};

struct NodeExpr
{
    std::variant<NodeExprIntLit, NodeExprIdent> var;
};

struct NodeExit
{
    std::variant<NodeExprIntLit, NodeExprIdent> var;
};

struct NodeStmtExit
{
    NodeExpr expr;
};

struct NodeStmtLet
{
    Token ident;
    NodeExpr expr;
};

struct NodeStmt
{
    std::variant<NodeStmtExit, NodeStmtLet> var;
};

struct NodeProg
{
    std::vector<NodeStmt> stmts;
};


class Parser
{
        const std::vector<Token> m_tokens;
        size_t m_index = 0;

        [[nodiscard]] std::optional<Token> peek(int offset = 0) const
        {
            if (m_index + offset >= m_tokens.size())
            {
                return {};
            }
            return m_tokens.at(m_index + offset);
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
            if (peek().has_value() && peek().value().type == TokenType::int_lit)
            {
                return NodeExpr { .var = NodeExprIntLit {.int_lit = consume()} };
            }
            else if (peek().has_value() && peek().value().type == TokenType::ident)
            {
                return NodeExpr {.var = NodeExprIdent {.ident = consume()}};
            }
            return {};
        }

        std::optional<NodeExit> parse()
        {
            std::optional<NodeExit> exit_node;
            while (peek().has_value())
            {
                if (peek().value().type == TokenType::exit && peek(1).has_value() && peek(1).value().type == TokenType::open_paren)
                {
                    consume();
                    consume();
                    if (auto node_expr = parse_expr())
                    {
                        exit_node = NodeExit{.expr = node_expr.value()};
                    }
                    else {
                        std::cerr << "Invalid Expression" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    if (peek().has_value() && peek().value().type == TokenType::close_paren)
                    {
                        consume();
                    }
                    else
                    {
                        std::cerr << "Expected `)`" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    if (peek().has_value() && peek().value().type == TokenType::semi)
                    {
                        consume();
                    }
                    else {
                        std::cerr << "Expected `;`" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }
            m_index = 0;
            return exit_node;
        }
        
};
