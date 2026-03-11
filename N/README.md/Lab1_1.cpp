#include <iostream>
#include <vector>
#include <chrono>
#include <boost/thread.hpp>

// Рекурсивная функция для вычисления числа Фибоначчи.
long long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Функция, которую будет выполнять каждый поток.
void thread_task(int thread_id, int m) {
    // volatile, чтобы компилятор не оптимизировал вычисление
    volatile long long result = fibonacci(m);
}

int main() {
    // Параметры задачи
    const int M = 40;               // Какое число Фибоначчи вычисляем
    const int num_threads_list[] = {2, 4, 8}; // Количества потоков для тестирования


    // --- Последовательное выполнение для разного количества задач ---
    std::cout << "\n--- Последовательное выполнение ---\n";
    
    long long seq_times[3]; // массив для хранения времен последовательного выполнения
    
    for (int idx = 0; idx < 3; ++idx) {
        int num_tasks = num_threads_list[idx];
        
        auto start_seq = std::chrono::high_resolution_clock::now();
        
        // Выполняем num_tasks вычислений последовательно
        for (int i = 0; i < num_tasks; ++i) {
            fibonacci(M);
        }
        
        auto end_seq = std::chrono::high_resolution_clock::now();
        auto duration_seq = std::chrono::duration_cast<std::chrono::milliseconds>(end_seq - start_seq);
        
        seq_times[idx] = duration_seq.count();
        std::cout << "  " << num_tasks << " задача(и): " << duration_seq.count() << " мс\n";
    }

    // --- Многопоточное выполнение с Boost.Thread ---
    std::cout << "\n--- Многопоточное выполнение (Boost.Thread) ---\n";

    for (int idx = 0; idx < 3; ++idx) {
        int num_threads = num_threads_list[idx];
        std::cout << "\nТест с " << num_threads << " поток(ами):\n";

        std::vector<boost::thread> threads;

        // Засекаем время
        auto start_mt = std::chrono::high_resolution_clock::now();

        // Создаем и запускаем потоки
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(thread_task, i, M);
        }

        // Ожидаем завершения
        for (auto& t : threads) {
            t.join();
        }

        auto end_mt = std::chrono::high_resolution_clock::now();
        auto duration_mt = std::chrono::duration_cast<std::chrono::milliseconds>(end_mt - start_mt);

        std::cout << "  Время выполнения: " << duration_mt.count() << " мс\n";
    }

    return 0;
}