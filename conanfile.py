"""
conanfile.py for the xmsgrid project.
"""
from xmsconan.xms_conan2_file import XmsConan2File


class XmsgridConanFile(XmsConan2File):
    """
    XmsgridConanFile class used for defining the conan info.
    """
    name = "xmsgrid"
    url = "https://github.com/Aquaveo/xmsgrid"
    description = "Grid library for XMS products"
    xms_dependencies = [
        "xmscore/6.2.5-5-g2bd6574b",
    ]
    extra_export_sources = ['test_files']

LIBRARY_NAME = XmsgridConanFile.name
