//
// Created by gbian on 02/02/2024.
//

// NOLINTBEGIN(*-include-cleaner)
#pragma once
#include "../headers.hpp"

/**
 * \cond
 */
DISABLE_WARNINGS_PUSH(26447)
/** \endcond */

namespace vnd {
    /**
     * @brief Represents the source location in code (file, line, column).
     * This class provides a representation of the source location in code, including
     * the file name, line number, and column number.
     */
    class CodeSourceLocation {
    public:
        /**
         * @brief Default constructor.
         * @details Constructs a CodeSourceLocation with default values.
         */
        CodeSourceLocation() noexcept = default;

        /**
         * @brief Constructor with all parameters.
         * @param fileName The name of the source file.
         * @param line The line number in the source file.
         * @param column The column number in the source file.
         */
        CodeSourceLocation(const std::string_view fileName, std::size_t line, std::size_t column) noexcept
          : _fileName(fileName), _line(line), _column(column) {}

        /**
         * @brief Perfect forwarding constructor.
         * @param fileName The name of the source file.
         * @param line The line number in the source file.
         * @param column The column number in the source file.
         */
        template <typename StringOrStringView>
        CodeSourceLocation(StringOrStringView &&fileName, std::size_t line, std::size_t column) noexcept
          : _fileName(std::forward<std::decay_t<StringOrStringView>>(fileName)), _line(line), _column(column) {}

        /**
         * @brief Copy constructor.
         * @param other The CodeSourceLocation object to copy.
         */
        CodeSourceLocation(const CodeSourceLocation &other) = default;

        /**
         * @brief Move constructor.
         * @param other The CodeSourceLocation object to move.
         */
        CodeSourceLocation(CodeSourceLocation &&other) noexcept = default;

        /**
         * @brief Copy assignment operator.
         * @param other The CodeSourceLocation object to copy.
         * @return A reference to the assigned CodeSourceLocation.
         */
        CodeSourceLocation &operator=(const CodeSourceLocation &other) = default;

        /**
         * @brief Move assignment operator.
         * @param other The CodeSourceLocation object to move.
         * @return A reference to the assigned CodeSourceLocation.
         */
        CodeSourceLocation &operator=(CodeSourceLocation &&other) noexcept = default;

        /**
         * @brief Destructor.
         */
        ~CodeSourceLocation() = default;

        /**
         * @brief Getter method for file name.
         * @return The file name as a string view.
         */
        [[nodiscard]] std::string_view getFileName() const noexcept { return _fileName; }

        /**
         * @brief Getter method for line number.
         * @return The line number.
         */
        [[nodiscard]] std::size_t getLine() const noexcept { return _line; }

        /**
         * @brief Getter method for column number.
         * @return The column number.
         */
        [[nodiscard]] std::size_t getColumn() const noexcept { return _column; }

        /**
         * @brief Setter method for file name.
         * @param fileName The name of the source file.
         */
        void setFileName(std::string_view fileName) noexcept { _fileName = fileName; }

        /**
         * @brief Setter method for line number.
         * @param line The line number in the source file.
         */
        void setLine(std::size_t line) noexcept { _line = line; }

        /**
         * @brief Setter method for column number.
         * @param column The column number in the source file.
         */
        void setColumn(std::size_t column) noexcept { _column = column; }

        /**
         * @brief Creates a CodeSourceLocation object representing an unknown location.
         * @return A CodeSourceLocation object with "unknown" file name and (0, 0) coordinates.
         */
        static CodeSourceLocation unknown() noexcept { return CodeSourceLocation("unknown", 0, 0); }

        /**
         * @brief Equality operator.
         * @param other The CodeSourceLocation to compare with.
         * @return True if the CodeSourceLocations are equal, false otherwise.
         */
        bool operator==(const CodeSourceLocation &other) const noexcept = default;

        /**
         * @brief Inequality operator.
         * @param other The CodeSourceLocation to compare with.
         * @return True if the CodeSourceLocations are not equal, false otherwise.
         */
        bool operator!=(const CodeSourceLocation &other) const noexcept = default;

        /**
         * @brief Spaceship operator for comparison.
         * @param other The CodeSourceLocation to compare with.
         * @return The result of the three-way comparison.
         */
        auto operator<=>(const CodeSourceLocation &other) const noexcept = default;

        [[nodiscard]] std::string toString() const noexcept { return FORMAT("(file:{}, line:{}, column:{})", _fileName, _line, _column); }
        [[nodiscard]] std::string compat_to_string() const noexcept { return FORMAT("(f:{}, l:{}, c:{})", _fileName, _line, _column); }

    private:
        std::string_view _fileName;  ///< The name of the source file.
        std::size_t _line{};         ///< The line number in the source file.
        std::size_t _column{};       ///< The column number in the source file.
    };

}  // namespace vnd

DISABLE_WARNINGS_POP()

/**
 * This function is a formatter for CodeSourceLocation using fmt.
 * \cond
 */
// NOLINTNEXTLINE
template <> struct fmt::formatter<vnd::CodeSourceLocation> : fmt::formatter<std::string_view> {
    auto format(const vnd::CodeSourceLocation &val, format_context &ctx) const -> format_context::iterator {
        return fmt::formatter<std::string_view>::format(val.toString(), ctx);
    }
};
/** \endcond */
// NOLINTEND(*-include-cleaner)
