/*  File:       Elmekki_particles.h
    Author:     Mohamed Elmekki
    Date:       06-03-2017
    Topic:      CST 8234 Assignment 3
                To generate a particle system: a computer graphic technique to
                simulate fuzzy objects.
    Purpose:    Design, code, and test a simple implementation of linked lists.
                Use multiple files in a program.
                Use of a Makefile.
    Notes:
*/

/* -----------------------------------------------------------------------------
    INCLUDES
----------------------------------------------------------------------------- */
#include <stdlib.h>

/* -----------------------------------------------------------------------------
    DEFINES
----------------------------------------------------------------------------- */
#define DFLT_INIT_NUM_PARTICLES 50
#define DELTA_LIFESPAN 1

/* -----------------------------------------------------------------------------
    STRUCT DECLARATIONS
------------------------------------------------------------------------------*/
struct vector {
    float x, y, z;
};

typedef struct vector Point3D_t;
typedef struct vector Vector3D_t;

typedef struct colour {
    float r, g, b, a;
} colour4_t;

typedef struct particle {
    colour4_t           col;
    Point3D_t           pos;
    Vector3D_t          dir;
    Vector3D_t          spd;
    int                 lifespan;
    float               size;
    struct particle*    next;
} particle_t;

/*------------------------------------------------------------------------------
    FUNCTION PROTOTYPES
------------------------------------------------------------------------------*/
int particle_init(struct particle *p);
int particle_add(struct particle **head);
int particle_remove(struct particle *p);
int particle_destroy(struct particle **head);
int particle_update(struct particle **head);
int particle_destroy_recur(struct particle *part);
int random_number(int min, int max);