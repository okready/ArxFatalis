Currently Unnamed Arx Fatalis Source Project

This is an attempt to port Arx Fatalis to other platforms (i.e. Linux, Mac OS
X).  The current set of goals are as follows:

- Use Premake to generate build files for easier cross-platform development.
- Implement an OpenGL renderer (preferably keeping the Direct3D 7 renderer
  intact).
- Port remaining Windows-specific code over to a platform independent layer and
  implement for other platforms as appropriate.
- ???
- Sandwiches.

Development is currently being done on Windows until the OpenGL renderer is
implemented, after which it will switch over to Linux.  I don't have access to
a computer running OS X, so assistance will be appreciated once that point is
reached.

Since current versions of the DirectX SDK do not include support for creating
Direct3D 7 apps, an older copy of the SDK is currently needed for building on
Windows.  A copy can be acquired from
http://bcb-tools.com/Downloads.htm#DirectX7.  The Premake script is configured
to look for the SDK includes and libraries in a "DX" subdirectory of "Sources".

- Ted Cipicchio <ted@thereisnospork.com>