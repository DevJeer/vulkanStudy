#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>


const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication 
{
public:
	#pragma region RUNNING
	void run() 
	{
		//初始化窗口
		initWindow();
		//初始化vulkan
		initVulkan();
		//主循环
		mainLoop();
		//释放内存
		cleanup();
	}
	#pragma endregion
private:
	//GLFW窗口
	GLFWwindow* window;
	//VULKAN实例
	VkInstance instance;

	//初始化窗口
	void initWindow() 
	{
		glfwInit();
		//显式地阻止GLFW自动创建Opengl上下文
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		//禁止窗口自动变化
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "MyApplication---Vulkan_Init", nullptr, nullptr);
	}

	void initVulkan() 
	{
		createInstance();
	}

	//主循环DO SOMETHINGS
	void mainLoop()
	{
		while (!glfwWindowShouldClose(window)) 
		{
			glfwPollEvents();
		}
	}

	void cleanup() 
	{
		//删除实例
		vkDestroyInstance(instance, nullptr);
		//删除当前的GLFW窗口
		glfwDestroyWindow(window);

		glfwTerminate();
	}
	//创建VULKAN实例
	void createInstance()
	{
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "vulkan draw Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		//VULKAN instanceinfo
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;


		//获取全局扩展  类似于开启某个功能
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::cout << *glfwExtensions << std::endl;

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		#pragma region print available extensions

		std::cout << "now available extensions : \n";

		uint32_t extensionsCount = 0;
		//首先获取扩展数 extensionCount
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);

		std::vector<VkExtensionProperties> extensions(extensionsCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());

		for (const auto& extension : extensions)
		{
			std::cout << "\t" << extension.extensionName << std::endl;
		}

		#pragma endregion

		createInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create instance!");
		}
	}
};

int main() 
{
	HelloTriangleApplication app;

	try {
		app.run();
	}
	catch (const std::exception& e) 
	{
		//返回错误信息
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}