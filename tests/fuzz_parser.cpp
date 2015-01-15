#include <fstream>
#include <iostream>
#include <sstream>

#include "parser.h"
#include "util.h"

std::string reconstitute(const Token &t)
{
    switch (t.type) {
        case NONE:        exit(1);
        case END_OF_FILE: return "";
        case NUMBER:      return number_to_string(t.value);
        case STRING:      return "\"" + t.text + "\"";
        case IDENTIFIER:  return t.text;
        case LPAREN:      return "(";
        case RPAREN:      return ")";
        case LBRACKET:    return "[";
        case RBRACKET:    return "]";
        case LBRACE:      return "{";
        case RBRACE:      return "}";
        case COLON:       return ":";
        case ASSIGN:      return ":=";
        case PLUS:        return "+";
        case MINUS:       return "-";
        case TIMES:       return "*";
        case DIVIDE:      return "/";
        case MOD:         return "MOD";
        case EXP:         return "^";
        case CONCAT:      return "&";
        case EQUAL:       return "=";
        case NOTEQUAL:    return "#";
        case LESS:        return "<";
        case GREATER:     return ">";
        case LESSEQ:      return "<=";
        case GREATEREQ:   return ">=";
        case COMMA:       return ",";
        case IF:          return "IF";
        case THEN:        return "THEN";
        case ELSE:        return "ELSE";
        case END:         return "END";
        case WHILE:       return "WHILE";
        case DO:          return "DO";
        case VAR:         return "VAR";
        case FUNCTION:    return "FUNCTION";
        case RETURN:      return "RETURN";
        case FALSE:       return "FALSE";
        case TRUE:        return "TRUE";
        case AND:         return "AND";
        case OR:          return "OR";
        case NOT:         return "NOT";
        case FOR:         return "FOR";
        case TO:          return "TO";
        case STEP:        return "STEP";
        case ARRAY:       return "Array";
        case DICTIONARY:  return "Dictionary";
        case DOT:         return ".";
        case TYPE:        return "TYPE";
        case RECORD:      return "RECORD";
        case ENUM:        return "ENUM";
        case CONST:       return "CONST";
        case IMPORT:      return "IMPORT";
        case IN:          return "IN";
        case OUT:         return "OUT";
        case INOUT:       return "INOUT";
        case ELSIF:       return "ELSIF";
        case CASE:        return "CASE";
        case WHEN:        return "WHEN";
        case DOTDOT:      return "..";
        case EXTERNAL:    return "EXTERNAL";
        case EXIT:        return "EXIT";
        case NEXT:        return "NEXT";
        case LOOP:        return "LOOP";
        case REPEAT:      return "REPEAT";
        case UNTIL:       return "UNTIL";
        case DECLARE:     return "DECLARE";
        case EXCEPTION:   return "EXCEPTION";
        case TRY:         return "TRY";
        case RAISE:       return "RAISE";
        case POINTER:     return "POINTER";
        case NEW:         return "NEW";
        case NIL:         return "NIL";
        case VALID:       return "VALID";
        case ARROW:       return "->";
        case SUBBEGIN:	  return "";
        case SUBFMT:      return "";
        case SUBEND:  	  return "";
        case MAX_TOKEN:   return "";
    }
    return "";
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        exit(1);
    }
    std::ifstream inf(argv[1]);
    std::stringstream buf;
    buf << inf.rdbuf();
    std::vector<Token> tokens;
    int i = 0;
    for (auto b: buf.str()) {
        if (b > END_OF_FILE && b < MAX_TOKEN) {
            Token t;
            t.type = static_cast<TokenType>(b);
            if (t.type == IDENTIFIER) {
                t.text = std::string(1, 'a'+(i%4));
            }
            tokens.push_back(t);
        } else {
            exit(1);
        }
        i++;
    }
    Token t;
    t.type = END_OF_FILE;
    tokens.push_back(t);
    for (auto t: tokens) {
        std::cout << reconstitute(t) << " ";
    }
    std::cout << std::endl;
    try {
        parse(tokens);
    } catch (SourceError &) {
        exit(1);
    }
}
