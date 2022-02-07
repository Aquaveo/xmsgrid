"""Install the xmsgrid package."""
import os

from setuptools import setup

from xms.grid import __version__


# allow setup.py to be run from any path
os.chdir(os.path.normpath(os.path.join(os.path.abspath(__file__), os.pardir)))

requires = [
    'numpy',
    'xmscore>=6.0.0',
]

version = __version__

setup(
    python_requires='>=3.10',
    name='xmsgrid',
    version=version,
    packages=['xms.grid', 'xms.grid.geometry', 'xms.grid.triangulate',
              'xms.grid.ugrid', ],
    include_package_data=True,
    license='BSD 2-Clause License',
    description='',
    author='Aquaveo',
    install_requires=requires,
    package_data={'': ['*.pyd', '*.so']},
    test_suite='tests',
    dependency_links=[
        'https://public.aquapi.aquaveo.com/aquaveo/stable'
    ],
)
