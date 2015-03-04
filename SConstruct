
import os
def getSubdirs(abs_path_dir):
    lst = [ name for name in os.listdir(abs_path_dir) if os.path.isdir(os.path.join(abs_path_dir, name)) and name[0] != '.' ]
    lst.sort()
    return lst


num_cpu = int(os.environ.get('NUM_CPU', 2))
src_dir = 'src'
atabox_sources = []
modules = getSubdirs(src_dir)
print('modules {}'.format(modules))
for module in modules:
    atabox_sources.append(Glob(os.path.join(src_dir, module, '*.cpp')))
    if len(Glob(os.path.join(src_dir, module, '*.hpp'))))

atabox_sources.append(Glob(os.path.join(src_dir, '*.cpp')))

print(atabox_sources)
cpp_defined = {'DEBUG': 1, 'BOOST_LOG_DYN_LINK': 'yes'}
common_libs = [
    'pthread',
    'boost_system',
    'boost_thread',
    'boost_filesystem',
    'boost_program_options',
    'boost_log',
    'rocksdb',
    'bz2',
    'z',
    'cpprest'

]


SetOption('num_jobs', num_cpu)
print "running with -j", GetOption('num_jobs')

include_dir = [
    "external/aquila/aquila/",
    "external/casablanca/Release/include/",
    "external/rocksdb_source/include/",
    "external/kiss_fft",
    "external/boost",
    "src"
]

cppflags = ['--std=c++11',  '-Wall', '-g']

tests = ARGUMENTS.get('tests', False)
if tests:
    common_libs.append('gcov')
    cppflags.append('-O0')
    cppflags.append('-g3')
            # -c -fmessage-length=0  -fprofile-arcs -ftest-coverage


env = Environment()
env.Append(CPPPATH=include_dir)
env.Append(CPPFLAGS=cppflags)
env.Append(CPPDEFINES=cpp_defined)
env.Append( LIBS = common_libs )
env.Program('build/atabox', atabox_sources )



