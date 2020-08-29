#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/string.h>

#include <stdlib.h>

#include "mrb_channel_value.h"

mrb_value
mrb_channel_value_new(mrb_state* mrb, mrb_value object) {
  struct RClass* channel_value_cls = mrb_class_get_under(mrb, mrb_class_get(mrb, "Channel"), "Value");

  return mrb_obj_new(mrb, channel_value_cls, 1, &object);
}

static void
mrb_channel_value_free(mrb_state* mrb, void* ptr) {
  if(ptr) {
    channel_value_mut channel_value = ptr;
    channel_value_release(channel_value);
  }
}

static const struct mrb_data_type mrb_channel_value_type = {
  "mrb_channel_value", mrb_channel_value_free
};

static void
init_value_instance(mrb_state* mrb, mrb_value object, mrb_value instance) {
  channel_value_type type = Unknown;
  channel_value_data data;

  switch(mrb_type(object)) {
    case MRB_TT_TRUE:
    case MRB_TT_FALSE:
      type = Boolean;
      data.boolean = mrb_bool(object);
      break;
    default:
      mrb_raisef(mrb, E_TYPE_ERROR, "Can't convert %S into binary data", mrb_inspect(mrb, object));
  }

  channel_value channel_value = channel_value_allocate(type, data, NULL);
  if(channel_value == NULL) mrb_exc_raise(mrb, mrb_obj_value(mrb->nomem_err));

  mrb_data_init(instance, (channel_value_mut)channel_value, &mrb_channel_value_type);
}

static mrb_value
mrb_channel_value_initialize(mrb_state* mrb, mrb_value instance) {
  mrb_value object;
  mrb_get_args(mrb, "o", &object);

  init_value_instance(mrb, object, instance);

  return instance;
};

static mrb_value
mrb_channel_value_data(mrb_state* mrb, mrb_value instance) {
  channel_value channel_value = DATA_PTR(instance);

  int mem_size = channel_value_size(channel_value);

  return mrb_str_new(mrb, (void*)channel_value, mem_size);
};

mrb_value
mrb_channel_value_restore(mrb_state* mrb, mrb_value instance) {
  channel_value channel_value = DATA_PTR(instance);

  //__sync_add_and_fetch(&mrb_value_stats.bytes_transferred, channel_value_data_size(channel_value));

  switch(channel_value->type) {
    case Boolean:
      return mrb_bool_value(channel_value->data.boolean);
    default:
      mrb_raisef(mrb, E_TYPE_ERROR, "Can't convert from %s", channel_value_type_names[channel_value->type]);
  }
}

static mrb_value
mrb_channel_value_size(mrb_state* mrb, mrb_value instance) {
  channel_value channel_value = DATA_PTR(instance);

  int data_size = channel_value_payload_size(channel_value);

  return mrb_fixnum_value(data_size);
};

static mrb_value
mrb_channel_value_data_cls(mrb_state* mrb, mrb_value cls) {
  mrb_value object;
  mrb_get_args(mrb, "o", &object);

  mrb_value instance = mrb_channel_value_new(mrb, object);

  return mrb_funcall(mrb, instance, "data", 0);
};

static mrb_value
mrb_channel_value_restore_cls(mrb_state* mrb, mrb_value cls) {
  mrb_value binary_data;
  mrb_get_args(mrb, "S", &binary_data);

  channel_value copy = channel_value_copy((channel_value)(RSTRING_PTR(binary_data)));
  if(copy == NULL) mrb_exc_raise(mrb, mrb_obj_value(mrb->nomem_err));

  struct RClass* channel_value_cls = mrb_class_get_under(mrb, mrb_class_get(mrb, "Channel"), "Value");
  mrb_value instance = mrb_obj_value(mrb_obj_alloc(mrb, MRB_TT_DATA, channel_value_cls));
  mrb_data_init(instance, (channel_value_mut)copy, &mrb_channel_value_type);

  return instance;
};

void
mrb_channel_value_init(mrb_state* mrb, struct RClass* channel_class) {
  struct RClass* value_class = mrb_define_class_under(mrb, channel_class, "Value", mrb->object_class);
  MRB_SET_INSTANCE_TT(value_class, MRB_TT_DATA);

  mrb_define_method(mrb, value_class, "initialize", mrb_channel_value_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, value_class, "data", mrb_channel_value_data, MRB_ARGS_NONE());
  mrb_define_method(mrb, value_class, "restore", mrb_channel_value_restore, MRB_ARGS_NONE());
  mrb_define_method(mrb, value_class, "size", mrb_channel_value_size, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, value_class, "data", mrb_channel_value_data_cls, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, value_class, "restore", mrb_channel_value_restore_cls, MRB_ARGS_REQ(1));

  return;
}
