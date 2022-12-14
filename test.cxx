#include "tinyjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)                       \
  do {                                                                         \
    test_count++;                                                              \
    if (equality)                                                              \
      test_pass++;                                                             \
    else {                                                                     \
      fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n",        \
              __FILE__, __LINE__, expect, actual);                             \
    }                                                                          \
  } while (0)

#define EXPECT_EQ_INT(expect, actual)                                          \
  EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
// About null
static void test_parse_null() {
  Json_value v;

  v.type = JSON_FALSE;
  EXPECT_EQ_INT(JSON_PARSE_OK, json_parse(&v, "null"));
  EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));
}

// about true and false
static void test_parse_true() {
  Json_value v;

  v.type = JSON_NULL;
  EXPECT_EQ_INT(JSON_PARSE_OK, json_parse(&v, "true"));
  EXPECT_EQ_INT(JSON_TRUE, json_get_type(&v));
}

static void test_parse_false() {
  Json_value v;

  v.type = JSON_NULL;
  EXPECT_EQ_INT(JSON_PARSE_OK, json_parse(&v, "false"));
  EXPECT_EQ_INT(JSON_FALSE, json_get_type(&v));
}
static void test_parse_expect_value() {
  Json_value v;

  v.type = JSON_FALSE;
  EXPECT_EQ_INT(JSON_PARSE_EXPECT_VALUE, json_parse(&v, ""));
  EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));

  v.type = JSON_FALSE;
  EXPECT_EQ_INT(JSON_PARSE_EXPECT_VALUE, json_parse(&v, " "));
  EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));
}

static void test_parse_invalid_value() {
  Json_value v;

  v.type = JSON_FALSE;
  EXPECT_EQ_INT(JSON_PARSE_INVALID_VALUE, json_parse(&v, "nul"));
  EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));

  v.type = JSON_NULL;
  EXPECT_EQ_INT(JSON_PARSE_INVALID_VALUE, json_parse(&v, "tru"));
  EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));

  v.type = JSON_NULL;
  EXPECT_EQ_INT(JSON_PARSE_INVALID_VALUE, json_parse(&v, "fal"));
  EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));

  v.type = JSON_FALSE;
  EXPECT_EQ_INT(JSON_PARSE_INVALID_VALUE, json_parse(&v, "?"));
  EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));
}

static void test_parse_root_not_singular() {
  Json_value v;

  v.type = JSON_FALSE;
  EXPECT_EQ_INT(JSON_PARSE_ROOT_NOT_SINGULAR, json_parse(&v, "null x"));
  EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));

  v.type = JSON_NULL;
  EXPECT_EQ_INT(JSON_PARSE_ROOT_NOT_SINGULAR, json_parse(&v, "true x"));
  EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));

  v.type = JSON_NULL;
  EXPECT_EQ_INT(JSON_PARSE_ROOT_NOT_SINGULAR, json_parse(&v, "false x"));
  EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));
}

static void test_parse() {
  test_parse_null();
  test_parse_expect_value();
  test_parse_invalid_value();
  test_parse_root_not_singular();
}

int main() {
  test_parse();
  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count,
         test_pass * 100.0 / test_count);
  return main_ret;
}
