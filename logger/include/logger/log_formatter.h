// 日志格式化模块 / Message formatter interface
#pragma once

#include "logger/log_message.h"
#include <string>

namespace logger {

/**
 * @brief 日志格式化工具类（只提供静态方法）
 *        Utility class for formatting log messages.
 */
class log_formatter {
  public:
    /**
     * @brief 将日志消息格式化为字符串
     *        Format a log_message into a human-readable string.
     *
     * @param msg 一条日志消息 / A single log message
     * @return 格式化后的字符串 / Formatted string for output
     */
    static std::string format(const log_message &msg);

    // 未来：支持模板格式、JSON 格式、颜色输出等
};

} // namespace logger