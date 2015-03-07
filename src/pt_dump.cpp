#include "pt_dump.h"

#include <iostream>
#include <iso646.h>

#include "util.h"

using namespace pt;

class Dumper: public IParseTreeVisitor {
public:
    Dumper(std::ostream &out): out(out), depth(0) {}

    virtual void visit(const TypeSimple *node) {
        write("TypeSimple(" + node->name + ")");
    }
    virtual void visit(const TypeEnum *node) {
        write("TypeEnum(" + join(node->names) + ")");
    }
    virtual void visit(const TypeRecord *node) {
        write("TypeRecord(" + join(node->fields) + ")");
    }
    virtual void visit(const TypePointer *node) {
        write("TypePointer");
        child(node->reftype);
    }
    virtual void visit(const TypeParameterised *node) {
        write("TypeParameterised(" + node->name + ")");
        child(node->elementtype);
    }

    virtual void visit(const BooleanLiteralExpression *node) {
        write("BooleanLiteralExpression(" + std::string(node->value ? "true" : "false") + ")");
    }
    virtual void visit(const NumberLiteralExpression *node) {
        write("NumberLiteralExpression(" + number_to_string(node->value) + ")");
    }
    virtual void visit(const StringLiteralExpression *node) {
        write("StringLiteralExpression(" + node->value + ")");
    }
    virtual void visit(const ArrayLiteralExpression *node) {
        write("ArrayLiteralExpression");
        for (auto x: node->elements) {
            child(x);
        }
    }
    virtual void visit(const DictionaryLiteralExpression *node) {
        write("DictionaryLiteralExpression");
        depth++;
        for (auto x: node->elements) {
            write(x.first.text);
            child(x.second);
        }
        depth--;
    }
    virtual void visit(const NilLiteralExpression *) {
        write("NilLiteralExpression");
    }
    virtual void visit(const IdentifierExpression *node) {
        write("IdentifierExpression(" + node->name + ")");
    }
    virtual void visit(const DotExpression *node) {
        write("DotExpression(" + node->name.text + ")");
        child(node->base);
    }
    virtual void visit(const ArrowExpression *node) {
        write("ArrowExpression(" + node->name.text + ")");
        child(node->base);
    }
    virtual void visit(const SubscriptExpression *node) {
        write("SubscriptExpression");
        child(node->base);
        child(node->index);
    }
    virtual void visit(const InterpolatedStringExpression *node) {
        write("InterpolatedStringExpression");
        depth++;
        for (auto x: node->parts) {
            write("FormatString(" + x.second + ")");
            child(x.first);
        }
        depth--;
    }
    virtual void visit(const FunctionCallExpression *node) {
        write("FunctionCallExpression");
        child(node->base);
        for (auto x: node->args) {
            child(x);
        }
    }
    virtual void visit(const UnaryMinusExpression *node) {
        write("UnaryMinusExpression");
        child(node->expr);
    }
    virtual void visit(const LogicalNotExpression *node) {
        write("LogicalNotExpression");
        child(node->expr);
    }
    virtual void visit(const ExponentiationExpression *node) {
        write("ExponentiationExpression");
        child(node->left);
        child(node->right);
    }
    virtual void visit(const MultiplicationExpression *node) {
        write("MultiplicationExpression");
        child(node->left);
        child(node->right);
    }
    virtual void visit(const DivisionExpression *node) {
        write("DivisionExpression");
        child(node->left);
        child(node->right);
    }
    virtual void visit(const ModuloExpression *node) {
        write("ModuloExpression");
        child(node->left);
        child(node->right);
    }
    virtual void visit(const AdditionExpression *node) {
        write("AdditionExpression");
        child(node->left);
        child(node->right);
    }
    virtual void visit(const SubtractionExpression *node) {
        write("SubtractionExpression");
        child(node->left);
        child(node->right);
    }
    virtual void visit(const ConcatenationExpression *node) {
        write("ConcatenationExpression");
        child(node->left);
        child(node->right);
    }
    virtual void visit(const ComparisonExpression *node) {
        write("ComparisonExpression(" + std::to_string(node->comp) + ")");
        child(node->left);
        child(node->right);
    }
    virtual void visit(const ChainedComparisonExpression *node) {
        write("ChainedComparisonExpression");
        for (auto x: node->comps) {
            child(x);
        }
    }
    virtual void visit(const MembershipExpression *node) {
        write("MembershipExpression");
        child(node->left);
        child(node->right);
    }
    virtual void visit(const ConjunctionExpression *node) {
        write("ConjunctionExpression");
        child(node->left);
        child(node->right);
    }
    virtual void visit(const DisjunctionExpression *node) {
        write("DisjunctionExpression");
        child(node->left);
        child(node->right);
    }
    virtual void visit(const ConditionalExpression *node) {
        write("ConditionalExpression");
        child(node->cond);
        child(node->left);
        child(node->right);
    }
    virtual void visit(const NewRecordExpression *node) {
        write("NewRecordExpression");
        child(node->type);
    }
    virtual void visit(const ValidPointerExpression *node) {
        write("ValidPointerExpression(" + node->name.text + ")");
        child(node->ptr);
    }

