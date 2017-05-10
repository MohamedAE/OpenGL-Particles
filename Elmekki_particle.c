/*  File:       Elmekki_particle.c
	Author:     Mohamed Elmekki
	Date:       06-03-2017
	Topic:      CST 8234 Assignment 3
				To generate a particle system: a computer graphic technique to
				simulate fuzzy objects.
	Purpose:    Design, code, and test a simple implementation of linked lists.
				Use multiple files in a program.
				Use of a Makefile.
	Notes:		"Fountain of Colours"
*/

/* -----------------------------------------------------------------------------
	INCLUDES
----------------------------------------------------------------------------- */
#include "Elmekki_particle.h"

/*------------------------------------------------------------------------------
	FUNCTIONS
----------------------------------------------------------------------------- */

/*------------------------------------------------------------------------------
	Function    :   particle_init
	Purpose     :   initialize the properties of a single particle_init
	Input       :   pointer to the particle structure to be initialized
	Output      :   returns -1 on error, 0 on success
------------------------------------------------------------------------------*/
int particle_init(struct particle *p) {
	/* Initialize colour (white) */
	p->col.r = (rand() % 10) * .1;
	p->col.g = (rand() % 10) * .1;
	p->col.b = (rand() % 10) * .1;
	p->col.a = 0.01;

	/* Initialize position to 0,-300 */
	p->pos.x = 0.0;
	p->pos.y = -300.0;

	/* Initialize random direction vector; x */
	p->dir.x = random_number(-5, 5);

	/* Initialize random direction vector; y */
	p->dir.y = random_number(100, 500) * 0.01;

	/* Initialize speed vector */
	p->spd.x = 0.2;
	p->spd.y = 2.0;

	/* Initialize lifespan and size */
	p->lifespan = 100;
	p->size = 5;

	return 0;
}

/*------------------------------------------------------------------------------
	Function    :   particle_add
	Purpose     :   add a particle to the dynamic particle linked list
	Input       :   struct particle *head; head of the particle lists
	Output      :   returns -1 on error, 0 on success
	Notes       :   calls particle_init()
------------------------------------------------------------------------------*/
int particle_add(struct particle **head) {
	particle_t *newNode;

	if ((newNode = (particle_t *) malloc(sizeof(particle_t))) == NULL) {
		return -1;
	}

	particle_init(newNode);

	newNode->next = *head;
	*head = newNode;

	return 0;
}

/*------------------------------------------------------------------------------
	Function    :   particle_remove
	Purpose     :   remove a specific particle from the dynamic particle linked
					list
	Input       :   pointer to the particle to remove
	Output      :   returns -1 on error, 0 on success
	Notes       :   particle can be situated in any place in the list
					usually deleted because lifespan ran out
------------------------------------------------------------------------------*/
int particle_remove(struct particle *p) {
	particle_t *part = p;
	particle_t *remove;

	if (p->next == NULL) return -1;

	remove = part->next;
	part->next = remove->next;
	free(remove);

	return 0;
}

/*------------------------------------------------------------------------------
	Function    :   particle_destroy
	Purpose     :   free memory used by the dynamic particle linked list
	Input       :   struct **head; head of the particle linked list
	Output      :   returns -1 on error, the number of particles destroyed on
					success
	Notes       :   removes all particles from the list
					calls particle_remove() on each
------------------------------------------------------------------------------*/
int particle_destroy(struct particle **head) {
	particle_t *remove;
	int count = 0;

	if (*head == NULL) return -1;

	while (*head != NULL) {
		remove = *head;
		*head = remove->next;
		particle_remove(remove);
		count++;
	}

	return count;
}

/*------------------------------------------------------------------------------
	Function    :   particle_update
	Purpose     :   update the particle's properties to be renedered in the next
					frame
	Input       :   struct particle **head; head of the particle linked list
	Output      :   returns -1 on error, 0 on success
	Notes       :   GO NUTS!!!!
------------------------------------------------------------------------------*/
int particle_update(struct particle **head) {
	particle_t *curr = *head;

	if (curr == NULL) return -1;

	while (curr != NULL) {
		/* Increment alpha by a small value */
		curr->col.a += 0.01;

		/* Update x position */
		curr->pos.x += (curr->spd.x * curr->dir.x);

		/* If particle passes window boundaries, reinitialize */
		if (curr->pos.x > 300 || curr->pos.x < -300) {
			particle_init(curr);
		}

		/* Update y position */
		curr->pos.y += (curr->spd.y * curr->dir.y);

		/* If particle passes window boundaries, reinitialize */
		if (curr->pos.y > 300 || curr->pos.y < -300) {
			particle_init(curr);
		}

		/* Decrement vertical direction slightly, simulating gravity */
		curr->dir.y -= 0.005;

		curr = curr->next;
	}

	return 0;
}

/*------------------------------------------------------------------------------
	Function    :   random_number
	Purpose     :   generate and return a random number
	Input       :   boundaries within witch a number is calculated
	Output      :   returns a random number within given boundaries
------------------------------------------------------------------------------*/
int random_number(int min, int max) {
	return (min + rand() % (max - min + 1));
}