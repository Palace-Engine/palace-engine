#include "../../../include/graphics/vulkan/vulkan_context.hpp"

#include "../../../include/graphics/vulkan/vulkan_formatters.hpp"

palace::VulkanContext::~VulkanContext() {}

palace::Result palace::VulkanContext::initialize(const Parameters &parameters) {
    PALACE_LOG_INFO("Initializing Vulkan graphics context");
    {
        const Result result =
                GraphicsContext::initialize(parameters.baseParameters);
        if (!isSuccessful(result)) { return result; }
    }

#if PALACE_SUPPORTS_VULKAN
    DynamicArray<const char *> extensions;
    extensions.append(VK_KHR_SURFACE_EXTENSION_NAME);
    getRequiredExtensions(extensions);

    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pNext = NULL;
    app_info.pApplicationName = "";
    app_info.applicationVersion = 1;
    app_info.pEngineName = "Palace Game Engine";
    app_info.engineVersion = 1;
    app_info.apiVersion = VK_MAKE_API_VERSION(
            parameters.version.variant, parameters.version.major,
            parameters.version.minor, parameters.version.patch);

    const char *layers[] = {"VK_LAYER_KHRONOS_validation"};

    VkInstanceCreateInfo inst_info = {};
    inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    inst_info.pNext = nullptr;
    inst_info.flags = 0;
    inst_info.pApplicationInfo = &app_info;
    inst_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    inst_info.ppEnabledExtensionNames = extensions.data();
    inst_info.enabledLayerCount = 1;
    inst_info.ppEnabledLayerNames = layers;

    VkInstance instance = NULL;
    const VkResult result = vkCreateInstance(&inst_info, nullptr, &instance);

    if (result != VkResult::VK_SUCCESS) {
        PALACE_LOG_ERROR("vkCreateInstance failed with error: {}", result);
        return Result::ApiError;
    }

    m_instance = instance;
    return Result::Success;
#else
    PALACE_LOG_ERROR("Vulkan is not supported");
    return Result::Unsupported;
#endif
}

void palace::VulkanContext::enumerateDevices() {
#if PALACE_SUPPORTS_VULKAN
    VkResult result;

    uint32_t deviceCount;
    result = vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
    if (result != VkResult::VK_SUCCESS) {
        PALACE_LOG_ERROR("vkEnumeratePhysicalDevices failed with error: {}",
                         result);
        return;
    }

    DynamicArray<VkPhysicalDevice> devices;
    devices.resize(static_cast<size_t>(deviceCount));
    result = vkEnumeratePhysicalDevices(m_instance, &deviceCount,
                                        devices.writeable());
    if (result != VkResult::VK_SUCCESS) {
        PALACE_LOG_ERROR("vkEnumeratePhysicalDevices failed with error: {}",
                         result);
        return;
    }

    VkPhysicalDeviceProperties deviceProperties;
    m_physicalDevices.resize(static_cast<size_t>(deviceCount));
    for (size_t i = 0; i < static_cast<size_t>(deviceCount); ++i) {
        vkGetPhysicalDeviceProperties(devices[i], &m_physicalDevices[i].properties);
    }
#endif
}

size_t palace::VulkanContext::deviceCount() { return 0; }

palace::string palace::VulkanContext::deviceName(size_t i) { return ""; }

palace::VulkanContext::VulkanContext(Platform platform)
    : GraphicsContext(platform, GraphicsApi::Vulkan) {
    m_instance = NULL;
}

#if PALACE_SUPPORTS_VULKAN
palace::VulkanVersion palace::VulkanContext::highestSupportedVersion() {
    uint32_t version;
    VkResult result = vkEnumerateInstanceVersion(&version);

    if (result != VkResult::VK_SUCCESS) { return {0, 0, 0, 0}; }

    return VulkanVersion{.variant = VK_API_VERSION_VARIANT(version),
                         .major = VK_API_VERSION_MAJOR(version),
                         .minor = VK_API_VERSION_MINOR(version),
                         .patch = VK_API_VERSION_PATCH(version)};
}

bool palace::VulkanContext::supports(const palace::VulkanVersion &version) {
    uint32_t highestSupported;
    VkResult result = vkEnumerateInstanceVersion(&highestSupported);

    if (result != VkResult::VK_SUCCESS) { return false; }

    return VK_MAKE_API_VERSION(version.variant, version.major, version.minor,
                               version.patch) <= highestSupported;
}
#endif
