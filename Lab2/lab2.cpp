//Еремин Даниил Андреевич РИ-221055

#include <iostream>
#include <ctime>


using namespace std;


int main(){
    setlocale(LC_ALL, "");

    //1.
    int size1 = 10;
    int m1[size1]; //В данном случае если не инициализировать массив значениями,
                   //то получим случайные данные находящиеся в памяти которая выделилась под массив
    for (int i = 0; i < size1; i++)
    {
        cout << m1[i] << " ";
    }
    cout << "\n";

    //2.
    srand(time(0));
    int size2 = 10;
    int m2[size2];

    for (int i = 0; i < size2; i++)
    {
        m2[i] = rand()% 21 - 10;
        cout << m2[i] << " ";
    }
    cout << "\n";

    //3.
    int size3 = 5;
    short m3[size3];
    wcout << L"Введите элементы массива:" << endl;
    for (int i = 0; i < size3; i++)
    {
        wcout << L"Введите " << i+1 << L" элемент: ";
        cin >> m3[i];
    }

    //4.

    for (int i = 0; i < size2; i++)
    {
        if (m2[i] % 2 == 0)
        {
            m2[i] *= 3;
        }
        else
        {
            m2[i] *= 5;
        }
        cout << m2[i] << " ";
    }
    cout << "\n";

    //2.1 Двумерные массивы
    int row = 5;
    int col = 5;
    int arr1[row][col];

    wcout << L"Исходный двумерный массив:\n";
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            arr1[i][j]= rand()% 21 - 10;
            cout << arr1[i][j] << "\t";
        }
        cout << "\n";
    }

    //2.2 Сумма строк

    for (int i = 0; i < row; i++)
    {
        int sumRow = 0;
        for (int j = 0; j < col; j++)
        {
            sumRow += arr1[i][j];
        }
        wcout << L"Сумма " << i+1 << L" строки: " << sumRow << "\n";
    }

    //2.3 Замена
    wcout << L"В двумерном массиве отрицательные заменены на 0" << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (arr1[i][j] < 0)
            {
                arr1[i][j] = 0;
            }
            cout << arr1[i][j] << "\t";
        }
        cout << "\n";
    }
}
