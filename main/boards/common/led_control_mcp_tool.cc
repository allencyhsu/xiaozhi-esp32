#include "led_control_mcp_tool.h"
#include <esp_log.h>

#define TAG "LedControlMcpTool"

LedControlMcpTool::LedControlMcpTool(gpio_num_t red_pin, gpio_num_t green_pin, gpio_num_t blue_pin)
    : red_pin_(red_pin), green_pin_(green_pin), blue_pin_(blue_pin) {
    
    // Initialize GPIOs
    gpio_reset_pin(red_pin_);
    gpio_set_direction(red_pin_, GPIO_MODE_OUTPUT);
    gpio_set_level(red_pin_, 0); // Ensure off initially

    gpio_reset_pin(green_pin_);
    gpio_set_direction(green_pin_, GPIO_MODE_OUTPUT);
    gpio_set_level(green_pin_, 0); // Ensure off initially

    gpio_reset_pin(blue_pin_);
    gpio_set_direction(blue_pin_, GPIO_MODE_OUTPUT);
    gpio_set_level(blue_pin_, 0); // Ensure off initially

    color_to_gpio_["red"] = red_pin_;
    color_to_gpio_["green"] = green_pin_;
    color_to_gpio_["blue"] = blue_pin_;
}

ReturnValue LedControlMcpTool::SetLedState(const PropertyList& properties) {
    std::string color = properties["color"].value<std::string>();
    bool state = properties["state"].value<bool>();

    auto it = color_to_gpio_.find(color);
    if (it == color_to_gpio_.end()) {
        ESP_LOGE(TAG, "Invalid LED color: %s", color.c_str());
        throw std::runtime_error("Invalid LED color");
    }

    gpio_num_t gpio_pin = it->second;
    gpio_set_level(gpio_pin, state ? 1 : 0);
    ESP_LOGI(TAG, "Set LED %s (GPIO %d) to %s", color.c_str(), gpio_pin, state ? "ON" : "OFF");

    return true;
}

void LedControlMcpTool::RegisterTools(McpServer& mcp_server) {
    mcp_server.AddTool(
        "self.led.set_color",
        "Control the state (on/off) of a specific color LED. Available colors are 'red', 'green', 'blue'.",
        PropertyList({
            Property("color", kPropertyTypeString),
            Property("state", kPropertyTypeBoolean)
        }),
        [this](const PropertyList& properties) -> ReturnValue {
            return SetLedState(properties);
        }
    );
}
