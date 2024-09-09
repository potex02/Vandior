// NOLINTBEGIN(*-include-cleaner)
#include "Vandior/vandior.hpp"

namespace vnd {
    auto timeTokenizer(Tokenizer &tokenizer, std::vector<Token> &tokens) -> void {
        tokens.clear();
#ifdef INDEPT
        const AutoTimer timer("tokenization");
#endif
        tokens = tokenizer.tokenize();
    }

    auto timeParser(std::unique_ptr<vnd::ASTNode> &ast, vnd::Parser &parser) -> void {
#ifdef INDEPT
        const AutoTimer timer("parse");
#endif
        ast = vnd_move_always_even_const(parser.parse());
    }

    auto timeParse(Parser &parser) -> std::unique_ptr<ASTNode> {
        std::unique_ptr<ASTNode> ast;
        timeParser(ast, parser);
        return ast;
    }
}

// NOLINTEND(*-include-cleaner)