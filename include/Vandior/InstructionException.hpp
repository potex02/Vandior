#pragma once
#include <stdexcept>
#include "Token.hpp"

namespace vnd {
    class InstructionException : public std::runtime_error {
    public:
        explicit InstructionException(const Token &token);
    };
}