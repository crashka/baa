# BAA - Budget Analytical Advisory

## Original Project Information

Project Homepage: [BAA - Budget Analytical Advisory][1]

Team Members: Megan, Tim, Paola, Anoushka, Anya

## Fork Information

### Overview

The purpose of this fork is to demonstrate how to incoporate a relational database into a project
such as `BAA`.  We use an [ORM][2] instead of [ODBC][3] or a native call interface
(e.g. [libpqxx][4] for PostgreSQL, or the [C++ Connector][5] for MySQL), since the source code
integration is generally more tidy and does not require intimate knowledge of SQL.  But more
importantly for the demonstration purposes at hand, it is a pattern prevalent in higher-level
languages (such as Python and Java *\[lol\]*) commonly used for rapid program development (and
occasionally production code), especially when performance is not a primary concern.  The ORM
that we are using here is [ODB][6] (see **ODB Notes** below).

The changes in this fork (which should generally map to the order of commits):

* Rename source code directory to `src` and add `Makefile` for build support
* Move `Finances` class declaration and implementation into separate `.cpp` and `.hpp` files,
  respectively, to support the ODB intergration (as well as for general neatness)
* Add `Finances *userInfo` as a pointer to `personalInfo[userIndex]` for prorcessing in `main.cpp`,
  in order to support ODB integration (wherein `personalInfo` is not used)
* Add ODB-based persistence (as a replacement for the `readFile.txt` mechanism), switched on the
  `#define USE_ODB` preprocessor flag

### Instructions

**Edit `Makefile`**

Minimally, the following variables (and possibly others) need to be appropriately set for your
build and runtime environment:

* `CPPFLAGS`
* `ODBFLAGS`
* `LDFLAGS`
* `DBNAME`

**Build `baa-cli` and database**

    $ make EXTRA_CPPFLAGS=-DUSE_ODB
    $ make loaddb

Note that omitting the `EXTRA_CPPFLAGS` directive for `make` should yield a binary functionally
identical to the original project code.

**Run `baa-cli`**

    $ baa-cli --host=localhost

where the appropriate database connect information should be specified.  The following arguments
(including `--host=<host>`) are recognized:

* `--user=<login>` (*or* `--username=<login>`)
* `--password=<password>`
* `--database=<name>` (*or* `--dbname=<name>`)
* `--host=<host>`
* `--port=<integer>`
* `--options-file=<file>`

### ODB Notes

It is not clear whether&mdash;or for how long&mdash;the support for ODB will continue.  There is
monthly activity on the [odb-users][96] mailing list, and a new Beta version (2.5.0) of ODB was
released in March 2019, however the list of supported [O/S and C++ compiler platforms][97] seems to
be rather outdated.  Despite the assertion that ODB should work with any modern C++ compiler, the
current production version (2.4.0) from the [ODB Download][98] page was incompatible with Ubuntu
18.04 and GCC version 7.4.  The software available on the ODB Download page may be compatible with
other O/S and compiler combinations, but for Ubuntu 18.04, it was necessary to compile and install
from sources (see below).

#### Building on Ubuntu 18.04

The following is based on [instructions from Boris Kolpackov][99]:

**Build and install lastest build2 binaries and toolchain**

    $ mkdir build2
    $ cd build2
    $ curl -sSfO https://stage.build2.org/0/0.12.0-a.0/build2-install-0.12.0-a.0-stage.sh
    $ sh build2-install-0.12.0-a.0-stage.sh /home/crash/.local
    $ cd ..

**Build and install ODB from sources (along with PostgreSQL support)**

    $ bpkg create -d odb cc config.cxx=g++ config.install.root=/home/crash/.local/
    $ cd odb
    $ bpkg build odb@https://stage.build2.org/1
    $ bpkg build libodb-pgsql@https://stage.build2.org/1
    $ b install
    $ cd ..

The following is the complete list of database platforms supported, along with the associated
library name (which is also the build target, used as above):

| Database Platform | Library Name |
| --- | --- |
| MySQL | `libodb-mysql` |
| SQLite | `libodb-sqlite` |
| PostgreSQL | `libodb-pgsql` |
| Oracle | `libodb-oracle` |
| Microsoft SQL Server | `libodb-mssql` |


[1]: https://devpost.com/software/baa-budgetary-analytical-advisor
[2]: https://stackoverflow.com/a/1279678
[3]: https://docs.microsoft.com/en-us/sql/odbc/reference/odbc-overview
[4]: https://github.com/jtv/libpqxx
[5]: https://dev.mysql.com/doc/dev/connector-cpp
[6]: https://www.codesynthesis.com/products/odb/
[95]: https://www.codesynthesis.com/
[96]: https://codesynthesis.com/pipermail/odb-users/
[97]: https://www.codesynthesis.com/products/odb/platforms.xhtml
[98]: https://www.codesynthesis.com/products/odb/download.xhtml
[99]: https://www.codesynthesis.com/pipermail/odb-users/2018-June/004039.html
