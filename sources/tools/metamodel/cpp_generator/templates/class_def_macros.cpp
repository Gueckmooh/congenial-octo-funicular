{%- macro default_ctor(class) -%}
[[nodiscard]] {{ class.name }}::{{ class.name }}() = default;
{%- endmacro -%}

{%- macro copy_ctor(class) -%}
[[nodiscard]] {{ class.name }}::{{ class.name }}(const {{ class.name }}& other) = default;
{%- endmacro %}

{%- macro move_ctor(class) -%}
[[nodiscard]] {{ class.name }}::{{ class.name }}({{ class.name }}&& other) = default;
{%- endmacro %}

{%- macro copy_opt(class) -%}
{{ class.name }}& {{ class.name }}::operator=(const {{ class.name }}& other) = default;
{%- endmacro %}

{%- macro move_opt(class) -%}
    {{ class.name }}& {{ class.name }}::operator=({{ class.name }}&& other) = default;
{%- endmacro %}

{%- macro maybe_move(var) -%}
{%- if not type_is_trivially_copyable(type=var.ty) %}std::move({{ var.name }}){% else %}{{ var.name }}{% endif -%}
{%- endmacro %}

{%- macro ctor(class) -%}
{%- set_global params = [] %}
{%- for field in class.fields %}
{%- set param = type_str(type=field.ty) ~ " " ~ field.name %}
{%- set_global params = params | concat(with=param) %}
{%- endfor -%}
[[nodiscard]] {{ class.name }}::{{ class.name }}({{ params | join(sep=", ")}})
{%- set_global is_first = true -%}
{%- for field in class.fields %}
    {% if is_first %}: {% else %}, {% endif %}{{ field_name(name=field.name) }}(
        {{- self::maybe_move(var=field) -}}
    )
{%- set_global is_first = false -%}
{% endfor %} {}
{%- endmacro -%}


{% macro getter_def(class, field) -%}
[[nodiscard]] {{ type_str(type=type_view(type=field.ty)) }} {{ class.name }}::{{ getter_name(name=field.name) }}() const {
    return this->{{ field_name(name=field.name) }};
}
{%- endmacro %}


{%- macro setter_def(class, field) -%}
void {{ class.name }}::{{ setter_name(name=field.name) }}({{ type_str(type=field.ty) }} {{ field.name }}) {
    this->{{ field_name(name=field.name) }} = {{ self::maybe_move(var=field) }};
}
{%- endmacro %}
