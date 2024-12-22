# Demonstration of Stack and Implementation of LRU Algorithm in OpenGL

Welcome to the **Demonstration of Stack and Implementation of LRU Algorithm**! This project visualizes the Least Recently Used (LRU) caching algorithm using OpenGL, demonstrating how stacks can be utilized in managing cache efficiently.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Stack Push and Pop operations**: See how the push and pop operations of stack work.
- **LRU Algorithm Visualization**: See how the LRU algorithm works in real-time.
- **OpenGL Graphics**: Experience a graphical representation of caching mechanisms.
- **Interactive User Input**: Enter page requests to see how the cache responds.

## Installation

To run this project locally, follow these steps:

1. **Clone the repository**:
	```bash
	git clone https://github.com/RoystonDAlmeida/stack-and-lru-opengl.git
	cd stack-and-lru-opengl
	```

2. **Install Required Libraries**:
Make sure you have OpenGL and GLUT installed on your system. For Ubuntu, you can install them using:
	```bash
	sudo apt-get install freeglut3-dev
	sudo apt-get install libglew-dev
	```

3. **Compile the Code**:
Use the following command to compile the project:
	```bash
	g++ main.cpp -o lru_visualization -lGL -lGLU -lglut
	```

## Usage

1. **Run the Application**:
After compiling, run the application with:
	```bash
	./lru_visualization
	```
2. **Stack and LRU Page Replacement Algorithm options**:
After executing the program, three options are available on the CLI.

3. **STACK(PUSH AND POP)**:
The CLI prompts to enter an element, and a window is displayed sideways to simulate inserting of elements in LIFO order.

- If a top element is to be removed from the stack, press `q` or `Q` on the window simulating the stack.

4. **LRU Page Replacement Algorithm**:
Follow the on screen instructions, and click on `New simulation`. The elements hardcoded in the program are simulated in an LRU algorithm.

- Click on `Help` to view user instructions.

5. **Visualize Caching**:
Watch as the program visualizes how pages are loaded into cache and how the LRU algorithm manages them.

## How It Works

1. **Stack Implementation**: The stack data structure is used to manage page requests efficiently.
2. **LRU Algorithm Logic**: The Least Recently Used (LRU) algorithm removes the least recently accessed items from the cache when it reaches its capacity.
3. **OpenGL Rendering**: The visualization is rendered using OpenGL, providing real-time feedback on cache operations.

### Example Operations

- **Adding Pages**: When you add pages to the cache, they are displayed visually.
- **Cache Replacement**: If a new page is requested and the cache is full, the least recently used page is removed.

## Contributing

We welcome contributions! To contribute to this project, please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Make your changes and commit them (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.

Please ensure that your code adheres to our coding standards and includes appropriate tests.

## License

This project is licensed under the MIT License - see the [LICENSE](https://opensource.org/licenses/MIT) file for details.

---

Thank you for checking out our LRU Algorithm Visualization Project! We hope you find it useful and engaging. If you have any questions or feedback, feel free to reach out!
