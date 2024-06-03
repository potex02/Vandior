//
// Created by gbian on 07/05/2024.
//

#pragma once

#include "TokenType.hpp"

namespace vnd {
    [[nodiscard]] inline std::string comp_tokType(TokenType type) {
        using enum TokenType;
        switch(type) {
        case INTEGER:
            return "INT";
        case DOUBLE:
            return "DBL";
        case BOOLEAN:
            return "BOOL";
        case PLUS:
            return "PLUS_OP";
        case MINUS:
            return "MINUS_OP";
        case EQUAL:
            return "EQUAL_OP";
        case DOT:
            return "DOT_OP";
        case STAR:
            return "STAR_OP";
        case DIVIDE:
            return "DIVIDE_OP";
        case XOR:
            return "XOR_OP";
        case PERCENT:
            return "PERCENT_OP";
        case OR:
            return "OR_OP";
        case AND:
            return "AND_OP";
        case LESS:
            return "LESS_OP";
        case GREATER:
            return "GREATER_OP";
        case PLUSPLUS:
            return "PLUSPLUS_OP";
        case MINUSMINUS:
            return "MINUSMINUS_OP";
        case PLUSEQUAL:
            return "PLUSEQUAL_OP";
        case MINUSEQUAL:
            return "MINUSEQUAL_OP";
        case NOTEQUAL:
            return "NOTEQUAL_OP";
        case STAREQUAL:
            return "STAREQUAL_OP";
        case DIVIDEEQUAL:
            return "DIVIDEEQUAL_OP";
        case XOREQUAL:
            return "XOREQUAL_OP";
        case PERCENTEQUAL:
            return "PERCENTEQUAL_OP";
        case OROR:
            return "OROR_OP";
        case ANDAND:
            return "ANDAND_OP";
        case EQUALEQUAL:
            return "EQUALEQUAL_OP";
        case LESSEQUAL:
            return "LESSEQUAL_OP";
        case GREATEREQUAL:
            return "GREATEREQUAL_OP";
        case IDENTIFIER:
            return "IDENT";
        case CHAR:
            return "CH";
        case STRING:
            return "STR";
        case EOFT:
            return "EOF";
        case K_MAIN:
            return "K_MAIN";
        case K_VAR:
            return "K_VAR";
        case K_IF:
            return "K_IF";
        case K_WHILE:
            return "K_WHILE";
        case K_ELSE:
            return "K_ELSE";
        case K_FOR:
            return "K_FOR";
        case K_BREAK:
            return "BREAK";
        case K_FUN:
            return "K_FUN";
        case K_RETURN:
            return "K_RETURN";
        case K_NULLPTR:
            return "K_NULLPTR";
        case OPEN_PARENTESIS:
            return "OPEN_PAR";
        case OPEN_SQ_PARENTESIS:
            return "OPEN_SQ_PAR";
        case OPEN_CUR_PARENTESIS:
            return "OPEN_CUR_PAR";
        case CLOSE_PARENTESIS:
            return "CLOSE_PAR";
        case CLOSE_SQ_PARENTESIS:
            return "CLOSE_SQ_PAR";
        case CLOSE_CUR_PARENTESIS:
            return "CLOSE_CUR_PAR";
        case NOT:
            return "NOT_OP";
        case COMMA:
            return "COMMA";
        case COLON:
            return "COLON";
        case COMMENT:
            return "COMMENT";
        // Add more cases as needed
        case UNKNOWN:
            [[fallthrough]];
        default:
            return "UNKNOWN";
        }
    }
}  // namespace vnd
