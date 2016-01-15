#include <stdio.h>

void split_merge( int *list, int *temp, int start, int end );
void merge( int *list, int *temp, int start, int middle, int end );

void merge_sort( int *list, int size )
{
    int temp[size];
    split_merge( list, temp, 0, size );
}

void split_merge( int *list, int *temp, int start, int end )
{
    if( end - start < 2 ) return;

    int middle = start + ((end - start) / 2);

    split_merge( list, temp, start, middle );
    split_merge( list, temp, middle, end );
    merge( list, temp, start, middle, end );
    for( int i = start; i < end; i++ ) list[i] = temp[i];
}

void merge( int *list, int *temp, int start, int middle, int end )
{
    int i = start, j = middle;
    for( int k = start; k < end; k++ )
    {
        if( i < middle && (j >= end || list[i] < list[j] ) )
        {
            temp[k] = list[i];
            i++;
        }
        else
        {
            temp[k] = list[j];
            j++;
        }
    }
}

int main( int argc, char *argv[] )
{
    int list[] = { 5, 4, 7, 8, 1, 9, 2, 6, 3, 0 };
    int size = sizeof( list ) / sizeof( list[0] );
    merge_sort( list, size );
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
