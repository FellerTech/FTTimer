#https://github.com/tiernemi/meson-sample-project/blob/master/meson.build

project( 'fttimer'
  , 'cpp'
  , version : '0.0.1.-1'
  , license : 'Apache 2.0'
  )

fttimer_lib = static_library( 'fttimer'
  , 'src/FTTimer.cpp'
  , include_directories : 'src' 
  )

fttimer_dep = declare_dependency(
  include_directories : include_directories('src');
  )

# Build gtest
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')

#gtest_dep = dependency( 'gtest', fallback : ['gtest', 'gtest_dep'])




#gtest_cmake = import('cmake')
##gtest_proj = gtest_cmake.subproject('googletest')
##gtest_dep = dependency('googletest', main : true, required : false)
##gmock_dep = dependency('gmock', disabler: true, required: false)
#
#gtest_proj = subproject('gtest')
#gtest_dep = gtest_proj.get_variable('gtest_dep')
#gmock_dep = gtest_proj.get_variable('gmock_dep')
#gtest_dep = dependency('gtest', main : true, required : false)
#gmock_dep = dependency('gmock', main : true, required : false)
#
#gtest_lib = static_library('gtest', install : true)
#gmock_lib = static_library('gmock', install: true)

tests_src = [ 'tests/FTTimerTest.cpp' ]

tests = executable('FTTimerTest'
  , sources : tests_src
  , include_directories : ['src']
  , dependencies : [gtest_dep, gmock_dep]
  , link_with : [fttimer_lib]
  )



test( 'gtest tests', tests )


#testexec = executable( 'FTTimerTest', 'FTTimerTest.cpp' )
#test( 'Unit Test', testexec )

#Test sources
#gtest = subproject('gtest')



