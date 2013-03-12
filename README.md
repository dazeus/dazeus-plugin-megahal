# MegaHAL conversation simulator plugin for DaZeus

Intended for use with DaZeus-Core. The C bindings for DaZeus are also necessary
for connecting to DaZeus. Both are available at https://github.com/dazeus.

This plugin ships along the only two necessary files from the MegaHAL project,
which were retrieved via the MegaHAL website:
http://megahal.alioth.debian.org/. They were taken from the MegaHAL 9.1.1
release, and only adapted to remove the inclusion of the header file `malloc.h`
which is non-standard. It only exists on Linux and serves to import the
`malloc()` call, which is defined in `stdlib.h` as defined in POSIX.

# Author

The author of MegaHAL itself is mr. Jason L. Hutchens. The author of this
plugin and DaZeus itself is Sjors Gielen.

# License

MegaHAL is released under the GNU General Public License version 2, therefore
this plugin is released under the same license. See the `LICENSE.TXT` file, as
copied from the original MegaHAL distribution, for the full license text.
