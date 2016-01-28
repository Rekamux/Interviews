#include <vector>

using namespace std;

struct Vertex;
struct Edge;

typedef vector<Vertex *> Vertices;
typedef vector<Edge> Edges;

struct Edge
{
    Vertex *vertex;
    int weight;
};

struct Vertex
{
    Edges edges;
    const char *name;

    Vertex( const char *name ) : name( name );
};

struct Graph
{
    Vertices vertices;
};

void addVertex( Graph *graph, const char *name )
{
    Vertex *v = new Vertex( name );

    if( !v ) throw "Failed to allocate Vertex";

    graph->vertices.push_back( v );
}

Vertex *removeVertex( Graph *graph, const char *name )
{
    Vertex *res = nullptr;

    for( int i = 0; i < graph->vertices.size(); i++ )
    {
        Vertex *v = graph->vertices.at( i );
        if( strcmp( v->name, name ) == 0 )
        {
            res = v;
            graph->vertices.erase( i );
            break;
        }
    }
    if( !res ) return nullptr;

    res->edges.clear();

    for( int i = 0; i < graph->vertices.size(); i++ )
    {
        Vertex *v = graph->vertices.at( i );
        for( int j = 0; j < v->edges.size(); j++ )
        {
            if( v->edges.at( j ).vertex == res )
            {
                v->edges.erase( j );
                break;
            }
        }
    }

    return res;
}

void addEdge( Graph *graph, Vertex *v1, Vertex *v2, int w )
{
    
}

