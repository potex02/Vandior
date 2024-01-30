#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace vnd {

    class Scope {
    public:
        [[nodiscard]] static std::shared_ptr<Scope> create(std::shared_ptr<Scope> parent) noexcept;
        [[nodiscard]] static std::shared_ptr<Scope> createMain() noexcept;
        std::shared_ptr<Scope> getParent() const noexcept;
        void removeParent() noexcept;
        void addType(const std::string_view type) noexcept;
        void addVariable(const std::string_view identifer, const std::string_view type, const bool isConst) noexcept;
        [[nodiscard]] bool isMainScope() const noexcept;
        [[nodiscard]] bool checkType(const std::string_view type) const noexcept;
        [[nodiscard]] std::pair<bool, bool> checkVariable(const std::string_view type, const bool shadowing = false) const noexcept;
    private:
        Scope(std::shared_ptr<Scope> parent) noexcept;
        std::unordered_map<std::string_view, std::string_view> _vars;
        std::unordered_map<std::string_view, std::string_view> _consts;
        std::unordered_set<std::string_view> _types;
        std::shared_ptr<Scope> _parent;
    };

}  // namespace vnd