// 日志等级定义（枚举） / Log level enum definition
#pragma once

namespace logger {
    enum class log_level {
        debug = 0,
        info,
        warn,
        error,
        fatal
    };

// 将日志等级转换为字符串
const char* to_string(log_level level);

}   // namespace logger