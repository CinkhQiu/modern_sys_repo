// 时间戳、线程ID等工具函数 / Time/thread ID utility functions
#pragma once

#include <chrono>
#include <sstream>
#include <string>
#include <thread>

namespace logger {

/**
 * @brief 工具函数：获取当前时间戳（格式化字符串）
 *        Utility: get current timestamp as formatted string.
 *
 * @return 字符串形式时间戳，例如 "2025-04-09 21:02:30.123"
 *         Timestamp string like "2025-04-09 21:02:30.123"
 */
std::string get_current_timestamp();

/**
 * @brief 工具函数：获取当前线程 ID 的字符串形式
 *        Utility: get current thread ID as string.
 *
 * @return 线程ID字符串，例如 "140391"
 *         Thread ID string like "140391"
 */
std::string get_thread_id_string();

} // namespace logger