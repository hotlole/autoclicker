#include <Windows.h>
#include <iostream>
#include <thread>

const int numThreads = 4; // Используем 4 потока

void Click(int count) {
    for (int i = 0; i < count; ++i) {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        // Добавляем небольшую задержку между кликами (можете настроить по своему усмотрению)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    int clickCount = 1000;
    int xCoord = 400;
    int yCoord = 400;

    Sleep(5000);

    // Используем std::async для асинхронного выполнения
    std::vector<std::future<void>> futures;
    for (int i = 0; i < numThreads; ++i) {
        futures.emplace_back(std::async(std::launch::async, Click, clickCount));
    }

    // Выполняем клики в основном потоке
    for (int i = 0; i <= clickCount; ++i) {
        SetCursorPos(xCoord, yCoord);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }

    // Дожидаемся завершения всех потоков
    for (auto& future : futures) {
        future.wait();
    }

    return 0;
}