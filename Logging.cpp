#include "Logging.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::logger;

void Log::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    logger = spdlog::stdout_color_mt("ENGINE");
}