# UGrid File IO Tutorial

\tableofcontents
# UGrid File IO Tutorial {#FileIO_Tutorial}

## Introduction {#Intro_FileIO}
The purpose of this tutorial is to provide explanation on how to use File IO with xmsgrid. The XmUGrid class does not have file IO members.  Functions are available in the files named XmUGridUtils to provide File IO.

## Example - Writing UGrid data to ASCII file format {#Example_XmWriteUGridFromAsciiFile}
This example shows how to write an exisiting UGrid to an ASCII file using function xms::XmWriteUGridToAsciiFile(). This function takes a XmUGrid and filename with path. The testing code for this example is XmUGridUtilsTests::testWriteThenReadUGridFileToAscii.

## Example - Reading a UGrid from ASCII file format {#Example_XmReadUGridFromAsciiFile}
This example shows how to read a UGrid from an ASCII file using function xms::XmReadUGridFromAsciiFile. This function takes a filename with path and returns an XmUGrid. The testing code for this example is XmUGridUtilsTests::testWriteThenReadUGridFileToAscii.



\snippet xmsgrid/ugrid/XmUGridUtils.cpp snip_test_WriteReadAscii

