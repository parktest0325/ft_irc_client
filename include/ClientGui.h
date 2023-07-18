#pragma once
#include <string>
#include <imgui.h>

class ClientGui
{
public:
	constexpr static ImGuiWindowFlags MainWindowFlags =
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
	constexpr static ImVec2 MainWindowSize = ImVec2(1280.0F, 720.0F);
	constexpr static ImVec2 MainWindowPos = ImVec2(0.0F, 0.0F);
	constexpr static float MainFontScale = 1.5f;

public:
	void Draw(std::string label);

	void DrawMenu();
	void DrawChat();
	void DrawChatInput();

};

void render(ClientGui& clientGui);
