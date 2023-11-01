from conan import ConanFile

class MyConanFile(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "zlib/1.2.13",
        "sfml/2.6.0",
        "nlohmann_json/3.11.2",
        "boost/1.83.0",
        "gtest/1.14.0",
        "sdl/2.26.5",
        "sdl_image/2.0.5",
        "lz4/1.9.4",
        "sdl_ttf/2.20.2"
    ]
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("freetype/2.12.1", override=True)
        if self.settings.os == "Linux":
            self.requires("libalsa/1.2.10", override=True)