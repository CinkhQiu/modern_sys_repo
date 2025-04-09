// 日志配置（路径、等级、异步等）/ Logger config definitions
#pragma once

#include "logger/log_level.h";
#include <filesystem>

namespace logger {

namespace fs = std::filesystem;

/**
 * @brief 日志配置结构体，控制日志器初始化时的参数
 *        Logger configuration structure used during initialization
 * log_config 是日志系统的配置项，用于初始化整个 logger（包括路径、等级、是否异步等）
 */
struct log_config {
    fs::path log_file_path; // 日志文件路径 / Log file path
    log_level level;        // 日志等级 / Log level
    bool async_mode;        // 是否异步 / Async logging enabled
    size_t queue_capacity;  // 队列容量 / Queue size
    bool console_output;    // 是否输出到控制台 / Also log to console

    log_config(const fs::path &log_file_path = "log/log.txt",
               log_level level = log_level::info, bool async_mode = true,
               size_t queue_capacity = 1024, bool console_output = true);
};

} // namespace logger