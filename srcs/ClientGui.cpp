#include "ClientGui.h"
#include "IrcClient.h"
#include <iostream>

void ClientGui::Draw(std::string label)
{
	ImGui::SetNextWindowSize(MainWindowSize);
	ImGui::SetNextWindowPos(MainWindowPos);
	

	ImGui::Begin(label.data(), nullptr, MainWindowFlags);

	DrawMenu();
	ImGui::Separator();
	DrawChat();
	ImGui::Separator();
	DrawChatInput();

	ImGui::End();
}

void ClientGui::DrawMenu()
{
	const ImVec2 wrapperSize = ImVec2(ImGui::GetContentRegionAvail().x, 50.0f);
	ImGui::BeginChild("###DrawMenu", wrapperSize);

	const float originalFontSize = ImGui::GetFontSize();
	ImGui::SetWindowFontScale(MainFontScale);
	
	ImGui::Text("Address: ");
	ImGui::SameLine();

	static char ipBuffer[16] = { 0, };
	constexpr static float ipWidth = 7 * sizeof(ipBuffer) * MainFontScale + 10.0f;
	ImGui::PushItemWidth(ipWidth);
	ImGui::InputText("###ipaddr", ipBuffer, sizeof(ipBuffer));
	ImGui::PopItemWidth();
	ImGui::SameLine();

	static char portBuffer[6] = { 0, };
	constexpr static float portWidth = 7 * sizeof(portBuffer) * MainFontScale + 10.0f;
	ImGui::PushItemWidth(portWidth);
	ImGui::InputText("###port", portBuffer, sizeof(portBuffer));
	ImGui::PopItemWidth();
	ImGui::SameLine();

	if (ImGui::Button("Connect"))
	{
		IrcClient::GetInstance().Connect(ipBuffer, portBuffer);
	}
	ImGui::SameLine();

	if (ImGui::Button("Disconnect"))
	{
		IrcClient::GetInstance().Disconnect();
	}

	ImGui::SameLine();

	if (ImGui::Button("ClearChat"))
	{
		IrcClient::GetInstance().MsgsCleanup();
	}

	ImGui::SetWindowFontScale(originalFontSize);

	ImGui::EndChild();
}

void ClientGui::DrawChat()
{
	const ImVec2 wrapperSize = ImVec2(ImGui::GetContentRegionAvail().x, 500.0f);

	ImGui::BeginChild("###DrawChat", wrapperSize, true);

	const float originalFontSize = ImGui::GetFontSize();
	ImGui::SetWindowFontScale(MainFontScale);

	std::vector<std::string> msgs = IrcClient::GetInstance().GetMsgs();

	for (std::string msg : msgs)
		ImGui::Text(msg.data());

	if (!msgs.empty()) ImGui::SetScrollHereY(1.0f);

	ImGui::SetWindowFontScale(originalFontSize);

	ImGui::EndChild();
}

void ClientGui::DrawChatInput()
{
	static bool isFocused = false;
	const bool isPressed_shift
		= ImGui::GetIO().KeyShift;
	const bool isPressed_enter
		= ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter));

	ImGui::BeginChild("###DrawChatInput");
	const float originalFontSize = ImGui::GetFontSize();
	ImGui::SetWindowFontScale(MainFontScale);

	static char textBuffer[256] = { 0, };
	ImGui::InputText("###sendText", textBuffer, sizeof(textBuffer) - 1);
	if (isFocused)
	{
		ImGui::SetKeyboardFocusHere(-1);
		isFocused = false;
	}
	ImGui::SameLine();

	if (ImGui::Button("Send")
		|| (isPressed_shift && isPressed_enter))
	{
		IrcClient::GetInstance().SendMsg(textBuffer);
		std::memset(textBuffer, 0, sizeof(textBuffer));
		isFocused = true;
	}
	ImGui::SameLine();

	if (ImGui::Button("Send With \\n")
		|| (!isPressed_shift && isPressed_enter))
	{
		IrcClient::GetInstance().SendMsgWithNl(textBuffer);
		std::memset(textBuffer, 0, sizeof(textBuffer));
		isFocused = true;
	}

	ImGui::SetWindowFontScale(originalFontSize);
	ImGui::EndChild();
}

void render(ClientGui& clientGui)
{
	clientGui.Draw("irc client");
}

