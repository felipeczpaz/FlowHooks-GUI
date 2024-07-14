## FlowHooks-GUI

FlowHooks-GUI is a C++/DirectX 9 GUI library inspired by FlowHooks, designed for creating interactive graphical user interfaces for DirectX 9 applications. This repository includes a built-in DirectX 9 environment for testing GUI components.

## Screenshots

![App Screenshot](https://i.imgur.com/dsWpOaM.png)

### Features

- **Multiple Window Support:** Manage multiple windows in the same runtime.
- **Interactive Controls:** Supports windows, checkboxes, tabs, group boxes, dropdowns, and more.
- **Customizable:** Easily customize GUI elements to suit your needs.

### Prerequisites

- Visual Studio 2019 or newer

### Example Usage

To integrate FlowHooks-GUI into your DirectX 9 application, follow these steps:

1. **Initialization and Setup:**

   Initialize FlowHooks-GUI and set up your GUI elements.
	```cpp
	#include "FHGUI.hpp"

	void InitializeFlowHooksGUI()
	{
	    // Create a window
	    FHGUI::Window* mainWindow = new FHGUI::Window("Main Window", 50, 50, 600, 400);
	    FHGUI::Instance::Get().RegisterWindow(mainWindow);

	    // Add controls to the window
	    FHGUI::Tab* tab1 = new FHGUI::Tab("Tab 1");
	    mainWindow->RegisterTab(tab1);

	    FHGUI::GroupBox* groupBox = new FHGUI::GroupBox("Group Box", 10, 10, 200, 150);
	    tab1->RegisterControl(groupBox);

	    bool checkBoxValue = false;
	    FHGUI::CheckBox* checkBox = new FHGUI::CheckBox("Check Box", &checkBoxValue, "Enable/Disable something.");
	    groupBox->RegisterControl(checkBox);

	    // Add more controls as needed...
	}
	```

2. **Updating and Rendering:**

   In your main application loop, ensure to call `Update()` and `Render()` methods of `FHGUI::Instance::Get()` to update and display GUI elements alongside your DirectX 9 rendering.
	```cpp
	int main()
	{
	    // Initialize DirectX 9 and other application setup
	    InitializeDirectX9();

	    // Initialize FlowHooks-GUI
	    InitializeFlowHooksGUI();

	    // Main application loop
	    while (true)
	    {
	        // Handle user input, game logic, etc.
	        
	        // Update GUI state
	        FHGUI::Instance::Get().Update();

	        // Render GUI
	        FHGUI::Instance::Get().Render();

	        // Render DirectX 9 scene
	        RenderDirectX9Scene();

	        // Present the DirectX 9 scene
	        PresentDirectX9Scene();
	    }

	    return 0;
	}

	```

### Getting Started

Clone the repository from [FlowHooks-GUI](https://github.com/felipeczpaz/FlowHooks-GUI/) and follow the setup instructions to integrate FlowHooks-GUI into your DirectX 9 project. For detailed usage examples and API documentation, refer to the repository's README and code comments.

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### Acknowledgments

- FlowHooks for inspiration and initial concept.

### Contributing

Contributions are welcome! Fork the repository and submit pull requests with your enhancements.

### Authors

- Flow - Inspiration

### Feedback and Support

For feedback, bug reports, or support, please open an issue on the [GitHub repository](https://github.com/felipeczpaz/FlowHooks-GUI/issues).