    virtual void visit(const ImportDeclaration *node) {
        write("ImportDeclaration(" + node->name.text + ")");
    }
    virtual void visit(const TypeDeclaration *node) {
        write("TypeDeclaration");
        child(node->type);
    }
    virtual void visit(const ConstantDeclaration *node) {
        write("ConstantDeclaration(" + node->name + ")");
        child(node->type);
        child(node->value);
    }
    virtual void visit(const VariableDeclaration *node) {
        write("VariableDeclaration(" + join(node->names) + ")");
        child(node->type);
        child(node->value);
    }
    virtual void visit(const BaseFunctionDeclaration *node) {
        write("BaseFunctionDeclaration(" + node->name.text + ")");
        child(node->returntype);
        depth++;
        for (auto x: node->args) {
            write(std::to_string(x->mode) + " " + x->name.text);
            child(x->type);
        }
        depth--;
    }
    virtual void visit(const FunctionDeclaration *node) {
        write("FunctionDeclaration(" + node->name.text + ")");
        child(node->returntype);
        depth++;
        for (auto x: node->args) {
            write(std::to_string(x->mode) + " " + x->name.text);
            child(x->type);
        }
        depth--;
        for (auto x: node->body) {
            child(x);
        }
    }
    virtual void visit(const ExternalFunctionDeclaration *node) {
        write("ExternalFunctionDeclaration(" + node->name.text + ")");
        child(node->returntype);
        depth++;
        for (auto x: node->args) {
            write(std::to_string(x->mode) + " " + x->name.text);
            child(x->type);
        }
        depth--;
        child(node->dict);
    }
    virtual void visit(const ExceptionDeclaration *node) {
        write("ExceptionDeclaration(" + node->name + ")");
    }

    virtual void visit(const AssignmentStatement *node) {
        write("AssignmentStatement");
        for (auto x: node->variables) {
            child(x);
        }
        child(node->expr);
    }
    virtual void visit(const CaseStatement *node) {
        write("CaseStatement");
        child(node->expr);
        depth++;
        for (auto x: node->clauses) {
            for (const CaseStatement::WhenCondition *when: x.first) {
                const CaseStatement::ComparisonWhenCondition *cw = dynamic_cast<const CaseStatement::ComparisonWhenCondition *>(when);
                const CaseStatement::RangeWhenCondition *rw = dynamic_cast<const CaseStatement::RangeWhenCondition *>(when);
                if (cw != nullptr) {
                    write("ComparisonWhenCondition(" + std::to_string(cw->comp) + ")");
                    child(cw->expr);
                }
                if (rw != nullptr) {
                    write("RangeWhenCondition");
                    child(rw->low_expr);
                    child(rw->high_expr);
                }
            }
            for (auto s: x.second) {
                child(s);
            }
        }
        depth--;
    }
    virtual void visit(const ExitStatement *node) {
        write("ExitStatement(" + std::to_string(node->type) + ")");
    }
    virtual void visit(const ExpressionStatement *node) {
        write("ExpressionStatement");
        child(node->expr);
    }
    virtual void visit(const ForStatement *node) {
        write("ForStatement(" + node->var.text + ")");
        child(node->start);
        child(node->end);
        child(node->step);
        for (auto x: node->body) {
            child(x);
        }
    }
    virtual void visit(const IfStatement *node) {
        write("IfStatement");
        for (auto x: node->condition_statements) {
            child(x.first);
            for (auto y: x.second) {
                child(y);
            }
        }
        for (auto x: node->else_statements) {
            child(x);
        }
    }
    virtual void visit(const LoopStatement *node) {
        write("LoopStatement");
        for (auto x: node->body) {
            child(x);
        }
    }
    virtual void visit(const NextStatement *node) {
        write("NextStatement(" + std::to_string(node->type) + ")");
    }
    virtual void visit(const RaiseStatement *node) {
        write("RaiseStatement(" + node->name.text + ")");
        child(node->info);
    }
    virtual void visit(const RepeatStatement *node) {
        write("RepeatStatement");
        child(node->cond);
        for (auto x: node->body) {
            child(x);
        }
    }
    virtual void visit(const ReturnStatement *node) {
        write("ReturnStatement");
        child(node->expr);
    }
    virtual void visit(const TryStatement *node) {
        write("TryStatement");
        for (auto x: node->body) {
            child(x);
        }
        // TODO: internal_error("TODO: TryStatement");
    }
    virtual void visit(const WhileStatement *node) {
        write("WhileStatement");
        child(node->cond);
        for (auto x: node->body) {
            child(x);
        }
    }
    virtual void visit(const Program *node) {
        write("Program");
        for (auto s: node->body) {
            child(s);
        }
    }
private:
    std::ostream &out;
    int depth;

    void write(const std::string &s) {
        out << std::string(depth*2, ' ') << s << "\n";
    }

    void child(const ParseTreeNode *node) {
        depth++;
        if (node != nullptr) {
            node->accept(this);
        } else {
            write("nullptr");
        }
        depth--;
    }

    static std::string join(const std::vector<std::string> &a) {
        std::string r;
        for (auto x: a) {
            if (not r.empty()) {
                r += ",";
            }
            r += x;
        }
        return r;
    }

    static std::string join(const std::vector<Token> &a) {
        std::string r;
        for (auto x: a) {
            if (not r.empty()) {
                r += ",";
            }
            r += x.text;
        }
        return r;
    }

    static std::string join(const std::vector<std::pair<Token, int>> &a) {
        std::vector<std::string> b;
        for (auto x: a) {
            b.push_back(x.first.text);
        }
        return join(b);
    }

    static std::string join(const std::vector<std::pair<Token, const Type *>> &a) {
        std::vector<std::string> b;
        for (auto x: a) {
            b.push_back(x.first.text);
        }
        return join(b);
    }
private:
    Dumper(const Dumper &);
    Dumper &operator=(const Dumper &);
};

void pt::dump(std::ostream &out, const ParseTreeNode *node)
{
    Dumper d(out);
    node->accept(&d);
}