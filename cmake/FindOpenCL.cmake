find_path(OPENCL_INCLUDE_DIR
  NAMES CL/cl.h OpenCL/cl.h
  PATHS
    /usr/include
    /usr/local/include
)

find_library(OPENCL_LIBRARY
  NAMES OpenCL
  PATHS
    /usr/lib
    /usr/lib64
    /usr/lib/x86_64-linux-gnu
    /usr/local/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OpenCL DEFAULT_MSG OPENCL_LIBRARY OPENCL_INCLUDE_DIR)

if(OpenCL_FOUND)
  add_library(OpenCL::OpenCL UNKNOWN IMPORTED)
  set_target_properties(OpenCL::OpenCL PROPERTIES
    IMPORTED_LOCATION "${OPENCL_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${OPENCL_INCLUDE_DIR}"
  )
endif()
