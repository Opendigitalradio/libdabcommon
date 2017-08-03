# pylint: disable=missing-docstring
from conans import ConanFile, CMake


class LibDABCommonConan(ConanFile):
    name = 'libdabcommon'
    description = """The common subsystem for the ODR DAB data toolkit"""
    license = 'BSD 3-clause'
    version = '1.0.1'
    url = 'https://github.com/Opendigitalradio/libdabcommon.git'
    settings = None
    options = {"test": [True, False]}
    default_options = "test=False"
    exports_sources = (
        'include/*.h',
    )

    def build(self):
        if self.options.test:
            cmake = CMake(self)
            self.run('cmake libdabcommon %s' % cmake.command_line)
            self.run('cmake --build . %s' % cmake.build_config)

    def package(self):
        self.copy('*.h', dst='include', src='include')

    def package_info(self):
        self.cpp_info.libs = ['pthread']

    def requirements(self):
        if self.options.test:
            self.requires('CUTEX/[>=1.0]@fmorgner/stable')
