#include <iostream>
#include <vector>
#include <algorithm>
#include <future>    // для асинхронных задач
#include <clocale>   // для поддержки русского языка

// Функция для поиска минимального элемента в подвекторе [start, end)
std::promise<size_t> findMinIndexAsync(const std::vector<int>& vec, size_t start, size_t end)
{
    std::promise<size_t> promise;

    // Ищем минимальный элемент в заданном диапазоне
    size_t minIndex = start;
    for (size_t i = start + 1; i < end; ++i)
    {
        if (vec[i] < vec[minIndex])
        {
            minIndex = i;
        }
    }

    promise.set_value(minIndex); // Устанавливаем результат в promise
    return promise;
}

// Функция сортировки выбором с асинхронным поиском минимального элемента
void selectionSortAsync(std::vector<int>& vec)
{
    for (size_t i = 0; i < vec.size() - 1; ++i)
    {
        // Запускаем асинхронную задачу для поиска минимального элемента
        auto promise = findMinIndexAsync(vec, i, vec.size());
        auto future = promise.get_future();

        // Получаем результат из future (ожидание происходит здесь)
        size_t minIndex = future.get();

        // Меняем местами текущий элемент с минимальным найденным
        if (minIndex != i)
        {
            std::swap(vec[i], vec[minIndex]);
        }
    }
}

int main()
{
    // Устанавливаем локаль для поддержки русского языка
    setlocale(LC_ALL, "Russian");

    std::vector<int> numbers;
    int n, num;

    std::cout << "Введите количество элементов: ";
    std::cin >> n;

    std::cout << "Введите " << n << " чисел:\n";
    for (int i = 0; i < n; ++i)
    {
        std::cin >> num;
        numbers.push_back(num);
    }

    std::cout << "\nИсходный массив:\n";
    for (const auto& num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Сортируем массив с использованием асинхронного поиска
    selectionSortAsync(numbers);

    std::cout << "\nОтсортированный массив (сортировка выбором):\n";
    for (const auto& num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}
