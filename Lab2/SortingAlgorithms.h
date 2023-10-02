#pragma once
#include <vector>
#include <random>
#include <algorithm>

template<typename T>
class SortingAlgorithms {

public:

    static void bubble_sort(std::vector<T>& main_array) {

        const auto N{ static_cast<int>(main_array.size()) };
        bool swapped{};

        for (int i{ 0 }; i < N - 1; i++) {
            swapped = false;
            for (int j{ 0 }; j < N - i - 1; j++) {
                if (main_array[j] > main_array[j + 1]) {
                    std::swap(main_array[j], main_array[j + 1]);
                    swapped = true;
                }
            }

            if (!swapped)
                break;
        }
    }

    static void insert_sort(std::vector<T>& main_array) {

        const auto N{ static_cast<int>(main_array.size()) };

        for (int i{ 1 }; i < N; i++) {
            const auto KEY{ main_array[i] };
            int j{ i - 1 };

            while (j >= 0 && KEY < main_array[j]) {
                main_array[j + 1] = main_array[j];
                --j;
            }

            main_array[j + 1] = KEY;
        }
    }

    static void select_sort(std::vector<T>& main_array) {

        const auto N{ static_cast<int>(main_array.size()) };

        for (int i = 0; i < N; i++) {
            int index_minimum{ i };

            for (int j = i + 1; j < N; j++) {
                if (main_array[j] < main_array[index_minimum])
                    index_minimum = j;
            }

            std::swap(main_array[i], main_array[index_minimum]);
        }
    }

    static void shell_sort(std::vector<T>& main_array) {

        const auto N{ static_cast<int>(main_array.size()) };
        int interval{ N / 2 };

        while (interval > 0) {

            for (int i{ interval }; i < N; i++) {
                auto temp{ main_array[i] };
                int j = i;

                while (j >= interval && main_array[j - interval] > temp) {
                    main_array[j] = main_array[j - interval];
                    j -= interval;
                }

                main_array[j] = temp;
            }
            interval /= 2;
        }
    }

    static void heap_sort(std::vector<T>& main_array) {

        const auto N{ static_cast<int>(main_array.size()) };

        for (int i{ N / 2 - 1 }; i >= 0; i--) {
            heapify(main_array, N, i);
        }

        for (int i{ N - 1 }; i >= 0; i--) {
            std::swap(main_array[0], main_array[i]);
            heapify(main_array, i, 0);
        }
    }

    static void quick_sort(std::vector<T>& main_array) {
        quick_sort_aux(main_array, 0, static_cast<int>(main_array.size()) - 1);
    }

    static void merge_sort(std::vector<T>& main_array) {

        const auto N{ static_cast<int>(main_array.size()) };

        if (N < 2)
            return;

        std::vector<T> left_array(main_array.begin(), main_array.begin() + N / 2);
        std::vector<T> right_array(main_array.begin() + N / 2, main_array.end());

        merge_sort(left_array);
        merge_sort(right_array);

        const auto SIZE_LEFT_ARRAY{ static_cast<int>(left_array.size()) };
        const auto SIZE_RIGHT_ARRAY{ static_cast<int>(right_array.size()) };

        int i{ 0 };
        int j{ 0 };
        int k{ 0 };

        while (i < SIZE_LEFT_ARRAY && j < SIZE_RIGHT_ARRAY) {
            if (left_array[i] <= right_array[j]) {
                main_array[k] = left_array[i];
                i++;
            }
            else {
                main_array[k] = right_array[j];
                j++;
            }
            k++;
        }

        while (i < SIZE_LEFT_ARRAY) {
            main_array[k] = left_array[i];
            i++;
            k++;
        }

        while (j < SIZE_RIGHT_ARRAY) {
            main_array[k] = right_array[j];
            j++;
            k++;
        }
    }

private:

    static void quick_sort_aux(std::vector<T>& main_array, const int begin, const int end) {

        if (begin > end)
            return;

        const auto PIVOT_INDEX{ quick_sort_partition(main_array, begin, end) };

        quick_sort_aux(main_array, begin, PIVOT_INDEX - 1);
        quick_sort_aux(main_array, PIVOT_INDEX + 1, end);
    }

    static int quick_sort_partition(std::vector<T>& main_array, const int begin, const int end) {
      
        const auto PIVOT_VALUE{ main_array[end] };
        int i{ begin - 1 };

        for (int j{ begin }; j < end; j++) {
            if (main_array[j] <= PIVOT_VALUE) {
                i++;
                std::swap(main_array[i], main_array[j]);
            }
        }
        std::swap(main_array[i + 1], main_array[end]);
        return i + 1;
    }

    static void heapify(std::vector<T>& main_array, const int heap_size, const int i) {

        int largest_index = i; 
        int left_index = 2 * i + 1; 
        int right_index = 2 * i + 2; 

        if (left_index < heap_size && main_array[left_index] > main_array[largest_index]) {
            largest_index = left_index;
        }

        if (right_index < heap_size && main_array[right_index] > main_array[largest_index]) {
            largest_index = right_index;
        }

        if (largest_index != i) {
            std::swap(main_array[i], main_array[largest_index]);
            heapify(main_array, heap_size, largest_index);
        }
    }

	SortingAlgorithms() = default;
};