#include "Vandior/lexer/Tokenizer.hpp"

using namespace std::literals::string_view_literals;
// NOLINTBEGIN(*-include-cleaner, *-easily-swappable-parameters, *-avoid-magic-numbers, *-magic-numbers)
DISABLE_WARNINGS_PUSH(26446)
namespace vnd {
    std::vector<Token> Tokenizer::tokenize() {
        std::vector<Token> tokens;
        while(positionIsInText()) {
            const char &currentChar = _input.at(position);
            if(std::isalpha(currentChar)) [[likely]] {
                tokens.emplace_back(handleAlpha());
            } else if(std::isdigit(currentChar)) [[likely]] {
                tokens.emplace_back(handleDigits());
            } else if(TokenizerUtility::isUnderscore(currentChar)) [[likely]] {
                tokens.emplace_back(handleUnderscoreAlpha());
            } else if(TokenizerUtility::isHasterisc(currentChar)) [[likely]] {
                tokens.emplace_back(handleHexadecimalOrOctal());
            } else if(std::isspace(currentChar)) [[likely]] {
                handleWhiteSpace();
                continue;  // Continue the loop to get the next token
            } else if(TokenizerUtility::isComment(_input, position)) {
                tokens.emplace_back(handleComment());
            } else if(TokenizerUtility::isOperator(currentChar)) [[likely]] {
                auto opTokens = handleOperators();
                tokens.insert(tokens.end(), std::begin(opTokens), std::end(opTokens));
            } else if(TokenizerUtility::isDot(currentChar)) {
                tokens.emplace_back(handleDot());
            } else if(TokenizerUtility::isBrackets(currentChar)) [[likely]] {
                tokens.emplace_back(handleBrackets());
            } else if(TokenizerUtility::isApostrophe(currentChar)) [[likely]] {
                tokens.emplace_back(handleChar());
            } else if(TokenizerUtility::isQuotation(currentChar)) [[likely]] {
                tokens.emplace_back(handleString());
            } else if(TokenizerUtility::isComma(currentChar)) {
                tokens.emplace_back(TokenType::COMMA, ","sv, CodeSourceLocation{_filename, line, column - 1});
                incPosAndColumn();
            } else if(TokenizerUtility::isColon(currentChar)) {
                tokens.emplace_back(TokenType::COLON, ":"sv, CodeSourceLocation{_filename, line, column - 1});
                incPosAndColumn();
            } else [[unlikely]] {
                handleError(std::string(1, currentChar), "Unknown Character");
            }
        }
        tokens.emplace_back(TokenType::EOFT, CodeSourceLocation{_filename, line, column});
        return tokens;
    }

    bool Tokenizer::positionIsInText() const noexcept { return position < _inputSize; }

    Token Tokenizer::handleAlpha() {
        const auto start = position;
        auto type = TokenType::IDENTIFIER;
        while(positionIsInText() && (TokenizerUtility::isalnumUnderscore(_input[position]))) { incPosAndColumn(); }
        const auto value = _input.substr(start, position - start);
        kewordType(value, type);
        return {type, value, {_filename, line, column - value.size()}};
    }

    Token Tokenizer::handleUnderscoreAlpha() {
        const auto start = position;
        incPosAndColumn();
        while(positionIsInText() && (TokenizerUtility::isalnumUnderscore(_input[position]))) { incPosAndColumn(); }
        const auto value = _input.substr(start, position - start);
        return {TokenType::IDENTIFIER, value, {_filename, line, column - value.size()}};
    }

