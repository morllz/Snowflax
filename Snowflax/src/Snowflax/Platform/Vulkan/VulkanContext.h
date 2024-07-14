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


		// Instance
		void CreateInstance();

		static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
		static std::vector<VkLayerProperties> GetSupportedInstanceLayers();
		static bool CheckInstanceExtensionSupport(const char* _extensionName);
		static bool CheckInstanceLayerSupport(const char* _layerName);
		static std::vector<const char*> GetRequiredInstanceExtensions();
		static std::vector<const char*> GetRequiredInstanceLayers();

		// Physical Device
		void PickPhysicalDevice();

		std::vector<VkPhysicalDevice> GetPhysicalDevices() const;
		static VkPhysicalDeviceProperties GetPhysicalDeviceProperties(VkPhysicalDevice& _device);
		static VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures(VkPhysicalDevice& _device);
		static std::vector<VkQueueFamilyProperties> GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice& _device);

		struct QueueFamilyIndices
		{
		    std::optional<uint32_t> GraphicsFamily;
		
		    bool IsComplete() const {
		        return GraphicsFamily.has_value();
		    }
		};

		static QueueFamilyIndices FindPhysicalDeviceQueueFamilies(VkPhysicalDevice& _device);
		static bool CheckPhysicalDeviceProperties(VkPhysicalDevice& _device);
		static bool CheckPhysicalDeviceFeatures(VkPhysicalDevice& _device);
		static bool CheckPhysicalDeviceLimits(VkPhysicalDevice& _device);
		static bool CheckPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice& _device);
		static int RatePhysicalDeviceSuitability(VkPhysicalDevice& _device);

		// Logical Device
		void CreateLogicalDevice();

		static std::vector<VkExtensionProperties> GetSupportedDeviceExtensions(VkPhysicalDevice& _device);
		static std::vector<VkLayerProperties> GetSupportedDeviceLayers(VkPhysicalDevice& _device);
		static bool CheckDeviceExtensionSupport(VkPhysicalDevice& _device, const char* _extensionName);
		static bool CheckDeviceLayerSupport(VkPhysicalDevice& _device, const char* _layerName);
		static std::vector<const char*> GetRequiredDeviceExtensions();
		static std::vector<const char*> GetRequiredDeviceLayers();
		// Validation layer

#ifdef SFLX_VULKAN_ENABLE_VALIDATION_LAYERS
		static std::vector<const char*> GetValidationLayers();
#endif

		// Debug Messenger
#ifdef SFLX_VULKAN_ENABLE_DEBUG_MESSENGER
		void SetupDebugMessenger();

		static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& _createInfo);

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugMessengerCallback(
			const VkDebugUtilsMessageSeverityFlagBitsEXT _messageSeverity,
			const VkDebugUtilsMessageTypeFlagsEXT _messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* _pCallbackData,
			void* _pUserData);

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
		VkDevice m_LogicalDevice = VK_NULL_HANDLE;
	};
}
