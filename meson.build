#############################################
# FTTimer meson build file
#############################################
# References:
# - https://github.com/tiernemi/meson-sample-project/blob/master/meson.build
#############################################
project( 'fttimer'
  , 'cpp'
  , version: '0.0.1'
  , license : 'Apache 2.0'
  #  , default_options : ['c_std=c20', 'cpp_std=c++20']
    , default_options : ['c_std=c11', 'cpp_std=c++11']
  )

#Extract git information for build versioning
branch = run_command(['git', 'branch', '--show-current', '|tr','\'\n\'', '\'\''])
hash = run_command(['git', 'rev-parse', '--short', 'HEAD'])
commit=run_command(['git', 'rev-list', '--count', 'HEAD'])
tag = '0.0.1'

version=tag + '_' + branch.stdout().strip() + '.' + commit.stdout()
version = version.strip()
devenv = environment()

devenv.set('BUILD_VERSION', version )
devenv.set('DOCUMENTATION_DIR', meson.current_build_dir()+'/docs')
message('BUILD_VERSION: '+version)
message('DOCUMENTATION_DIR: '+ meson.current_build_dir()+'/docs')


##############################################
## Make hourglass suproject
##############################################
#hrgls_cmake = import('cmake')
#hrgls_proj = hrgls_cmake.subproject('Hourglass'
#  #  , hrgls_cmake_options : ['DCMAKE_CXX_FLAGS=-fpic']
#    , cmake_options : ['DCMAKE_CXX_FLAGS=-fpic']
#  )
##hrgls_dep = hrgls_proj.get_variable('cm_hrgls_dep')
#hrgls_lib = hrgls_proj.dependency('hrgls')
#
#hrgls_includes = [ 'subprojects/Hourglass',
#  'subprojects/Hourglass/__CMake_build/' 
#  ]


#############################################
#Define library build information
#############################################
fttimer_lib = static_library( 'fttimer'
  #  , ['src/FTTimer.cpp', 'src/FTTimeTracker.cpp']
    , ['src/FTTimer.cpp']
  , include_directories : 'src'
  , cpp_args : '-DBUILD_VERSION="'+version+'"'
  #  , dependencies : hrgls_lib
  )

fttimer_inc = include_directories('src')
fttimer_dep = declare_dependency(
  include_directories : include_directories('src')
  )


# Build gtest
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')

tests_src = [ 'tests/FTTimerTest.cpp' ]

tests = executable('FTTimerTest'
  , sources : tests_src
  , include_directories : ['src']
  , dependencies : [ fttimer_dep, gtest_dep, gmock_dep]
  , link_with : [fttimer_lib]
  )

test( 'gtest tests', tests )

#Build Doxygen
doxygen = find_program('doxygen', required : false )
if doxygen.found()
  doc_dest=meson.current_build_dir().strip()+'/docs'
  message('Generating Documentation at '+doc_dest)

  #Set build variables
  cdata= {'BUILD_VERSION':version
    , 'DOCUMENTATION_DIR': doc_dest
    , 'INPUT': meson.current_source_dir()
    , 'EXCLUDE': 'subprojects test'
    , 'EXCLUDE_PATTERN':'*test*'
    }
#  cdata.set('BUILD_VERSION', version)
#  cdata.set('DOCUMENTATION_DIR', doc_dest)

  doxyfile = configure_file( input: 'Doxyfile.in'
    , output: 'Doxyfile'
    , configuration: cdata
    , install: true
    , install_dir: meson.current_build_dir()
    )
  
  #  message('Doxyfile: '+ doxyfile)
  dfile=meson.current_build_dir()+'/Doxyfile'
  
  #Specify input directory
  input = meson.current_source_dir()

  message('DFILE: '+dfile)

  run_target('docs'
    , command : [ doxygen, dfile]
    #    , env : {'BUILD_VERSION':version ,'DOCUMENTATION_DIR':doc_dest}
    )
else
  warning('Documentation disabled without doxygen')
endif





