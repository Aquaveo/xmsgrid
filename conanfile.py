"""
conanfile.py for the xmsgrid project.
"""
from xmsconan.xms_conan_file import XmsConanFile


class XmsgridConanFile(XmsConanFile):
    """
    XmsgridConan class used for defining the conan info.
    """
    name = "xmsgrid"
    url = "https://github.com/Aquaveo/xmsgrid"
    description = "Grid library for XMS products"
    xms_dependencies = [
        "xmscore/[>=6.0.1 <7.0.0]@aquaveo/stable",
    ]
    extra_export_sources = ['test_files']

LIBRARY_NAME = XmsgridConanFile.name
