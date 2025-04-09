// 后台线程类声明 / Background log writer thread (declaration)

#pragma once

#include <atomic>
#include <filesystem>
#include <fstream>
#include <memory>
#include <thread>

#include "logger/log_config.h"
#include "logger/log_formatter.h"
#include "logger/log_queue.h"

namespace logger {

namespace fs = std::filesystem;

/**
 * @brief 日志工作线程类，负责从队列中读取日志并写入文件。
 *        Log worker thread, consumes log messages and writes to file.
 * log_worker 是封装了线程的类，它在你的日志系统中是日志写入的最小执行单位
 */
class log_worker {
  public:
    /**
     * @brief 构造函数，初始化配置和输出文件。
     *        Constructor: accepts configuration and sets up output.
     */
    explicit log_worker(const log_config &config);

    /**
     * @brief 启动后台线程。
     *        Start the background logging thread.
     */
    void start();

    /**
     * @brief 请求安全停止线程（写入剩余日志并退出）。
     *        Request thread shutdown (flush remaining logs and exit).
     */
    void stop();

    /**
     * @brief 将日志消息加入队列。
     *        Push a log message to the queue.
     */
    bool push(log_message &&msg);

  private:
    void run(); // 后台线程主函数 / Main thread loop

    log_config config_;                // 日志配置 / Logger configuration
    std::ofstream log_file_;           // 文件输出流 / Log file stream
    std::unique_ptr<log_queue> queue_; // 日志队列 / Log message queue
    std::thread worker_thread_;        // 后台线程 / Background thread
    std::atomic<bool> running_{false}; // 运行标志 / Running flag
};

} // namespace logger