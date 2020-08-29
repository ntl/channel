# Channel::Value

## Summary

Channels allow primitive data, such as integers, strings and arrays, to be transferred between processes. Objects cannot be shared over channels, unless they are copied and converted to primitive data first. A `Channel::Value` holds a reference to a single primitive data value, and acts as the vessel for safely conveying the data from one process to the next.

## Usage

To envelop a ruby value, such as an `Integer`, instantiate `Channel::Value`:

``` ruby
some_value = Channel::Value.new(11)
```

Convert the value to raw binary data:

``` ruby
binary_data = some_value.data
=> "\x00\x01\x02\x03…"
```

Restore the original value from raw binary data:

``` ruby
new_value = Channel::Value.restore(binary_data)
```

Value instances can also be restored:

``` ruby
some_value.restore
=> 11
```

Inspect the storage size of the value in bytes:

``` ruby
some_value.size
=> 4
```

## Compatible Ruby Classes

In addition to the Integer used above, the following classes can also be cast into values:

- TrueClass
- FalseClass
- Integer
- Float
- Symbol
- String
- Array\*
- Hash\*
- Range\*
- Channel

## Diagnostic Statistics

Cumulative statistics can be read via `Channel::Value.stats`. Every time a value is converted and/or restored, the stats object is updated.

- `bytes_converted` - number of bytes that have been serialized
- `bytes_restored` - number of bytes that have been deserialized
- `values_converted` - number of values that have been serialized
- `values_restored` - number of values that have been deserialized

Since channels can be read by multiple processes, each independent read of the same value will increase `bytes_restored` and `values_restored`.
