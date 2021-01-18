// Сombination without repetitions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <limits>
#include <locale.h>
#include <math.h.>
#include <fstream>
#include <random>
#include <iomanip> 
#include <string> 
#include <cassert>
#include <sstream>
using namespace std;

//Выводит двухмерный массив в консоль
void printToConsole(int** on_print, int a, int b)
{
    for (int i = 0; i < a; i++)
    {
        cout << i+1 << ":   ";
        for (int j = 0; j < b; j++)
            cout << on_print[i][j] << " ";
        cout << endl;
    }
}
//Выводит двухмерный массив в файл
void printToFile(int** on_print, int a, int b)
{
    ofstream fout;
    fout.open("C:/Users/IvanA/OneDrive/Desktop/Сombinatorial problems/file.txt");
    for (int i = 0; i < a; i++)
    {
        fout << i + 1 << ":   ";
        for (int j = 0; j < b; j++)
            fout << on_print[i][j] << " ";
        fout << endl;
    }
    fout.close();
}

//Находит максимальный элемент в массиве
int max(int n, int* array)
{
    int max = array[0];
    for (int i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}
//Находит значение n!
int factorial(int n)
{
    int result = 1;
    for (int i = n; i > 1; i--)
        result = result * i;
    return result;
}

//Находит количество перестановок n элементов без повторений 
int numberOfPermutationWithoutRepetitions(int n)
{
    return factorial(n);
}
//Находит количество сочетаний из n по k без повторений
int numberOfCombinationsWithoutRepetitions(int n, int k)
{  
    int** B = new int* [n + 1];
    for (int i = 0; i < n + 1; i++)
        B[i] = new int[n + 1];
    for (int i = 0; i <= n; ++i) 
    {
        B[i][0] = 1;        
        B[i][i] = 1;
        for (int j = 1; j < i; ++j)
        {   
            B[i][j] = B[i - 1][j - 1] + B[i - 1][j];
        }
    }
    return B[n][k];
}
//Находит количество размещений из n по k без повторений
int numberOfPlacementWithoutRepetitions(int n, int k)
{
    int buff = 1;
    for (int i = n; i > n - k; i--)
        buff = buff * i;
    return buff;
}
//Находит количество перестановок n элементов с повторениями (m - число различных элементов, repetitions[i] - сколько раз встречается элемент (i+1))
int numberOfPermutationWithRepetitions(int n, int m, int* repetitions)
{
    int maximum = max(m, repetitions);
    int result = 1;
    for (int i = n; i > maximum; i--)
        result = result * i;
    bool skip = true;
    for (int i = 0; i < m; i++)
        if (skip)
            if (repetitions[i] != maximum)
                result = result / factorial(repetitions[i]);
            else
                skip = false;
        else
            result = result / factorial(repetitions[i]);
    return result;
}
//Находит количество сочетаний из n по k с повторениями
int numberOfCombinationWithRepetitions(int n, int k)
{
    return numberOfCombinationsWithoutRepetitions(n + k - 1, k);
}
//Находит количество размещений из n по k с повторениями
long long numberOfPlacementWithRepetitions(int n, int k)
{
    return pow(n, k);
}

//Генерирует массив всех перестановок без повторений
int** permutationWithoutRepetitions(int n)
{
    if (n < 1)
        return NULL;
    int number_of_permutations = factorial(n);
    int** result = new int* [number_of_permutations];
    for (int i = 0; i < number_of_permutations; i++)
        result[i] = new int[n];
    
    int counter = 1;
    int i, x, k, buff;
    int* p = new int[n];
    int* c = new int[n];
    bool* pr = new bool[n];
    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;
        c[i] = 0;
        pr[i] = true;
    }
    c[n - 1] = -1;

    //counter++;
    for (i = 0; i < n; i++)
        result[counter - 1][i] = p[i];
    i = 0;

    while (i < n - 1)
    {

        i = 0;
        x = 0;

        while (c[i] == n - 1 - i)
        {
            pr[i] = !pr[i];
            c[i] = 0;
            if (pr[i])
                x++;
            i++;
        }
        if (i < n - 1)
        {
            if (pr[i])
                k = c[i] + x;
            else
                k = n - 2 - i - c[i] + x;

            buff = p[k];
            p[k] = p[k + 1];
            p[k + 1] = buff;

            counter++;
            for (int j = 0; j < n; j++)
                result[counter - 1][j] = p[j];
            c[i]++;
        }
    }
    return result;
}
//Генерирует массив всех сочетаний без повторений
int** combinationWithoutRepetitions(int n, int k)
{
    if ((n < k) || (k < 1) || (n < 1))
        return NULL;
    int number_of_combinations = numberOfCombinationsWithoutRepetitions(n, k);
    int* array = new int[k];
    int** result = new int* [number_of_combinations];
    for (int i = 0; i < number_of_combinations; i++)
        result[i] = new int[k];
    int counter = 1;
    for (int i = 0; i < k; i++)
    {
        array[i] = i + 1;
        result[counter - 1][i] = array[i];
    }


    while (true)
    {
        bool exit = true;
        for (int i = k - 1; i > -1; i--)
            if (array[i] < (n - k + i + 1))
            {
                exit = false;
                array[i] ++;
                for (i++; i < k; i++)
                    array[i] = array[i - 1] + 1;
                break;
            }
        if (exit)
            break;
        else
        {
            counter++;
            for (int i = 0; i < k; i++)
                result[counter - 1][i] = array[i];
        }
    }
    return result;
}
//Генерирует массив всех размещений без повторений
int** placementWithoutRepetitions(int n, int k)
{
    //Проверяем корректность исходных данных. В случае их некорректности, возвращаем NULL.
    if ((n < k) || (k < 1) || (n < 1))
        return NULL;

    //Вычисляем количество перестановок без повторений
    int number_of_permutations = factorial(k);
    //Вычисляем количество сочетаний без повторений
    int number_of_combinations = numberOfCombinationsWithoutRepetitions(n, k);
    //Вычисляем количество размещений без повторений
    int number_of_placement = numberOfPlacementWithoutRepetitions(n, k);

    //Создаем двухмерный массив, в который будет записан результат работы функции
    int** result = new int* [number_of_placement];
    for (int i = 0; i < number_of_placement; i++)
        result[i] = new int[k];

    //Генерируем массив перестановок 
    int** permutation = permutationWithoutRepetitions(k);
    //Генерируем массив сочетаний
    int** combination = combinationWithoutRepetitions(n, k);

    int counter = 0; //Счетчик размещений

    //Получаем массив размещений, используя полученные выше массивы перестановок и сочетаний
    for (int i = 0; i < number_of_combinations; i++)//Для каждого сочетания
        for (int j = 0; j < number_of_permutations; j++)//Для каждой перестановки
        {
                for (int z = 0; z < k; z++)//Для каждого элемента в перестановке
                    //Записываем в массив result элемент, соответствующий элементу в выбранном сочетании, с индексом, соответствующим выбранному элементу в выбранной перестановке (например, для выбранного сочетания {2,4,5}, выбранной перестановки {2,1,3} будет получено следующее размещение: {4,2,5})
                    result[counter][z] = combination[i][permutation[j][z]-1];
                counter++;//Считаем количество уже полученных размещений
        }
    //Возвращаем полученный результат
    return result;
}
//Генерирует массив всех перестановок с повторениями
int** permutationWithRepetitions(int n, int k, int* repetitions)
{
    //Проверяем корректность исходных данных. В случае их некорректности, возвращаем NULL.
    int sum = 0;
    for (int i = 0; i < k; i++)
        sum = sum + repetitions[i];

    if ((k < 1) || (n < 1) || (sum != n))
        return NULL;
    //Вычисляем количество перестановок с повторениями
    int number_of_premutations = numberOfPermutationWithRepetitions(n, k, repetitions);
    //Создаем двухмерный массив, в который будет записан результат работы функции
    int** result = new int* [number_of_premutations];
    for (int i = 0; i < number_of_premutations; i++)
        result[i] = new int[n];
    //Инициализируем массив NULLами
    for (int i = 0; i < number_of_premutations; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = NULL;

    //Создаем массив stepsLimit, в который записываем количество сочетаний без повторений, соответствующих каждому конкретному уникальному элементу в перестановке
    int* stepsLimit = new int[k];
    int lim = n;
    for (int i = 0; i < k; i++)
    {
        stepsLimit[i] = numberOfCombinationsWithoutRepetitions(lim, repetitions[i]);
        lim = lim - repetitions[i];
    }

    //Создаем массив, в котором будут храниться сочетания без повторений соответствующих каждому конкретному уникальному элементу в перестановке
    int*** combinations = new int** [k];
    for (int i = 0; i < k; i++) 
    {
        combinations[i] = new int* [stepsLimit[i]]; //выделяем память на столбцы
        for (int j = 0; j < stepsLimit[i]; j++) 
            combinations[i][j] = new int[repetitions[i]]; //выделяем память на строки.
    }

    //Заполняем массив сочетаниями без повторений 
    lim = n;
    for (int z = 0; z < k; z++)
    {
        int** combination = combinationWithoutRepetitions(lim, repetitions[z]);
        for (int y = 0; y < stepsLimit[z]; y++)
            for (int x = 0; x < repetitions[z]; x++)
                combinations[z][y][x] = combination[y][x];
        lim = lim - repetitions[z];
    }

    //Создаем массив, который отвечает за выбор комбинации 
    int** steps = new int* [number_of_premutations];
    for (int i = 0; i < number_of_premutations; i++)
        steps[i] = new int[k];

    //Инициализируем его данными

    //Создаем буферный массив
    int* array = new int[k];
    for (int i = 0; i < k; i++)
    {
        array[i] = 0;
        steps[0][i] = 0;
    }

    for (int i = 1; i < number_of_premutations; i++)
    {
        int j = 1;
        while (array[k - j] + 1 == stepsLimit[k-j])
        {
            array[k - j] = 0;
            j++;
        }
        array[k - j]++;

        for (int z = 0; z < k; z++)
            steps[i][z] = array[z];
    }

    //По массиву с сочетаниями без повторений и массиву их комбинаций создаем массив-результат
    for (int counter = 0; counter < number_of_premutations; counter++)
    {
        bool* skip = new bool[n];
        for (int i = 0; i < n; i++)
            skip[i] = false;
        for (int z = 0; z < k; z++)
        {
            for (int x = 0; x < repetitions[z]; x++)
            {
                int shift = 0;
                int realShift = 0;
                
                while (shift <= combinations[z][steps[counter][z]][x] - 1)
                {
                    if (!skip[realShift])
                        shift++; 
                    realShift++;
                }
                result[counter][realShift-1] = z + 1;   
            }
            for (int i = 0; i < n; i++)
            {
                if (result[counter][i] != NULL)

                    skip[i] = true;
            }  
        }
    }
    
    return result;
}
//Генерирует массив всех сочетаний с повторениями
int** combinationWithRepetitions(int n, int k)
{
    //Проверяем корректность исходных данных. В случае их некорректности, возвращаем NULL.
    if ((k < 1) || (n < 1))
        return NULL;
    //Вычисляем количество сочетаний без повторений
    int number_of_combinations = numberOfCombinationWithRepetitions(n, k);
    //Создаем двухмерный массив, в который будет записан результат работы функции
    int** result = new int* [number_of_combinations];
    for (int i = 0; i < number_of_combinations; i++)
        result[i] = new int[k];

    int* repetitions = new int[2];
    repetitions[0] = n-1;
    repetitions[1] = k;
    int** premutations = permutationWithRepetitions(n - 1 + k, 2, repetitions);

    //printToConsole(premutations, numberOfPermutationWithRepetitions(n - 1 + k, 2, repetitions), n - 1 + k);

    for (int i = 0; i < number_of_combinations; i++)
    {
        int value = 1;
        int amount = 0;
        int index = 0;
        for (int j = 0; j < n + k + 1; j++) {
            if ((premutations[i][j] - 1) != 0)
                amount++;
            else
            {
                if (amount == 0)
                    value++;
                else
                {
                    for (int c = 0; c < amount; c++)
                    {
                        result[i][index] = value;
                        index++;
                    }
                    value++;
                    amount = 0;
                }
            }
        }
        if (amount != 0)
            for (int c = 0; c < amount; c++)
            {
                result[i][index] = value;
                index++;
            }
    }

    return result;
}
//Генерирует массив всех размещений с повторениями
int** placementWithRepetitions(int n, int k) 
{
    //Проверяем корректность исходных данных. В случае их некорректности, возвращаем NULL.
    if ((k < 1) || (n < 1))
        return NULL;
    //Вычисляем количество размещений без повторений
    long long number_of_placement = numberOfPlacementWithRepetitions(n, k);
    //Создаем двухмерный массив, в который будет записан результат работы функции
    int** result = new int* [number_of_placement];
    for (int i = 0; i < number_of_placement; i++)
        result[i] = new int[k];

    //Создаем буферный массив
    int* array = new int [k];
    for (int i = 0; i < k; i++)
    {
        array[i] = 0;
        result[0][i] = 0;
    }
  
    for (int i = 1; i < number_of_placement; i++)
    {
       int j = 1;
       while (array[k - j] + 1 == n)
       {
           array[k - j] = 0;
           j++;
       }
       array[k - j]++;

       for (int z = 0; z < k; z++)
           result[i][z] = array[z];
    }
    return result;
}

//Проверяет, есть ли в двумерном  массиве повторяющиеся строки (под строкой подразумеваются все элементы массива с одинаковым первым индексом). Данная функция оптимальна для проверки уникальности перестановок и размещений.
bool repetitionСheck(int** sample, int a, int b)
{
    for (int i1 = 0; i1 < a; i1++)//Для каждой строки в массиве
        for (int i2 = i1 + 1; i2 < a; i2++)//Для каждой строки массиве, которая ниже первой выбранной строки
        {
            bool strings_are_equal = true;//По умолчанию строки совпадают
            for (int j = 0; j < b; j++)//Для каждой пары элементов из этих двух строк с одинаковыми индексами
                if (sample[i1][j] != sample[i2][j])//Если хотя бы одна пара элементов из пары выбранных строк не совпадает 
                    strings_are_equal = false;//Значит выбранные строки не совпадают
            if (strings_are_equal)//Если хотя бы одна пара строк совпала, значит в массиве есть повторения
                return true; //Возвращаем истину
        }
    //Если ни одна пара строк не совпала, значит в массиве нет повторений. Возвращаем ложь.
    return false;
}
//Проверяет, есть ли в двумерном  массиве строки, состоящие из одинаковых элементов (порядок не важен). Данная функция оптимальна для проверки уникальности сочетаний.
bool repetitionСheckForCombinationsWithoutRepetitions(int** sample, int a, int b)
{
    //Создаем массив характеристических строк, который будем использовать для эффективного сравнения
    int* setInt = new int [a];
    for (int i = 0; i < a; i++)
        setInt[i] = 0; //Инициализируем его нулями

    //Для каждого сочетания формируем характеристическую строку бит
    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++)
            setInt[i] = setInt[i] + pow(2, sample[i][j]-1);

    //Попарно сравниваем полученные характеристические строки
    for (int i1 = 0; i1 < a; i1++)
        for (int i2 = i1 + 1; i2 < a; i2++)
            if (setInt[i1] == setInt[i2])//Если хлтя бы одна характеристическая строка повторяется, значит в массиве есть повторения
                return true;//Возвращаем истину
    //Если ни одно сочетание не совпало, значит в массиве нет повторений. Возвращаем ложь.
    return false;
}

