
import os
import fnmatch
import subprocess


def getSubdirs(abs_path_dir):
    lst = [ name for name in os.listdir(abs_path_dir) if os.path.isdir(os.path.join(abs_path_dir, name)) and name[0] != '.' ]
    lst.sort()
    return lst

def getSources(src_dir):
    sources = []
    for root, dirnames, filenames in os.walk(src_dir):
        for filename in fnmatch.filter(filenames, '*.cpp'):
            sources.append(str(os.path.join(root, filename)))
        for filename in fnmatch.filter(filenames, '*.hpp'):
            sources.append(str(os.path.join(root, filename)))
    return sources


def cmd_exists(cmd):
    return subprocess.call("type " + cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE) == 0

def prepare_env(env_vars):
    env = {}
    for var in env_vars:
        if var in os.environ:
            env[var] = os.environ[var]
    return env

num_cpu = int(os.environ.get('NUM_CPU', 2))
src_dir = 'src'
atabox_sources = getSources(src_dir)
modules = getSubdirs(src_dir)

print('modules {}'.format(modules))
cpp_defined = {'DEBUG': 1, 'BOOST_LOG_DYN_LINK': 'yes'}
common_libs = [
    'pthread',
    'boost_system',
    'boost_thread-mt',
    'boost_iostreams',
    'boost_filesystem',
    'boost_log-mt',
    'boost_chrono',
    'rocksdb',
    'bz2',
    'z',
    'cpprest',
    'Aquila',
    'Ooura_fft'

]
libs_path = ['external/aquila/lib', 'libs/']
CXX = 'g++'
# if cmd_exists('clang++'):
#     CXX = 'clang++'

SetOption('num_jobs', num_cpu)
print "running with -j", GetOption('num_jobs')

include_dir = [
    "src",
    "external/aquila/aquila/",
    "external/casablanca/Release/include/",
    "external/rocksdb_source/include/",
    "external/kiss_fft",
    "external/rbm/src"
    "external/"
]

cppflags = ['--std=c++11',  '-Wall', '-g',  '-fdiagnostics-color=always']


output = 'atabox-server'
build_dir = 'build'
print(atabox_sources)



source_files = [os.path.join(build_dir, s) for s in atabox_sources]
comp = ARGUMENTS.get('env', 'debug')
if comp.startswith('tests'):
    print('---------------------_TEST_---------------------------')
    CXX = 'g++'
    common_libs.append('gcov')
    common_libs += ['gtest', 'gmock']
    cppflags.append('-g3')
    cppflags += ['-c', '-fmessage-length=0', '-fprofile-arcs', '-ftest-coverage']
    output = 'atabox-tests'
    atabox_sources.pop(0)
    source_files.pop(0)

    atabox_sources += getSources('tests')
    if 'jenkins' in comp:
        cppflags.remove('-Wall')
        cppflags.remove('-fdiagnostics-color=always')
        cppflags.append('-O0')
        cppflags.append('-w')
    source_files +=  [os.path.join(build_dir, s) for s in getSources('tests')]
else:
    common_libs += ['boost_program_options']


env_env = prepare_env(['PATH','TERM', 'HOME'])


VariantDir(build_dir, '.')
env = Environment(ENV = env_env, CXX = CXX )
# import SCons.Tool
# static_obj, shared_obj = SCons.Tool.createObjBuilders(env)
#
# static_obj.add_action('.hpp', SCons.Defaults.CXXAction)
# shared_obj.add_action('.hpp', SCons.Defaults.ShCXXAction)
# static_obj.add_emitter('.hpp', SCons.Defaults.StaticObjectEmitter)
# shared_obj.add_emitter('.hpp', SCons.Defaults.SharedObjectEmitter)

env.Append(CPPPATH=include_dir)
env.Append(CPPFLAGS=cppflags)
env.Append(CPPDEFINES=cpp_defined)
env.Append( LIBS = common_libs )
env.Append(LIBPATH = libs_path)





env.Program('build/' + output, source_files)



