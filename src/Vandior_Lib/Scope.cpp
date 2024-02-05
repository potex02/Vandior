#include "Vandior/Scope.hpp"

namespace vnd {

    // NOLINTNEXTLINE
    std::vector<std::string> Scope::_numberTypes = {"int", "float"};

    Scope::Scope(std::shared_ptr<Scope> parent) noexcept : _vars({}), _consts({}), _funs({}), _parent(std::move(parent)) {}

    std::shared_ptr<Scope> Scope::create(std::shared_ptr<Scope> parent) noexcept {
        return std::make_shared<Scope>(Scope(std::move(parent)));
    }

    std::shared_ptr<Scope> Scope::createMain() noexcept {
        std::shared_ptr<Scope> mainScope = std::make_shared<Scope>(Scope(nullptr));
        mainScope->addType("int");
        mainScope->addType("float");
        mainScope->addType("double");
        mainScope->addType("char");
        mainScope->addType("bool");
        mainScope->addType("string");
        mainScope->addFun("test", std::make_tuple<std::string, std::vector<std::string>>("int", {}));
        mainScope->addFun("testPar", std::make_tuple<std::string, std::vector<std::string>>("int", {"int", "int"}));
        mainScope->addFun("testPar", std::make_tuple<std::string, std::vector<std::string>>("int", {"string"}));
        return mainScope;
    }

    bool Scope::isNumber(const std::string &type) noexcept {
        return std::ranges::find(Scope::_numberTypes, type) != Scope::_numberTypes.end();
    }

    bool Scope::canAssign(const std::string &left, const std::string &right) noexcept {
        return (Scope::isNumber(left) && Scope::isNumber(right)) || left == right;
    }

    std::shared_ptr<Scope> Scope::getParent() const noexcept { return _parent; }

    void Scope::removeParent() noexcept { _parent = nullptr; }

    void Scope::addType(const std::string_view type) noexcept {
        _types.emplace(type);
    }

    void Scope::addVariable(const std::string_view identifier, const std::string_view type, const bool isConst) noexcept {
        if(isConst) {
            _consts[std::string{identifier}] = std::string{type};
            return;
        }
        _vars[std::string{identifier}] = type;
    }

    void Scope::addFun(const std::string_view identifier, const FunType &fun) noexcept {
        std::string key = std::string{identifier};
        if(_funs.find(key) == _funs.end()) { _funs[key] = {}; }
        _funs[key].emplace_back(fun);
    }

    bool Scope::isMainScope() const noexcept { return _parent == nullptr; }

    bool Scope::checkType(const std::string_view type) const noexcept {  // NOLINT(*-no-recursion)
        if(_types.find(std::string{type}) != _types.end()) { return true; }
        if(_parent) { return _parent->checkType(type); }
        return false;
    }

    // NOLINTNEXTLINE
    std::pair<bool, bool> Scope::checkVariable(const std::string_view identifier, const bool shadowing) const noexcept {
        if(_vars.find(std::string{identifier}) != _vars.end() || _consts.find(std::string{identifier}) != _consts.end()) {
            return {true, shadowing};
        }
        if(_parent) { return _parent->checkVariable(identifier, true); }
        return {false, false};
    }

    std::string_view Scope::getVariableType(const std::string_view identifier) const noexcept {  // NOLINT(*-no-recursion)
        if(_vars.find(std::string{identifier}) != _vars.end()) { return _vars.at(std::string{identifier}); }
        if(_consts.find(std::string{identifier}) != _consts.end()) { return _consts.at(std::string{identifier}); }
        if(_parent) { return _parent->getVariableType(identifier); }
        return "";
    }

    std::string Scope::getFunType(const std::string_view identifier, const std::vector<Expression> &expressions) const noexcept {  // NOLINT(*-no-recursion)
        std::string_view result;
        bool found;
        if(_funs.find(std::string{identifier}) != _funs.end()) {
            for(FunType fun : _funs.at(std::string{identifier})) {
                found = true;
                if(std::get<1>(fun).size() != expressions.size()) {
                    found = false;
                } else {
                    for(size_t par = 0; par != std::get<1>(fun).size(); par++) {
                        if(!Scope::canAssign(get<1>(fun).at(par), expressions.at(par).getType())) { found = false; }
                    }
                }
                if(found) {
                    return std::string{std::get<0>(fun)};
                }
            }
        }
        if(_parent) { return _parent->getFunType(identifier, expressions); }
        return "";
    }

}  // namespace vnd