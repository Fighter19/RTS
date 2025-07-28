#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <imgui_freetype.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wdumpdoc.h"

static void DebugLog(const char *format, ...) {
	char buffer[1024];
	buffer[0] = 0;
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	va_end(args);
	printf("%s\n", buffer);
}
#define DEBUG_LOG(x) DebugLog x

static void OnFileOpened(void *userdata, const char *const *filelist, int filter) {
	if (filelist == nullptr || filelist[0] == nullptr) {
		DEBUG_LOG(("OnFileOpened: Failed to open file dialog: %s", SDL_GetError()));
		return;
	}

	DEBUG_LOG(("OnFileOpened: %s, filter: %d", filelist, filter));

	std::vector<WDumpDoc> &openedDocs = *static_cast<std::vector<WDumpDoc> *>(userdata);
	openedDocs.emplace_back(filelist[0]); // Create a new WDumpDoc instance with the opened file
										   // Handle file opened event here
}

int main(int argc, char *argv[]) {
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
		DEBUG_LOG(("Error: SDL_Init(): %s\n", SDL_GetError()));
		return EXIT_FAILURE;
	}

	// Create window with SDL_Renderer graphics context
	float mainScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
	SDL_WindowFlags windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
	SDL_Window *window = SDL_CreateWindow("WDump", (int)(1280 * mainScale), (int)(720 * mainScale), windowFlags);
	if (window == nullptr) {
		DEBUG_LOG(("Error: SDL_CreateWindow(): %s\n", SDL_GetError()));
		return EXIT_FAILURE;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
	SDL_SetRenderVSync(renderer, 1);
	if (renderer == nullptr) {
		DEBUG_LOG(("Error: SDL_CreateRenderer(): %s\n", SDL_GetError()));
		return EXIT_FAILURE;
	}
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_ShowWindow(window);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;			  // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;			  // Enable Gamepad Controls
	io.Fonts->FontBuilderIO = ImGuiFreeType::GetBuilderForFreeType(); // Use FreeType font loader

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// ImGui::StyleColorsLight();

	// Setup scaling
	ImGuiStyle &style = ImGui::GetStyle();
	style.ScaleAllSizes(mainScale); // Bake a fixed style scale. (until we have a solution for dynamic style scaling,
									 // changing this requires resetting Style + calling this again)

	// Setup Platform/Renderer backends
	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Opened docs
	std::vector<WDumpDoc> openedDocs;

	// File filters
	const static SDL_DialogFileFilter filters[] = {{"Westwood 3D Models", "w3d;W3D"}, {"Any file", "*"}};

	// Main loop
	bool done = false;
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT)
				done = true;
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
				done = true;
			// Check for hotkey events
			if (event.type == SDL_EVENT_KEY_DOWN) {
				if (event.key.key == SDLK_Q && (event.key.mod & SDL_KMOD_CTRL)) {
					done = true; // Ctrl+Q to quit
				} else if (event.key.key == SDLK_O && (event.key.mod & SDL_KMOD_CTRL)) {
					SDL_ShowOpenFileDialog(OnFileOpened, &openedDocs, window, filters, 2, nullptr,
										   false); // Ctrl+O to open file dialog
				}
			}
		}

		// [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your SDL_AppIterate() function]
		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
			SDL_Delay(10);
			continue;
		}

		// Start the Dear ImGui frame
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Open", "Ctrl+O")) {
					SDL_ShowOpenFileDialog(OnFileOpened, &openedDocs, window, filters, 2, nullptr, false);
				}
				if (ImGui::MenuItem("Quit", "Ctrl+Q")) {
					done = true;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		// Render opened documents
		for (auto &doc : openedDocs) {
			ImGui::Begin(doc.GetFilename().c_str());
			if (doc.Render()) {
				// Render the document content
				// Add more rendering logic here as needed
			} else {
				ImGui::Text("Failed to render document: %s", doc.GetFilename().c_str());
			}
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		SDL_RenderClear(renderer);
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
		SDL_RenderPresent(renderer);
	}

	// Cleanup
	// [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your SDL_AppQuit() function]
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
} // end main