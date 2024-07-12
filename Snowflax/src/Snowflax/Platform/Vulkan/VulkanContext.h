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
		void PickPhysicalDevice();

		static std::vector<VkExtensionProperties> GetSupportedExtensions();
		static std::vector<VkLayerProperties> GetSupportedLayers();
		static bool CheckExtensionSupport(const char* _extensionName);
		static bool CheckLayerSupport(const char* _layerName);
		static std::vector<const char*> GetRequiredExtensions();
		static std::vector<const char*> GetRequiredLayers();

		struct QueueFamilyIndices
		{
		    std::optional<uint32_t> GraphicsFamily;
		
		    bool IsComplete() const {
		        return GraphicsFamily.has_value();
		    }
		};

		std::vector<VkPhysicalDevice> GetPhysicalDevices() const;
		static VkPhysicalDeviceProperties GetPhysicalDeviceProperties(VkPhysicalDevice& _device);
		static VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures(VkPhysicalDevice& _device);
		static std::vector<VkQueueFamilyProperties> GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice& _device);
		static QueueFamilyIndices FindPhysicalDeviceQueueFamilies(VkPhysicalDevice& _device);
		static bool CheckPhysicalDeviceProperties(VkPhysicalDevice& _device);
		static bool CheckPhysicalDeviceFeatures(VkPhysicalDevice& _device);
		static bool CheckPhysicalDeviceLimits(VkPhysicalDevice& _device);
		static bool CheckPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice& _device);
		static int RatePhysicalDeviceSuitability(VkPhysicalDevice& _device);

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

		VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;
#endif

		VkInstance m_Instance = VK_NULL_HANDLE;
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
	};
}
