#include <stdlib.h>
#include <stdio.h>

struct Chain
{
    int data;
    struct Chain *n;
};

void deallocate( Chain *chain )
{
    if( !chain ) return;

    deallocate( chain->n );
    free( chain );
}

Chain *allocate( int *data, int count )
{
    Chain *chain = NULL, *first = NULL, *prev = NULL;

    if( !count ) return NULL;

    for( int i = 0; i < count; i++ )
    {
        chain = (Chain *)malloc( sizeof( Chain ) );
        if( !chain )
        {
            deallocate( first );
            return NULL;
        }
        if( i == 0 ) first = chain;
        chain->data = data[i];
        if( prev ) prev->n = chain;
        prev = chain;
    }

    chain->n = NULL;

    return first;
}

void reverse( Chain **pchain )
{
    Chain *iter = *pchain, *prev_iter = NULL;

    if( !iter || !iter->n ) return;

    prev_iter = iter;
    iter = iter->n;
    prev_iter->n = NULL;

    while( iter )
    {
        Chain *iter_next = iter->n;
        iter->n = prev_iter;
        prev_iter = iter;
        iter = iter_next;
    }

    *pchain = prev_iter;
}

int main( int argc, char *argv[] )
{
    static const int size = 100;
    int test[size];
    Chain *chain = NULL, *iter;

    for( int i = 0; i < size; i++ )
    {
        test[i] = i;
    }

    chain = allocate( test, size );
    if( !chain )
    {
        fprintf( stderr, "Can't allocate chain\n" );
        return -1;
    }

    reverse( &chain );

    iter = chain;
    for( int i = 0; i < size; i++ )
    {
        if( !iter )
        {
            fprintf( stderr, "Chain has size of %d instead of %d!\n", i, size );
            return -1;
        }

        if( iter->data != size - 1 - i )
        {
            fprintf( stderr, "Got %d, expected %d\n", iter->data, size - 1 - i );
            return -1;
        }

        iter = iter->n;
    }

    deallocate( chain );

    printf( "Success.\n" );

    return 0;
}

