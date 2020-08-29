ruby_gemspec = Gem::Specification.load(File.join(__dir__, "channel.gemspec"))

MRuby::Gem::Specification.new("mruby-#{ruby_gemspec.name}") do |spec|
  spec.authors = ruby_gemspec.authors
  spec.homepage = ruby_gemspec.homepage
  spec.licenses = ruby_gemspec.licenses
  spec.summary = ruby_gemspec.summary

  spec.mrblib_dir = 'lib'

  spec.test_rbfiles = Dir.glob(File.join(__dir__, 'test/mrbtest/**/*.rb'))

  loader_files = ['lib/channel.rb']

  if ENV.fetch('MRUBY_COMPILE_CONTROLS', 'on') == 'on'
    loader_files << 'lib/channel/controls.rb'
  end

  if ENV.fetch('MRUBY_COMPILE_FIXTURES', 'off') == 'on'
    loader_files << 'lib/channel/fixtures.rb'
  end

  loader_files.each do |loader_file|
    loader_file = File.join(__dir__, loader_file)

    whitespace = '[[:blank:]]*'
    feature = "['\"](.*)['\"]"
    require_statement_pattern = /^#{whitespace}require#{whitespace}#{feature}/

    File.read(loader_file).scan(require_statement_pattern) do |(feature)|
      file = File.join(__dir__, spec.mrblib_dir, feature)

      file << '.rb' unless file.end_with?('.rb')

      if File.exist?(file)
        spec.rbfiles << file
      end
    end
  end
end
