#pragma once

#include "headers.hpp"

namespace vnd {

    /**
     * @class FolderCreationResult
     * @brief Represents the result of a folder creation operation.
     */
    class FolderCreationResult {
    public:
        /**
         * @brief Checks if the folder creation was successful.
         * @return True if the folder creation was successful, false otherwise.
         */
        [[nodiscard]] constexpr bool success() const noexcept { return success_; }

        /**
         * @brief Returns the path of the created folder.
         * @return The path of the created folder.
         */
        [[nodiscard]] std::filesystem::path path() const { return path_; }

        /**
         * @brief Returns a reference to the path of the created folder.
         * @return A reference to the path of the created folder.
         */
        [[nodiscard]] std::filesystem::path &pathref() noexcept { return path_; }

        /**
         * @brief Returns a const reference to the path of the created folder.
         * @return A const reference to the path of the created folder.
         */
        [[nodiscard]] const std::filesystem::path &pathcref() const noexcept { return path_; }

        /**
         * @brief Sets the success status of the folder creation.
         * @param success The success status of the folder creation.
         */
        void set_success(const bool success) noexcept { success_ = success; }

        /**
         * @brief Sets the path of the created folder.
         * @param path The path of the created folder.
         * @throws std::invalid_argument if the path is empty.
         */
        void set_path(const std::filesystem::path &path) {
            if(path.empty()) { throw std::invalid_argument("Path cannot be empty"); }
            path_ = path;
        }

        /**
         * @brief Default constructor for FolderCreationResult.
         */
        FolderCreationResult() = default;

        /**
         * @brief Constructs a FolderCreationResult with the specified success status and path.
         * @param success The success status of the folder creation.
         * @param path The path of the created folder.
         */
        FolderCreationResult(const bool success, const std::filesystem::path &path) : success_{success}, path_{path} {}

        /**
         * @brief Copy constructor for FolderCreationResult.
         */
        FolderCreationResult(const FolderCreationResult &other) = default;

        /**
         * @brief Move constructor for FolderCreationResult.
         */
        FolderCreationResult(FolderCreationResult &&other) noexcept = default;

        /**
         * @brief Copy assignment operator for FolderCreationResult.
         */
        FolderCreationResult &operator=(const FolderCreationResult &other) = default;

        /**
         * @brief Move assignment operator for FolderCreationResult.
         */
        FolderCreationResult &operator=(FolderCreationResult &&other) noexcept = default;

        /**
         * @brief Equality operator for FolderCreationResult.
         * @param lhs The left-hand side FolderCreationResult.
         * @param rhs The right-hand side FolderCreationResult.
         * @return True if both FolderCreationResult objects are equal, false otherwise.
         */
        friend bool operator==(const FolderCreationResult &lhs, const FolderCreationResult &rhs) noexcept = default;

        /**
         * @brief Swaps the contents of two FolderCreationResult objects.
         * @param lhs The first FolderCreationResult object.
         * @param rhs The second FolderCreationResult object.
         */
        friend void swap(FolderCreationResult &lhs, FolderCreationResult &rhs) noexcept {
            std::swap(lhs.success_, rhs.success_);
            std::swap(lhs.path_, rhs.path_);
        }

        /**
         * @brief Calculates the hash value of a FolderCreationResult object.
         * @param obj The FolderCreationResult object to hash.
         * @return The hash value of the object.
         */
        friend std::size_t hash_value(const FolderCreationResult &obj) noexcept {
#ifdef __llvm__
            std::hash<bool> bool_hasher;
            std::hash<std::string> string_hasher;
            return bool_hasher(obj.success_) ^ (string_hasher(obj.path_.string()) << 1);
#else
            std::hash<bool> bool_hasher;
            std::hash<std::filesystem::path> path_hasher;
            return bool_hasher(obj.success_) ^ (path_hasher(obj.path_) << 1);
#endif
        }

        /**
         * @brief Outputs the FolderCreationResult object to an output stream.
         * @param os The output stream.
         * @param obj The FolderCreationResult object to output.
         * @return The output stream after writing the FolderCreationResult object.
         */
        friend std::ostream &operator<<(std::ostream &os, const FolderCreationResult &obj) {
            return os << "success_: " << obj.success_ << " path_: " << obj.path_;
        }

        [[nodiscard]] static auto createFolder(const std::string &folderName, const fs::path &parentDir) -> FolderCreationResult {
            // Validate the parameters
            if(folderName.empty()) {
                LERROR("Invalid parameters: parentPath or folderName is empty.");
                return {false, fs ::path()};
            }

            auto newDirPath = parentDir / folderName;
            if(fs::exists(newDirPath)) {
                LWARN("The folder already exists: {}", newDirPath);
                return {true, newDirPath};  // Return true since the folder already exists
            }

            // Create the new directory
            std::error_code error_codec;
            if(fs::create_directories(newDirPath, error_codec)) {
                LINFO("Folder '{}' created successfully at '{}'", folderName, newDirPath);
                return {true, newDirPath};
            } else {
                if(error_codec) {
                    // Log the error with specific details
                    LERROR("Failed to create folder '{}' at '{}': {} (Error code: {})", folderName, newDirPath, error_codec.message(),
                           error_codec.value());
                } else {
                    LERROR("Failed to create folder '{}' at '{}' for an unknown error", folderName, newDirPath);
                }
                return {false, fs ::path()};
            }
        }

        [[nodiscard]] static auto createFolderNextToFile(const fs::path &filePath, const std::string &folderName) -> FolderCreationResult {
            try {
                // Get the parent directory of the file
                auto parentDir = filePath.parent_path();

                // Construct the path for the new directory
                return vnd::FolderCreationResult::createFolder(folderName, parentDir);
            } catch(const std::exception &e) {
                LERROR("Exception occurred: {}", e.what());
                return {false, fs ::path()};
            }
        }

        // Add the to_json and from_json functions here:
        friend void to_json(nlohmann::json &j, const FolderCreationResult &result) {
            j = nlohmann::json{
                {"success", result.success()}, {"path", result.path().string()}  // Convert path to string for JSON
            };
        }

        friend void from_json(const nlohmann::json &j, FolderCreationResult &result) {
            result.set_success(j.at("success").get<bool>());
            result.set_path(j.at("path").get<std::filesystem::path>());
        }

    private:
        bool success_ = false;        ///< The success status of the folder creation.
        std::filesystem::path path_;  ///< The path of the created folder.
    };

}  // namespace vnd
