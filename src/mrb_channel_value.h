#ifndef CHANNEL_MRB_CHANNEL_VALUE_H
#define CHANNEL_MRB_CHANNEL_VALUE_H

#include <mruby.h>

#include "channel_value.h"

mrb_value mrb_channel_value_new(mrb_state*, mrb_value);
mrb_value mrb_channel_value_restore(mrb_state*, mrb_value);

void mrb_channel_value_init(mrb_state*, struct RClass*);

#endif /* CHANNEL_MRB_CHANNEL_VALUE_H */
