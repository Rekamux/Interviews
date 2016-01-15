#include <stdio.h>

struct StructNode
{
    int data;
    struct StructNode *left, *right;
    StructNode( int data ) : data( data ), left( NULL ), right( NULL ) {}
};

typedef struct StructNode Node;

void insert( Node **node, int value )
{
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
}

void construct( int *list, Node **node, int first, int last )
{
    if( first > last ) return;

    int middle = first + (last - first) / 2;

    insert( node, list[middle] );
    construct( list, node, first, middle - 1 );
    construct( list, node, middle + 1, last );
}

int max( int a, int b ) { return a < b ? b : a; }

int tree_height( Node *node )
{
    if( !node ) return 0;

    return max( tree_height( node->left ), tree_height( node->right ) ) + 1;
}

void print_tree( Node *node, int d )
{
    if( !node ) return;
    for( int i = 0; i < d; i++ ) printf( " " );
    printf( "%d -> %d -> %d\n", node->data, node->left ? node->left->data : 0, node->right ? node->right->data : 0 );
    print_tree( node->left, d + 1 );
    print_tree( node->right, d + 1 );
}

int main( int argc, char *argv[] )
{
    int list[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    int size = sizeof( list ) / sizeof( list[0] );
    Node *node = NULL;
    int height;

    construct( list, &node, 0, size - 1 );
    height = tree_height( node );
    print_tree( node, 0 );
    printf( "Height:  %d\n", height );

    return 0;
}