int main()
{
    char* locale = setlocale(LC_ALL, "");
    
    while (true)
    {
        cout << "Выберите режим работы:\n1)Вывести перестановки без повторений\n2)Вывести сочетания без повторений\n3)Вывести размещения без повторений\n4)Вывести перестановки c повторениями\n5)Вывести сочетания с повторениями\n6)Вывести размещения с повторениями\n7)Закончить работу\nВаш выбор: ";
        int choice;
        cin >> choice;

        if ((choice < 1)||(choice > 6))
            return 0;

        int out;
        while (true)
        {
            cout << "\nВывести результат:\n1)В консоль\n2)В файл\nВаш выбор: ";
            cin >> out;
            if ((out != 1) && (out != 2))
            {
                cout << "Ошибка: введите допустимое значение\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
                break;
        }

        int n = NULL;
        while (true)
        {
            cout << "n=";
            cin >> n;
            if (n == NULL)
            {
                cout << "Ошибка: введите допустимое значение\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
                break;
        }
        int k = NULL;
        if (choice != 1)
        {
            while (true)
            {
                cout << "k=";
                cin >> k;
                if (k == NULL)
                {
                    cout << "Ошибка: введите допустимое значение\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                    break;
            }
        }
        int** result;
        bool success = false;
        int* repetitions = new int[k];

        switch(choice)
        {
        case 1:
            result = permutationWithoutRepetitions(n);
            if (result == NULL)
            {
                cout << "\nОшибка: введены некорректные данные\n\n";
                break;
            }
            if (out == 2)
                printToFile(result, factorial(n), n);
            else
                printToConsole(result, factorial(n), n);
            success = !repetitionСheck(result, factorial(n), n);
            break; 
        case 2:
            result = combinationWithoutRepetitions(n, k);
            if (result == NULL)
            {
                cout << "\nОшибка: введены некорректные данные\n\n";
                break;
            }
            if (out == 2)
                printToFile(result, numberOfCombinationsWithoutRepetitions(n, k), k);
            else
                printToConsole(result, numberOfCombinationsWithoutRepetitions(n, k), k);
            success = !repetitionСheckForCombinationsWithoutRepetitions(result, numberOfCombinationsWithoutRepetitions(n, k), k);
            break;
        case 3:
            result = placementWithoutRepetitions(n, k);
            if (result == NULL)
            {
                cout << "\nОшибка: введены некорректные данные\n\n";
                break;
            }
            if (out == 2)
                printToFile(result, numberOfPlacementWithoutRepetitions(n, k), k);
            else
                printToConsole(result, numberOfPlacementWithoutRepetitions(n, k), k);
            success = !repetitionСheck(result, numberOfPlacementWithoutRepetitions(n, k), k);
            break;
        case 4:
            //int* repetitions = new int[k];
            for (int i = 0; i < k; i++)
                repetitions[i] = NULL;
            while (true)
            {
                for (int i = 0; i < k; i++)
                {
                    while (true)
                    {
                        cout << "repetitions[" << i << "] = ";
                        cin >> repetitions[i];
                        if (repetitions[i] == NULL)
                        {
                            cout << "Ошибка: введите допустимое значение\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        else
                            break;
                    }
                }
                int sum = 0;
                for (int i = 0; i < k; i++)
                    sum = sum + repetitions[i];
                if (sum == n)
                    break;
                else
                {
                    cout << "Ошибка: введите допустимые значения\n";
                    for (int i = 0; i < k; i++)
                        repetitions[i] = NULL;
                }
            }

            result = permutationWithRepetitions(n, k, repetitions);
            if (result == NULL)
            {
                cout << "\nОшибка: введены некорректные данные\n\n";
                break;
            }
            if (out == 2)
                printToFile(result, numberOfPermutationWithRepetitions(n, k, repetitions), n);
            else
                printToConsole(result, numberOfPermutationWithRepetitions(n, k, repetitions), n);
            success = !repetitionСheck(result, numberOfPermutationWithRepetitions(n, k, repetitions), n);
            break;
        case 5:
            result = combinationWithRepetitions(n, k);
            if (result == NULL)
            {
                cout << "\nОшибка: введены некорректные данные\n\n";
                break;
            }
            if (out == 2)
                printToFile(result, numberOfCombinationWithRepetitions(n, k), k);
            else
                printToConsole(result, numberOfCombinationWithRepetitions(n, k), k);
            success = !repetitionСheck(result, numberOfCombinationWithRepetitions(n, k), k);
            break;
        case 6:
            result = placementWithRepetitions(n, k);
            if (result == NULL)
            {
                cout << "\nОшибка: введены некорректные данные\n\n";
                break;
            }
            if (out == 2)
                printToFile(result, numberOfPlacementWithRepetitions(n, k), k);
            else
                printToConsole(result, numberOfPlacementWithRepetitions(n, k), k);
            success = !repetitionСheck(result, numberOfPlacementWithRepetitions(n, k), k);
            break;
        }
        if (success) 
            cout << "\nПовторений не обнаружено, тестирование прошло успешно.\n\n";
        else
            cout << "\nОшибка: обнаружено повторение.\n\n";
    }
}
