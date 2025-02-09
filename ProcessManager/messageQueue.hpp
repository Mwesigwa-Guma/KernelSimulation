#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>

/**
 * @brief A class to manage the message queue for IPC.
 */
class MessageQueue {
public:
    /**
     * @brief Send a message to the queue.
     *
     * @param message The message to send.
     */
    void send(const std::string& message) {
        std::unique_lock<std::mutex> lock(mtx);
        queue.push(message);
        cv.notify_one();
    }

    /**
     * @brief Receive a message from the queue.
     *
     * @return std::string The received message.
     */
    std::string receive() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !queue.empty(); });
        std::string message = queue.front();
        queue.pop();
        return message;
    }

private:
    std::queue<std::string> queue; // The message queue
    std::mutex mtx;                // Mutex for thread safety
    std::condition_variable cv;    // Condition variable for synchronization
};

#endif // MESSAGE_QUEUE_H
