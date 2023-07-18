#include <iostream>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"
#include "imgui.h"

#include <GLFW/glfw3.h>

#include "ClientGui.h"

static void glfw_error_callback(int error, const char* description);

void start_cycle()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}


void end_cycle(GLFWwindow* const window)
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);
}

int main()
{
	// glfw �ʱ�ȭ
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		return 1;
	}


	// window ����� (width, height, title, monitor, share)
	GLFWwindow* window = glfwCreateWindow(
		ClientGui::MainWindowSize.x,
		ClientGui::MainWindowSize.y,
		"ImIRC", 0, 0);

	// context�� �׸��� ���� ������ ��� ����
	// window�� �ΰ��̸� context�� �ΰ��ϼ��� ����
	// �׷��� � context�� �׸��� ������� ��
	glfwMakeContextCurrent(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	ClientGui client;

	// ����ڰ� window â�� ���� ������
	while (!glfwWindowShouldClose(window)) {
		// ���콺 �����̴� ��. �̷��͵� ���ͼ� �ʿ��� window���� �����ֱ�
		glfwPollEvents();
		start_cycle();

		render(client);

		ImGui::Render();

		end_cycle(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
