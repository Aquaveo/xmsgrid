"""
XMSGrid Conanfile and Support
"""
import os
from conans import ConanFile, CMake, tools
from conans.errors import ConanException


class XmsgridConan(ConanFile):
    """XMSGrid Conanfile"""
    name = "xmsgrid"
    license = "BSD2"
    url = "https://github.com/Aquaveo/xmsgrid"
    description = "Grid library for XMS products"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "wchar_t": ['builtin', 'typedef'],
        "pybind": [True, False],
        "testing": [True, False],
    }
    default_options = {
        "wchar_t": 'builtin',
        "pybind": False,
        "testing": False,
    }
    generators = "cmake"
    build_requires = "cxxtest/4.4@aquaveo/stable"
    exports = "CMakeLists.txt", "LICENSE", "test_files/*"
    exports_sources = "xmsgrid/*", "test_files/*", "_package/*"

    def configure(self):
        # Set verion dynamically using XMS_VERSION env variable.
        self.version = self.env.get('XMS_VERSION', '99.99.99')

        # Raise ConanExceptions for Unsupported Versions
        s_os = self.settings.os
        s_compiler = self.settings.compiler
        s_compiler_version = self.settings.compiler.version

        if s_compiler == "apple-clang" and s_os == 'Linux':
            raise ConanException("Clang on Linux is not supported.")

        if s_compiler == "apple-clang" \
                and s_os == 'Macos' \
                and float(s_compiler_version.value) < 9.0:
            raise ConanException("Clang > 9.0 is required for Mac.")
        
        if s_compiler == 'Visual Studio' and self.options.wchar_t == 'typedef' and self.options.pybind:
            raise ConanException("wchar_t=typedef not supported with pybind=True")

        self.options['xmscore'].pybind = self.options.pybind
        self.options['xmscore'].testing = self.options.testing
        
        if s_compiler == 'Visual Studio':
            self.options['xmscore'].wchar_t = self.options.wchar_t
            self.options['boost'].wchar_t = self.options.wchar_t

    def config_options(self):
        if self.settings.compiler != 'Visual Studio':
            del self.options.wchar_t

    def requirements(self):
        """Requirements"""
        self.requires("boost/1.74.0.3@aquaveo/stable")
        if self.options.pybind:
            self.requires("pybind11/2.5.0@aquaveo/testing")
        self.requires("xmscore/5.0.1@aquaveo/stable")

    def build(self):
        cmake = CMake(self)

        # CXXTest doesn't play nice with PyBind. Also, it would be nice to not
        # have tests in release code. Thus, if we want to run tests, we will
        # build a test version (without python), run the tests, and then (on
        # sucess) rebuild the library without tests.
        cmake.definitions["XMS_VERSION"] = '{}'.format(self.version)
        cmake.definitions["IS_PYTHON_BUILD"] = self.options.pybind
        cmake.definitions["BUILD_TESTING"] = self.options.testing
        cmake.definitions["XMSGRID_TEST_PATH"] = "test_files"
        cmake.definitions["PYTHON_TARGET_VERSION"] = self.env.get("PYTHON_TARGET_VERSION", "3.6")
        if self.settings.compiler == 'Visual Studio':
            cmake.definitions["USE_TYPEDEF_WCHAR_T"] = (self.options.wchar_t == 'typedef')
        cmake.configure(source_folder=".")
        cmake.build()
        cmake.install()

        if self.options.testing:
            print("***********(0.0)*************")
            try:
                cmake.test()
            except ConanException:
                raise
            finally:
                if os.path.isfile("TEST-cxxtest.xml"):
                    with open("TEST-cxxtest.xml", "r") as f:
                        for line in f.readlines():
                            no_newline = line.strip('\n')
                            print(no_newline)
                print("***********(0.0)*************")
        elif self.options.pybind:
            with tools.pythonpath(self):
                if not self.settings.os == "Macos":
                  self.run('pip install --user numpy twine wheel')
                else:
                  self.run('pip install numpy twine wheel')
                self.run('python -m unittest discover -v -p *_pyt.py -s {}/_package/tests'.format(
                    os.path.join(self.build_folder)), cwd=os.path.join(self.package_folder, "_package"))
                # Create and upload wheel to PyPi if release and windows
                is_release = self.env.get("RELEASE_PYTHON", 'False')
                if is_release == 'True' and ((self.settings.os == "Macos" or self.settings.os == "Linux")
                                             or (self.settings.os == "Windows" and
                                             str(self.settings.compiler.runtime) == "MD")):
                    devpi_url = self.env.get("AQUAPI_URL", 'NO_URL')
                    devpi_username = self.env.get("AQUAPI_USERNAME", 'NO_USERNAME')
                    devpi_password = self.env.get("AQUAPI_PASSWORD", 'NO_PASSWORD')
                    self.run('devpi use {}'.format(devpi_url))
                    self.run('devpi login {} --password {}'.format(devpi_username, devpi_password))
                    plat_names = {'Windows': 'win_amd64', 'Linux': 'linux_x86_64', "Macos": 'macosx-10.6-intel'}
                    self.run('python setup.py bdist_wheel --plat-name={} --dist-dir {}'.format(
                        plat_names[str(self.settings.os)],
                        os.path.join(self.build_folder, "dist")), cwd=os.path.join(self.package_folder, "_package"))
                    self.run('devpi upload --from-dir {}'.format(os.path.join(self.build_folder, "dist")), cwd=".")

    def package(self):
        self.copy("license", dst="licenses", ignore_case=True, keep_path=False)

    def package_info(self):
        self.env_info.PYTHONPATH.append(os.path.join(self.package_folder, "_package"))
        if self.settings.build_type == 'Debug':
            self.cpp_info.libs = ["xmsgridlib_d"]
        else:
            self.cpp_info.libs = ["xmsgridlib"]
        if not self.in_local_cache:
            from os import path
            root = path.abspath(path.dirname(__file__))
            self.cpp_info.libdirs = [path.join(root, 'build/lib')]
