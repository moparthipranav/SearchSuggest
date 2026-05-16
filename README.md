# Trie-Based Search Suggestion System

This project implements a high-performance search suggestion engine using a C++ Trie data structure on the backend and a Flask-based Python web interface.

## Project Structure
- `CustomerQuery.cpp`: The core C++ engine that stores product names in a Trie and provides autocomplete suggestions.
- `app.py`: A Flask web server that acts as a bridge between the browser and the C++ executable.
- `templates/index.html`: A responsive frontend that provides real-time search suggestions as the user types.

## Prerequisites
- **C++ Compiler**: `g++` (MinGW for Windows or standard GCC for Linux/macOS).
- **Python 3.x**: Installed on your system path.
- **Flask**: Install via pip:
  ```bash
  pip install flask
  ```

## How to Run

### 1. Compile the C++ Engine
The Python script expects a compiled binary named `query_engine.exe`. Run the following command in the project directory:
```bash
g++ CustomerQuery.cpp -o query_engine.exe
```

### 2. Start the Flask Server
Run the Python application:
```bash
python app.py
```

### 3. Access the Interface
Open your web browser and navigate to `http://127.0.0.1:5000`.

## How It Works
1. **Data Loading**: The C++ engine loads a predefined database of products into a **Trie (Prefix Tree)**.
2. **Real-time Querying**: As the user types (at least 2 characters), the frontend sends a GET request to the Flask server.
3. **Inter-process Communication**: Flask spawns the C++ process, passes the query via standard input, and captures the suggestions from standard output.
4. **Prefix Matching**: The Trie structure allows for $O(L)$ search time complexity, where $L$ is the length of the query string, making it extremely efficient for large datasets.

## Performance Considerations
- Currently, the C++ process is spawned on every request. For production environments, consider using a persistent process with a socket connection or compiling the C++ logic as a Python extension module (e.g., using Pybind11).

## Author
Pranav