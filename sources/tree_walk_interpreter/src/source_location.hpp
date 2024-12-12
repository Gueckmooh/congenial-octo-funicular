#pragma once

#include <cstddef>
#include <filesystem>
#include <optional>

#include "crafting_interpreters/utilities/printable.hpp"

namespace tlox {


/// The `SourceLocation` class represents a location in the source code,
/// including the file path, line, and column.
///
/// It provides constructors, operators, and methods to work with source code
/// locations.
class SourceLocation : public details::Printable<SourceLocation> {
  public:
    /// ============
    /// Constructors
    /// ============
    ///

    /// Constructs a default SourceLocation with no file path, line, or column.
    [[nodiscard]] SourceLocation();

    /// Constructs a SourceLocation with the given line and column, but no file
    /// path.
    [[nodiscard]] SourceLocation(std::size_t line, std::size_t column);

    /// Constructs a SourceLocation with the given file path, line, and column.
    [[nodiscard]] SourceLocation(std::filesystem::path filePath,
                                 std::size_t line,
                                 std::size_t column);

    /// Copy constructor for SourceLocation.
    [[nodiscard]] SourceLocation(const SourceLocation& other);

    /// Move constructor for SourceLocation.
    [[nodiscard]] SourceLocation(SourceLocation&& other);

    /// Copy assignment operator for SourceLocation.
    SourceLocation& operator=(const SourceLocation& other);

    /// Move assignment operator for SourceLocation.
    SourceLocation& operator=(SourceLocation&& other);

    /// =========
    /// Operators
    /// =========
    ///

    /// Compares two SourceLocation objects for equality.
    ///
    /// @param other The SourceLocation object to compare against.
    /// @return `true` if the two SourceLocation objects have the same file
    /// path, line, and column; `false` otherwise.
    bool operator==(const SourceLocation& other) const;

    /// Compares two SourceLocation objects for inequality.
    ///
    /// @param other The SourceLocation object to compare against.
    /// @return `true` if the two SourceLocation objects do not have the same
    /// file path, line, and column; `false` otherwisej
    bool operator!=(const SourceLocation& other) const;

    /// ==========
    /// Propertues
    /// ==========
    ///

    /// Checks if the SourceLocation has a file path associated with it.
    ///
    /// @return `true` if the SourceLocation has a file path, `false` otherwise.
    bool isInFile() const;

    /// Gets the file path associated with the SourceLocation.
    ///
    /// @return A reference to the optional file path.
    const std::optional<std::filesystem::path>& getFilePath();

    /// Sets the file path associated with the SourceLocation.
    ///
    /// @param filePath The new file path to set.
    void setFilePath(std::filesystem::path filePath);

    /// Resets the file path associated with the SourceLocation, effectively
    /// removing it.
    void resetFilePath();

    /// Gets the line number associated with the SourceLocation.
    ///
    /// @return The line number.
    std::size_t getLine() const;

    /// Sets the line number associated with the SourceLocation.
    ///
    /// @param line The new line number to set.
    void setLine(std::size_t line);

    /// Advances the line number associated with the SourceLocation by the
    /// specified number of lines. It resets the column number to 1.
    ///
    /// @param nlines The number of lines to advance. Defaults to 1 if not
    /// specified.
    void advanceLine(std::size_t nlines = 1);

    /// Gets the column number associated with the SourceLocation.
    ///
    /// @return The column number.
    std::size_t getColumn() const;

    /// Sets the column number associated with the SourceLocation.
    ///
    /// @param column The new column number to set.
    void setColumn(std::size_t column);

    /// Advances the column number associated with the SourceLocation by the
    /// specified number of columns.
    ///
    /// @param ncolumns The number of columns to advance. Defaults to 1 if not
    /// specified.
    void advanceColumn(std::size_t ncolumns = 1);

    /// =========
    /// Printable
    /// =========
    ///

    /// Prints the SourceLocation to the given output stream.
    ///
    /// @param os The output stream to print to.
    void print(std::ostream& os) const noexcept;

  private:
    // @todo perf: consider string interning
    std::optional<std::filesystem::path> m_maybeFilePath;
    std::size_t m_line;
    std::size_t m_column;
};

} // namespace tlox
