{% import "class_macros.txt" as macros %}
#pragma once

class Class {

  private:
{{- macros::field_decl(name="foo", type="int") }}
{{- macros::field_decl(name="bar", type="int") }}
};
