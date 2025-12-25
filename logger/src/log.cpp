#include "../include/log.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/pattern_formatter.h>
#include <unistd.h>
#include <cstdio>
#include <mutex>

LogLevel Log::minLevel = LogLevel::LOG_TRACE;
bool Log::initialized = false;

// Custom flag for PID with magenta color
class pid_flag : public spdlog::custom_flag_formatter
{
public:
    void format(const spdlog::details::log_msg &, const std::tm &, spdlog::memory_buf_t &dest) override
    {
        auto pid = std::to_string(getpid());
        dest.append(pid.data(), pid.data() + pid.size());
    }

    std::unique_ptr<custom_flag_formatter> clone() const override
    {
        return spdlog::details::make_unique<pid_flag>();
    }
};

static std::shared_ptr<spdlog::logger> createLogger(const std::string& name)
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto logger = std::make_shared<spdlog::logger>(name, console_sink);
    
    auto formatter = std::make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<pid_flag>('*');
    
    // Spring Boot style format with colored log levels:
    // 2024-12-25 19:30:45.123  INFO 12345 --- [     main] c.e.Application      : Message
    formatter->set_pattern(
        "\033[2m%Y-%m-%d %H:%M:%S.%e\033[0m "  // datetime (faint)
        "%^%5l%$ "                               // level (colored by spdlog)
        "\033[35m%*\033[0m "                    // PID (magenta)
        "\033[2m---\033[0m "                    // separator (faint)
        "\033[2m[%10t]\033[0m "                 // thread (faint, 10 chars)
        "\033[36m%-20n\033[0m "                 // logger name (cyan, 20 chars)
        "\033[2m:\033[0m "                      // colon (faint)
        "%v"                                     // message
    );
    
    logger->set_formatter(std::move(formatter));
    return logger;
}

void Log::init()
{
    if (initialized) return;
    
    // Drop any existing loggers first
    spdlog::drop_all();
    
    auto console = createLogger("launcher");
    console->set_level(spdlog::level::trace);
    spdlog::set_default_logger(console);
    
    initialized = true;
}

void Log::setMinLevel(LogLevel level)
{
    minLevel = level;
    
    if (!initialized) init();
    
    spdlog::level::level_enum spdLevel;
    switch (level)
    {
        case LogLevel::LOG_TRACE: spdLevel = spdlog::level::trace; break;
        case LogLevel::LOG_DEBUG: spdLevel = spdlog::level::debug; break;
        case LogLevel::LOG_INFO:  spdLevel = spdlog::level::info; break;
        case LogLevel::LOG_WARN:  spdLevel = spdlog::level::warn; break;
        case LogLevel::LOG_ERROR: spdLevel = spdlog::level::err; break;
        default: spdLevel = spdlog::level::info; break;
    }
    spdlog::set_level(spdLevel);
    
    // Update all registered loggers
    spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) {
        l->set_level(spdLevel);
    });
}

void Log::vlog(LogLevel level, const char* tag, const char* text, va_list args)
{
    if (level < minLevel) return;
    if (!initialized) init();
    
    char buffer[4096];
    int len = vsnprintf(buffer, sizeof(buffer), text, args);
    if (len > (int)sizeof(buffer)) len = sizeof(buffer);
    while (len > 0 && (buffer[len - 1] == '\r' || buffer[len - 1] == '\n'))
        buffer[--len] = '\0';
    
    // Get or create logger for this tag
    auto logger = spdlog::get(tag);
    if (!logger)
    {
        logger = createLogger(tag);
        logger->set_level(spdlog::default_logger()->level());
        try {
            spdlog::register_logger(logger);
        } catch (const spdlog::spdlog_ex&) {
            // Logger already registered, get it again
            logger = spdlog::get(tag);
        }
    }
    
    switch (level)
    {
        case LogLevel::LOG_TRACE: logger->trace("{}", buffer); break;
        case LogLevel::LOG_DEBUG: logger->debug("{}", buffer); break;
        case LogLevel::LOG_INFO:  logger->info("{}", buffer); break;
        case LogLevel::LOG_WARN:  logger->warn("{}", buffer); break;
        case LogLevel::LOG_ERROR: logger->error("{}", buffer); break;
    }
}