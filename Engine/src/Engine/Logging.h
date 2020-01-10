#ifndef __LOGGING_H__
#define __LOGGING_H__

#include "spdlog/spdlog.h"

namespace Engine
{
    class Log
    {
        public:
            static void Init();

            inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return m_engineLogger; }
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_clientLogger; }
        private:
            static std::shared_ptr<spdlog::logger> m_engineLogger;
            static std::shared_ptr<spdlog::logger> m_clientLogger;
    };
}

#define ENGINE_TRACE(...) Engine::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define ENGINE_INFO(...) Engine::Log::GetEngineLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...) Engine::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) Engine::Log::GetEngineLogger()->error(__VA_ARGS__)

#define CLIENT_TRACE(...) Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_INFO(...) Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...) Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...) Engine::Log::GetClientLogger()->error(__VA_ARGS__)

#endif