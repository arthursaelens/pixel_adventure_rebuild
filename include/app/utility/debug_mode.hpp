#ifndef DEBUG_MODE_HPP
#define DEBUG_MODE_HPP


enum class DebugMode {
    AllDebugInfo,
    OnlyLogging,
    OnlyOnScreenInfo,
    NoDebugInfo
};

class DebugInfo {
public:
    DebugInfo(DebugMode initialMode = DebugMode::NoDebugInfo) : mode(initialMode) {}

    virtual void setDebugMode(DebugMode newMode);
    bool canPrintDebugInfo() const;
    bool canRenderOnScreenInfo() const;


private:
    DebugMode mode;
};

#endif 
