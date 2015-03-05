
import os
import fnmatch


def getSubdirs(abs_path_dir):
    lst = [ name for name in os.listdir(abs_path_dir) if os.path.isdir(os.path.join(abs_path_dir, name)) and name[0] != '.' ]
    lst.sort()
    return lst

def getSources(src_dir):
    sources = []
    for root, dirnames, filenames in os.walk(src_dir):
        for filename in fnmatch.filter(filenames, '*.cpp'):
            sources +=Glob(os.path.join(root, filename))
        for filename in fnmatch.filter(filenames, '*.hpp'):
            sources += Glob(os.path.join(root, filename))
    return sources


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

cppflags = ['--std=c++11',  '-Wall', '-g']


output = 'atabox-server'

comp = ARGUMENTS.get('env', 'debug')
if comp.startswith('tests'):
    print('---------------------_TEST_---------------------------')
    common_libs.append('gcov')
    common_libs += ['gtest', 'gmock']
    cppflags.append('-g3')
    cppflags += ['-c', '-fmessage-length=0', '-fprofile-arcs', '-ftest-coverage']
    output = 'tests'
    atabox_sources.pop(0)
    atabox_sources += getSources('tests')
    if 'jenkins' in comp:
        cppflags.remove('-Wall')
        cppflags.append('-O0')
        cppflags.append('-w')
else:
    common_libs += ['boost_program_options']



env = Environment()
env.Append(CPPPATH=include_dir)
env.Append(CPPFLAGS=cppflags)
env.Append(CPPDEFINES=cpp_defined)
env.Append( LIBS = common_libs )
env.Program('build/' + output, atabox_sources )



