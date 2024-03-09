project('raymarching', 'cpp', version: '0.1.0')

dependencies  = [
    dependency('libavcodec')
  , dependency('libavformat')
  , dependency('libavutil')
  , dependency('libswscale')
  ]
sources       = []
# include       = include_directories('include')
include       = include_directories()

raymarching_dep = declare_dependency(
    dependencies        : dependencies
  , include_directories : include
  )

executable('main', 'source/main.cpp', dependencies: dependencies)
