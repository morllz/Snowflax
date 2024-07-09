#pragma once

#include "Snowflax/Graphics/GraphicsContext.h"
#include <vulkan/vulkan.h>

#ifdef SFLX_VULKAN_ENABLE_VALIDATION_LAYERS
	#define SFLX_VULKAN_ENABLE_DEBUG_MESSENGER
#endif


namespace Snowflax
{
	class VulkanContext : public GraphicsContext
	{
	public:

		virtual void Init() override;
		virtual void CleanUp() override;

	private:

		void CreateInstance();

		static std::vector<VkExtensionProperties> GetSupportedExtensions();
		static std::vector<VkLayerProperties> GetSupportedLayers();
		static bool CheckExtensionSupport(const char* _extensionName);
		static bool CheckLayerSupport(const char* _layerName);
		static std::vector<const char*> GetRequiredExtensions();
		static std::vector<const char*> GetRequiredLayers();

#ifdef SFLX_VULKAN_ENABLE_DEBUG_MESSENGER
		void SetupDebugMessenger();

		static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& _createInfo);

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugMessengerCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

		static VkResult CreateDebugUtilsMessengerEXT(
			VkInstance _instance, 
			const VkDebugUtilsMessengerCreateInfoEXT* _pCreateInfo, 
			const VkAllocationCallbacks* _pAllocator, 
			VkDebugUtilsMessengerEXT* _pDebugMessenger);

		static void DestroyDebugUtilsMessengerEXT(
			VkInstance _instance, 
			VkDebugUtilsMessengerEXT _debugMessenger, 
			const VkAllocationCallbacks* _pAllocator);

		VkDebugUtilsMessengerEXT m_DebugMessenger = nullptr;
#endif

		VkInstance m_Instance = nullptr;
	};
}
