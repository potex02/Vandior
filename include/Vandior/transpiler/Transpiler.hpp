// NOLINTBEGIN(*-include-cleaner)
#pragma once

#include "../parser/Parser.hpp"
#include "ProjectBuilder.hpp"

namespace vnd {
    class Transpiler {
    public:
        Transpiler(const std::string_view &input, const std::string_view &filename);
        void transpile();

    private:
        /**
         * Creates a mock file.
         */
        void createMockfile();
        /**
         * @brief Maps a given type to a corresponding string view.
         *
         * @param type The type to be mapped.
         * @return The corresponding string view.
         */
        static auto mapType(const std::string_view type) -> std::string_view;
        /**
         * Transpiles the given ASTNode into a string representation.
         *
         * @param node The ASTNode to transpile.
         * @return The transpiled string representation of the node.
         */
        auto transpileNode(const ASTNode &node) -> std::string;
        /**
         * Transpiles a binary expression node.
         *
         * @param binaryNode The binary expression node to transpile.
         * @return The transpiled binary expression as a string.
         */
        auto transpileBinaryExpressionNode(const BinaryExpressionNode *binaryNode) -> std::string;
        /**
         * Transpiles a unary expression node.
         *
         * @param unaryNode The unary expression node to transpile.
         * @return The transpiled unary expression as a string.
         */
        auto transpileUnaryExpressionNode(const UnaryExpressionNode *unaryNode) -> std::string;
        /**
         * Transpiles a variable node into a string representation.
         *
         * @param variableNode The variable node to transpile.
         * @return The string representation of the transpiled variable node.
         */
        auto transpileVariableNode(const VariableNode *variableNode) -> std::string;
        /**
         * @brief Transpiles a numeric node.
         * 
         * This function takes a pointer to a NumberNode and transpiles it into a string representation.
         * The transpiled string is returned.
         * 
         * @tparam T The type of the numeric value.
         * @param numberNode Pointer to the NumberNode to be transpiled.
         * @return The transpiled string representation of the numeric node.
         */
        template <typename T> auto transpileNumericNode(const NumberNode<T> *numberNode) -> std::string;
        /**
         * @brief Transpiles a literal node to a string representation.
         * 
         * This function takes a literal node as input and returns a string representation of the node.
         * The template parameter `T` specifies the type of the literal value.
         * 
         * @param literalNode A pointer to the literal node to be transpiled.
         * @return The string representation of the transpiled literal node.
         */
        template <typename T> auto transpileLiteralNode(const LiteralNode<T> *literalNode) -> std::string;
        /**
         * Transpiles the given TypeNode into a string representation.
         *
         * @param typeNode The TypeNode to be transpiled.
         * @return The string representation of the transpiled TypeNode.
         */
        auto transpileTypeNode(const TypeNode *typeNode) -> std::string;
        /**
         * Transpiles the given IndexNode into a string representation.
         *
         * @param indexNode The IndexNode to transpile.
         * @return The transpiled string representation of the IndexNode.
         */
        auto transpileIndexNode(const IndexNode *indexNode) -> std::string;
        /**
         * Transpiles an ArrayNode into a string representation.
         *
         * @param arrayNode The ArrayNode to transpile.
         * @return The transpiled string representation of the ArrayNode.
         */
        auto transpileArrayNode(const ArrayNode *arrayNode) -> std::string;
        std::string_view _filename;
        ProjectBuilder _projectBuilder;
        Parser _parser;
        fs::path _vnBuildSrcFolder;
        fs::path _mainOutputFilePath;
    };
}  // namespace vnd

// NOLINTEND(*-include-cleaner)
