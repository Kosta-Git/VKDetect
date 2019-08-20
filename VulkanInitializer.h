#ifndef VULKAN_INITIALIZER_H
#define VULKAN_INITIALIZER_H

#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

namespace VKInit
{
void PrintPhysicalDevice( VkPhysicalDeviceProperties props );

VkInstance CreateInstance();

VkPhysicalDevice GetPhysicalDevice( VkInstance instance );

void PrintAllPhysicalDevices( VkInstance instance );

void DestroyInstance( VkInstance instance );

enum Vendors {
  NVIDIA = 0x10DE,
  AMD = 0x1002,
  SAPPHIRE = 0x174B
};

};

#endif
