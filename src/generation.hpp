#pragma once

#include "parser.hpp"
#include <sstream>

class Generator
{
    private:
        const NodeProg m_prog;
    public:
        Generator(NodeProg prog) : m_prog(std::move(prog)) {}
        
        std::string gen_expr(const NodeExpr& expr) const
        {
            struct ExprVisitor
            {
                void operator()(const NodeExprIntLit& expr_int_lit)
                {

                }
                void operator()(const NodeExprIdent& expr_ident)
                {

                }

            };
            ExprVisitor visitor;
            std::visit(visitor, expr.var);
        }
        std::string gen_stmt(const NodeStmt& stmt) const
        {
            std::stringstream output;
            struct StmtVisitor
            {
                void operator()(const NodeStmtExit& stmt_exit)
                {
                    output << "    mov rax, 60\n";
                    output << "    mov rdi, "; //TODO
                    output << "    syscall\n" << std::endl;

                }
                void operator()(const NodeStmtLet& stmt_let)
                {

                }
            };
            StmtVisitor visitor;
            std::visit(visitor, stmt.var);
        }

        std::string gen_prog() const
        {
            std::stringstream output;
            output << "global _start\n_start:\n";
            

            for (const NodeStmt& stmt : m_prog.stmts)
            {
                output << gen_stmt(stmt);
            }

            output << "    mov rax, 60\n";
            output << "    mov rdi, 0\n";
            output << "    syscall\n" << std::endl;
            return output.str();
        }

};
