# -*- encoding: utf-8 -*-
Gem::Specification.new do |s|
  s.name = 'channel'
  s.version = '0'

  s.authors = ['Nathan Ladd']
  s.email = 'nathanladd+github@gmail.com'
  s.homepage = 'https://github.com/esc/channel'
  s.licenses = %w(MIT)
  s.summary = "Thread-safe intra-process communication (IPC) for Ruby or MRuby"
  s.platform = Gem::Platform::RUBY

  s.require_paths = %w(lib)
  s.files = Dir.glob 'lib/**/*'

  s.add_development_dependency 'test_bench'
end
