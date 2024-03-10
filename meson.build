project('raymarching', 'cpp', version: '0.1.0')

dependencies  = []
sources       = []
include       = include_directories('include')

raymarching_dep = declare_dependency(
    dependencies        : dependencies
  , include_directories : include
  )

executable('main', 'source/main.cpp', dependencies: dependencies)
