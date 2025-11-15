#ifndef LED_CONTROL_MCP_TOOL_H
#define LED_CONTROL_MCP_TOOL_H

#include "mcp_server.h"
#include <driver/gpio.h>
#include <map>

class LedControlMcpTool {
public:
    LedControlMcpTool(gpio_num_t red_pin, gpio_num_t green_pin, gpio_num_t blue_pin);
    void RegisterTools(McpServer& mcp_server);

private:
    gpio_num_t red_pin_;
    gpio_num_t green_pin_;
    gpio_num_t blue_pin_;
    std::map<std::string, gpio_num_t> color_to_gpio_;

    ReturnValue SetLedState(const PropertyList& properties);
};

#endif // LED_CONTROL_MCP_TOOL_H
