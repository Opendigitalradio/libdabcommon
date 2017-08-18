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
`CUTEX <https://github.com/fmorgner/CUTEX>`_. Both of these libraries are
available via conan. In order for conan to be able to resolve the dependencies,
you will currently need to add an additional conan remote, using the following
command:

.. code:: bash

  conan remote add conan-fmorgner https://api.bintray.com/conan/fmorgner/conan-fmorgner

Running the Unit Tests
----------------------

To run the unit tests, use the included CMake environment. Simply use the
following commands from the source root:

.. code:: bash

  mkdir -p build
  cd build
  cmake ..
  cmake --build .

Locally Exporting the Conan Package
-----------------------------------

While the above remote also provides packages for all *data-over-dab* libraries,
you can also export a conan package to your local cache. This is especially
useful if you are working on DABCommon. To export the package, use the following
command:

.. code:: bash

  conan export Opendigitalradio/stable --build=missing
