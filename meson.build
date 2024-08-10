project('storytelling', 'cpp')

# Define dependencies
pugixml = dependency('pugixml')
sfmlg = dependency('sfml-graphics')
sfmls = dependency('sfml-system')
sfmlw = dependency('sfml-window')
spdlog = dependency('spdlog')

# Check if the required header file exists
cpp_compiler = meson.get_compiler('cpp')
if not cpp_compiler.has_header('tl/expected.hpp')
  error('Required dependency tl-expected <tl/expected.hpp> not found')
endif

# Determine build type and set compiler arguments
arguments = []
if get_option('buildtype') == 'debug'
  arguments += ['-DDEBUG']
endif

# Define the executable
executable(
  'storytelling',
  ['src/main.cpp', 'src/scene/scene.cpp', 'src/utils/argparse.cpp'],
  dependencies: [pugixml, sfmlg, sfmls, sfmlw, spdlog],
  link_args: ['-Wno-switch'],
  cpp_args: arguments
)
