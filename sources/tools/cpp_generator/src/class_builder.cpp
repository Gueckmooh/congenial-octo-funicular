module;

#include <string>
#include <vector>

#include "crafting_interpreters/cpp_generator/export.hpp"

export module cpp_generator:ClassBuilder;

import :CodeGenerator;

namespace cpp_generator {

namespace {

std::string capitalize(std::string_view s) {
    std::string out{s};
    if (out.length() == 0) {
        return out;
    }
    if (out[0] >= 'a' && out[0] <= 'z') {
        auto c = out[0];
        out[0] = c - 'a' + 'A';
    }
    return out;
}

} // namespace

export class CPP_GENERATOR_EXPORT ClassBuilder : public detail::Generatable {
  private:
    struct FieldInfo {
        std::string type;
        std::string name;

        std::string getterName() const {
            return "get" + capitalize(name);
        }
        std::string setterName() const {
            return "get" + capitalize(name);
        }
        std::string fieldName() const {
            return "m_" + name;
        }
    };

  public:
    ClassBuilder(std::string name)
        : m_name(std::move(name)) {}

    ClassBuilder& withField(std::string type, std::string name) {
        FieldInfo fi{
            .type = std::move(type),
            .name = std::move(name),
        };
        m_fields.emplace_back(std::move(fi));
        return *this;
    }

    void generate(CodeGenerator& gen) const override {
        gen.indent().write("class {} {{\n", m_name);
        gen.updateIndentation(+1);

        gen.halfIndent().write("public:\n");
        for (const auto& field : m_fields) {
            generateFieldGetter(gen, field);
            generateFieldSetter(gen, field);
        }

        gen.halfIndent().write("private:\n");
        for (const auto& field : m_fields) {
            generateField(gen, field);
        }

        gen.updateIndentation(-1);
        gen.indent().write("};\n");
    }

    void generateField(CodeGenerator& gen, const FieldInfo& field) const {
        gen.indent().write("{} {};\n", field.type, field.fieldName());
    }

    void generateFieldGetter(CodeGenerator& gen, const FieldInfo& field) const {
        gen.indent().write("const {}& {} const {{\n", field.type, field.getterName());
        gen.updateIndentation(+1);
        gen.indent().write("return {};\n", field.fieldName());
        gen.updateIndentation(-1);
        gen.indent().write("}").newline();
    }

    void generateFieldSetter(CodeGenerator& gen, const FieldInfo& field) const {
        gen.indent().write("void {}({} value) {{\n", field.getterName(), field.type);
        gen.updateIndentation(+1);
        gen.indent().write("{} = std::move(value);\n", field.fieldName());
        gen.updateIndentation(-1);
        gen.indent().write("}").newline();
    }

  private:
    std::string m_name;
    std::vector<FieldInfo> m_fields;
};

} // namespace cpp_generator
