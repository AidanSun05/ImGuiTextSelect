// Copyright 2024 Aidan Sun
// SPDX-License-Identifier: MIT

#undef GLFW_INCLUDE_NONE

#include <string_view>
#include <vector>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "textselect.hpp"

const std::vector<std::string_view> lines{
    "Line 1",
    "Line 2",
    "Line 3",
    "A longer line",
    "Text selection in Dear ImGui",
    "UTF-8 characters Ë ⑤ 三【 】┌──┐"
};

std::string_view getLineAtIdx(size_t idx) {
    return lines[idx];
}

size_t getNumLines() {
    return lines.size();
}

int main() {
    if (!glfwInit()) return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGuiTextSelect example", nullptr, nullptr);
    if (!window) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    TextSelect textSelect{ getLineAtIdx, getNumLines };

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize({ 300, 200 });
        ImGui::Begin("Text selection");

        ImGui::BeginChild("text", {}, 0, ImGuiWindowFlags_NoMove);

        for (const auto& line : lines) ImGui::TextUnformatted(line.data());

        textSelect.update();

        if (ImGui::BeginPopupContextWindow()) {
            ImGui::BeginDisabled(!textSelect.hasSelection());
            if (ImGui::MenuItem("Copy", "Ctrl+C")) textSelect.copy();
            ImGui::EndDisabled();

            if (ImGui::MenuItem("Select all", "Ctrl+A")) textSelect.selectAll();
            ImGui::EndPopup();
        }

        ImGui::EndChild();
        ImGui::End();

        ImGui::Render();
        int displayX, displayY;
        glfwGetFramebufferSize(window, &displayX, &displayY);
        glViewport(0, 0, displayX, displayY);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
