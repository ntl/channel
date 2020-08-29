assert "Boolean (true)" do
  value = Channel::Value.new(true)
  assert_equal(true, value.restore)
end

assert "Boolean (false)" do
  value = Channel::Value.new(false)
  assert_equal(false, value.restore)
end