    void Tokenizer::getType(const std::string_view &value, TokenType &type) noexcept {
        using enum TokenType;
        if(value == "i8"sv) { type = TYPE_I8; }
        if(value == "i16"sv) { type = TYPE_I16; }
        if(value == "i32"sv) { type = TYPE_I32; }
        if(value == "i64"sv) { type = TYPE_I64; }
        if(value == "u8"sv) { type = TYPE_U8; }
        if(value == "u16"sv) { type = TYPE_U16; }
        if(value == "u32"sv) { type = TYPE_U32; }
        if(value == "u64"sv) { type = TYPE_U64; }
        if(value == "f32"sv) { type = TYPE_F32; }
        if(value == "f64"sv) { type = TYPE_F64; }
        if(value == "c32"sv) { type = TYPE_C32; }
        if(value == "c64"sv) { type = TYPE_C64; }
        if(value == "char"sv) { type = TYPE_CHAR; }
        if(value == "string"sv) { type = TYPE_STRING; }
        if(value == "bool"sv) { type = TYPE_BOOL; }
    }
    void Tokenizer::kewordType(const std::string_view &value, TokenType &type) noexcept {
        using enum TokenType;
        if(value == "main"sv) { type = K_MAIN; }
        if(value == "var"sv || value == "val"sv || value == "const"sv) { type = K_VAR; }
        if(value == "if"sv) { type = K_IF; }
        if(value == "while"sv) { type = K_WHILE; }
        if(value == "else"sv) { type = K_ELSE; }
        if(value == "for"sv) { type = K_FOR; }
        if(value == "break"sv || value == "continue"sv) { type = K_BREAK; }
        if(value == "fun"sv) { type = K_FUN; }
        if(value == "return"sv) { type = K_RETURN; }
        if(value == "nullptr"sv) { type = K_NULLPTR; }
        if(value == "true"sv || value == "false"sv) { type = BOOLEAN; }
        getType(value, type);
    }

    bool Tokenizer::inTextAndE() const noexcept { return positionIsInText() && std::toupper(_input[position]) == ECR; }
    bool Tokenizer::inTextAnd(char chr) const noexcept { return positionIsInText() && _input[position] == chr; }

    Token Tokenizer::handleDigits() {
        using enum TokenType;
        auto tokenType = INTEGER;
        const auto start = position;
        extractDigits();
        if(inTextAnd(PNT)) {
            incPosAndColumn();
            extractDigits();
            if(inTextAndE()) {
                incPosAndColumn();
                extractExponent();
            }
            tokenType = DOUBLE;
        }
        if(inTextAndE()) {
            incPosAndColumn();
            extractExponent();
            tokenType = DOUBLE;
        }
        if(inTextAnd('i')) {
            incPosAndColumn();
            tokenType = DOUBLE;
        }
        if(inTextAnd('f')) {
            incPosAndColumn();
            tokenType = DOUBLE;
        }
        const auto value = _input.substr(start, position - start);
        return {tokenType, value, {_filename, line, column - value.size()}};
    }

    Token Tokenizer::handleComment() {
        auto nextposition = position + 1;
        if(_input[nextposition] == '/') { return handleSingleLineComment(); }
        if(_input[nextposition] == '*') { return handleMultiLineComment(); }
        return {TokenType::UNKNOWN, {_filename, line, column}};
    }

    Token Tokenizer::handleSingleLineComment() {
        const auto start = position;
        while(positionIsInText() && _input[position] != NL) { incPosAndColumn(); }
        const auto value = _input.substr(start, position - start);
        return {TokenType::COMMENT, value, {_filename, line, column - value.size()}};
    }

    Token Tokenizer::handleMultiLineComment() {
        const auto start = position;
        const auto startColumn = column;
        while(_input[position] != '*' || _input[position + 1] != '/') {
            if(position + 2 == _inputSize) {
                const auto value = _input.substr(start, position - start + 1);
                return {TokenType::UNKNOWN, value, {_filename, line, startColumn}};
            }
            handleWhiteSpace();
        }
        incPosAndColumn();
        incPosAndColumn();
        const auto value = _input.substr(start, position - start);
        return {TokenType::COMMENT, value, {_filename, line, startColumn}};
    }

    Token Tokenizer::handleDot() {
        const auto start = position;
        auto type = TokenType::DOT;
        incPosAndColumn();
        if(positionIsInText() && std::isdigit(_input[position])) {
            type = TokenType::DOUBLE;
            extractDigits();
            if(inTextAndE()) {
                incPosAndColumn();
                extractExponent();
            }
            if(inTextAnd('i')) { incPosAndColumn(); }
            if(inTextAnd('f')) { incPosAndColumn(); }
        }
        const auto value = _input.substr(start, position - start);
        return {type, value, {_filename, line, column - value.size()}};
    }

    void Tokenizer::extractExponent() noexcept {
        if(positionIsInText() && TokenizerUtility::isPlusOrMinus(_input[position])) { incPosAndColumn(); }
        extractDigits();
    }

    void Tokenizer::extractDigits() noexcept {
        while(positionIsInText() && isdigit(_input[position])) { incPosAndColumn(); }
    }

    void Tokenizer::incPosAndColumn() noexcept {
        position++;
        column++;
    }

    void Tokenizer::handleWhiteSpace() noexcept {
        if(_input[position] == '\n') [[unlikely]] {
            ++line;
            column = 1;
        } else {
            ++column;
        }
        ++position;
    }

