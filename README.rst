DABCommon
=========

.. role:: cpp(code)
   :language: cpp

This library provides some common infrastructure for the *data-over-dab*
libraries. It is a header-only library that encapsulates types like
:cpp:`dab::sample_queue_t` as well as some useful constants like
:cpp:`dab::kTransmissionMode1`.

Dependencies
------------

DABCommon has no dependencies per se. However, if you would like to build the
unit tests you will need `CUTE <https://github.com/PeterSommerlad/CUTE>`_ and
`CUTEX <https://github.com/fmorgner/CUTEX>`_. There are currently two resolution
mechanisms available in DABCommon, using Git or Conan.

Dependency Resolution via Conan
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Dependency resolution via Conan requires you to add an additional Conan remote.
This remote contains packages for CUTE and CUTEX. To register this new remote
with conan, you can use the following command:

.. code:: bash

  conan remote add conan-fmorgner https://api.bintray.com/conan/fmorgner/conan-fmorgner

After you have registered this new remote, you can select Conan-based dependency
resolution using the following argument to CMake:

.. code:: text

  -DDABCOMMON_DEPS_VIA=conan

Dependency Resolution via Git
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

As an alternative to Conan, you can also use Git for dependency resolution.
Since this is the default configuration, you don't need to setup anything.
However, if you would like to be explicit about using git to resolve the
dependencies of DABCommon, you can use the following argument to CMake:

.. code:: text

  -DDABCOMMON_DEPS_VIA=git

Running the Unit Tests
----------------------

To run the unit tests, use the included CMake environment. Simply use the
following commands from the source root:

.. code:: bash

  mkdir -p build
  cd build
  cmake .. [DEPENDENCY_RESOLUTION_MECHANISM]
  cmake --build .

Locally Exporting the Conan Package
-----------------------------------

While the above remote also provides packages for all *data-over-dab* libraries,
you can also export a conan package to your local cache. This is especially
useful if you are working on DABCommon. To export the package, use the following
command:

.. code:: bash

  conan export Opendigitalradio/stable --build=missing
