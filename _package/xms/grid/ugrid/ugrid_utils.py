from .._xmsgrid.ugrid import ugrid_utils as ugu
from .ugrid import UGrid


def read_ugrid_from_ascii_file(file_name):
    """
    Read a ugrid from an ascii file

    Args:
        file_name: file to read the ugrid from

    Returns:
        A ugrid read from a file
    """
    return UGrid(instance=ugu.read_ugrid_from_ascii_file(file_name))


def write_ugrid_to_ascii_file(ugrid, file_name):
    """
    Write a ugrid to an ascii file

    Args:
        ugrid: UGrid to write to a file
        file_name: File to write UGrid to
    """
    ugu.write_ugrid_to_ascii_file(ugrid._instance, file_name)