    Token Tokenizer::handleBrackets() {
        const auto start = position;
        incPosAndColumn();
        const auto value = _input.substr(start, position - start);
        const auto type = getBracketsType(value);
        return {type, value, {_filename, line, column - value.size()}};
    }

    Token Tokenizer::handleChar() {
        incPosAndColumn();
        const auto start = position;
        std::string_view value{};
        while(!TokenizerUtility::isApostrophe(_input[position])) {
            if(position + 1 == _inputSize) {
                incPosAndColumn();
                value = _input.substr(start, position - start);
                return {TokenType::UNKNOWN, value, {_filename, line, column - value.size()}};
            }
            incPosAndColumn();
        }
        value = _input.substr(start, position - start);
        const auto colum = column - value.size();
        incPosAndColumn();
        return {TokenType::CHAR, value, {_filename, line, colum}};
    }

    Token Tokenizer::handleString() {
        const auto startColumn = column;
        incPosAndColumn();
        const auto start = position;
        std::string_view value{};
        while(!TokenizerUtility::isQuotation(_input[position])) {
            if(position + 1 == _inputSize) {
                incPosAndColumn();
                value = _input.substr(start, position - start);
                return {TokenType::UNKNOWN, value, {_filename, line, startColumn}};
            }
            handleWhiteSpace();
        }
        value = _input.substr(start, position - start);
        incPosAndColumn();
        return {TokenType::STRING, value, {_filename, line, startColumn}};
    }

    void Tokenizer::extractVarLenOperator() {
        while(positionIsInText() && TokenizerUtility::isOperator(_input[position])) { incPosAndColumn(); }
    }

    TokenType Tokenizer::singoleCharOp(const char view) noexcept {
        switch(view) {
            using enum TokenType;
        case '-':
            return MINUS;
        case '=':
            return EQUAL;
        case '<':
            return LESS;
        case '>':
            return GREATER;
        case '!':
            return NOT;
        case '+':
            return PLUS;
        case '*':
            return STAR;
        case '/':
            return DIVIDE;
        case '^':
            return XOR;
        case '%':
            return PERCENT;
        case '|':
            return OR;
        case '&':
            return AND;
        default:
            return UNKNOWN;
        }
    }

    TokenType Tokenizer::multyCharOp(const std::string_view &view) noexcept {
        using enum TokenType;
        if(view == "+="sv) {
            return PLUSEQUAL;
        } else if(view == "-="sv) {
            return MINUSEQUAL;
        } else if(view == "*="sv) {
            return STAREQUAL;
        } else if(view == "/="sv) {
            return DIVIDEEQUAL;
        } else if(view == "^="sv) {
            return XOREQUAL;
        } else if(view == "%="sv) {
            return PERCENTEQUAL;
        }
        if(view == "=="sv) {
            return EQUALEQUAL;
        } else if(view == ">="sv) {
            return GREATEREQUAL;
        } else if(view == "<="sv) {
            return LESSEQUAL;
        } else if(view == "!="sv) {
            return NOTEQUAL;
        }
        if(view == "&&"sv) {
            return ANDAND;
        } else if(view == "||"sv) {
            return OROR;
        }
        if(view == "++"sv) {
            return PLUSPLUS;
        } else if(view == "--"sv) {
            return MINUSMINUS;
        }
        return UNKNOWN;
    }

    std::vector<Token> Tokenizer::handleOperators() {
        std::vector<Token> tokens;
        const auto start = position;
        extractVarLenOperator();
        auto value = _input.substr(start, position - start);
        while(!value.empty()) {
            Token token;
            if(value.size() > 1) {
                auto twoCharOp = value.substr(0, 2);
                token = {multyCharOp(twoCharOp), twoCharOp, {_filename, line, column - 2}};
            }
            if(token.isType(TokenType::UNKNOWN) || value.size() == 1) {
                auto oneCharOp = value.substr(0, 1);
                token = Token{singoleCharOp(oneCharOp[0]), oneCharOp, {_filename, line, column - 1}};
            }

            tokens.emplace_back(token);
            value = value.substr(token.getValue().size(), value.size() - token.getValue().size());
        }
        return tokens;
    }

