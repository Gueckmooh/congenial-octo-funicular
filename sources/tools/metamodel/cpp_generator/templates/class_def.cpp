{% import "class_def_macros.cpp" as macros %}
#include "{{ hpp_file_name }}"
#include <utility>
#include <iostream>

// =============================================================================
// Constructors
// =============================================================================
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

// =============================================================================
// Getters
// =============================================================================
{%- for field in class.fields %}
{{ macros::getter_def(class=class, field=field) }}
{% endfor %}


// =============================================================================
// Setters
// =============================================================================
{%- for field in class.fields %}
{%- if field.attributes.is_mutable %}
{{ macros::setter_def(class=class, field=field) }}
{% endif %}
{%- endfor %}


{%macro print_field(field)%}
os << "{{field.name}} = " << this->{{ field_name(name=field.name) }};
{%endmacro%}
{% if class.attributes.is_printable -%}
void {{class.name}}::print(std::ostream& os) const {
    os << "{{class.name}} { ";
    {%- set_global print_lines = [] %}
    {%- for field in class.fields %}
    {%- set print_line = self::print_field(field=field) %}
    {%- set_global print_lines = print_lines | concat(with=print_line) %}
    {%- endfor %}
    {{- print_lines | join(sep=`os << ", ";\n`) -}}
    os << " }";
}
{% endif %}
