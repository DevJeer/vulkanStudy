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
		//��ʼ������
		initWindow();
		//��ʼ��vulkan
		initVulkan();
		//��ѭ��
		mainLoop();
		//�ͷ��ڴ�
		cleanup();
	}
	#pragma endregion
private:
	//GLFW����
	GLFWwindow* window;
	//VULKANʵ��
	VkInstance instance;

	//��ʼ������
	void initWindow() 
	{
		glfwInit();
		//��ʽ����ֹGLFW�Զ�����Opengl������
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		//��ֹ�����Զ��仯
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "MyApplication---Vulkan_Init", nullptr, nullptr);
	}

	void initVulkan() 
	{
		createInstance();
	}

	//��ѭ��DO SOMETHINGS
	void mainLoop()
	{
		while (!glfwWindowShouldClose(window)) 
		{
			glfwPollEvents();
		}
	}

	void cleanup() 
	{
		//ɾ��ʵ��
		vkDestroyInstance(instance, nullptr);
		//ɾ����ǰ��GLFW����
		glfwDestroyWindow(window);

		glfwTerminate();
	}
	//����VULKANʵ��
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


		//��ȡȫ����չ  �����ڿ���ĳ������
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::cout << *glfwExtensions << std::endl;

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		#pragma region print available extensions

		std::cout << "now available extensions : \n";

		uint32_t extensionsCount = 0;
		//���Ȼ�ȡ��չ�� extensionCount
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
		//���ش�����Ϣ
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}