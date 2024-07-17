#include "SFLXpch.h"
#include "VulkanContext.h"
#include <GLFW/glfw3.h>


namespace Snowflax
{
	VulkanContext::VulkanContext(Window* _window) : m_Window(_window)
	{
	}

	void VulkanContext::Init()
	{
		CreateInstance();

#ifdef SFLX_VULKAN_ENABLE_DEBUG_MESSENGER
		SetupDebugMessenger();
#endif

		CreateSurface();
		PickPhysicalDevice();
		CreateLogicalDevice();
	}

	void VulkanContext::CleanUp()
	{
		vkDestroyDevice(m_LogicalDevice, nullptr);
		vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
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

		auto extensions = GetRequiredInstanceExtensions();
		for(auto extensionName : extensions)
		{
			SFLX_ASSERT(CheckInstanceExtensionSupport(extensionName), "Required vulkan instance extension not supported!");
		}
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		auto layers = GetRequiredInstanceLayers();
		for(auto layerName : layers)
		{
			SFLX_ASSERT(CheckInstanceLayerSupport(layerName), "Required vulkan instance layer not supported!");
		}
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
				std::make_pair(RatePhysicalDeviceSuitability(device, m_Surface), device));
		}

		SFLX_ASSERT(candidates.rbegin()->first > 0, "Failed to find suitable GPU!");

		if(candidates.rbegin()->first > 0) m_PhysicalDevice = candidates.rbegin()->second;
	}

	void VulkanContext::CreateLogicalDevice()
	{
		auto[graphicsFamily, presentationFamily] = FindPhysicalDeviceQueueFamilies(m_PhysicalDevice, m_Surface);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies;

		if(graphicsFamily.has_value())
			uniqueQueueFamilies.insert(graphicsFamily.value());
		if(presentationFamily.has_value())
			uniqueQueueFamilies.insert(presentationFamily.value());

		for(auto queueFamilyIndex : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
			queueCreateInfo.queueCount = 1;
			constexpr float queuePriority = 1.0f;
			queueCreateInfo.pQueuePriorities = &queuePriority;

			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());

		createInfo.pEnabledFeatures = &deviceFeatures;

		auto extensions = GetRequiredDeviceExtensions();
		for(auto extensionName : extensions)
		{
			SFLX_ASSERT(CheckDeviceExtensionSupport(m_PhysicalDevice, extensionName), "Required vulkan device extension not supported by physical device!");
		}
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		auto layers = GetRequiredDeviceLayers();
		for(auto layerName : layers)
		{
			SFLX_ASSERT(CheckDeviceLayerSupport(m_PhysicalDevice, layerName), "Required vulkan device layer not supported by physical device!");
		}
		createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
		createInfo.ppEnabledLayerNames = layers.data();

		auto result = vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_LogicalDevice);
		SFLX_ASSERT(result == VK_SUCCESS, "Creation of logical device failed");

		if(graphicsFamily.has_value())
			vkGetDeviceQueue(m_LogicalDevice, graphicsFamily.value(), 0, &m_GraphicsQueue);
		SFLX_ASSERT(graphicsFamily.has_value(), "Failed to get graphics queue as no graphics queue family is present!");
		if(presentationFamily.has_value())
			vkGetDeviceQueue(m_LogicalDevice, presentationFamily.value(), 0, &m_PresentationQueue);
		SFLX_ASSERT(presentationFamily.has_value(), "Failed to get presentation queue as no presentation queue family is present!");
	}

	std::vector<VkExtensionProperties> VulkanContext::GetSupportedInstanceExtensions()
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		return  extensions;
	}

	std::vector<VkLayerProperties> VulkanContext::GetSupportedInstanceLayers()
	{
		uint32_t layerCount = 0;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> layers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

		return layers;
	}

	bool VulkanContext::CheckInstanceExtensionSupport(const char* _extensionName)
	{
		const auto extensions = GetSupportedInstanceExtensions();

		for(const auto&[extensionName, specVersion] : extensions)
		{
			if(strcmp(extensionName, _extensionName) == 0) return true;
		}
		return false;
	}

	bool VulkanContext::CheckInstanceLayerSupport(const char* _layerName)
	{
		const auto layers = GetSupportedInstanceLayers();

		for(const auto&[layerName, specVersion, implementationVersion, description] : layers)
		{
			if(strcmp(layerName, _layerName) == 0) return true;
		}
		return false;
	}

	std::vector<const char*> VulkanContext::GetRequiredInstanceExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef SFLX_VULKAN_ENABLE_VALIDATION_LAYERS
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
		return extensions;
	}

	std::vector<const char*> VulkanContext::GetRequiredInstanceLayers()
	{
		std::vector<const char*> layers {};

#ifdef SFLX_VULKAN_ENABLE_VALIDATION_LAYERS
		const auto validationLayers = GetValidationLayers();

		for(auto layerName : validationLayers)
		{
			SFLX_ASSERT(CheckInstanceLayerSupport(layerName), "Vulkan validation layer not supported!");
			layers.push_back(layerName);
		}
#endif

		return layers;
	}

	void VulkanContext::CreateSurface()
	{
		auto window = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
		auto result = glfwCreateWindowSurface(m_Instance, window, nullptr, &m_Surface);
		SFLX_ASSERT(result == VK_SUCCESS, "Failed to create vulkan surface!");
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

	std::vector<VkQueueFamilyProperties> VulkanContext::GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice& _device)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, queueFamilies.data());

		return queueFamilies;
	}

	VulkanContext::QueueFamilyIndices VulkanContext::FindPhysicalDeviceQueueFamilies(VkPhysicalDevice& _device, VkSurfaceKHR& _surface)
	{
		QueueFamilyIndices familyIndices;

		auto familyProperties = GetPhysicalDeviceQueueFamilyProperties(_device);

		for(auto it = familyProperties.begin(); it != familyProperties.end(); ++it)
		{
			auto queueIndex = static_cast<uint32_t>(it - familyProperties.begin());

			if(it->queueFlags & VK_QUEUE_GRAPHICS_BIT)
				familyIndices.GraphicsFamily = queueIndex;

			VkBool32 presentationSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(_device, queueIndex, _surface, &presentationSupport);
			if(presentationSupport)
				familyIndices.PresentationFamily = queueIndex;

			if(familyIndices.IsComplete()) break;
		}

		return familyIndices;
	}

	bool VulkanContext::CheckPhysicalDeviceProperties(VkPhysicalDevice& _device)
	{
		auto properties = GetPhysicalDeviceProperties(_device);

		return
			properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ||
			properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU ||
			properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU;
	}

	bool VulkanContext::CheckPhysicalDeviceFeatures(VkPhysicalDevice& _device)
	{
		auto features = GetPhysicalDeviceFeatures(_device);

		return features.geometryShader;
	}

	bool VulkanContext::CheckPhysicalDeviceLimits(VkPhysicalDevice& _device)
	{
		return true;
	}

	bool VulkanContext::CheckPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice& _device, VkSurfaceKHR& _surface)
	{
		auto queueIndices = FindPhysicalDeviceQueueFamilies(_device, _surface);

		return queueIndices.IsComplete();
	}

	int VulkanContext::RatePhysicalDeviceSuitability(VkPhysicalDevice& _device, VkSurfaceKHR& _surface)
	{
		if(!(CheckPhysicalDeviceProperties(_device) && 
			CheckPhysicalDeviceFeatures(_device) && 
			CheckPhysicalDeviceLimits(_device)) &&
			CheckPhysicalDeviceQueueFamilyProperties(_device, _surface)
			) return 0;
		return 1;
	}

	std::vector<VkExtensionProperties> VulkanContext::GetSupportedDeviceExtensions(VkPhysicalDevice& _device)
	{
		uint32_t extensionCount = 0;
		vkEnumerateDeviceExtensionProperties(_device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(_device, nullptr, &extensionCount, extensions.data());

		return extensions;
	}

	std::vector<VkLayerProperties> VulkanContext::GetSupportedDeviceLayers(VkPhysicalDevice& _device)
	{
		uint32_t layerCount = 0;
		vkEnumerateDeviceLayerProperties(_device, &layerCount, nullptr);

		std::vector<VkLayerProperties> layers(layerCount);
		vkEnumerateDeviceLayerProperties(_device, &layerCount, layers.data());

		return layers;
	}

	bool VulkanContext::CheckDeviceExtensionSupport(VkPhysicalDevice& _device, const char* _extensionName)
	{
		const auto extensions = GetSupportedDeviceExtensions(_device);

		for(const auto&[extensionName, specVersion] : extensions)
		{
			if(strcmp(extensionName, _extensionName) == 0) return true;
		}
		return false;
	}

	bool VulkanContext::CheckDeviceLayerSupport(VkPhysicalDevice& _device, const char* _layerName)
	{
		const auto layers = GetSupportedDeviceLayers(_device);

		for(const auto&[layerName, specVersion, implementationVersion, description] : layers)
		{
			if(strcmp(layerName, _layerName) == 0) return true;
		}
		return false;
	}

	std::vector<const char*> VulkanContext::GetRequiredDeviceExtensions()
	{
		return {};
	}

	std::vector<const char*> VulkanContext::GetRequiredDeviceLayers()
	{
		std::vector<const char*> layers {};

#ifdef SFLX_VULKAN_ENABLE_VALIDATION_LAYERS
		const auto validationLayers = GetValidationLayers();

		for(auto layerName : validationLayers)
		{
			SFLX_ASSERT(CheckInstanceLayerSupport(layerName), "Vulkan validation layer not supported!");
			layers.push_back(layerName);
		}
#endif

		return layers;
	}

#ifdef SFLX_VULKAN_ENABLE_VALIDATION_LAYERS
	std::vector<const char*> VulkanContext::GetValidationLayers()
	{
		return {
			"VK_LAYER_KHRONOS_validation"
		};
	}
#endif

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
		const VkDebugUtilsMessageSeverityFlagBitsEXT _messageSeverity,
		const VkDebugUtilsMessageTypeFlagsEXT _messageType, 
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

		const std::string message = std::format("Vulkan ({}): {}", type, _pCallbackData->pMessage);

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
