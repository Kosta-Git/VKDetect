#include "VulkanInitializer.h"

VkInstance VKInit::CreateInstance( ) {
  VkApplicationInfo VkInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
  VkInfo.apiVersion = VK_API_VERSION_1_1;

  VkInstanceCreateInfo VkCreateInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
  VkCreateInfo.pApplicationInfo = &VkInfo;

  const char* VkVerificationLayers[1] = { "VK_LAYER_LUNARG_standard_validation" };
  VkCreateInfo.ppEnabledLayerNames = VkVerificationLayers;
  VkCreateInfo.enabledLayerCount   = sizeof ( VkVerificationLayers ) / sizeof ( VkVerificationLayers[0] );

  const char* extensions[1] = { VK_KHR_SURFACE_EXTENSION_NAME };
  VkCreateInfo.ppEnabledExtensionNames = extensions;
  VkCreateInfo.enabledExtensionCount   = sizeof ( extensions ) / sizeof ( extensions[0] );

  VkInstance instance = nullptr;
  int status = vkCreateInstance( &VkCreateInfo, nullptr, &instance );

  return status == VK_SUCCESS ? instance : nullptr;
}

VkPhysicalDevice VKInit::GetPhysicalDevice( VkInstance instance ) {
  VkPhysicalDevice device[8];
  uint32_t deviceCount = sizeof ( device ) / sizeof ( device[0] );

  vkEnumeratePhysicalDevices( instance, &deviceCount, device );
  printf( "Detected %d device(s)...\n", deviceCount );
  printf( "=======================================\n" );

  for( uint32_t i = 0; i < deviceCount; ++i ) {
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties( device[i], &props );

    if( props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ) {
      printf( "Selected: %s\n", props.deviceName );
      return device[i];
    }
  }

  if( deviceCount > 0 ) {
    printf( "Selected fallback device\n" );
    return device[0];
  }

  return nullptr;
}

void VKInit::PrintAllPhysicalDevices( VkInstance instance ) {
  VkPhysicalDevice device[8];
  uint32_t deviceCount = sizeof ( device ) / sizeof ( device[0] );

  vkEnumeratePhysicalDevices( instance, &deviceCount, device );
  printf( "Found %d device(s), starting iteration...\n\n", deviceCount );

  for( uint32_t i = 0; i < deviceCount; ++i ) {
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties( device[i], &props );

    PrintPhysicalDevice( props );
  }
}

void VKInit::PrintPhysicalDevice( VkPhysicalDeviceProperties props ) {
  switch( props.deviceType ) {
    case VK_PHYSICAL_DEVICE_TYPE_CPU:
      printf( "Detected CPU:\n" );
      break;
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
      printf( "Detected physical GPU:\n" );
      break;
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
      printf( "Detected integrated GPU:\n" );
      break;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
      printf( "Detected virtual GPU:\n" );
      break;
    case VK_PHYSICAL_DEVICE_TYPE_OTHER:
      printf( "Detected graphical device:\n" );
      break;
    default:
      return;
  }

  printf( "\tDevice name: %s\n", props.deviceName );
  printf( "\tDevice id: %d\n", props.deviceID );
  printf( "\tDevice Pipeline UUID: %d\n", *props.pipelineCacheUUID );

  switch( props.vendorID ) {
    case Vendors::NVIDIA:
      printf( "\tVendor name: NVIDIA\n" );
      break;
    case Vendors::SAPPHIRE:
      printf( "\tVendor name: SAPPHIRE\n" );
      break;
    case Vendors::AMD:
      printf( "\tVendor name: AMD\n" );
      break;
    default:
      printf( "\tVendor id: %d\n", props.vendorID );
      break;
  }

  printf( "\tVulkan Version: %d.%d.%d\n", VK_VERSION_MAJOR(props.apiVersion), VK_VERSION_MINOR(props.apiVersion), VK_VERSION_PATCH(props.apiVersion) );
  printf( "\tDriver Version: %d\n", props.driverVersion );
  printf( "\tRay Tracing Flag: %d\n", VK_NV_ray_tracing );
  printf( "\tDevice limits:\n");
  printf( "\t\tMax viewport: %d\n", props.limits.maxViewports );
  printf( "\t\tMax viewport dimension: ( %i;%i )\n", props.limits.maxViewportDimensions[0], props.limits.maxViewportDimensions[1] );
  printf( "\t\tViewport bounds: ( %f;%f )\n", props.limits. viewportBoundsRange[0], props.limits. viewportBoundsRange[1] );
  printf( "\t\tMax clip distance: %d\n", props.limits.maxClipDistances );
  printf( "\t\tMax cull distance: %d\n", props.limits.maxCullDistances );
  printf( "\t\tPrecision bits: %d ( Max divisions: %f )\n", props.limits.mipmapPrecisionBits, pow( props.limits.mipmapPrecisionBits, 2 ) );
  printf( "\t\tMax VK_IMAGE dimension: %d\n", props.limits.maxImageDimensionCube );
  printf( "\t\tLine precision MIN: %f; MAX: %f\n", props.limits.lineWidthRange[0], props.limits.lineWidthRange[1] );
  printf( "\t\tPoint precision MIN: %f; MAX: %f\n", props.limits.pointSizeRange[0], props.limits.pointSizeRange[1] );
  printf( "================================================================\n" );
}

void VKInit::DestroyInstance( VkInstance instance ) {
  vkDestroyInstance( instance, nullptr );
}
