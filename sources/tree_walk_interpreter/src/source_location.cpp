#include "source_location.hpp"
#include <pthread.h>

namespace tlox {

[[nodiscard]] SourceLocation::SourceLocation()
    : m_line(1)
    , m_column(1) {}

[[nodiscard]] SourceLocation::SourceLocation(std::size_t line, std::size_t column)
    : m_line(line)
    , m_column(column) {}

[[nodiscard]] SourceLocation::SourceLocation(std::filesystem::path filePath,
                                             std::size_t line,
                                             std::size_t column)
    : m_maybeFilePath(std::move(filePath))
    , m_line(line)
    , m_column(column) {}

[[nodiscard]] SourceLocation::SourceLocation(const SourceLocation& other) = default;

[[nodiscard]] SourceLocation::SourceLocation(SourceLocation&& other) = default;

SourceLocation& SourceLocation::operator=(const SourceLocation& other) = default;

SourceLocation& SourceLocation::operator=(SourceLocation&& other) = default;

/// =========
/// Operators
/// =========
///

bool SourceLocation::operator==(const SourceLocation& other) const {
    return m_maybeFilePath == other.m_maybeFilePath && m_line == other.m_line &&
           m_column == other.m_column;
}

bool SourceLocation::operator!=(const SourceLocation& other) const {
    return !operator==(other);
}

/// ==========
/// Propertues
/// ==========
///

bool SourceLocation::isInFile() const {
    return m_maybeFilePath.has_value();
}

const std::optional<std::filesystem::path>& SourceLocation::getFilePath() {
    return m_maybeFilePath;
}

void SourceLocation::setFilePath(std::filesystem::path filePath) {
    m_maybeFilePath = std::move(filePath);
}

void SourceLocation::resetFilePath() {
    m_maybeFilePath.reset();
}

std::size_t SourceLocation::getLine() const {
    return m_line;
}

void SourceLocation::setLine(std::size_t line) {
    m_line = line;
}

void SourceLocation::advanceLine(std::size_t nlines) {
    m_line += nlines;
    m_column = 1;
}

std::size_t SourceLocation::getColumn() const {
    return m_column;
}

void SourceLocation::setColumn(std::size_t column) {
    m_column = column;
}

void SourceLocation::advanceColumn(std::size_t ncolumns) {
    m_column += ncolumns;
}

/// =========
/// Printable
/// =========
///

void SourceLocation::print(std::ostream& os) const noexcept {
    if (m_maybeFilePath) {
        os << *m_maybeFilePath;
    } else {
        os << "<buffer>";
    }
    os << ':' << m_line << ':' << m_column;
}

} // namespace tlox
