#include <stdio.h>

void sub_quicksort( int *list, int first, int last );
int partition( int *list, int first, int last );

void quicksort( int *list, int size )
{
    sub_quicksort( list, 0, size - 1 );
}

void sub_quicksort( int *list, int first, int last )
{
    if( last <= first ) return;

    int placed = partition( list, first, last );
    sub_quicksort( list, first, placed - 1 );
    sub_quicksort( list, placed + 1, last );
}

void swap( int *a, int *b )
{
    int c = *a;
    *a = *b;
    *b = c;
}

int partition( int *list, int first, int last )
{
    int pivot = list[last];
    int i = first;

    for( int j = first; j < last; j++ )
    {
        if( list[j] < pivot )
        {
            swap( &list[j], &list[i] );
            i++;
        }
    }
    swap( &list[i], &list[last] );

    return i;
}

int main( int argc, char *argv[] )
{
    int list[] = { 5, 4, 7, 8, 1, 9, 2, 6, 3, 0 };
    int size = sizeof( list ) / sizeof( list[0] );

    quicksort( list, size );
    for( int i = 0; i < size; i++ )
    {
        if( list[i] != i )
        {
            printf( "FAILURE\n" );
            return -1;
        }
    }
    printf( "SUCCESS\n" );

    return 0;
}
