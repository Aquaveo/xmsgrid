"""UGrid related utilities."""
from .ugrid import UGrid
from .._xmsgrid.ugrid import ugrid_utils as ugu


def read_ugrid_from_ascii_file(file_name):
    """Read a ugrid from an ascii file.

    Args:
        file_name: file to read the ugrid from

    Returns:
        A ugrid read from a file
    """
    return UGrid(instance=ugu.read_ugrid_from_ascii_file(file_name))


def write_ugrid_to_ascii_file(ugrid, file_name):
    """Write a ugrid to an ascii file.

    Args:
        ugrid: UGrid to write to a file
        file_name: File to write UGrid to
    """
    ugu.write_ugrid_to_ascii_file(ugrid._instance, file_name)


def edges_equivalent(edge1, edge2):
    """Check if two edges are equivalent.

    Args:
        edge1: The first edge
        edge2: The second edge

    Returns:
        True if edges are equal, False otherwise
    """
    return ugu.edges_equivalent(edge1, edge2)


def remove_points(ugrid, point_ids):
    """Get a new UGrid with unwanted points removed.

    Args:
        ugrid: The UGrid to remove points from.
        point_ids: Iterable of point IDs to remove.

    Returns:
        A new UGrid with specified points removed.
    """
    new_grid = ugu.remove_points(ugrid._instance, point_ids)
    return UGrid(instance=new_grid)


def remove_cells(ugrid, cell_ids, remove_orphaned_points=False):
    """Get a new UGrid with unwanted cells removed.

    Args:
        ugrid: The UGrid to remove cells from.
        cell_ids: Iterable of cell IDs to remove.
        remove_orphaned_points: Whether to remove points that are no longer part of any cell after removing cells.

    Returns:
        A new UGrid with specified cells/points removed.
    """
    new_ugrid = ugu.remove_cells(ugrid._instance, cell_ids, remove_orphaned_points)
    return UGrid(instance=new_ugrid)


def remove_points_and_cells(ugrid, point_ids, cell_ids):
    """Get a new UGrid with unwanted points and cells removed.

    This function is not smart. If you delete a point without also deleting adjacent cells, it will fail.

    Args:
        ugrid: The UGrid to remove cells from.
        point_ids: Iterable of point IDs to remove.
        cell_ids: Iterable of cell IDs to remove.

    Returns:
        A new UGrid with specified cells/points removed.
    """
    new_ugrid = ugu.remove_points_and_cells(ugrid._instance, point_ids, cell_ids)
    return UGrid(instance=new_ugrid)
