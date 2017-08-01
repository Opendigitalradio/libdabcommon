# pylint: disable=missing-docstring
from conans import ConanFile, CMake


class LibdabcommonConan(ConanFile):
    name = 'libdabcommon'
    license = 'BSD 3-clause'
    version = '1.0.1'
    url = 'https://github.com/Opendigitalradio/libdabcommon.git'
    settings = None
    generators = ['cmake', 'txt']
    options = {"test": [True, False]}
    default_options = "test=True"

    def build(self):
        if self.options.test:
            cmake = CMake(self)
            self.run('cmake libdabcommon %s' % cmake.command_line)
            self.run('cmake --build . %s' % cmake.build_config)

    def package(self):
        self.copy('*.h', dst='include', src='libdabcommon/include')

    def package_info(self):
        self.cpp_info.includedirs = ['include']
        self.cpp_info.libs = ['pthread']

    def requirements(self):
        if self.options.test:
            self.requires('CUTEX/[>=1.0]@fmorgner/stable')

    def source(self):
        self.run('git clone %s' % self.url)
