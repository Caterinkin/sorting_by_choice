#include <iostream>
#include <vector>
#include <algorithm>
#include <future>    // ��� ����������� �����
#include <clocale>   // ��� ��������� �������� �����

// ������� ��� ������ ������������ �������� � ���������� [start, end)
std::promise<size_t> findMinIndexAsync(const std::vector<int>& vec, size_t start, size_t end)
{
    std::promise<size_t> promise;

    // ���� ����������� ������� � �������� ���������
    size_t minIndex = start;
    for (size_t i = start + 1; i < end; ++i)
    {
        if (vec[i] < vec[minIndex])
        {
            minIndex = i;
        }
    }

    promise.set_value(minIndex); // ������������� ��������� � promise
    return promise;
}

// ������� ���������� ������� � ����������� ������� ������������ ��������
void selectionSortAsync(std::vector<int>& vec)
{
    for (size_t i = 0; i < vec.size() - 1; ++i)
    {
        // ��������� ����������� ������ ��� ������ ������������ ��������
        auto promise = findMinIndexAsync(vec, i, vec.size());
        auto future = promise.get_future();

        // �������� ��������� �� future (�������� ���������� �����)
        size_t minIndex = future.get();

        // ������ ������� ������� ������� � ����������� ���������
        if (minIndex != i)
        {
            std::swap(vec[i], vec[minIndex]);
        }
    }
}

int main()
{
    // ������������� ������ ��� ��������� �������� �����
    setlocale(LC_ALL, "Russian");

    std::vector<int> numbers;
    int n, num;

    std::cout << "������� ���������� ���������: ";
    std::cin >> n;

    std::cout << "������� " << n << " �����:\n";
    for (int i = 0; i < n; ++i)
    {
        std::cin >> num;
        numbers.push_back(num);
    }

    std::cout << "\n�������� ������:\n";
    for (const auto& num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // ��������� ������ � �������������� ������������ ������
    selectionSortAsync(numbers);

    std::cout << "\n��������������� ������ (���������� �������):\n";
    for (const auto& num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}