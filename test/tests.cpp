#include <catch2/catch_test_macros.hpp>

#include <Vandior/vandior.hpp>

static inline constexpr std::size_t line = 5;
static inline constexpr std::size_t colum = 6;
static inline constexpr std::size_t colum2 = 5;
static inline constexpr std::size_t colum3 = 7;
static inline constexpr std::size_t colum4 = 8;
static inline constexpr std::size_t colum5 = 9;
static inline constexpr std::size_t colum6 = 10;
static inline constexpr auto lfh = 1.0;
static inline constexpr auto lfh2 = lfh+0.5;
static inline constexpr auto rhs = 2.0;
static inline constexpr auto identf = vnd::TokenType::IDENTIFIER;
static inline constexpr auto inte = vnd::TokenType::INTEGER;
static inline constexpr auto doub = vnd::TokenType::DOUBLE;
static inline constexpr auto oper = vnd::TokenType::OPERATOR;
#define REQ_FORMAT(type, string)  REQUIRE(FORMAT("{}", type) == (string)); // NOLINT(*-macro-usage)
TEST_CASE("corrected format for Tokentype", "[token_type]") {
    using enum vnd::TokenType;
    REQ_FORMAT(INTEGER, "INTEGER");
    REQ_FORMAT(DOUBLE,"DOUBLE");
    REQ_FORMAT(BOOLEAN, "BOOLEAN")
    REQ_FORMAT(OPERATOR, "OPERATOR");
    REQ_FORMAT(MINUS_OPERATOR, "MINUS_OPERATOR");
    REQ_FORMAT(EQUAL_OPERATOR, "EQUAL_OPERATOR");
    REQ_FORMAT(DOT_OPERATOR, "DOT_OPERATOR");
    REQ_FORMAT(IDENTIFIER,"IDENTIFIER");
    REQ_FORMAT(CHAR, "CHAR");
    REQ_FORMAT(STRING, "STRING");
    REQ_FORMAT(K_MAIN,"K_MAIN");
    REQ_FORMAT(K_VAR, "K_VAR");
    REQ_FORMAT(K_STRUCTURE, "K_STRUCTURE");
    REQ_FORMAT(K_FOR, "K_FOR");
    REQ_FORMAT(K_FUN, "K_FUN");
    REQ_FORMAT(K_RETURN, "K_RETURN");
    REQ_FORMAT(OPEN_PARENTESIS, "OPEN_PARENTESIS");
    REQ_FORMAT(OPEN_SQ_PARENTESIS, "OPEN_SQ_PARENTESIS");
    REQ_FORMAT(OPEN_CUR_PARENTESIS, "OPEN_CUR_PARENTESIS");
    REQ_FORMAT(CLOSE_PARENTESIS, "CLOSE_PARENTESIS");
    REQ_FORMAT(CLOSE_SQ_PARENTESIS, "CLOSE_SQ_PARENTESIS");
    REQ_FORMAT(CLOSE_CUR_PARENTESIS, "CLOSE_CUR_PARENTESIS");
    REQ_FORMAT(OPERATION_EQUAL, "OPERATION_EQUAL");
    REQ_FORMAT(BOOLEAN_OPERATOR, "BOOLEAN_OPERATOR");
    REQ_FORMAT(NOT_OPERATOR, "NOT_OPERATOR");
    REQ_FORMAT(LOGICAL_OPERATOR, "LOGICAL_OPERATOR");
    REQ_FORMAT(UNARY_OPERATOR, "UNARY_OPERATOR");
    REQ_FORMAT(COMMA, "COMMA");
    REQ_FORMAT(COLON, "COLON");
    REQ_FORMAT(COMMENT, "COMMENT");
    REQ_FORMAT(EOFT,"EOF");
    REQ_FORMAT(UNKNOWN,"UNKNOWN");
}

TEST_CASE("default constructed token", "[token]"){
    vnd::Token token{};
    REQUIRE(token.getType() == vnd::TokenType::UNKNOWN);
    REQUIRE(token.getValue().empty() == true);
    REQUIRE(token.getLine() == 0);
    REQUIRE(token.getColumn() == 0);
}

TEST_CASE("default constructed token toString", "[token]"){
    vnd::Token token{};
    REQUIRE(token.getType() == vnd::TokenType::UNKNOWN);
    REQUIRE(token.getValue().empty() == true);
    REQUIRE(token.getLine() == 0);
    REQUIRE(token.getColumn() == 0);
    REQUIRE(token.to_string() == "(type: UNKNOWN, value: '', source location:(file:unknown, line:0, column:0))");
}

TEST_CASE("default constructed token format", "[token]"){
    vnd::Token token{};
    REQUIRE(token.getType() == vnd::TokenType::UNKNOWN);
    REQUIRE(token.getValue().empty() == true);
    REQUIRE(token.getLine() == 0);
    REQUIRE(token.getColumn() == 0);
    REQUIRE(FORMAT("{}", token) == "(type: UNKNOWN, value: '', source location:(file:unknown, line:0, column:0))");
}

TEST_CASE("default constructed token set propriety", "[token]"){
    vnd::Token token{};
    REQUIRE(token.getType() == vnd::TokenType::UNKNOWN);
    REQUIRE(token.getValue().empty() == true);
    REQUIRE(token.getLine() == 0);
    REQUIRE(token.getColumn() == 0);
    token.setType(vnd::TokenType::INTEGER);
    token.setValue("assss");
    token.setLine(1);
    token.setColumn(1);
    REQUIRE(token.getType() == vnd::TokenType::INTEGER);
    REQUIRE(token.getValue().empty() == false);
    REQUIRE(token.getLine() == 1);
    REQUIRE(token.getColumn() == 1);
}

TEST_CASE("default constructed token set propriety tostring", "[token]"){
    vnd::Token token{};
    REQUIRE(token.getType() == vnd::TokenType::UNKNOWN);
    REQUIRE(token.getValue().empty() == true);
    REQUIRE(token.getLine() == 0);
    REQUIRE(token.getColumn() == 0);
    token.setType(vnd::TokenType::INTEGER);
    token.setValue("assss");
    token.setLine(1);
    token.setColumn(1);
    REQUIRE(token.getType() == vnd::TokenType::INTEGER);
    REQUIRE(token.getValue().empty() == false);
    REQUIRE(token.getLine() == 1);
    REQUIRE(token.getColumn() == 1);
    REQUIRE(token.to_string() == "(type: INTEGER, value: 'assss', source location:(file:unknown, line:1, column:1))");
}

