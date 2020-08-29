#include <stdlib.h>
#include <string.h>

#include "channel_value.h"

channel_value
channel_value_allocate(channel_value_type type, channel_value_data data, void* source_mem) {
  int size = sizeof(ChannelValue);

  channel_value_mut ch_value = malloc(size);
  if(ch_value == NULL) return NULL;

  ch_value->type = type;
  ch_value->data = data;

  return (channel_value)ch_value;
}

channel_value
channel_value_copy(channel_value channel_value) {
  int size = channel_value_size(channel_value);

  channel_value_mut copy = malloc(size);
  if(copy == NULL) return NULL;

  memcpy(copy, channel_value, size);

  return copy;
}

void
channel_value_release(channel_value_mut channel_value) {
  free(channel_value);
}

int
channel_value_payload_size(channel_value channel_value) {
  switch(channel_value->type) {
    case Boolean:
      return sizeof(channel_value->data.boolean);
    default:
      return -1;
  }
}

int
channel_value_size(channel_value channel_value) {
  int size = sizeof(ChannelValue);

  return size;
}
