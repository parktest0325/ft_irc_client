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
	// glfw 초기화
	glfwInit(); 

	// window 만들기 (width, height, title, monitor, share)
	GLFWwindow* window = glfwCreateWindow(640, 480, "Inyong", 0, 0);

	// context는 그리기 위한 내용을 담고 있음
	// window가 두개이면 context가 두개일수도 있음
	// 그러면 어떤 context로 그릴지 정해줘야 함
	glfwMakeContextCurrent(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	// 사용자가 window 창을 닫을 때까지
	while (!glfwWindowShouldClose(window)) {
		// window 그려주기
		render(window);

		// 마우스 움직이는 것. 이런것들 들고와서 필요한 window한테 보내주기
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
	// 지우는 색깔 (어떤 색으로 칠할건지)
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}