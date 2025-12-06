<div align="center">

<img src="img/logo.png" alt="DAZI-AI Logo" width="200"/>

# 🤖 DAZI-AI

**Serverless AI Smart Doorbell & Voice Assistant | ESP32 Platform | Pure Arduino**

</div>

## 📝 Project Introduction

DAZI-AI is a library designed to build **Serverless AI Voice Assistants** on the ESP32 platform. While it supports various voice applications, i created version for **AI Smart Doorbell**—a fully autonomous, intelligent intercom system that can converse with guests, take messages, and integrate with your smart home via MQTT, all without requiring an external server or complex backend.

## 🌟 Featured: AI Smart Doorbell

The **Smart Doorbell** (`examples/doorbell`) turns an ESP32 into a conversational agent that acts as your home's receptionist.

### Why is this special?

Unlike traditional doorbells that just ring, this AI:

1. **Talks to visitors** using OpenAI's ChatGPT.
2. **Identifies intent** (delivery, guest, security check) based on your custom system prompt.
3. **Does not need hardcoding**: You configure everything via a phone-friendly Web Dashboard.

### ✨ Doorbell Features

* **📱 Web Configuration Dashboard**:
  No need to recompile code to change WiFi password or API Keys. The device hosts its own website for easy setup.

* **🔗 MQTT Integration**:
  Connects seamlessly to Home Assistant, Node-RED, or OpenHAB.
  * **Publishes**: Guest speech text, AI response text, Button press events.
  * **Subscribes**: Remote trigger commands (open door, trigger talk, etc.).

* **🎨 Visual Feedback (RGB LED)**:
  * 🟢 **Green**: AI Speaking / Introducing itself.
  * 🔵 **Blue**: Listening (Guest should speak now).
  * 🔴 **Red**: Error (Check Microphone/WiFi).
  * ⚫ **Off**: Idle / Sleep.

* **🗣️ Intelligent Conversation**:
  * **Intro Mode**: The AI introduces itself when the button is first pressed.
  * **Continuous Loop**: Automatically listens for a reply after speaking, creating a natural conversation flow.

### 🚀 How to Use the Doorbell

1. **Flash the Code**: Upload `examples/doorbell/doorbell.ino` to your ESP32-S3.

2. **First Setup (AP Mode)**:
   * If the device cannot connect to WiFi, it creates a Hotspot:
   * **SSID**: `Escher-Doorbell-Setup`
   * **Password**: `12345678`

3. **Open Dashboard**:
   * Connect to the hotspot and visit `http://192.168.4.1`.
   * Enter your **WiFi credentials**, **OpenAI/ByteDance keys**, and **System Prompt**.
   * Click "Save & Restart".

4. **Operation**:
   * **Press the Button**: The AI starts the intro.
   * **Talk**: Speak when the LED turns **Blue**.
   * **Listen**: The AI responds when the LED turns **Green**.

### 📡 MQTT Topics

| Topic | Direction | Description |
| :--- | :--- | :--- |
| `escher/doorbell/guest` | Publish | Text spoken by the guest |
| `escher/doorbell/ai` | Publish | Text response from the AI |
| `escher/doorbell/button` | Publish | Sends "pressed" when conversation starts |
| `escher/doorbell/in` | Subscribe | Send "trigger" to this topic to remotely start the doorbell |

## 🚀 Key Features (Library)

✅ **Serverless Design**:
* More flexible secondary development
* Higher degree of freedom (customize prompts or models)
* Simpler deployment (no additional server required)

✅ **Complete Voice Interaction**:
* Voice input via INMP441 microphone
* Real-time speech recognition using ByteDance ASR API
* AI processing through OpenAI API
* Voice output via MAX98357A I2S audio amplifier

✅ **Continuous Conversation Mode**:
* Automatic speech recognition with VAD (Voice Activity Detection)
* Seamless ASR → LLM → TTS conversation loop
* Configurable conversation memory to maintain context

## 🔧 System Architecture

The system uses a modular design with the following key components:

* **Voice Input**: INMP441 microphone with I2S interface
* **Speech Recognition**: ByteDance ASR API for real-time transcription
* **AI Processing**: OpenAI ChatGPT API for conversation with memory support
* **Voice Output**: MAX98357A I2S audio amplifier for TTS playback
* **Connectivity**: WiFi for API communication

## 💻 Code Description

### Code Structure
