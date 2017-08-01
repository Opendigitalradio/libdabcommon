# pylint: disable=missing-docstring
import os
from conans import ConanFile, CMake


CHAN = os.getenv("CONAN_CHANNEL", "stable")
USER = os.getenv("CONAN_USERNAME", "fmorgner")


class CuteTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "libdabcommon/1.0.1@%s/%s" % (USER, CHAN)
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir=self.conanfile_directory, build_dir="./")
        cmake.build()

    def test(self):
        os.chdir("bin")
        self.run(".%spackage_test" % os.sep)
