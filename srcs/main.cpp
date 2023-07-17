#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"
#include "imgui.h"

#include <iostream>
#include <GLFW/glfw3.h>

void render(GLFWwindow* window);

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
	glfwInit(); 

	// window ����� (width, height, title, monitor, share)
	GLFWwindow* window = glfwCreateWindow(640, 480, "Inyong", 0, 0);

	// context�� �׸��� ���� ������ ��� ����
	// window�� �ΰ��̸� context�� �ΰ��ϼ��� ����
	// �׷��� � context�� �׸��� ������� ��
	glfwMakeContextCurrent(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	// ����ڰ� window â�� ���� ������
	while (!glfwWindowShouldClose(window)) {
		// window �׷��ֱ�
		render(window);

		// ���콺 �����̴� ��. �̷��͵� ���ͼ� �ʿ��� window���� �����ֱ�
		glfwPollEvents();
		start_cycle();

		ImGui::Begin("My name is window, ImGUI window");
		ImGui::Text("Hello there adventurer!");
		ImGui::End();
		ImGui::Render();

		end_cycle(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

}

void render(GLFWwindow* window)
{ 
	// ����� ���� (� ������ ĥ�Ұ���)
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}