#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef uint8_t u;

u sum2( u a, u b )
{
    u mask = 1;
    u c = 0;
    bool carry = false;

    while( mask )
    {
        bool new_carry = (a & b) & mask;
        c |= (a ^ b) & mask;
        if( carry )
        {
            if( c & mask )
            {
                c &= ~mask;
                new_carry = true;
            }
            else
            {
                c |= mask;
            }
        }
        carry = new_carry;
        mask <<= 1;
    }

    return c;
}

u sum3( u a, u b )
{
    if( !b ) return a;
    u c = a ^ b;
    u d = (a & b) << 1;
    return sum3( c, d );
}

u sum( u a, u b )
{
    while( b )
    {
        u c = a ^ b;
        b = (a & b) << 1;
        a = c;
    }
    
    return a;
}

bool verify( u a, u b )
{
    u c = sum( a, b );
    u ex = a + b;
    if( ex != c )
    {
        fprintf( stderr, "%u + %u: expected %u, got %u\n", a, b, ex, c );
        return false;
    }

    return true;
}

int main( int argc, char *argv[] )
{
    if( !verify( 1, 1 ) ||
        !verify( 255, 1 ) ||
        !verify( 255, 255 ) ||
        !verify( 0x70, 0x7 ) ||
        !verify( 8, 15 ) )
    {
        return -1;
    }

    printf( "Success.\n" );

    return 0;
}

