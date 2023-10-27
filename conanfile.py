from conan import ConanFile

class MyConanFile(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "zlib/1.2.13",
        "sfml/2.6.0",
        "nlohmann_json/3.11.2",
        "boost/1.83.0",
        "gtest/1.14.0",
        "lz4/1.9.4"
    ]
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        if self.settings.os == "Linux":
            self.requires("libalsa/1.2.10", override=True)
