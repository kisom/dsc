/*
 * Copyright (c) 2013 Kyle Isom <kyle@tyrfingr.is>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
 * OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 * ---------------------------------------------------------------------
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include "slist.h"


void
print_list(struct slist_node *head)
{
	struct slist_node	*node = NULL;

	node = head;
	while (node != NULL) {
		printf("%d->", *(int *)node->entry);
		node = node->next;
	}
	printf("EOL\n");
}


static void
slist_destroy_node(struct slist_node *node)
{
	free(node->entry);
	node->entry = NULL;
}


static struct slist_node *
slist_tail(struct slist_node *head)
{
	struct slist_node *node = NULL;

	if (NULL == head)
		return NULL;

	node = head;
	while (node->next != NULL)
		node = node->next;
	return node;
}


/*
 * Create a new head node. This is used to initialise a new list.
 */
struct slist_node *
slist_head(void *entry, size_t size)
{
	struct slist_node	*node;

	node = malloc(sizeof(struct slist_node));
	if (NULL != node) {
		node->entry = entry;
		node->size = size;
		node->next = NULL;
	}
	return node;
}


/*
 * Append an element onto the tail of the list.
 */
struct slist_node *
slist_append(struct slist_node *head, void * entry, size_t size)
{
	struct slist_node	*node, *tail;

	tail = slist_head(entry, size);
	if (NULL != head) {
		node = slist_tail(head);
		node->next = tail;
	} else {
		head = tail;
	}

	return head;
}


/*
 * Insert a node to the beginning of the list.
 */
struct slist_node *
slist_insert(struct slist_node *head, void *entry, size_t size)
{
	struct slist_node	*new_head;

	new_head = slist_head(entry, size);
	if (NULL == new_head)
		return NULL;

	if (NULL == head)
		new_head->next = NULL;
	else
		new_head->next = head;
	return new_head;
}


/*
 * Remove the node at the start of node.
 */
struct slist_node *
slist_remove_head(struct slist_node *head)
{
	struct slist_node	*node;

	node = head->next;
	slist_destroy_node(head);
	return node;
}


/*
 * Remove the last node in the list.
 */
struct slist_node *
slist_remove_tail(struct slist_node *head)
{
	struct slist_node	*node, *cursor;

	cursor = head;
	for (node = cursor->next; node != NULL; cursor = node);
	slist_destroy_node(node);
	cursor->next = NULL;
	return head;
}


/*
 * Destroy the entire list.
 */
void
slist_destroy(struct slist_node *head)
{
	struct slist_node	*node;

	node = head;
	while (node != NULL) {
		node = node->next;
		slist_destroy_node(head);
		free(head);
		head = node;
	}
}


/*
 * Returns the number of nodes in the list.
 */
size_t
slist_length(struct slist_node *head)
{
	size_t			 length = 0;
	struct slist_node	*node = NULL;

	node = head;
	while (node != NULL) {
		length++;
		node = node->next;
	}
	return length;
}
