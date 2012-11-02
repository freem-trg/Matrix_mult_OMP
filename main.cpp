#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <omp.h>
#include <iostream>

using namespace std;

const int rows = 3;
const int cols = 2;

int A[ rows * cols ] = { 0 }; // Матрица A
int B[ rows * cols ] = { 0 }; // Матрица B
int C[ rows * rows ] = { 0 }; // Матрица для резульатата

//Возвращает случайное число по основанию base
int rndNum( int base ){

    return random() % base + 1;
}

//Инициализация матриц случайными числами:
void initialize(){
    srand( time( NULL ) );
    for ( int i = 0; i < rows; i++ ){
        for ( int j = 0; j < cols; j++ ){
            A [ i * cols + j ] = rndNum( 10 );
            B [ j * rows + i ] = rndNum( 10 );
        }
    }

}

//Вывод матриц на экран:
void show(){
    cout << " A: " << endl;

    for ( int i = 0; i < rows; i++ ){
        for ( int j = 0; j < cols; j++ ){
            cout << A [ i * cols + j ] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << " B: " << endl;
    for ( int j = 0; j < cols; j++ ){
        for ( int i = 0; i < rows; i++ ){

            cout << B [ j * rows + i ] << " ";
        }
        cout << endl;
    }
    cout << endl;
}



int main()
{
    //Initialize matrices:
    initialize();
    show();

    //multiply:
    for ( int i = 0; i < rows; i++) {
        for ( int j = 0; j < rows; j++ ){

            int summ = 0;
#pragma omp parallel num_threads(cols)
            {
                int tid = omp_get_thread_num();
                summ += A[ i*cols + tid ] * B[ tid*rows + j ];
            }
            C[ i*rows + j ] = summ;
        }
    }

    //show:
    cout << " C: " << endl;
    for ( int i = 0; i < rows; i++) {
        for ( int j = 0; j < rows; j++ ){
            cout << C[ i*rows + j ] << " ";
        }
        cout << endl;
    }

    return 0;
}

