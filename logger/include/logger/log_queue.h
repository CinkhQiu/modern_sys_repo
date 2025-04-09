// 日志缓冲队列（线程安全）/ Thread-safe log queue
#pragma once

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

#include "logger/log_message.h"

namespace logger {
/**
 * @brief 线程安全的日志队列（生产者-消费者模式）
 *        Thread-safe log message queue (Producer-Consumer model)
 */
class log_queue {
  public:
    /**
     * @brief 构造函数，初始化最大容量
     * Constructor to initialize queue with capacity
     */
    explicit log_queue(size_t capacity);

    /**
     * @brief 推入一条消息（阻塞或丢弃策略）
     * Push a log message into the queue
     *
     * @param msg 日志消息 / Log message
     * @return 是否入队成功（队满可能返回false）/ Whether the push succeeded
     */
    bool push(log_message &&msg);

    /**
     * @brief 弹出一条日志消息（阻塞直到有新消息或关闭）
     *        Pop a message from the queue (blocks if empty).
     *
     * @return 可选的日志消息 / Optional log message
     */
    std::optional<log_message> pop();

    /**
     * @brief 通知队列停止运行（唤醒所有等待线程）
     *        通知后台日志线程：程序即将退出，请停止等待，处理完剩余日志并安全退出。
     *        Signal shutdown to all waiting threads.
     */
    void shutdown();

  private:
    std::queue<log_message> queue_; // 日志缓冲区 / Message buffer
    size_t capacity_;               // 最大容量 / Max queue size

    std::mutex mutex_;           // 互斥锁 / Mutex for thread safety
    std::condition_variable cv_; // 条件变量 / Used for waiting and notifying
    bool stop_flag_ = false;     // 停止标志 / Stop signal for shutdown
};
} // namespace logger
