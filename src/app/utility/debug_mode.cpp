#include "app/utility/debug_mode.hpp"

void DebugInfo::setDebugMode(DebugMode newMode) {
    mode = newMode;
}

bool DebugInfo::canPrintDebugInfo() const{
    return mode == DebugMode::AllDebugInfo || mode == DebugMode::OnlyLogging;
}

bool DebugInfo::canRenderOnScreenInfo() const{
    return mode == DebugMode::AllDebugInfo || mode == DebugMode::OnlyOnScreenInfo;
}
