#include "Vandior/Transpiler.hpp"

namespace vnd {

    Transpiler::Transpiler(std::vector<Instruction> instructions) noexcept
      : _tabs(0), _text(""), _instructions(instructions), _scope(Scope::createMain()), _main(false) {}

    Transpiler Transpiler::create(std::vector<Instruction> instructions) noexcept { return {instructions}; }

    void Transpiler::transpile() {
        using enum TokenType;
        using enum InstructionType;
        _output.open("output.cpp");
        _text += "#include <iostream>\n";
        _text += "#include <vector>\n";
        try {
            for(const Instruction &i : _instructions) {
                _text += std::string(_tabs, '\t');
                switch(i.getLastType()) {
                case MAIN:
                    transpileMain(i);
                    break;
                case DECLARATION:
                case INITIALIZATION:
                    transpileDeclaration(i);
                    break;
                case OPEN_SCOPE:
                    _text += "{";
                    openScope();
                    checkTrailingBracket(i);
                    break;
                case CLOSE_SCOPE:
                    _text.pop_back();
                    if(_scope->isMainScope()) { throw TranspilerException("Unexpected }", i); }
                    checkTrailingBracket(i);
                    break;
                }
                _text += "\n";
            }
            if(!_scope->isMainScope()) { throw TranspilerException("Expected }", Instruction::create()); }
            _output << _text;
        } catch(TranspilerException &e) {
            LERROR("{}", e.what());
            _output.close();
        }
        _output.close();
    }

    void Transpiler::checkTrailingBracket(const Instruction &instruction) {
        if(instruction.getTokens().back().getType() == TokenType::CLOSE_CUR_PARENTESIS) {
            _text += "}";
            closeScope();
        }
    }

    void Transpiler::transpileMain(const Instruction &instruction) {
        if(!_scope->isMainScope()) { throw TranspilerException("Cannot declare main here", instruction); }
        if(_main) { throw TranspilerException("Main already declared", instruction); }
        if(_scope->getParent() != nullptr) { throw TranspilerException("Cannot declare main here", instruction); }
        _text += "int main() {";
        openScope();
        checkTrailingBracket(instruction);
        _main = true;
    }

    void Transpiler::transpileDeclaration(const Instruction& instruction) {
        std::vector<Token> tokens = instruction.getTokens();
        std::string type;
        std::vector<Token>::iterator i = tokens.begin();
        bool isConst = i->getValue() == "const";
        std::vector<std::string_view> variables = extractVariables(i);
        ExpressionFactory factory = ExpressionFactory::create(i, tokens.end());
        type = (++i)->getValue();
        while(i != tokens.end() && i->getType() != TokenType::EQUAL_OPERATOR) {
            if(i->getType() == TokenType::OPEN_SQ_PARENTESIS) { type = "std::vector<" + type + ">"; }
            i++;
        }
        _text += type;
        _text += " ";
        if(i != tokens.end() && i->getType() == TokenType::EQUAL_OPERATOR) {
            i++;
            while(i != tokens.end()) {
                factory.parse(TokenType::COMMA);
                if(i != tokens.end()) { i++; }
            }
        }
        if(isConst && variables.size() > factory.size()) {
            throw TranspilerException(FORMAT("Uninitialized constant: {} values for {} constants",
                                      factory.size(), variables.size()), instruction);
        }
        for(std::string_view j : variables) {
            _text += j;
            if(!factory.empty()) {
                _text += " =";
                _text += factory.getExpression();
            }
            emplaceCommaColon(j == variables.back());
        }
    }

    std::vector<std::string_view> Transpiler::extractVariables(std::vector<Token>::iterator &iterator) {
        using enum TokenType;
        std::vector<std::string_view> result;
        if(iterator->getValue() == "const") { _text += "const "; }
        while(iterator->getType() != COLON) {
            if(iterator->getType() == IDENTIFIER) {
                // this->scope->checkVariable(i->getValue());
                result.emplace_back(iterator->getValue());
            }
            iterator++;
        }
        return result;
    }

    void Transpiler::openScope() noexcept {
        std::shared_ptr<Scope> newScope = Scope::create(_scope);
        _scope = newScope;
        _tabs++;
    }

    void Transpiler::closeScope() noexcept {
        std::shared_ptr<Scope> oldScope = _scope;
        _scope = _scope->getParent();
        oldScope->removeParent();
       _tabs--;
    }

    void Transpiler::emplaceCommaColon(const bool colon) noexcept {
        if(colon) {
            _text += ";";
            return;
        }
        _text += ", ";
    }

}  // namespace vnd