#include <vector>
#include <tuple>
#include <memory>
#include "Token.hpp"
#include "Scope.hpp"
#include "Expression.hpp"

namespace vnd {

    class ExpressionFactory {
    public:
        [[nodiscard]] static ExpressionFactory create(std::vector<Token>::iterator &iterator, std::vector<Token>::iterator end,
                                                      std::shared_ptr<Scope> scope) noexcept;
        [[nodiscard]] static bool isNumber(const std::string &type) noexcept;
        [[nodiscard]] std::string parse(const std::vector<TokenType> &endToken) noexcept;
        [[nodiscard]] std::size_t size() const noexcept;
        [[nodiscard]] bool empty() const noexcept;
        [[nodiscard]] Expression getExpression() noexcept;
    private:
        ExpressionFactory(std::vector<Token>::iterator &iterator, std::vector<Token>::iterator end,
                          std::shared_ptr<Scope> scope) noexcept;
        static std::vector<std::string> _numberTypes;
        [[nodiscard]] static std::string checkType(std::tuple<bool, bool, std::string> &oldType, const std::string_view newType) noexcept;
        std::vector<Token>::iterator &_iterator;
        std::vector<Token>::iterator _end;
        std::shared_ptr<Scope> _scope;
        std::vector<std::string> _text;
        std::vector<Expression> _expressions;
        char _lastOperator;
        [[nodiscard]] std::string_view getTokenType(const Token &token) const noexcept;
        void emplaceToken() noexcept;
        [[nodiscard]] std::string writeToken() noexcept;
        [[nodiscard]] std::string handleInnerExpression(std::tuple<bool, bool, std::string> &type) noexcept;
        [[nodiscard]] std::string handleToken(std::tuple<bool, bool, std::string>& type) noexcept;
    };

}  // namespace vnd