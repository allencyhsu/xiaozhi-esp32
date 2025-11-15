# GEMINI.md: AI-Generated Project Context

This document is an AI-generated summary of the `xiaozhi-esp32` project, providing context for development and interaction.

## Project Overview

This project, named "小智 AI 聊天机器人" (Xiaozhi AI Chatbot), is a sophisticated firmware for ESP32-based devices to create a voice-controlled AI assistant. It acts as a voice interface to large language models (LLMs) like Qwen and DeepSeek.

The system is built in C++ on top of the Espressif IoT Development Framework (ESP-IDF). It follows a modern, object-oriented design, with a central `Application` class orchestrating various services.

### Key Technologies & Features

*   **MCU:** Natively supports ESP32-S3, ESP32-C3, and ESP32-P4.
*   **Framework:** Built on ESP-IDF v5.4 or higher.
*   **Language:** C++ (Google C++ code style).
*   **Architecture:**
    *   Event-driven architecture using FreeRTOS event groups.
    *   Core logic is managed by a central `Application` singleton.
    *   Services for audio processing (`AudioService`), network communication (`Protocol`), and OTA updates (`Ota`).
*   **Audio:**
    *   Offline wake-word detection via `ESP-SR`.
    *   Voice Activity Detection (VAD).
    *   OPUS audio codec for efficient streaming.
*   **Connectivity:** Supports Wi-Fi and 4G (via ML307 Cat.1 module).
*   **Communication Protocols:**
    *   Implements both WebSocket and a custom MQTT+UDP protocol for communication with a backend server.
    *   Features a custom **Machine Control Protocol (MCP)** for controlling device peripherals (lights, motors) and extending LLM capabilities (smart home, PC control).
*   **Hardware Support:** The project is highly portable and supports over 70 different open-source hardware boards, with a clear structure for adding new custom boards under `main/boards/`.

## Building and Running

The project uses the ESP-IDF toolchain. The build process is managed by a custom Python script that wraps the standard `idf.py` commands.

### Environment Setup

1.  **Install ESP-IDF:** Follow the official Espressif documentation to install ESP-IDF **version 5.4 or higher**. The `release-v5.5` branch is used in CI.
2.  **Install Dependencies:** The `build.yml` workflow installs `jq`.
3.  **Set up Environment:** Source the ESP-IDF export script:
    ```bash
    source /path/to/esp-idf/export.sh
    ```

### Build Command

The primary build command is executed via the `scripts/release.py` script. This script handles the configuration for different hardware boards.

To see a list of supported boards, you can run:
```bash
python scripts/release.py --list-boards
```

To build the firmware for a specific board (e.g., `esp32-s3-box3`):
```bash
# The script takes the board identifier and a release name
python scripts/release.py esp32-s3-box3 --name my-custom-build
```
The final merged binary will be located at `build/merged-binary.bin`.

### Flashing the Device

After building, use `esptool.py` or the `idf.py flash` command to flash the `build/merged-binary.bin` file to your device. For new users, the project recommends flashing pre-compiled binaries available from the project's website.

## Development Conventions

*   **Code Style:** The project adheres to the **Google C++ Style Guide**.
*   **Directory Structure:**
    *   `main/`: Contains the core application source code.
    *   `main/boards/`: Board-specific configurations and initializations. To add a new board, create a new subdirectory here.
    *   `main/audio/`: Audio processing pipeline, including codecs and wake-word models.
    *   `main/protocols/`: Implementations of WebSocket and MQTT protocols.
    *   `docs/`: Detailed documentation on protocols, custom board creation, and more.
    *   `scripts/`: Helper scripts for building, releasing, and asset generation.
    *   `managed_components/`: ESP-IDF managed dependencies.
*   **Modularity:** The code is well-structured, with clear separation of concerns between the main application logic, hardware-specific code, audio services, and communication protocols.
*   **Configuration:** Project features are configured using `Kconfig`, which is standard for ESP-IDF projects.
