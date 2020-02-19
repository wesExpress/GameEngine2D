#include "Logging.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine
{
    std::shared_ptr<spdlog::logger> Log::m_engineLogger;
    std::shared_ptr<spdlog::logger> Log::m_clientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        m_engineLogger = spdlog::stdout_color_mt("ENGINE");
        m_engineLogger->set_level(spdlog::level::trace);
        
        m_clientLogger = spdlog::stdout_color_mt("CLIENT");
        m_clientLogger->set_level(spdlog::level::trace);
    }
}