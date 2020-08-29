MRuby::Build.new do |conf|
  toolchain :gcc

  enable_debug

  conf.cc.flags << '-Wno-declaration-after-statement'

  conf.gem __dir__

  conf.gem :github => 'test-bench/test-bench'

  conf.gem File.join(root, 'mrbgems/mruby-bin-mirb')
end

MRuby::Build.new('mrbtest') do |conf|
  toolchain :gcc

  conf.cc.flags << '-Wno-declaration-after-statement'

  enable_debug
  conf.enable_test

  conf.gem __dir__

  conf.gem File.join(root, 'mrbgems/mruby-test')
end
