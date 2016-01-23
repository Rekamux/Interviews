#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int data;
    int height;
    struct Node *left, *right;
    Node( int data ) : data( data ), height( 1 ), left( NULL ), right( NULL ) {}
};

int max( int a, int b )
{
    return a < b ? b : a;
}

int get_height( Node *node )
{
    if( !node )
    {
        return 0;
    }

    return node->height;
}

int get_balance( Node *node )
{
    if( !node )
    {
        return 0;
    }

    return get_height( node->left ) - get_height( node->right );
}

void update_height( Node *node )
{
    if( !node )
    {
        return;
    }

    node->height = max( get_height( node->left ), get_height( node->right ) ) + 1;
}

void rotate_right( Node **node )
{
    if( !(*node) || !(*node)->left )
    {
        return;
    }

    Node *old_left = (*node)->left;
    Node *old_left_right = (*node)->left->right;

    old_left->right = *node;
    (*node)->left = old_left_right;
    (*node) = old_left;

    update_height( (*node)->right );
    update_height( *node );
}

void rotate_left( Node **node )
{
    if( !(*node) || !(*node)->right )
    {
        return;
    }

    Node *old_right = (*node)->right;
    Node *old_right_left = (*node)->right->left;

    old_right->left = *node;
    (*node)->right = old_right_left;
    (*node) = old_right;

    update_height( (*node)->left );
    update_height( *node );
}

void print_tree( Node *node, int d = 0 )
{
    if( !node ) return;

    Node *l = node->left, *r = node->right;

    for( int i = 0; i < d; i++ )
    {
        printf( "-" );
    }

    printf( "> %d\n", node->data );
    print_tree( node->left, d + 1 );
    print_tree( node->right, d + 1 );

}

void insert( Node **node, int value )
{
    int balance;

    if( *node == NULL )
    {
        *node = new Node( value );
        return;
    }

    if( value < (*node)->data )
    {
        insert( &((*node)->left), value );
    }
    else
    {
        insert( &((*node)->right), value );
    }
    update_height( *node );

    balance = get_balance( *node );
    if( balance > 1 )
    {
        if( get_balance( (*node)->left ) <= -1 )
        {
            rotate_left( &((*node)->left) );
        }
        rotate_right( node );
    }
    else if( balance < -1 )
    {
        if( get_balance( (*node)->right ) >= 1 )
        {
            rotate_right( &((*node)->right) );
        }
        rotate_left( node );
    }
    update_height( *node );
}

void construct( int *list, int size, Node **node )
{
    for( int i = 0; i < size; i++ )
    {
        insert( node, list[i] );
    }
}

int tree_height( Node *node )
{
    if( !node ) return 0;

    return max( tree_height( node->left ), tree_height( node->right ) ) + 1;
}

void shuffle_list( int *list, int size )
{
    srand( time( NULL ) );
    for( int i = 0; i < size; i++ )
    {
        int j = rand() % size;
        int tmp = list[i];
        list[i] = list[j];
        list[j] = tmp;
    }
}

int verify_balances( Node *node )
{
    int balance;

    if( !node ) return 0;

    if( verify_balances( node->left ) || verify_balances( node->right ) )
    {
        return -1;
    }

    balance = get_balance( node );
    if( balance < -1 || balance > 1 )
    {
        fprintf( stderr, "%s: invalid balance\n", __FUNCTION__ );
        return -1;
    }

    return 0;
}

void transverse( int *list, int size, Node *node, int *index )
{
    if( !node ) return;

    transverse( list, size, node->left, index );
    list[(*index)] = node->data;
    (*index)++;
    transverse( list, size, node->right, index );
}

int verify_order( int *list, int size, Node *node )
{
    int other[size];
    int index = 0;

    transverse( other, size, node, &index );

    for( int i = 0; i < size; i++ )
    {
        if( i != other[i] )
        {
            fprintf( stderr, "expected %d got %d\n", i, other[i] );
            return -1;
        }
    }

    return 0;
}

int main( int argc, char *argv[] )
{
    int list[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_height = 5;
    int size = sizeof( list ) / sizeof( list[0] );
    Node *node = NULL;
    int height;

    shuffle_list( list, size );
    construct( list, size, &node );
    print_tree( node );

    height = tree_height( node );
    if( height > expected_height )
    {
        fprintf( stderr, "Height is wrong, expected %d got %d\n", expected_height, height );
        return -1;
    }
    printf( "Height:  %d\n", height );

    if( verify_balances( node ) )
    {
        return -1;
    }

    if( verify_order( list, size, node ) )
    {
        return -1;
    }

    printf( "Success.\n" );

    return 0;
}

