#ifndef TINYJSON_H_
#define TINYJSON_H_

typedef enum Json_type {
  JSON_NULL,
  JSON_FALSE,
  JSON_TRUE,
  JSON_NUMBER,
  JSON_STRING,
  JSON_ARRAY,
  JSON_OBJECT
};

typedef struct Json_value {
  Json_type type;
};

enum {
  JSON_PARSE_OK = 0,
  JSON_PARSE_EXPECT_VALUE,
  JSON_PARSE_INVALID_VALUE,
  JSON_PARSE_ROOT_NOT_SINGULAR
};

int json_parse(Json_value *v, const char *json);

Json_type json_get_type(const Json_value *v);

#endif // end of TINYJSON_H_
