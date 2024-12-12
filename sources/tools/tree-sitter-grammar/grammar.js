/**
 * @file Grammar grammar for tree-sitter
 * @author Enzo Brignon
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "grammar",

  extras: $ => [
    /\s|\\\r?\n/,
    $.comment,
  ],

  rules: {
    // TODO: add the actual grammar rules
    source_file: $ => repeat($._definition),

    _definition: $ => choice(
      $.terminal_definition,
      $.rule_definition,
    ),

    terminal_definition: $ => seq(
      "terminal",
      field('name', $.symbol),
      ";",
    ),

    rule_definition: $ => seq(
      "rule",
      field('name', $.symbol),
      "->",
      field('body', $.choice),
      ";",
    ),

    choice: $ => $._choice,
    _choice: $ => choice(
      $.sequence,
      seq(
        $.sequence,
        "|",
        $._choice,
      ),
    ),

    sequence: $ => $._sequence,
    _sequence: $ => choice(
      $._rule_element,
      seq(
        $._rule_element,
        $._sequence,
      ),
    ),

    _rule_element: $ => choice(
      $._thing,
      $.affectation,
    ),

    _thing: $ => choice(
      $.symbol,
      $._grouping,
    ),

    _grouping: $ => seq(
      "(",
      $.choice,
      ")",
    ),

    affectation: $ => seq(
      field('name', $.symbol),
      "=",
      field('value', $._thing),
    ),

    symbol: $ => /[a-zA-Z_]+/,

    comment: _ => token(choice(
      seq('//', /(\\+(.|\r?\n)|[^\\\n])*/),
      seq(
        '/*',
        /[^*]*\*+([^/*][^*]*\*+)*/,
        '/',
      ),
    )),
  }
});
