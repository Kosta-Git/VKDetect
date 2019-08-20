#include <vulkan/vulkan.h>

#include <stdlib.h>
#include <stdio.h>

#include "VulkanInitializer.h"

int main( )
{
  printf(" _   _ _   __ ______     _            _   \n");
  printf("| | | | | / / |  _  \\   | |          | |  \n");
  printf("| | | | |/ /  | | | |___| |_ ___  ___| |_ \n");
  printf("| | | |    \\  | | | / _ \\ __/ _ \\/ __| __|\n");
  printf("\\ \\_/ / |\\  \\ | |/ /  __/ ||  __/ (__| |_ \n");
  printf(" \\___/\\_| \\_/ |___/ \\___|\\__\\___|\\___|\\__|\n\n\n");

  VkInstance instance = VKInit::CreateInstance();

  if( instance == nullptr ) {
    printf( "An error occured, make sure you have Vulkan 1.1 installed\n" );
    return EXIT_FAILURE;
  }

  VKInit::PrintAllPhysicalDevices( instance );

  VKInit::DestroyInstance( instance );
  return EXIT_SUCCESS;
}
