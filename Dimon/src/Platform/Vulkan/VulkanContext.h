#pragma once
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "vulkan/vulkan.h"
#include "Dimon/Render/GraphicsContext.h"
struct GLFWwindow;
namespace Dimon {

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		bool isComplete() {
			return graphicsFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class VulkanContext: public GraphicsContext {
	public:
		VulkanContext(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffers() override;

		//Vulkan
		VkInstance m_Instance;
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice m_Device;
		VkSurfaceKHR m_Surface;

		VkQueue m_GraphicsQueue;
		VkQueue m_PresentQueue;
		VkSwapchainKHR m_SwapChain;

		std::vector<VkImage> m_SwapChainImages;
		VkFormat m_SwapChainImageFormat;
		VkExtent2D m_SwapChainExtent;

		std::vector<VkImageView> m_SwapChainImageViews;

		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
		VkRenderPass m_RenderPass;
		VkPipelineLayout m_PipelineLayout;
		VkPipeline m_GraphicsPipeline;
		std::vector<VkFramebuffer> m_SwapChainFramebuffers;
		VkCommandPool m_CommandPool;

		std::vector<VkCommandBuffer> m_CommandBuffers;
		std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		std::vector<VkSemaphore> m_RenderFinishedSemaphores;
		std::vector<VkFence> m_InFlightFences;
		std::vector<VkFence> m_ImagesInFlight;
		size_t currentFrame = 0;
		bool m_FramebufferResized = false;
		void Run();
		void drawFrame();
		void cleanup();
	private:
#pragma region initVulkan
		void initVulkan();
		void createInstance();
		void setupDebugMessenger();
		void createSurface();
		void pickPhysicalDevice();
		void createLogicalDevice();			
		void createSwapChain();
		void recreateSwapChain();
		void cleanupSwapChain();
		void createImageViews();
#pragma region  pipeline
		void createRenderPass();
		void createGraphicsPipeline();

		VkShaderModule createShaderModule(const std::vector<char>& code);
#pragma endregion
		void createFramebuffers();
		void createCommandPool();
		void createCommandBuffers();
		void createSyncObjects();
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		//void cleanup();
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
#pragma endregion

		
	private:
		GLFWwindow* m_Window;

		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;
		const int MAX_FRAMES_IN_FLIGHT = 2;
		const std::vector<const char* > validationLayers = {
		"VK_LAYER_KHRONOS_validation"
		};
		//debug
#ifdef NDEBUG
		const bool enableValidacionLayers = false;
#else
		const bool enableValidationLayers = true;
#endif // NDEBUG
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData) {

			if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
				// Message is important enough to show
				if (messageType >= VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
					// Message is important enough to show
				}
			}

			std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

			return VK_FALSE;
		}
		static std::vector<char> readFile(const std::string& filename) {
			std::ifstream file("D:/"+filename, std::ios::ate | std::ios::binary);

			if (!file.is_open()) {
				throw std::runtime_error("failed to open file!");
			}
			size_t fileSize = (size_t)file.tellg();
			std::vector<char> buffer(fileSize);
			file.seekg(0);
			file.read(buffer.data(), fileSize);
			file.close();

			return buffer;
		}
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
			auto app = reinterpret_cast<VulkanContext*>(glfwGetWindowUserPointer(window));
			app->m_FramebufferResized = true;
		}
		VkDebugUtilsMessengerEXT debugMessenger;
	};
}