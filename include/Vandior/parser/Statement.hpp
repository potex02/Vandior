//
// Created by potex02 on 20/09/2024.
//
// NOLINTBEGIN(*-include-cleaner)
#pragma once
#include "ASTNode.hpp"

namespace vnd {

    class Statement : public ASTNode {
    public:
        [[nodiscard]] explicit Statement(const Token &token) noexcept : ASTNode(token) {}

        /**
         * @brief Gets the type of the AST node.
         * @return NodeType enumeration value.
         */
        [[nodiscard]] NodeType getType() const noexcept override { return NodeType::Statement; }

        /**
         * @brief Returns a string representation of the AST node.
         * @return String representation of the AST node.
         */
        [[nodiscard]] std::string print() const override { return ""; }

        /**
         * @brief Returns a compact string representation of the AST node for compilation purposes.
         * @return Compact string representation of the AST node.
         */
        [[nodiscard]] std::string comp_print() const override { return ""; }

        friend void swap(Statement &lhs, Statement &rhs) noexcept {
            using std::swap;
            swap(static_cast<ASTNode &>(lhs), static_cast<ASTNode &>(rhs));
            swap(lhs.nodes, rhs.nodes);
        }

    private:
        std::vector<ASTNode> nodes;
    };

}  // namespace vnd

// NOLINTEND(*-include-cleaner)