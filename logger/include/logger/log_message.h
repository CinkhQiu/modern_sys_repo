// 日志消息结构体 / Structure for individual log messages
#pragma once

#include <chrono>
#include <string.h>
#include <thread>

#include "logger/log_level.h"

namespace logger {
/**
 *  @brief 日志消息结构体，表示一条待格式化或待写入的日志。
 *         Log message structure, representing a single log entry.
 **/

struct log_message {
    std::chrono::system_clock::time_point timestamp; // 时间戳 / Timestamp
    std::thread::id thread_id;                       // 线程ID / Thread ID
    log_level level;                                 // 日志等级 / log level
    std::string message; // 日志内容 / Message body

    /**
     * @brief 构造函数，创建一条日志记录
     *        Constructor to create a log message
     *
     * @param level 日志等级 / Log level
     * @param message 日志内容 / Log body
     **/
    log_message(log_level level, const std::string &message);
};

} // namespace logger