find_package(PkgConfig)

pkg_check_modules(OpenCL REQUIRED OpenCL)

set(OpenCL_INCLUDE_DIRS ${OpenCL_INCLUDE_DIRS} CACHE PATH "OpenCL include dirs")
set(OpenCL_LIBRARIES ${OpenCL_LIBRARIES} CACHE STRING "OpenCL libraries")
