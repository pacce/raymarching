cmake   = import('cmake')
options = cmake.subproject_options()
options.add_cmake_defines({'RC_ENABLE_GTEST': 'ON'})

rapidcheck_project  = cmake.subproject('rapidcheck', options: options)

rapidcheck          = rapidcheck_project.dependency('rapidcheck')
rapidcheck_gtest    = rapidcheck_project.dependency('rapidcheck_gtest')
gtest               = dependency('gtest')

dependencies  = [gtest, rapidcheck, rapidcheck_gtest, raymarching_dep]

test('geometry', executable('geometry', 'geometry.cpp', dependencies: dependencies))
