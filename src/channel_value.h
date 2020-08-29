#ifndef CHANNEL_CHANNEL_VALUE_H
#define CHANNEL_CHANNEL_VALUE_H

#include <stdbool.h>

static const char* const channel_value_type_names[] = {
  "Unknown",
  "Boolean",
  "Integer",
  "Decimal",
  "InternalString",
  "String",
  "Array",
  "Hash",
  "Range",
  "Channel"
};

typedef enum {
  Unknown = 0,
  Boolean,
  Integer,
  Decimal,
  InternalString,
  String,
  Array,
  Hash,
  Range,
  Channel
} channel_value_type;

typedef union {
  bool boolean;
  int integer;
  double decimal;
  const char* internal_string;
  int mem_size;
} channel_value_data;

typedef struct {
  channel_value_type type;
  channel_value_data data;
  char mem[];
} ChannelValue;
typedef const ChannelValue* const channel_value;
typedef ChannelValue* const channel_value_mut;

channel_value channel_value_allocate(channel_value_type, channel_value_data, void*);
channel_value channel_value_copy(channel_value);
void channel_value_release(channel_value_mut channel_value);

int channel_value_payload_size(channel_value);
int channel_value_size(channel_value);

#endif /* CHANNEL_CHANNEL_VALUE_H */
