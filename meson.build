project('raymarching', 'cpp', version: '0.1.0', default_options : ['warning_level=3', 'cpp_std=c++20'])

dependencies  = [
    dependency('eigen3')
  , dependency('geometry')
  , dependency('libpng')
  ]
sources       = []
include       = include_directories('include')

raymarching_dep = declare_dependency(
    dependencies        : dependencies
  , include_directories : include
  )

executable('main', 'source/main.cpp', dependencies: [raymarching_dep])

if not meson.is_subproject()
  subdir('tests')
endif
