project('storytelling', 'cpp')

pugixml = dependency('pugixml')
sfmlg = dependency('sfml-graphics')
sfmls = dependency('sfml-system')
sfmlw = dependency('sfml-window')
spdlog = dependency('spdlog')

cpp_compiler = meson.get_compiler('cpp')
if not cpp_compiler.has_header('tl/expected.hpp')
  error('Required dependency tl-expected <tl/expected.hpp> not found')
endif

arguments = ['-Wno-switch', '-std=c++17']
if get_option('buildtype') == 'debug'
  arguments += ['-DDEBUG']
endif

executable(
  'storytelling',
  ['src/main.cpp', 'src/scene/scene.cpp', 'src/utils/argparse.cpp'],
  dependencies: [pugixml, sfmlg, sfmls, sfmlw, spdlog],
  cpp_args: arguments,
)