TEST_CASE("default constructed token set propriety format", "[token]"){
    vnd::Token token{};
    REQUIRE(token.getType() == vnd::TokenType::UNKNOWN);
    REQUIRE(token.getValue().empty() == true);
    REQUIRE(token.getLine() == 0);
    REQUIRE(token.getColumn() == 0);
    token.setType(vnd::TokenType::INTEGER);
    token.setValue("assss");
    token.setLine(1);
    token.setColumn(1);
    REQUIRE(token.getType() == vnd::TokenType::INTEGER);
    REQUIRE(token.getValue().empty() == false);
    REQUIRE(token.getLine() == 1);
    REQUIRE(token.getColumn() == 1);
    REQUIRE(FORMAT("{}", token) == "(type: INTEGER, value: 'assss', source location:(file:unknown, line:1, column:1))");
}

TEST_CASE("Token Comparison Equality", "[Token]") {
    vnd::Token token1(oper, "+", vnd::CodeSourceLocation("unkown.vn", line,  colum));
    vnd::Token token2(oper, "+", vnd::CodeSourceLocation("unkown.vn", line,  colum));
    REQUIRE(token1 == token2);
}

TEST_CASE("Token Comparison Inequality", "[Token]") {
    vnd::Token token1(identf, "variable", vnd::CodeSourceLocation("unkown.vn", line,  colum));
    vnd::Token token2(identf, "variable2", vnd::CodeSourceLocation("unkown.vn", line,  colum));
    REQUIRE(token1 != token2);
}

TEST_CASE("tokenizer emit identifier token", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"a a_ a0 a000_","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0] == vnd::Token(identf, "a",vnd::CodeSourceLocation("unkown.vn", 1, 1)));
    REQUIRE(tokens[1] == vnd::Token(identf, "a_",vnd::CodeSourceLocation("unkown.vn", 1, 3)));
    REQUIRE(tokens[2] == vnd::Token(identf, "a0",vnd::CodeSourceLocation("unkown.vn", 1, 6)));
    REQUIRE(tokens[3] == vnd::Token(identf, "a000_",vnd::CodeSourceLocation("unkown.vn", 1, 9)));
}

TEST_CASE("tokenizer emit identifier token new line", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"a a_\na0 a000_","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0] == vnd::Token(identf, "a", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(identf, "a_", vnd::CodeSourceLocation("unkown.vn",1, 3)));
    REQUIRE(tokens[2] == vnd::Token(identf, "a0", vnd::CodeSourceLocation("unkown.vn",2, 1)));
    REQUIRE(tokens[3] == vnd::Token(identf, "a000_",vnd::CodeSourceLocation("unkown.vn", 2, 4)));
}

