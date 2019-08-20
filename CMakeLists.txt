cmake_minimum_required( VERSION 3.2 )

set( PROJECT_NAME VKDetect )
project( ${PROJECT_NAME} )

# Find vulkan
find_package( Vulkan REQUIRED )

# Set source files
set( SOURCES
  "VulkanInitializer.h"
  "VulkanInitializer.cpp"
  "main.cpp")
add_executable( ${PROJECT_NAME} ${SOURCES} )

if ( WIN32 )
  target_compile_definitions( ${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR)
  target_link_libraries( ${PROJECT_NAME} Vulkan::Vulkan )
endif( WIN32 )

if ( UNIX )
  find_package( X11 REQUIRED )
  link_libraries( ${X11_LIBRARIES} )
  add_definitions( -DVK_USE_PLATFORM_XLIB_KHR )
endif ( UNIX )

target_link_libraries( ${PROJECT_NAME} Vulkan::Vulkan )
