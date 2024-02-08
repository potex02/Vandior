#include "Vandior/Token.hpp"
std::string vnd::Token::to_string() const {
    if(_type == eofTokenType) { return FORMAT("(type: {}, source location:{})", _type, _sourceLocation); }
    return FORMAT("(type: {}, value: '{}', source location:{})", _type, _value, _sourceLocation);
}  // NOLINT(*-include-cleaner)
