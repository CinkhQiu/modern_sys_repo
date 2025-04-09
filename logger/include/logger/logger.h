// 日志模块主接口（对外暴露） / Main logger interface
#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "logger/log_config.h"
#include "logger/log_level.h"
#include "logger/log_worker.h"

namespace logger {

/**
 * @brief Logger 顶层接口类（单例）<br>
 *        Logger main interface (Singleton-style).
 */
class logger {
  public:
    /**
     * @brief 初始化日志系统（必须先调用）<br>
     *        Initialize logger system (must be called before use).
     *
     * @param config 日志配置项 / Logging configuration
     */
    static void init(const log_config &config);

    /**
     * @brief 写一条日志消息（自动按等级过滤）<br>
     *        Log a message (filtered by level).
     *
     * @param level   日志等级 / Log level
     * @param message 日志内容 / Log content string
     */
    static void log(log_level level, const std::string &message);

    /**
     * @brief 关闭日志系统（释放线程、flush 文件）<br>
     *        Shutdown logger system (flush + stop worker thread).
     */
    static void shutdown();

  private:
    logger() = default;
    ~logger() = default;

    logger(const logger &) = delete;
    logger &operator=(const logger &) = delete;

    static std::unique_ptr<log_worker>
        worker_; // 后台工作线程实例 / Background log writer
    static log_level
        global_level_; // 当前日志等级（用于过滤）/ Current global log level
    static std::mutex init_mutex_; // 初始化互斥锁 / Protect init/shutdown
};

/**
 * @brief 宏封装，方便使用不同等级的日志（不写等级）<br>
 *        Logging macros for convenience
 */
#define LOG_DEBUG(msg) ::logger::logger::log(::logger::log_level::debug, msg)
#define LOG_INFO(msg) ::logger::logger::log(::logger::log_level::info, msg)
#define LOG_WARN(msg) ::logger::logger::log(::logger::log_level::warn, msg)
#define LOG_ERROR(msg) ::logger::logger::log(::logger::log_level::error, msg)
#define LOG_FATAL(msg) ::logger::logger::log(::logger::log_level::fatal, msg)

} // namespace logger
