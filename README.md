
# LLM-Inference-CPP

**Author:** Harsha Vardhan Khurdula

LLMs in your CPP code? Now possible using, C++ with **libcurl** to send HTTP requests to a locally served language model (LLM) via **ollama**. This setup allows you to query a local model efficiently without relying on external services.

## Table of Contents

- [Overview](#overview)
- [Requirements](#requirements)
- [Setup](#setup)
- [Usage](#usage)
  - [Running the Server](#running-the-server)
  - [Making Inference Requests](#making-inference-requests)
- [Code Overview](#code-overview)
- [BibTeX Citation](#bibtex-citation)

## Overview

This repository provides code to wrap **libcurl** in C++ for sending HTTP POST requests to a language model served by **ollama**. You can use this to send prompts and retrieve model responses from any LLM hosted locally.

### File Structure

- **`rest_api.h`**: Header file defining the REST API client.
- **`rest_api.cpp`**: Implementation of the REST API client using libcurl.
- **`main.cpp`**: Main program for sending requests to the model and processing responses.

## Requirements

- **C++11** or later
- **libcurl**: Used for HTTP requests
- **ollama**: Used to serve the model locally

### Installing Dependencies

1. **libcurl**: Install **libcurl** on your machine.
    - **Linux**: `sudo apt-get install libcurl4-openssl-dev`
    - **macOS**: `brew install curl`
    - **Windows**: [Download and install](https://curl.se/windows/)

2. **ollama**: Install **ollama** to serve the model.
    ```bash
    brew install ollama
    ```

## Setup

Clone this repository and navigate to the project directory:

```bash
git clone https://github.com/Khurdhula-Harshavardhan/LLM-Inference-CPP.git
cd LLM-Inference-CPP
```

### Compile the Code

Use the following command to compile the C++ code:

```bash
g++ -std=c++17 main.cpp rest_api.cpp -o llm_inference -lcurl
```

This will create an executable named `llm_inference`.

## Usage

### Running the Server

Start the **ollama** server locally to serve the language model:

```bash
ollama serve
```

### Making Inference Requests

With the **ollama** server running, execute the compiled C++ code to send prompts to the model.

```bash
./llm_inference
```

The program will prompt you to enter:
1. **LLM Identifier**: The model name hosted on `ollama`.
2. **Query**: Your question or prompt for the model.

#### Example Interaction

```plaintext
Enter LLM identifier: llama3.2
$$$ Why is the sky blue?
====================
llama3.2 says: The sky is blue due to Rayleigh scattering.
====================
```

## Code Overview

### `rest_api.h`

Defines the `RestClient` class, which handles REST API requests with methods such as `get` and `post`.

### `rest_api.cpp`

Implements the `RestClient` class using **libcurl**.

- **post**: Constructs and sends a `POST` request with JSON data.
- **get**: (optional) Method to handle `GET` requests.

### `main.cpp`

This is the main program file:
1. Prompts for a model identifier and query.
2. Constructs a JSON payload with these inputs.
3. Uses `RestClient` to send a `POST` request to the **ollama** server.
4. Parses and displays the model’s response.

### Example Code Snippet

An example JSON payload construction in `main.cpp`:

```cpp
std::string jsonData = R"({
    "model": ")" + model + R"(",
    "prompt": ")" + user_query + R"(",
    "stream": false
})";
```

## BibTeX Citation

If you use this code, please cite it as follows:

```bibtex
@misc{Khurdula2024LLMInferenceCPP,
  author = {Harsha Vardhan Khurdula},
  title = {LLM-CPP-Inference: C++ Client for LLM Inference via Ollama},
  year = {2024},
  howpublished = {\url{https://github.com/Khurdhula-Harshavardhan/LLM-Inference-CPP}},
  }
}
```

--- 

This documentation provides the necessary steps to query a local LLM with **ollama** and **libcurl** in C++. For questions or contributions, please open an issue or submit a pull request.