    template <StringOrStringView T> void Tokenizer::handleError(const T &value, const std::string_view &errorMsg) {
        const auto &lineStart = findLineStart();
        const auto &lineEnd = findLineEnd();

        const auto contextLine = getContextLine(lineStart, lineEnd);
        const auto highlighting = getHighlighting(lineStart, lineEnd, value);
        const auto errorMessage = getErrorMessage(value, errorMsg, contextLine, highlighting);

        throw std::runtime_error(errorMessage);
    }

    std::size_t Tokenizer::findLineStart() const noexcept {
        auto lineStart = position;
        while(lineStart > 0 && _input[lineStart - 1] != NL) { --lineStart; }
        return lineStart;
    }

    std::size_t Tokenizer::findLineEnd() const noexcept {
        auto lineEnd = position;
        while(lineEnd < _inputSize && _input[lineEnd] != NL) { ++lineEnd; }
        return lineEnd;
    }

    std::string Tokenizer::extract_context(const std::size_t &lineStart, const std::size_t &lineEnd) const {
        return std::string(_input.substr(lineStart, (lineEnd - lineStart)));
    }

    std::string Tokenizer::getContextLine(const std::size_t &lineStart, const std::size_t &lineEnd) const {
        return extract_context(lineStart, lineEnd).append(NEWL);
    }

    /**
     * @brief Extracts leading tabs from the given string view.
     *
     * This function removes leading tab characters from the beginning of the
     * provided string view and returns the modified string view without those tabs.
     *
     * @param input The input string view from which tabs are to be extracted.
     * @return A string view containing the input string without leading tabs.
     * @note The function is marked as [[nodiscard]] to ensure that the return value
     * is not discarded unintentionally.
     * @note The function is marked as noexcept to indicate that it does not throw
     * any exceptions.
     */
    [[nodiscard]] std::string_view extractTabs(const std::string_view &input) noexcept {
        // Find the position of the first character that is not a tab
        const auto pos = input.find_first_not_of(ctab);

        // Return a substring starting from the beginning of the input string view
        // up to the position of the first non-tab character found.
        // If no non-tab character is found, return an empty string view.
        return input.substr(0, pos == std::string_view::npos ? 0 : pos);
    }

    std::string Tokenizer::getHighlighting(const std::size_t &lineStart, const std::size_t &lineEnd, const std::string_view value) const {
        const auto temtp_val = extract_context(lineStart, lineEnd);
        auto tabs_section = extractTabs(temtp_val);
        if(const auto pos = temtp_val.find(value); pos != std::string::npos) {
            const auto val_len = value.length();
            if(pos == 0) [[unlikely]] {
                return FORMAT("{}{: ^{}}{:^{}}{}", tabs_section, "", pos, "^", val_len, NEWL);
            } else {
                return FORMAT("{}{: ^{}}{:^{}}{}", tabs_section, "", pos - 1, "^", val_len, NEWL);
            }
        }
        return FORMAT("{:^{}}{}", "^", (lineEnd - lineStart), NEWL);
    }

    template <StringOrStringView T>
    std::string Tokenizer::getErrorMessage(const T &value, const std::string_view &errMsg, const std::string &contextLine,
                                           const std::string &highlighting) {
        std::ostringstream errorMessageStream;
        errorMessageStream << FORMAT("{} '{}' (line {}, column {}):{}", errMsg, value, line, column, NEWL);
        errorMessageStream << FORMAT("Context: {}", NEWL);
        errorMessageStream << contextLine;
        errorMessageStream << highlighting;
        return errorMessageStream.str();
    }

    Token Tokenizer::handleHexadecimalOrOctal() {
        const auto start = position;
        incPosAndColumn();
        if(positionIsInText() && std::tolower(_input[position]) == 'o') {
            // Gestione dei numeri ottali
            incPosAndColumn();
            while(positionIsInText() && TokenizerUtility::isOctalDigit(_input[position])) { incPosAndColumn(); }
        } else if(positionIsInText() && std::isxdigit(_input[position])) {
            // Gestione dei numeri esadecimali
            while(positionIsInText() && std::isxdigit(_input[position])) { incPosAndColumn(); }
        } else [[unlikely]] {
            const auto error_value = _input.substr(start, position);
            handleError(error_value, "malformed exadecimal number or octal number");
        }

        const auto value = _input.substr(start, position - start);
        return {TokenType::INTEGER, value, {_filename, line, column - value.size() - 1}};
    }
}  // namespace vnd
DISABLE_WARNINGS_POP()
// NOLINTEND(*-include-cleaner, *-easily-swappable-parameters, *-avoid-magic-numbers, *-magic-numbers)
