#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// 前向声明
class task;

class dispatcher {
  public:
    // 构造函数：初始化监听端口（默认8888）
    explicit dispatcher(int listen_port = 8888);

    // 析构函数：释放资源
    ~dispatcher();

    // 注册任务类型（通过任务名和工厂函数）
    void register_task_type(
        const std::string &task_type,
        std::function<std::unique_ptr<task>(const std::string &)> creator);

    // 提交任务（将任务放入到调度队列）
    void submit_task(const std::string &task_type, const std::string &param);

    // 启动调度器：监听端口、接收worker、分发任务
    void run();

  private:
    // 监听套接字
    // 用来建立新的worker连接（只用于 accept()）
    int listen_fd_;

    // 已连接的 worker 套接字集合
    // 用来存储已经连接的worker
    std::vector<int> worker_fds_;

    // 等待调度的任务队列
    std::vector<std::unique_ptr<task>> task_queue_;

    // 注册表：任务类型 -> 构造任务的工厂函数
    std::unordered_map<
        std::string, std::function<std::unique_ptr<task>(const std::string &)>>
        task_registry_;

  private:
    // 内部函数：监听端口并接收 worker 连接
    void accept_worker();

    // 内部函数：将任务分发给 worker
    void dispatch_tasks();
};