#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 26
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 24
#define ALIAS_COUNT 0
#define TOKEN_COUNT 11
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 3
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 4

enum ts_symbol_identifiers {
  anon_sym_terminal = 1,
  anon_sym_SEMI = 2,
  anon_sym_rule = 3,
  anon_sym_DASH_GT = 4,
  anon_sym_PIPE = 5,
  anon_sym_LPAREN = 6,
  anon_sym_RPAREN = 7,
  anon_sym_EQ = 8,
  sym_symbol = 9,
  sym_comment = 10,
  sym_source_file = 11,
  sym__definition = 12,
  sym_terminal_definition = 13,
  sym_rule_definition = 14,
  sym_choice = 15,
  sym__choice = 16,
  sym_sequence = 17,
  sym__sequence = 18,
  sym__rule_element = 19,
  sym__thing = 20,
  sym__grouping = 21,
  sym_affectation = 22,
  aux_sym_source_file_repeat1 = 23,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_terminal] = "terminal",
  [anon_sym_SEMI] = ";",
  [anon_sym_rule] = "rule",
  [anon_sym_DASH_GT] = "->",
  [anon_sym_PIPE] = "|",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_EQ] = "=",
  [sym_symbol] = "symbol",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym__definition] = "_definition",
  [sym_terminal_definition] = "terminal_definition",
  [sym_rule_definition] = "rule_definition",
  [sym_choice] = "choice",
  [sym__choice] = "_choice",
  [sym_sequence] = "sequence",
  [sym__sequence] = "_sequence",
  [sym__rule_element] = "_rule_element",
  [sym__thing] = "_thing",
  [sym__grouping] = "_grouping",
  [sym_affectation] = "affectation",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_terminal] = anon_sym_terminal,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_rule] = anon_sym_rule,
  [anon_sym_DASH_GT] = anon_sym_DASH_GT,
  [anon_sym_PIPE] = anon_sym_PIPE,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_EQ] = anon_sym_EQ,
  [sym_symbol] = sym_symbol,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym__definition] = sym__definition,
  [sym_terminal_definition] = sym_terminal_definition,
  [sym_rule_definition] = sym_rule_definition,
  [sym_choice] = sym_choice,
  [sym__choice] = sym__choice,
  [sym_sequence] = sym_sequence,
  [sym__sequence] = sym__sequence,
  [sym__rule_element] = sym__rule_element,
  [sym__thing] = sym__thing,
  [sym__grouping] = sym__grouping,
  [sym_affectation] = sym_affectation,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_terminal] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rule] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [sym_symbol] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__definition] = {
    .visible = false,
    .named = true,
  },
  [sym_terminal_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_rule_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_choice] = {
    .visible = true,
    .named = true,
  },
  [sym__choice] = {
    .visible = false,
    .named = true,
  },
  [sym_sequence] = {
    .visible = true,
    .named = true,
  },
  [sym__sequence] = {
    .visible = false,
    .named = true,
  },
  [sym__rule_element] = {
    .visible = false,
    .named = true,
  },
  [sym__thing] = {
    .visible = false,
    .named = true,
  },
  [sym__grouping] = {
    .visible = false,
    .named = true,
  },
  [sym_affectation] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_body = 1,
  field_name = 2,
  field_value = 3,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_body] = "body",
  [field_name] = "name",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_name, 1},
  [1] =
    {field_body, 3},
    {field_name, 1},
  [3] =
    {field_name, 0},
    {field_value, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(21);
      if (lookahead == '(') ADVANCE(27);
      if (lookahead == ')') ADVANCE(28);
      if (lookahead == '-') ADVANCE(8);
      if (lookahead == '/') ADVANCE(5);
      if (lookahead == ';') ADVANCE(23);
      if (lookahead == '=') ADVANCE(29);
      if (lookahead == '\\') SKIP(20);
      if (lookahead == 'r') ADVANCE(18);
      if (lookahead == 't') ADVANCE(10);
      if (lookahead == '|') ADVANCE(26);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(4);
      END_STATE();
    case 2:
      if (lookahead == '\n') SKIP(4);
      if (lookahead == '\r') SKIP(1);
      END_STATE();
    case 3:
      if (lookahead == '\r') ADVANCE(34);
      if (lookahead == '\\') ADVANCE(32);
      if (lookahead != 0) ADVANCE(33);
      END_STATE();
    case 4:
      if (lookahead == '(') ADVANCE(27);
      if (lookahead == ')') ADVANCE(28);
      if (lookahead == '/') ADVANCE(5);
      if (lookahead == ';') ADVANCE(23);
      if (lookahead == '=') ADVANCE(29);
      if (lookahead == '\\') SKIP(2);
      if (lookahead == '|') ADVANCE(26);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(4);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(30);
      END_STATE();
    case 5:
      if (lookahead == '*') ADVANCE(7);
      if (lookahead == '/') ADVANCE(33);
      END_STATE();
    case 6:
      if (lookahead == '*') ADVANCE(6);
      if (lookahead == '/') ADVANCE(31);
      if (lookahead != 0) ADVANCE(7);
      END_STATE();
    case 7:
      if (lookahead == '*') ADVANCE(6);
      if (lookahead != 0) ADVANCE(7);
      END_STATE();
    case 8:
      if (lookahead == '>') ADVANCE(25);
      END_STATE();
    case 9:
      if (lookahead == 'a') ADVANCE(13);
      END_STATE();
    case 10:
      if (lookahead == 'e') ADVANCE(17);
      END_STATE();
    case 11:
      if (lookahead == 'e') ADVANCE(24);
      END_STATE();
    case 12:
      if (lookahead == 'i') ADVANCE(16);
      END_STATE();
    case 13:
      if (lookahead == 'l') ADVANCE(22);
      END_STATE();
    case 14:
      if (lookahead == 'l') ADVANCE(11);
      END_STATE();
    case 15:
      if (lookahead == 'm') ADVANCE(12);
      END_STATE();
    case 16:
      if (lookahead == 'n') ADVANCE(9);
      END_STATE();
    case 17:
      if (lookahead == 'r') ADVANCE(15);
      END_STATE();
    case 18:
      if (lookahead == 'u') ADVANCE(14);
      END_STATE();
    case 19:
      if (eof) ADVANCE(21);
      if (lookahead == '\n') SKIP(0);
      END_STATE();
    case 20:
      if (eof) ADVANCE(21);
      if (lookahead == '\n') SKIP(0);
      if (lookahead == '\r') SKIP(19);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_terminal);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_rule);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(anon_sym_DASH_GT);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_PIPE);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(sym_symbol);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(30);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\r') ADVANCE(34);
      if (lookahead == '\\') ADVANCE(32);
      if (lookahead != 0) ADVANCE(33);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(3);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(33);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(3);
      if (lookahead != 0) ADVANCE(33);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 4},
  [3] = {.lex_state = 4},
  [4] = {.lex_state = 4},
  [5] = {.lex_state = 4},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 4},
  [9] = {.lex_state = 4},
  [10] = {.lex_state = 4},
  [11] = {.lex_state = 4},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 4},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 0},
  [25] = {.lex_state = 4},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_terminal] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_rule] = ACTIONS(1),
    [anon_sym_DASH_GT] = ACTIONS(1),
    [anon_sym_PIPE] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(24),
    [sym__definition] = STATE(6),
    [sym_terminal_definition] = STATE(6),
    [sym_rule_definition] = STATE(6),
    [aux_sym_source_file_repeat1] = STATE(6),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_terminal] = ACTIONS(7),
    [anon_sym_rule] = ACTIONS(9),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      sym_symbol,
    STATE(15), 1,
      sym_sequence,
    STATE(16), 1,
      sym__sequence,
    STATE(18), 1,
      sym__choice,
    STATE(22), 1,
      sym_choice,
    STATE(4), 4,
      sym__rule_element,
      sym__thing,
      sym__grouping,
      sym_affectation,
  [28] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      sym_symbol,
    STATE(15), 1,
      sym_sequence,
    STATE(16), 1,
      sym__sequence,
    STATE(18), 1,
      sym__choice,
    STATE(20), 1,
      sym_choice,
    STATE(4), 4,
      sym__rule_element,
      sym__thing,
      sym__grouping,
      sym_affectation,
  [56] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      sym_symbol,
    STATE(13), 1,
      sym__sequence,
    ACTIONS(15), 3,
      anon_sym_SEMI,
      anon_sym_PIPE,
      anon_sym_RPAREN,
    STATE(4), 4,
      sym__rule_element,
      sym__thing,
      sym__grouping,
      sym_affectation,
  [80] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      sym_symbol,
    STATE(15), 1,
      sym_sequence,
    STATE(16), 1,
      sym__sequence,
    STATE(17), 1,
      sym__choice,
    STATE(4), 4,
      sym__rule_element,
      sym__thing,
      sym__grouping,
      sym_affectation,
  [105] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_terminal,
    ACTIONS(9), 1,
      anon_sym_rule,
    ACTIONS(17), 1,
      ts_builtin_sym_end,
    STATE(7), 4,
      sym__definition,
      sym_terminal_definition,
      sym_rule_definition,
      aux_sym_source_file_repeat1,
  [124] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      ts_builtin_sym_end,
    ACTIONS(21), 1,
      anon_sym_terminal,
    ACTIONS(24), 1,
      anon_sym_rule,
    STATE(7), 4,
      sym__definition,
      sym_terminal_definition,
      sym_rule_definition,
      aux_sym_source_file_repeat1,
  [143] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(29), 1,
      anon_sym_EQ,
    ACTIONS(27), 5,
      anon_sym_SEMI,
      anon_sym_PIPE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      sym_symbol,
  [157] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 5,
      anon_sym_SEMI,
      anon_sym_PIPE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      sym_symbol,
  [168] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 5,
      anon_sym_SEMI,
      anon_sym_PIPE,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      sym_symbol,
  [179] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(35), 1,
      sym_symbol,
    STATE(9), 2,
      sym__thing,
      sym__grouping,
  [193] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 3,
      ts_builtin_sym_end,
      anon_sym_terminal,
      anon_sym_rule,
  [202] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(39), 3,
      anon_sym_SEMI,
      anon_sym_PIPE,
      anon_sym_RPAREN,
  [211] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(41), 3,
      ts_builtin_sym_end,
      anon_sym_terminal,
      anon_sym_rule,
  [220] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      anon_sym_PIPE,
    ACTIONS(43), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [231] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 3,
      anon_sym_SEMI,
      anon_sym_PIPE,
      anon_sym_RPAREN,
  [240] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [248] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(51), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [256] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(53), 1,
      anon_sym_SEMI,
  [263] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 1,
      anon_sym_RPAREN,
  [270] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(57), 1,
      sym_symbol,
  [277] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(59), 1,
      anon_sym_SEMI,
  [284] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(61), 1,
      anon_sym_DASH_GT,
  [291] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(63), 1,
      ts_builtin_sym_end,
  [298] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(65), 1,
      sym_symbol,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 28,
  [SMALL_STATE(4)] = 56,
  [SMALL_STATE(5)] = 80,
  [SMALL_STATE(6)] = 105,
  [SMALL_STATE(7)] = 124,
  [SMALL_STATE(8)] = 143,
  [SMALL_STATE(9)] = 157,
  [SMALL_STATE(10)] = 168,
  [SMALL_STATE(11)] = 179,
  [SMALL_STATE(12)] = 193,
  [SMALL_STATE(13)] = 202,
  [SMALL_STATE(14)] = 211,
  [SMALL_STATE(15)] = 220,
  [SMALL_STATE(16)] = 231,
  [SMALL_STATE(17)] = 240,
  [SMALL_STATE(18)] = 248,
  [SMALL_STATE(19)] = 256,
  [SMALL_STATE(20)] = 263,
  [SMALL_STATE(21)] = 270,
  [SMALL_STATE(22)] = 277,
  [SMALL_STATE(23)] = 284,
  [SMALL_STATE(24)] = 291,
  [SMALL_STATE(25)] = 298,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__sequence, 1, 0, 0),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [21] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(21),
  [24] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(25),
  [27] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__thing, 1, 0, 0),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [31] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_affectation, 3, 0, 3),
  [33] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__grouping, 3, 0, 0),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_definition, 5, 0, 2),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__sequence, 2, 0, 0),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_terminal_definition, 3, 0, 1),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__choice, 1, 0, 0),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [47] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sequence, 1, 0, 0),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__choice, 3, 0, 0),
  [51] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_choice, 1, 0, 0),
  [53] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [55] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [57] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [59] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [61] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [63] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_grammar(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
