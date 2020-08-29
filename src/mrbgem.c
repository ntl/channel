#include <mruby.h>

#include "mrb_channel_value.h"

void
mrb_mruby_channel_gem_init(mrb_state* mrb) {
  /* ::Channel */
  struct RClass* channel_class = mrb_define_class(mrb, "Channel", mrb->object_class);

  /* ::Channel::Value */
  mrb_channel_value_init(mrb, channel_class);

  return;
}

void
mrb_mruby_channel_gem_final(mrb_state* mrb) {
  return;
}
