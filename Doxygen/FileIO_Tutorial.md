# UGrid File IO Tutorial

\tableofcontents
# UGrid File IO Tutorial {#FileIO_Tutorial}

## Introduction {#Intro_FileIO}
The purpose of this tutorial is to provide explanation on how to use File IO
with xmsgrid. The xms::XmUGrid class itself does not have file IO members;
instead, free functions in `XmUGridUtils.h` provide IO and bulk-modification
helpers. This tutorial covers reading and writing UGrids and the modification
utilities (point/cell removal, clipping) that are most commonly used together
with IO.

## Example - Writing UGrid data to ASCII file format {#Example_XmWriteUGridFromAsciiFile}
This example shows how to write an existing UGrid to an ASCII file using function xms::XmWriteUGridToAsciiFile. This function takes a XmUGrid and filename with path. The testing code for this example is XmUGridUtilsTests::testWriteThenReadUGridFileToAscii.

## Example - Reading a UGrid from ASCII file format {#Example_XmReadUGridFromAsciiFile}
This example shows how to read a UGrid from an ASCII file using function xms::XmReadUGridFromAsciiFile. This function takes a filename with path and returns an XmUGrid. The testing code for this example is XmUGridUtilsTests::testWriteThenReadUGridFileToAscii.

\snippet xmsgrid/ugrid/XmUGridUtils.cpp snip_test_WriteReadAscii

## Example - Streaming UGrid data {#Example_XmStreamingUGrid}
For callers that need to read or write to a stream rather than a file path,
xmsgrid exposes stream-based overloads:

* xms::XmReadUGridFromStream(std::istream&) - construct a UGrid from any
  input stream.
* xms::XmWriteUGridToStream(std::shared_ptr<XmUGrid>, std::ostream&) - write a
  UGrid to an output stream.
* xms::XmWriteUGridToStream(const XmUGrid&, std::ostream&, bool a_binary) -
  write a UGrid to an output stream, optionally using a more compact binary
  format. Streams written in binary form must be read back through the stream
  overload of `XmReadUGridFromStream`.

These functions implement the file-path versions above and are useful for
in-memory round-trip serialization (e.g. in tests) or for embedding a UGrid
inside a larger document.

## Example - Removing Points from a UGrid {#Example_XmRemovePoints}
The xms::XmRemovePoints function returns a new UGrid with the specified
points removed. Cells that referenced any of the removed points are removed
as well. There is an overload that also returns the set of cell indices that
were removed so callers can update parallel data structures (e.g. cell
attributes). Point and cell indices in the returned UGrid are renumbered to
be contiguous.

## Example - Removing Cells from a UGrid {#Example_XmRemoveCells}
The xms::XmRemoveCells function returns a new UGrid with the specified cells
removed. By default the points referenced by the removed cells are retained,
but passing `a_deleteOrphanedPoints = true` causes any points that no longer
belong to a cell to be removed as well. An overload also returns the set of
point indices that were deleted.

## Example - Removing Points and Cells Together {#Example_XmRemovePointsAndCells}
For more advanced workflows, xms::XmRemovePointsAndCells provides direct
access to the underlying construction primitives. It takes a UGrid plus the
sets of point and cell indices to remove and returns the resulting points
vector and cellstream by reference. Callers can then construct a new UGrid
from those primitives or compose them with other modifications. The supplied
point and cell removal sets must be consistent: removing a point without
also removing its adjacent cells is not handled.

## Example - Clipping a UGrid to Loops {#Example_XmClipUGrid}
The xms::XmClipUGrid function (declared in `xmsgrid/ugrid/detail/UGridClipper.h`,
included transitively by `XmUGridUtils.h`) returns a new UGrid clipped to a
collection of polygonal loops. Each loop is a vector of point indices into
the input UGrid. Boundary loops should be supplied in clockwise order, while
interior holes should be supplied in counter-clockwise order. Cells that fall
outside the boundary loops or inside hole loops are removed from the
returned grid.
