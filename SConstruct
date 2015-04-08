
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
            sources += Glob(os.path.join(root, filename))
    return sources


def cmd_exists(cmd):
    return subprocess.call("type " + cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE) == 0

num_cpu = int(os.environ.get('NUM_CPU', 2))
src_dir = 'src'
atabox_sources = getSources(src_dir)
modules = getSubdirs(src_dir)

print('modules {}'.format(modules))
cpp_defined = {'DEBUG': 1, 'BOOST_LOG_DYN_LINK': 'yes'}
common_libs = [
    'pthread',
    'boost_system',
    'boost_thread',
    'boost_iostreams',
    'boost_filesystem',
    'boost_log',
    'rocksdb',
    'bz2',
    'z',
    'cpprest'

]
CXX = 'g++'
if cmd_exists('clang++'):
    CXX = 'clang++'

SetOption('num_jobs', num_cpu)
print "running with -j", GetOption('num_jobs')

include_dir = [
    "src",
    "external/aquila/aquila/",
    "external/casablanca/Release/include/",
    "external/rocksdb_source/include/",
    "external/kiss_fft",
    "external/"
]

cppflags = ['--std=c++11',  '-Wall', '-g',  '-fdiagnostics-color=always']


output = 'atabox-server'
build_dir = 'build'

source_files = [os.path.join(build_dir, s) for s in atabox_sources]
comp = ARGUMENTS.get('env', 'debug')
if comp.startswith('tests'):
    print('---------------------_TEST_---------------------------')
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
        cppflags.append('-O0')
        cppflags.append('-w')
    source_files +=  [os.path.join(build_dir, s) for s in getSources('tests')]
else:
    common_libs += ['boost_program_options']


VariantDir(build_dir, '.')
env = Environment(ENV = {'PATH' : os.environ['PATH'],
                         'TERM' : os.environ['TERM'],
                         'HOME' : os.environ['HOME']},
                 CXX = CXX
                         )
env.Append(CPPPATH=include_dir)
env.Append(CPPFLAGS=cppflags)
env.Append(CPPDEFINES=cpp_defined)
env.Append( LIBS = common_libs )





env.Program('build/' + output, source_files)