TEST_CASE("tokenizer emit integer token for hexadecimals numbers", "[tokenizer]"){
    // hexadecimals 0xhexnum a-f A-F 0-9
    vnd::Tokenizer tokenizer{"#0 #23 #24 #ff #7f","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 6);
    REQUIRE(tokens[0] == vnd::Token(inte, "#0",vnd::CodeSourceLocation("unkown.vn", 1, 0)));
    REQUIRE(tokens[1] == vnd::Token(inte, "#23",vnd::CodeSourceLocation("unkown.vn", 1, 3)));
    REQUIRE(tokens[2] == vnd::Token(inte, "#24",vnd::CodeSourceLocation("unkown.vn", 1, 7)));
    REQUIRE(tokens[3] == vnd::Token(inte, "#ff",vnd::CodeSourceLocation("unkown.vn", 1, 11)));
    REQUIRE(tokens[4] == vnd::Token(inte, "#7f",vnd::CodeSourceLocation("unkown.vn", 1, 15)));
}

TEST_CASE("tokenizer emit integer token for octal numbers", "[tokenizer]"){
    // octal 0oOctnum 0-7
    vnd::Tokenizer tokenizer{"#o0 #o23 #o24","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 4);
    REQUIRE(tokens[0] == vnd::Token(inte, "#o0", vnd::CodeSourceLocation("unkown.vn",1, 0)));
    REQUIRE(tokens[1] == vnd::Token(inte, "#o23", vnd::CodeSourceLocation("unkown.vn",1, 4)));
    REQUIRE(tokens[2] == vnd::Token(inte, "#o24", vnd::CodeSourceLocation("unkown.vn",1, 9)));
}

TEST_CASE("tokenizer emit integer token", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"42 333 550 34000000","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0] == vnd::Token(inte, "42", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(inte, "333", vnd::CodeSourceLocation("unkown.vn",1, 4)));
    REQUIRE(tokens[2] == vnd::Token(inte, "550", vnd::CodeSourceLocation("unkown.vn",1, 8)));
    REQUIRE(tokens[3] == vnd::Token(inte, "34000000", vnd::CodeSourceLocation("unkown.vn",1, 12)));
}

TEST_CASE("tokenizer emit integer token new line", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"42 333\n550 34000000","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0] == vnd::Token(inte, "42", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(inte, "333", vnd::CodeSourceLocation("unkown.vn",1, 4)));
    REQUIRE(tokens[2] == vnd::Token(inte, "550", vnd::CodeSourceLocation("unkown.vn",2, 1)));
    REQUIRE(tokens[3] == vnd::Token(inte, "34000000", vnd::CodeSourceLocation("unkown.vn",2, 5)));
}

TEST_CASE("tokenizer emit double token", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"1. 1.0 1e+1 1E+1 1.1e+1 1.1E+1 1e-1 1E-1 1.1e-1 1.1E-1 .4e12","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 12);
    REQUIRE(tokens[0] == vnd::Token(doub, "1.", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(doub, "1.0", vnd::CodeSourceLocation("unkown.vn",1, 4)));
    REQUIRE(tokens[2] == vnd::Token(doub, "1e+1", vnd::CodeSourceLocation("unkown.vn",1, 8)));
    REQUIRE(tokens[3] == vnd::Token(doub, "1E+1", vnd::CodeSourceLocation("unkown.vn",1, 13)));
    REQUIRE(tokens[4] == vnd::Token(doub, "1.1e+1", vnd::CodeSourceLocation("unkown.vn",1, 18)));
    REQUIRE(tokens[5] == vnd::Token(doub, "1.1E+1", vnd::CodeSourceLocation("unkown.vn",1, 25)));
    REQUIRE(tokens[6] == vnd::Token(doub, "1e-1", vnd::CodeSourceLocation("unkown.vn",1, 32)));
    REQUIRE(tokens[7] == vnd::Token(doub, "1E-1", vnd::CodeSourceLocation("unkown.vn",1, 37)));
    REQUIRE(tokens[8] == vnd::Token(doub, "1.1e-1", vnd::CodeSourceLocation("unkown.vn",1, 42)));
    REQUIRE(tokens[9] == vnd::Token(doub, "1.1E-1", vnd::CodeSourceLocation("unkown.vn",1, 49)));
    REQUIRE(tokens[10] == vnd::Token(doub, ".4e12", vnd::CodeSourceLocation("unkown.vn",1, 56)));
}

TEST_CASE("tokenizer emit operator token", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"* / = , : < > ! | & + - ^ .","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 15);
    REQUIRE(tokens[0] == vnd::Token(oper, "*", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(oper, "/", vnd::CodeSourceLocation("unkown.vn",1, 3)));
    REQUIRE(tokens[2] == vnd::Token(vnd::TokenType::EQUAL_OPERATOR, "=", vnd::CodeSourceLocation("unkown.vn",1, 5)));
    REQUIRE(tokens[3] == vnd::Token(vnd::TokenType::COMMA, ",", vnd::CodeSourceLocation("unkown.vn",1, 6)));
    REQUIRE(tokens[4] == vnd::Token(vnd::TokenType::COLON, ":", vnd::CodeSourceLocation("unkown.vn",1, 8)));
    REQUIRE(tokens[5] == vnd::Token(vnd::TokenType::BOOLEAN_OPERATOR, "<", vnd::CodeSourceLocation("unkown.vn",1, 11)));
    REQUIRE(tokens[6] == vnd::Token(vnd::TokenType::BOOLEAN_OPERATOR, ">", vnd::CodeSourceLocation("unkown.vn",1, 13)));
    REQUIRE(tokens[7] == vnd::Token(vnd::TokenType::NOT_OPERATOR, "!", vnd::CodeSourceLocation("unkown.vn",1, 15)));
    REQUIRE(tokens[8] == vnd::Token(oper, "|", vnd::CodeSourceLocation("unkown.vn",1, 17)));
    REQUIRE(tokens[9] == vnd::Token(oper, "&", vnd::CodeSourceLocation("unkown.vn",1, 19)));
    REQUIRE(tokens[10] == vnd::Token(oper, "+", vnd::CodeSourceLocation("unkown.vn",1, 21)));
    REQUIRE(tokens[11] == vnd::Token(vnd::TokenType::MINUS_OPERATOR, "-", vnd::CodeSourceLocation("unkown.vn",1, 23)));
    REQUIRE(tokens[12] == vnd::Token(oper, "^", vnd::CodeSourceLocation("unkown.vn",1, 25)));
    REQUIRE(tokens[13] == vnd::Token(vnd::TokenType::DOT_OPERATOR, ".", vnd::CodeSourceLocation("unkown.vn",1, 27)));
}

TEST_CASE("tokenizer emit operationEqual token", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"+= -= *= /=","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::OPERATION_EQUAL, "+=", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(vnd::TokenType::OPERATION_EQUAL, "-=", vnd::CodeSourceLocation("unkown.vn",1, 4)));
    REQUIRE(tokens[2] == vnd::Token(vnd::TokenType::OPERATION_EQUAL, "*=", vnd::CodeSourceLocation("unkown.vn",1, 7)));
    REQUIRE(tokens[3] == vnd::Token(vnd::TokenType::OPERATION_EQUAL, "/=", vnd::CodeSourceLocation("unkown.vn",1, 10)));
}

TEST_CASE("tokenizer emit boolean operator token", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"== >= <= !=","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::BOOLEAN_OPERATOR, "==", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(vnd::TokenType::BOOLEAN_OPERATOR, ">=", vnd::CodeSourceLocation("unkown.vn",1, 4)));
    REQUIRE(tokens[2] == vnd::Token(vnd::TokenType::BOOLEAN_OPERATOR, "<=", vnd::CodeSourceLocation("unkown.vn",1, 7)));
    REQUIRE(tokens[3] == vnd::Token(vnd::TokenType::BOOLEAN_OPERATOR, "!=", vnd::CodeSourceLocation("unkown.vn",1, 10)));
}

TEST_CASE("tokenizer emit logical operator token", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"&& ||","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::LOGICAL_OPERATOR, "&&", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(vnd::TokenType::LOGICAL_OPERATOR, "||", vnd::CodeSourceLocation("unkown.vn",1, 4)));
}

TEST_CASE("tokenizer emit unary operator token", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"++ --","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::UNARY_OPERATOR, "++", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(vnd::TokenType::UNARY_OPERATOR, "--", vnd::CodeSourceLocation("unkown.vn",1, 4)));
}

TEST_CASE("tokenizer emit parenthesis token", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"( )","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::OPEN_PARENTESIS, "(", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(vnd::TokenType::CLOSE_PARENTESIS, ")", vnd::CodeSourceLocation("unkown.vn",1, 3)));
}

TEST_CASE("tokenizer emit square parenthesis token", "[tokenizer]"){
    vnd::Tokenizer tokenizer{"[ ]","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::OPEN_SQ_PARENTESIS, "[", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(vnd::TokenType::CLOSE_SQ_PARENTESIS, "]", vnd::CodeSourceLocation("unkown.vn",1, 3)));
}

TEST_CASE("Tokenizer emit square curly token", "[Tokenizer]"){
    vnd::Tokenizer tokenizer{"{ }","unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::OPEN_CUR_PARENTESIS, "{", vnd::CodeSourceLocation("unkown.vn",1, 1)));
    REQUIRE(tokens[1] == vnd::Token(vnd::TokenType::CLOSE_CUR_PARENTESIS, "}", vnd::CodeSourceLocation("unkown.vn",1, 3)));
}

TEST_CASE("Tokenizer emit char token", "[Tokenizer]"){
    constexpr std::string_view code2 = R"('a' '\\' '')";
    vnd::Tokenizer tokenizer{code2,"unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 4);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::CHAR, "a", vnd::CodeSourceLocation("unkown.vn",1, 2)));
    REQUIRE(tokens[1] == vnd::Token(vnd::TokenType::CHAR,  R"(\\)", vnd::CodeSourceLocation("unkown.vn",1, 6)));
    REQUIRE(tokens[2] == vnd::Token(vnd::TokenType::CHAR, "", vnd::CodeSourceLocation("unkown.vn",1, 11)));
}

TEST_CASE("Tokenizer emit exception for unkonwn char", "[Tokenizer]") {
    vnd::Tokenizer tokenizer{";","unkown.vn"};
    REQUIRE_THROWS_AS(tokenizer.tokenize(), std::runtime_error);
}

TEST_CASE("Tokenizer emit string token", "[Tokenizer]"){
    constexpr std::string_view code2 = R"("a" "\\" "")";
    vnd::Tokenizer tokenizer{code2,"unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 4);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::STRING, "a", vnd::CodeSourceLocation("unkown.vn",1,1)));
    REQUIRE(tokens[1] == vnd::Token(vnd::TokenType::STRING, R"(\\)", vnd::CodeSourceLocation("unkown.vn",1, 5)));
    REQUIRE(tokens[2] == vnd::Token(vnd::TokenType::STRING, "", vnd::CodeSourceLocation("unkown.vn",1, 10)));
}

TEST_CASE("tokenizer emit unknown token on non closed char token", "[tokenizer]"){
    constexpr std::string_view code2 = R"('a")";
    vnd::Tokenizer tokenizer{code2,"unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::UNKNOWN, R"(a")", vnd::CodeSourceLocation("unkown.vn",1, 2)));
}

TEST_CASE("tokenizer emit comment token", "[tokenizer]"){
    constexpr std::string_view code2 = R"(// line comment)";
    vnd::Tokenizer tokenizer{code2,"unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::COMMENT, "// line comment", vnd::CodeSourceLocation("unkown.vn",1, 1)));
}

TEST_CASE("tokenizer emit multiline comment token", "[tokenizer]"){
    constexpr std::string_view code2 = R"(/*multi\nline\ncomment*/)";
    vnd::Tokenizer tokenizer{code2,"unkown.vn"};
    std::vector<vnd::Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0] == vnd::Token(vnd::TokenType::COMMENT, R"(/*multi\nline\ncomment*/)", vnd::CodeSourceLocation("unkown.vn",1, 1)));
}


/*
TEST_CASE("tokenizer emit unknown token on non closed string token", "[tokenizer]"){
    constexpr std::string_view code2 = R"("a')";
    Tokenizer tokenizer{code2,"unkown.vn"};
    std::vector<Token> tokens = tokenizer.tokenize();
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0] == Token(TokenType::UNKNOWN, R"(a')", vnd::CodeSourceLocation("unkown.vn",1, 2)));
}*/
TEST_CASE("corrected format for InstructionType", "[Instruction_type]") {
    using enum vnd::InstructionType;
    REQ_FORMAT(PARAMETER_EXPRESSION, "PARAMETER_EXPRESSION");
    REQ_FORMAT(OPERATION, "OPERATION");
    REQ_FORMAT(ASSIGNATION, "ASSIGNATION")
    REQ_FORMAT(EXPRESSION, "EXPRESSION");
    REQ_FORMAT(SQUARE_EXPRESSION, "SQUARE_EXPRESSION");
    REQ_FORMAT(RETURN_EXPRESSION, "RETURN_EXPRESSION");
    REQ_FORMAT(DECLARATION, "DECLARATION");
    REQ_FORMAT(INITIALIZATION, "INITIALIZATION");
    REQ_FORMAT(ARRAY_INIZIALIZATION, "ARRAY_INIZIALIZATION");
    REQ_FORMAT(MAIN, "MAIN");
    REQ_FORMAT(STRUCTURE, "STRUCTURE");
    REQ_FORMAT(FOR_STRUCTURE, "FOR_STRUCTURE");
    REQ_FORMAT(FOR_INITIALIZATION, "FOR_INITIALIZATION");
    REQ_FORMAT(FOR_CONDITION, "FOR_CONDITION");
    REQ_FORMAT(FOR_STEP, "FOR_STEP");
    REQ_FORMAT(DEFINITION, "DEFINITION");
    REQ_FORMAT(PARAMETER_DEFINITION, "PARAMETER_DEFINITION");
    REQ_FORMAT(RETURN_DEFINITION, "RETURN_DEFINITION");
    REQ_FORMAT(OPEN_SCOPE, "OPEN_SCOPE");
    REQ_FORMAT(CLOSE_SCOPE, "CLOSE_SCOPE");
    REQ_FORMAT(BLANK, "BLANK");
}

TEST_CASE("Instruction typeToString function", "[Instruction]") {
    vnd::Instruction instruction = vnd::Instruction::create("unkown.vn");
    std::vector<std::string> result = instruction.typeToString();
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == "BLANK");
}

TEST_CASE("Instruction checkToken function for valid tokens", "[Instruction]") {
    vnd::Instruction instruction = vnd::Instruction::create("unkown.vn");
    vnd::Token identifierToken(vnd::TokenType::IDENTIFIER, "variable", vnd::CodeSourceLocation("unkown.vn",1, 2));
    instruction.checkToken(identifierToken);
    REQUIRE(instruction.canTerminate() == true);
}

TEST_CASE("Instruction checkToken function for invalid tokens", "[Instruction]") {
    vnd::Instruction instruction = vnd::Instruction::create("unkown.vn");
    vnd::Token invalidToken(vnd::TokenType::UNKNOWN, "invalid", vnd::CodeSourceLocation("unkown.vn",1, 2));
    REQUIRE_THROWS_AS(instruction.checkToken(invalidToken), vnd::InstructionException);
}

TEST_CASE("Corrected type of assignation istruction","[Instruction]") {
    vnd::Instruction instruction = vnd::Instruction::create("unkown.vn");
    REQUIRE(instruction.getLastType() == vnd::InstructionType::BLANK);
    instruction.checkToken(vnd::Token{vnd::TokenType::IDENTIFIER, "a", vnd::CodeSourceLocation("unkown.vn",1, 0)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::OPERATION);
    instruction.checkToken(vnd::Token{vnd::TokenType::EQUAL_OPERATOR, "", vnd::CodeSourceLocation("unkown.vn",1, 1)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::ASSIGNATION);
    instruction.checkToken(vnd::Token{vnd::TokenType::OPEN_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",1, 2)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::EXPRESSION);
}

TEST_CASE("Corrected type of multy assignation instruction","[Instruction]") {
    vnd::Instruction instruction = vnd::Instruction::create("unkown.vn");
    instruction.checkToken(vnd::Token{vnd::TokenType::K_VAR, "", vnd::CodeSourceLocation("unkown.vn",0, 0)});
    instruction.checkToken(vnd::Token{vnd::TokenType::IDENTIFIER, "", vnd::CodeSourceLocation("unkown.vn",0, 1)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::DECLARATION);
    instruction.checkToken(vnd::Token{vnd::TokenType::COLON, "", vnd::CodeSourceLocation("unkown.vn",0, 2)});
    instruction.checkToken(vnd::Token{vnd::TokenType::IDENTIFIER, "", vnd::CodeSourceLocation("unkown.vn",0, 3)});
    instruction.checkToken(vnd::Token{vnd::TokenType::OPEN_SQ_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",0, 4)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::SQUARE_EXPRESSION);
    instruction.checkToken(vnd::Token{vnd::TokenType::CLOSE_SQ_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",0, colum2)});
    instruction.checkToken(vnd::Token{vnd::TokenType::EQUAL_OPERATOR, "", vnd::CodeSourceLocation("unkown.vn",0, colum)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::INITIALIZATION);
    instruction.checkToken(vnd::Token{vnd::TokenType::IDENTIFIER, "", vnd::CodeSourceLocation("unkown.vn",0, colum3)});
    instruction.checkToken(vnd::Token{vnd::TokenType::OPEN_SQ_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",0, colum4)});
    instruction.checkToken(vnd::Token{vnd::TokenType::INTEGER, "", vnd::CodeSourceLocation("unkown.vn",0, colum5)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::SQUARE_EXPRESSION);
    instruction.checkToken(vnd::Token{vnd::TokenType::CLOSE_SQ_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",0, colum6)});
}

TEST_CASE("Corrected type of parameter expression instruction","[Instruction]") {
    vnd::Instruction instruction = vnd::Instruction::create("unkown.vn");
    instruction.checkToken(vnd::Token{vnd::TokenType::IDENTIFIER, "", vnd::CodeSourceLocation("unkown.vn",0, 0)});
    instruction.checkToken(vnd::Token{vnd::TokenType::OPEN_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",0, 1)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::PARAMETER_EXPRESSION);
}

TEST_CASE("Corrected type of parameter definition instruction","[Instruction]") {
    vnd::Instruction instruction = vnd::Instruction::create("unkown.vn");
    instruction.checkToken(vnd::Token{vnd::TokenType::K_FUN, "", vnd::CodeSourceLocation("unkown.vn",0, 0)});
    instruction.checkToken(vnd::Token{vnd::TokenType::IDENTIFIER, "", vnd::CodeSourceLocation("unkown.vn",0, 1)});
    instruction.checkToken(vnd::Token{vnd::TokenType::OPEN_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",0, 2)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::PARAMETER_DEFINITION);
    instruction.checkToken(vnd::Token{vnd::TokenType::CLOSE_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",0, 3)});
}

TEST_CASE("Corrected type of return expression instruction","[Instruction]") {
    vnd::Instruction instruction = vnd::Instruction::create("unkown.vn");
    instruction.checkToken(vnd::Token{vnd::TokenType::K_RETURN, "", vnd::CodeSourceLocation("unkown.vn",0, 0)});
    instruction.checkToken(vnd::Token{vnd::TokenType::BOOLEAN, "", vnd::CodeSourceLocation("unkown.vn",0, 1)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::RETURN_EXPRESSION);
}

TEST_CASE("Corrected type of main instruction","[Instruction]") {
    vnd::Instruction instruction = vnd::Instruction::create("unkown.vn");
    instruction.checkToken(vnd::Token{vnd::TokenType::K_MAIN, "", vnd::CodeSourceLocation("unkown.vn",0, 0)});
    instruction.checkToken(vnd::Token{vnd::TokenType::OPEN_CUR_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",0, 1)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::MAIN);
}

TEST_CASE("Corrected type of structure instruction","[Instruction]") {
    vnd::Instruction instruction = vnd::Instruction::create("unkown.vn");
    instruction.checkToken(vnd::Token{vnd::TokenType::K_STRUCTURE, "", vnd::CodeSourceLocation("unkown.vn",0, 0)});
    instruction.checkToken(vnd::Token{vnd::TokenType::OPEN_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",0, 1)});
    instruction.checkToken(vnd::Token{vnd::TokenType::CLOSE_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",0, 2)});
    instruction.checkToken(vnd::Token{vnd::TokenType::OPEN_CUR_PARENTESIS, "", vnd::CodeSourceLocation("unkown.vn",0, 3)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::STRUCTURE);
}

TEST_CASE("Corrected type of for instruction","[Instruction]") {
    vnd::Instruction instruction = vnd::Instruction::create("unkown.vn");
    instruction.checkToken(vnd::Token{vnd::TokenType::K_FOR, "", vnd::CodeSourceLocation("unkown.vn",0, 0)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::FOR_STRUCTURE);
    instruction.checkToken(vnd::Token{vnd::TokenType::IDENTIFIER, "", vnd::CodeSourceLocation("unkown.vn",0, 1)});
    instruction.checkToken(vnd::Token{vnd::TokenType::EQUAL_OPERATOR, "", vnd::CodeSourceLocation("unkown.vn",0, 2)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::FOR_INITIALIZATION);
    instruction.checkToken(vnd::Token{vnd::TokenType::DOUBLE, "", vnd::CodeSourceLocation("unkown.vn",0, 3)});
    instruction.checkToken(vnd::Token{vnd::TokenType::COMMA, "", vnd::CodeSourceLocation("unkown.vn",0, 4)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::FOR_CONDITION);
    instruction.checkToken(vnd::Token{vnd::TokenType::DOUBLE, "", vnd::CodeSourceLocation("unkown.vn",0, colum2)});
    instruction.checkToken(vnd::Token{vnd::TokenType::COMMA, "", vnd::CodeSourceLocation("unkown.vn",0, colum)});
    REQUIRE(instruction.getLastType() == vnd::InstructionType::FOR_STEP);
}

TEST_CASE("Parser emit number node", "[parser]"){
    vnd::Parser parser("1","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::Number);
    const auto * number = dynamic_cast<const NumberNode*>(ast.get());
    REQUIRE(number != nullptr);
    REQUIRE(number->getValue()==lfh);
}

TEST_CASE("Parser emit number node print", "[parser]"){
    vnd::Parser parser("1","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::Number);
    const auto * number = dynamic_cast<const NumberNode*>(ast.get());
    REQUIRE(number != nullptr);
    REQUIRE(number->getValue()==lfh);
    REQUIRE(number->print() == "NUMBER(1)");
}

TEST_CASE("Parser emit number node compat print", "[parser]"){
    vnd::Parser parser("1","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::Number);
    const auto * number = dynamic_cast<const NumberNode*>(ast.get());
    REQUIRE(number != nullptr);
    REQUIRE(number->getValue()==lfh);
    REQUIRE(number->comp_print() == "NUM(1)");
}

TEST_CASE("Parser emit variable node", "[parser]"){
    vnd::Parser parser("y","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::Variable);
    const auto * variable = dynamic_cast<const VariableNode*>(ast.get());
    REQUIRE(variable != nullptr);
    REQUIRE(variable->getName() ==  "y");
}

TEST_CASE("Parser emit number node double", "[parser]"){
    vnd::Parser parser("1.5","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::Number);
    const auto * number = dynamic_cast<const NumberNode*>(ast.get());
    REQUIRE(number != nullptr);
    REQUIRE(number->getValue()==lfh2);
}

TEST_CASE("Parser emit number node double print", "[parser]"){
    vnd::Parser parser("1.5","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::Number);
    const auto * number = dynamic_cast<const NumberNode*>(ast.get());
    REQUIRE(number != nullptr);
    REQUIRE(number->getValue()==lfh2);
    REQUIRE(number->print() == "NUMBER(1.5)");
}

TEST_CASE("Parser emit number node double compat print", "[parser]"){
    vnd::Parser parser("1.5","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::Number);
    const auto * number = dynamic_cast<const NumberNode*>(ast.get());
    REQUIRE(number != nullptr);
    REQUIRE(number->getValue()==lfh2);
    REQUIRE(number->comp_print() == "NUM(1.5)");
}


TEST_CASE("Parser emit variable node print", "[parser]"){
    vnd::Parser parser("y","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::Variable);
    const auto * variable = dynamic_cast<const VariableNode*>(ast.get());
    REQUIRE(variable != nullptr);
    REQUIRE(variable->getName() ==  "y");
    REQUIRE(variable->print()=="VARIABLE (y)");
}

TEST_CASE("Parser emit variable node compat print", "[parser]"){
    vnd::Parser parser("y","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::Variable);
    const auto * variable = dynamic_cast<const VariableNode*>(ast.get());
    REQUIRE(variable != nullptr);
    REQUIRE(variable->getName() ==  "y");
    REQUIRE(variable->comp_print()=="VAR(y)");
}

TEST_CASE("Parser emit unary expression node", "[parser]") {
    vnd::Parser parser("-x","unkown.vn");
    auto ast = parser.parse();

    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::UnaryExpression);

    const auto* unaryNode = dynamic_cast<const UnaryExpressionNode*>(ast.get());

    // Check the operator and operand
    REQUIRE(unaryNode->getOp() == "-");

    const auto& operand = unaryNode->getOperand();
    REQUIRE(operand != nullptr);
    REQUIRE(operand->getType() == NodeType::Variable);

    const auto* variableNode = dynamic_cast<const VariableNode*>(operand.get());
    REQUIRE(variableNode != nullptr);
    REQUIRE(variableNode->getName() == "x");
}

TEST_CASE("Parser emit unary expression node print", "[parser]") {
    vnd::Parser parser("-x","unkown.vn");
    auto ast = parser.parse();

    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::UnaryExpression);

    const auto* unaryNode = dynamic_cast<const UnaryExpressionNode*>(ast.get());

    // Check the operator and operand
    REQUIRE(unaryNode->getOp() == "-");

    const auto& operand = unaryNode->getOperand();
    REQUIRE(operand != nullptr);
    REQUIRE(operand->getType() == NodeType::Variable);

    const auto* variableNode = dynamic_cast<const VariableNode*>(operand.get());
    REQUIRE(variableNode != nullptr);
    REQUIRE(variableNode->getName() == "x");
    REQUIRE(unaryNode->print()== "UNARY_EXPRESION(op:\"-\" operand:VARIABLE (x))");
}

TEST_CASE("Parser emit unary expression node compat print", "[parser]") {
    vnd::Parser parser("-x","unkown.vn");
    auto ast = parser.parse();

    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::UnaryExpression);

    const auto* unaryNode = dynamic_cast<const UnaryExpressionNode*>(ast.get());

    // Check the operator and operand
    REQUIRE(unaryNode->getOp() == "-");

    const auto& operand = unaryNode->getOperand();
    REQUIRE(operand != nullptr);
    REQUIRE(operand->getType() == NodeType::Variable);

    const auto* variableNode = dynamic_cast<const VariableNode*>(operand.get());
    REQUIRE(variableNode != nullptr);
    REQUIRE(variableNode->getName() == "x");
    REQUIRE(unaryNode->comp_print()== "UNE(op:\"-\" opr:VAR(x))");
}



TEST_CASE("Parser emit binary expression node", "[parser]") {
    vnd::Parser parser("1 + 2","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());
    REQUIRE(binaryNode != nullptr);

    // Check the operation
    REQUIRE(binaryNode->getOp() == "+");

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());

    REQUIRE(leftNumber != nullptr);
    REQUIRE(rightNumber != nullptr);

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rightNumber->getValue() == rhs);
}

TEST_CASE("Parser emit binary expression node multiply", "[parser]") {
    vnd::Parser parser("1 * 2","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());
    REQUIRE(binaryNode != nullptr);

    // Check the operation
    REQUIRE(binaryNode->getOp() == "*");

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());

    REQUIRE(leftNumber != nullptr);
    REQUIRE(rightNumber != nullptr);

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rightNumber->getValue() == rhs);
}

TEST_CASE("Parser emit binary expression node divide", "[parser]") {
    vnd::Parser parser("1 / 2","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());
    REQUIRE(binaryNode != nullptr);

    // Check the operation
    REQUIRE(binaryNode->getOp() == "/");

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());

    REQUIRE(leftNumber != nullptr);
    REQUIRE(rightNumber != nullptr);

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rightNumber->getValue() == rhs);
}

TEST_CASE("Parser emit binary expression node multiply print", "[parser]") {
    vnd::Parser parser("1 * 2","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());
    REQUIRE(binaryNode != nullptr);

    // Check the operation
    REQUIRE(binaryNode->getOp() == "*");

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());

    REQUIRE(leftNumber != nullptr);
    REQUIRE(rightNumber != nullptr);

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rightNumber->getValue() == rhs);
    REQUIRE(binaryNode->print() == "BINARY_EXPRESION(op:\"*\" left:NUMBER(1), right:NUMBER(2))");
}

TEST_CASE("Parser emit binary expression node divide print", "[parser]") {
    vnd::Parser parser("1 / 2","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());
    REQUIRE(binaryNode != nullptr);

    // Check the operation
    REQUIRE(binaryNode->getOp() == "/");

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());

    REQUIRE(leftNumber != nullptr);
    REQUIRE(rightNumber != nullptr);

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rightNumber->getValue() == rhs);
    REQUIRE(binaryNode->print() == "BINARY_EXPRESION(op:\"/\" left:NUMBER(1), right:NUMBER(2))");
}

TEST_CASE("Parser emit binary expression node multiply comp print", "[parser]") {
    vnd::Parser parser("1 * 2","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());
    REQUIRE(binaryNode != nullptr);

    // Check the operation
    REQUIRE(binaryNode->getOp() == "*");

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());

    REQUIRE(leftNumber != nullptr);
    REQUIRE(rightNumber != nullptr);

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rightNumber->getValue() == rhs);
    REQUIRE(binaryNode->comp_print() == "BINE(op:\"*\" l:NUM(1), r:NUM(2))");
}

TEST_CASE("Parser emit binary expression node divide comp print", "[parser]") {
    vnd::Parser parser("1 / 2","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());
    REQUIRE(binaryNode != nullptr);

    // Check the operation
    REQUIRE(binaryNode->getOp() == "/");

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());

    REQUIRE(leftNumber != nullptr);
    REQUIRE(rightNumber != nullptr);

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rightNumber->getValue() == rhs);
    REQUIRE(binaryNode->comp_print() == "BINE(op:\"/\" l:NUM(1), r:NUM(2))");
}

TEST_CASE("Parser emit binary expression node print", "[parser]") {
    vnd::Parser parser("1 + 2","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());

    // Check the operation
    REQUIRE(binaryNode->getOp() == "+");

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());

    REQUIRE(leftNumber != nullptr);
    REQUIRE(rightNumber != nullptr);

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rightNumber->getValue() == rhs);
    REQUIRE(binaryNode->print()== "BINARY_EXPRESION(op:\"+\" left:NUMBER(1), right:NUMBER(2))");
}

TEST_CASE("Parser emit binary expression node compact print", "[parser]") {
    vnd::Parser parser("1 + 2","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());

    // Check the operation
    REQUIRE(binaryNode->getOp() == "+");

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());

    REQUIRE(leftNumber != nullptr);
    REQUIRE(rightNumber != nullptr);

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rightNumber->getValue() == rhs);
    REQUIRE(binaryNode->comp_print() == "BINE(op:\"+\" l:NUM(1), r:NUM(2))");
}

TEST_CASE("Parser emit binary expression node parentesis", "[parser]") {
    vnd::Parser parser("1 + (2 + 3)","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());

    // Check the operation
    REQUIRE(binaryNode->getOp() == "+");

    REQUIRE(binaryNode->getLeft()->getType() == NodeType::Number);
    REQUIRE(binaryNode->getRight()->getType() == NodeType::BinaryExpression);

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * right = dynamic_cast<const BinaryExpressionNode*>(binaryNode->getRight().get());
    REQUIRE(leftNumber != nullptr);
    REQUIRE(right != nullptr);
    // Check the left and right operands
    const auto * rLeftNumber = dynamic_cast<const NumberNode*>(right->getLeft().get());
    const auto * rRightNumber = dynamic_cast<const NumberNode*>(right->getRight().get());

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rLeftNumber->getValue() == rhs);
    REQUIRE(rRightNumber->getValue() == rhs+1);
}

TEST_CASE("Parser emit binary expression node parentesis 2", "[parser]") {
    vnd::Parser parser("(2 + 3) + 1","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());

    // Check the operation
    REQUIRE(binaryNode->getOp() == "+");

    REQUIRE(binaryNode->getLeft()->getType() == NodeType::BinaryExpression);
    REQUIRE(binaryNode->getRight()->getType() == NodeType::Number);

    // Check the left and right operands
    const auto * left = dynamic_cast<const BinaryExpressionNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());
    REQUIRE(left != nullptr);
    REQUIRE(rightNumber != nullptr);
    // Check the left and right operands
    const auto * lLeftNumber = dynamic_cast<const NumberNode*>(left->getLeft().get());
    const auto * lRightNumber = dynamic_cast<const NumberNode*>(left->getRight().get());

    // Check the values of left and right operands
    REQUIRE(lLeftNumber->getValue() == rhs);
    REQUIRE(lRightNumber->getValue() == rhs+1);
    REQUIRE(rightNumber->getValue() == lfh);
}


TEST_CASE("Parser emit binary expression node parentesis print", "[parser]") {
    vnd::Parser parser("1 + (2 + 3)","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());

    // Check the operation
    REQUIRE(binaryNode->getOp() == "+");

    REQUIRE(binaryNode->getLeft()->getType() == NodeType::Number);
    REQUIRE(binaryNode->getRight()->getType() == NodeType::BinaryExpression);

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * right = dynamic_cast<const BinaryExpressionNode*>(binaryNode->getRight().get());
    REQUIRE(leftNumber != nullptr);
    REQUIRE(right != nullptr);
    // Check the left and right operands
    const auto * rLeftNumber = dynamic_cast<const NumberNode*>(right->getLeft().get());
    const auto * rRightNumber = dynamic_cast<const NumberNode*>(right->getRight().get());

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rLeftNumber->getValue() == rhs);
    REQUIRE(rRightNumber->getValue() == rhs+1);
    REQUIRE(binaryNode->print()== "BINARY_EXPRESION(op:\"+\" left:NUMBER(1), right:BINARY_EXPRESION(op:\"+\" left:NUMBER(2), right:NUMBER(3)))");
}

TEST_CASE("Parser emit binary expression node parentesis 2 print", "[parser]") {
    vnd::Parser parser("(2 + 3) + 1","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());

    // Check the operation
    REQUIRE(binaryNode->getOp() == "+");

    REQUIRE(binaryNode->getLeft()->getType() == NodeType::BinaryExpression);
    REQUIRE(binaryNode->getRight()->getType() == NodeType::Number);

    // Check the left and right operands
    const auto * left = dynamic_cast<const BinaryExpressionNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());
    REQUIRE(left != nullptr);
    REQUIRE(rightNumber != nullptr);
    // Check the left and right operands
    const auto * lLeftNumber = dynamic_cast<const NumberNode*>(left->getLeft().get());
    const auto * lRightNumber = dynamic_cast<const NumberNode*>(left->getRight().get());

    // Check the values of left and right operands
    REQUIRE(lLeftNumber->getValue() == rhs);
    REQUIRE(lRightNumber->getValue() == rhs+1);
    REQUIRE(rightNumber->getValue() == lfh);
    REQUIRE(binaryNode->print()== "BINARY_EXPRESION(op:\"+\" left:BINARY_EXPRESION(op:\"+\" left:NUMBER(2), right:NUMBER(3)), right:NUMBER(1))");
}


TEST_CASE("Parser emit binary expression node parentesis compat print", "[parser]") {
    vnd::Parser parser("1 + (2 + 3)","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());

    // Check the operation
    REQUIRE(binaryNode->getOp() == "+");

    REQUIRE(binaryNode->getLeft()->getType() == NodeType::Number);
    REQUIRE(binaryNode->getRight()->getType() == NodeType::BinaryExpression);

    // Check the left and right operands
    const auto * leftNumber = dynamic_cast<const NumberNode*>(binaryNode->getLeft().get());
    const auto * right = dynamic_cast<const BinaryExpressionNode*>(binaryNode->getRight().get());
    REQUIRE(leftNumber != nullptr);
    REQUIRE(right != nullptr);
    // Check the left and right operands
    const auto * rLeftNumber = dynamic_cast<const NumberNode*>(right->getLeft().get());
    const auto * rRightNumber = dynamic_cast<const NumberNode*>(right->getRight().get());

    // Check the values of left and right operands
    REQUIRE(leftNumber->getValue() == lfh);
    REQUIRE(rLeftNumber->getValue() == rhs);
    REQUIRE(rRightNumber->getValue() == rhs+1);
    REQUIRE(binaryNode->comp_print() == "BINE(op:\"+\" l:NUM(1), r:BINE(op:\"+\" l:NUM(2), r:NUM(3)))");
}

TEST_CASE("Parser emit binary expression node parentesis 2 compat print", "[parser]") {
    vnd::Parser parser("(2 + 3) + 1","unkown.vn");
    auto ast = parser.parse();
    REQUIRE(ast != nullptr);
    REQUIRE(ast->getType() == NodeType::BinaryExpression);

    const auto* binaryNode = dynamic_cast<const BinaryExpressionNode*>(ast.get());

    // Check the operation
    REQUIRE(binaryNode->getOp() == "+");

    REQUIRE(binaryNode->getLeft()->getType() == NodeType::BinaryExpression);
    REQUIRE(binaryNode->getRight()->getType() == NodeType::Number);

    // Check the left and right operands
    const auto * left = dynamic_cast<const BinaryExpressionNode*>(binaryNode->getLeft().get());
    const auto * rightNumber = dynamic_cast<const NumberNode*>(binaryNode->getRight().get());
    REQUIRE(left != nullptr);
    REQUIRE(rightNumber != nullptr);
    // Check the left and right operands
    const auto * lLeftNumber = dynamic_cast<const NumberNode*>(left->getLeft().get());
    const auto * lRightNumber = dynamic_cast<const NumberNode*>(left->getRight().get());

    // Check the values of left and right operands
    REQUIRE(lLeftNumber->getValue() == rhs);
    REQUIRE(lRightNumber->getValue() == rhs+1);
    REQUIRE(rightNumber->getValue() == lfh);
    REQUIRE(binaryNode->comp_print()== "BINE(op:\"+\" l:BINE(op:\"+\" l:NUM(2), r:NUM(3)), r:NUM(1))");
}