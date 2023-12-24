#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    int num, i=0;
    wcout << L"Введите число: ";
    cin >> num;
    //Выводим числа до введенного значения
    if(num < 15)
    {
        for (int i=0; i<=num; i++)
        {
            cout << i << endl;
        }
    }
    //Выводим числа, но нечетные заменяем символом b
    else if(num >= 15 && num < 45)
    {
        while (i<num)
        {
            if (i%2 == 0) {
                cout<<i<<endl;
            }
            else{
                cout<<"b"<<endl;
            }
            i++;
        }
    }
    //Вариант когда число num слишком большое(num >= 1000)
    //то выводим сообщение каждую тысячу итераций
    else
    {
        for (int i=1; i<=num; i++)
        {
            if(i%1000==0)
            {
                wcout<< L"Прошла " <<i/1000<< L" итераций"<< endl;
            }
        }
    }
}
