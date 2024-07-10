#include "SFLXpch.h"
#include "VulkanContext.h"
#include <GLFW/glfw3.h>


namespace Snowflax
{
	void VulkanContext::Init()
	{
		CreateInstance();

#ifdef SFLX_VULKAN_ENABLE_DEBUG_MESSENGER
		SetupDebugMessenger();
#endif

		PickPhysicalDevice();
	}

	void VulkanContext::CleanUp()
	{
#ifdef SFLX_VULKAN_ENABLE_DEBUG_MESSENGER
		DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
#endif

		vkDestroyInstance(m_Instance, nullptr);
	}

	void VulkanContext::CreateInstance()
	{
		// Application Info
		VkApplicationInfo appInfo {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Application";
		appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
		appInfo.pEngineName = "Snowflax";
		appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Instance Info
		VkInstanceCreateInfo createInfo {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

#ifdef SFLX_VULKAN_ENABLE_DEBUG_MESSENGER
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		PopulateDebugMessengerCreateInfo(debugCreateInfo);

		createInfo.pNext = &debugCreateInfo;
#endif

		auto extensions = GetRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		auto layers = GetRequiredLayers();
		createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
		createInfo.ppEnabledLayerNames = layers.data();

		VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
		SFLX_ASSERT(result == VK_SUCCESS, "Failed to create vulkan instance!");
	}

	void VulkanContext::PickPhysicalDevice()
	{
		auto devices = GetPhysicalDevices();

		std::multimap<int, VkPhysicalDevice> candidates;

		for(auto device : devices)
		{
			candidates.insert(
				std::make_pair(RatePhysicalDeviceSuitability(device), device));
		}

		SFLX_ASSERT(candidates.rbegin()->first > 0, "Failed to find suitable GPU!");

		if(candidates.rbegin()->first > 0) m_PhysicalDevice = candidates.rbegin()->second;
	}

	std::vector<VkExtensionProperties> VulkanContext::GetSupportedExtensions()
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		return  extensions;
	}

	std::vector<VkLayerProperties> VulkanContext::GetSupportedLayers()
	{
		uint32_t layerCount = 0;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> layers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

		return layers;
	}

	bool VulkanContext::CheckExtensionSupport(const char* _extensionName)
	{
		auto extensions = GetSupportedExtensions();

		for(auto&[extensionName, specVersion] : extensions)
		{
			if(strcmp(extensionName, _extensionName) == 0) return true;
		}
		return false;
	}

	bool VulkanContext::CheckLayerSupport(const char* _layerName)
	{
		auto layers = GetSupportedLayers();

		for(auto&[layerName, specVersion, implementationVersion, description] : layers)
		{
			if(strcmp(layerName, _layerName) == 0) return true;
		}
		return false;
	}

	std::vector<const char*> VulkanContext::GetRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef SFLX_VULKAN_ENABLE_VALIDATION_LAYERS
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
		return extensions;
	}

	std::vector<const char*> VulkanContext::GetRequiredLayers()
	{
		std::vector<const char*> layers {};

#ifdef SFLX_VULKAN_ENABLE_VALIDATION_LAYERS
		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		for(auto layerName : validationLayers)
		{
			SFLX_ASSERT(CheckLayerSupport(layerName), "Vulkan validation lay not supported!");
			layers.push_back(layerName);
		}
#endif

		return layers;
	}

	std::vector<VkPhysicalDevice> VulkanContext::GetPhysicalDevices() const
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);
		SFLX_ASSERT(deviceCount, "Failed to find GPUs with vulkan support!");

		std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, physicalDevices.data());

		return physicalDevices;
	}

	VkPhysicalDeviceProperties VulkanContext::GetPhysicalDeviceProperties(VkPhysicalDevice& _device)
	{
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(_device, &properties);

		return properties;
	}

	VkPhysicalDeviceFeatures VulkanContext::GetPhysicalDeviceFeatures(VkPhysicalDevice& _device)
	{
		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceFeatures(_device, &features);

		return features;
	}

	bool VulkanContext::CheckPhysicalDeviceFeatures(VkPhysicalDevice& _device)
	{
		return true;
	}

	bool VulkanContext::CheckPhysicalDeviceLimits(VkPhysicalDevice& _device)
	{
		return true;
	}

	int VulkanContext::RatePhysicalDeviceSuitability(VkPhysicalDevice& _device)
	{
		if(!CheckPhysicalDeviceFeatures(_device) || !CheckPhysicalDeviceLimits(_device)) return 0;
		return 1;
	}

#ifdef SFLX_VULKAN_ENABLE_DEBUG_MESSENGER
	void VulkanContext::SetupDebugMessenger()
	{
		VkDebugUtilsMessengerCreateInfoEXT createInfo {};
		PopulateDebugMessengerCreateInfo(createInfo);

		SFLX_ASSERT(CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr, &m_DebugMessenger) == VK_SUCCESS, "Failed to create vulkan debug messenger!");
	}

	void VulkanContext::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& _createInfo)
	{
		_createInfo = {};
		_createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		_createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		_createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		_createInfo.pfnUserCallback = DebugMessengerCallback;
		_createInfo.pUserData = nullptr;
	}

	VkBool32 VulkanContext::DebugMessengerCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT _messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT _messageType, 
		const VkDebugUtilsMessengerCallbackDataEXT* _pCallbackData,
		void* _pUserData)
	{
		std::string type;

		switch (_messageType)
		{
		case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
			{
				type = "General";
				break;
			}
		case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
			{
				type = "Validation";
				break;
			}
		case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
			{
				type = "Performance";
				break;
			}
		default:
			break;
		}

		std::string message = std::format("Vulkan ({}): {}", type, _pCallbackData->pMessage);

		if(_messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
			SFLX_LOG_DEBUG(message);
		else if(_messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
			SFLX_LOG_TRACE(message);
		else if(_messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
			SFLX_LOG_WARN(message);
		else if(_messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
			SFLX_LOG_ERROR(message);

		return VK_FALSE;
	}

	VkResult VulkanContext::CreateDebugUtilsMessengerEXT(
		VkInstance _instance,
		const VkDebugUtilsMessengerCreateInfoEXT* _pCreateInfo, 
		const VkAllocationCallbacks* _pAllocator,
		VkDebugUtilsMessengerEXT* _pDebugMessenger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) 
		{
			return func(_instance, _pCreateInfo, _pAllocator, _pDebugMessenger);
		}
		else 
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void VulkanContext::DestroyDebugUtilsMessengerEXT(
		VkInstance _instance, 
		VkDebugUtilsMessengerEXT _debugMessenger,
		const VkAllocationCallbacks* _pAllocator)
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) 
		{
			func(_instance, _debugMessenger, _pAllocator);
		}
	}
#endif
}
