---
layout: post
title: Simple MySQL Example
---

<pre>
========================================================================
    CONSOLE APPLICATION : example1 Project Overview
========================================================================

AppWizard has created this example1 application for you.

This file contains a summary of what you will find in each of the files that
make up your example1 application.


example1.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

example1.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

example1.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named example1.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
</pre>

Preparations on your system
---

Get helpful hints [here](http://c3r0.de/2008/07/26/mysql_vs_project_cpp/).

Assumes you have a valid "Visual Studio 2010" installation (won't describe command line compilation with Microsoft Visual C++ 2010 Express here, although it should work out of the box, don't blame me if not).

Have `MYSQLHOME` environment variable defined, i. e.:

    MYSQLHOME=S:\Home\mysql-5.1.56-win32

Load [Community Server Version of MySQL](http://dev.mysql.com/downloads/mysql/5.0.html#win32) to `%MYSQLHOME%`. Check if you need to set passwords or similar [post setup steps](http://dev.mysql.com/doc/refman/5.1/de/post-installation.html), I will leave that off for simplicity here. So start the MySQL daemon for testing purpose with (see [here](http://dev.mysql.com/doc/refman/5.1/de/windows-server-first-start.html) and [here ("Startup")](http://www.devside.net/guides/windows/mysql)):

    %MYSQLHOME%\bin\mysqld --console --standalone --bind-address=127.0.0.1 --datadir %MYSQLHOME%\data

You might test it with:

    telnet localhost 3306

Settings in your Visual Studio Solution File
---

As project type have chosen "Win32 Console Application" and left the rest on defaults in the App Wizard:
`File >> New >> Project... >> Visual C++ >> Win32 >> Win32 Console Application >> Application Settings >> Application type: Console application`

The directories containing the Header-Files (include) for MySQL are added
to the C/C++-Compiler settings:
`Solution >> Project >> Properties >> Configuration Properties >> C/C++ >> Additional Include Directories: $(MYSQLHOME)\include`

The directories containing the Library-Files for MySQL are added
to the Linker settings:
`Solution >> Project >> Properties >> Configuration Properties >> Linker >> Additional Library Directories: $(MYSQLHOME)\lib\debug` for the Debug build.

`Solution >> Project >> Properties >> Configuration Properties >> Linker >> Additional Library Directories: $(MYSQLHOME)\lib\opt` for the Release build.

`Solution >> Project >> Properties >> Configuration Properties >> Linker >> Input >> Additional Dependencies: libmysql.lib` (prepend that to the already existent list there) for both the Debug and the Release build. For a rough overview, when to take which library file (`*.lib` vs. `*.dll` and how it relates with build configuration settings in Visual Studio) see [again here, text after "3. Als letzte Einstellung"](http://c3r0.de/2008/07/26/mysql_vs_project_cpp/).

The example itself is taken from [MySql Visual Studio Projekt (C++)](http://c3r0.de/2008/07/26/mysql_vs_project_cpp/).

When built, the `*.exe` file is created below the solution folder (or the output folder you declared, inside Debug/Release). At a command line prompt push into that folder, append `%MYSQLHOME%\lib\debug` (Debug build) or `%MYSQLHOME%\lib\opt` (Release build) - is where the `*.dll` files for MySQL are found - to the `PATH` variable. Now you may run:

    %MYSQLHOME%\bin\mysqladmin variables

first to get an expected output and then the compiled app to see roughly the same, formatted differently:

    example1.exe

Please remember the project at its current state uses a passwordless connection, so if you set up passwords, ou need to change the according source line in `example1.cpp`, but that's an easy task isn't it?

