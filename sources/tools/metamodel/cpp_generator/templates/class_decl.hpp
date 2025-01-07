{% import "class_decl_macros.hpp" as macros %}
#pragma once
{%for dependency in dependencies%}
#include {{ include_file_for_type(type=dependency) }}
{%endfor%}
#include <ostream>

class {{ class.name }} {
  public:
    // =========================================================================
    // Constructors
    // =========================================================================
    {%- if class.attributes.has_default %}
    {{ macros::default_ctor(class=class) }}
    {%- endif %}
    {{ macros::ctor(class=class) }}

    {{ macros::move_ctor(class=class) }}
    {{ macros::move_opt(class=class) }}

    {% if class.attributes.is_copyable -%}
    {{ macros::copy_ctor(class=class) }}
    {{ macros::copy_opt(class=class) }}
    {%- endif %}

    // =========================================================================
    // Getters
    // =========================================================================
    {%- for field in class.fields %}
    {{ macros::getter_decl(field=field) }}
    {%- endfor %}

    // =========================================================================
    // Setters
    // =========================================================================
    {%- for field in class.fields %}
    {%- if field.attributes.is_mutable %}
    {{ macros::setter_decl(field=field) }}
    {%- endif %}
    {%- endfor %}

    {% if class.attributes.is_printable -%}
    void print(std::ostream& os) const;
    friend inline std::ostream& operator<<(std::ostream& os, const {{ class.name }}& value) {
        value.print(os);
        return os;
    }
    {% endif %}

  private:
    // =========================================================================
    // Fields
    // =========================================================================
    {%- for field in class.fields %}
    {{ macros::field_decl(field=field) }}
    {%- endfor %}
}; // class {{ class.name }}
