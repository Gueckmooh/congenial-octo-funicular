{%- macro default_ctor(class) -%}
    [[nodiscard]] {{ class.name }}();
{%- endmacro %}

{%- macro copy_ctor(class) -%}
    [[nodiscard]] {{ class.name }}(const {{ class.name }}& other);
{%- endmacro %}

{%- macro move_ctor(class) -%}
    [[nodiscard]] {{ class.name }}({{ class.name }}&& other);
{%- endmacro %}

{%- macro copy_opt(class) -%}
    {{ class.name }}& operator=(const {{ class.name }}& other);
{%- endmacro %}

{%- macro move_opt(class) -%}
    {{ class.name }}& operator=({{ class.name }}&& other);
{%- endmacro %}

{%- macro ctor(class) %}
{%- set_global params = [] %}
{%- for field in class.fields %}
{%- set param = type_str(type=field.ty) ~ " " ~ field.name %}
{%- set_global params = params | concat(with=param) %}
{%- endfor -%}
    [[nodiscard]] {{ class.name }}({{ params | join(sep=", ") }});
{%- endmacro %}

{%- macro field_decl(field) -%}
    {% if not field.attributes.is_mutable %}const {% endif %}{{ type_str(type=field.ty) }} {{ field_name(name=field.name) }};
{%- endmacro field_decl -%}

{%- macro getter_decl(field) -%}
    [[nodiscard]] {{ type_str(type=type_view(type=field.ty)) }} {{ getter_name(name=field.name) }}() const;
{%- endmacro getter_decl -%}

{%- macro setter_decl(field) -%}
    void {{ setter_name(name=field.name) }}({{ type_str(type=field.ty) }} {{ field.name }});
{%- endmacro setter_decl -%}
