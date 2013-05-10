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
#include <stdlib.h>
#include <string.h>

#include "dlist.h"


static void
dlist_destroy_node(struct dlist_node *node)
{
	free(node->entry);
	node->entry = NULL;
}


static struct dlist_node *
dlist_tail(struct dlist_node *head)
{
	struct dlist_node *node = NULL;

	if (NULL == head)
		return NULL;

	node = head;
	while (node->next != NULL)
		node = node->next;
	return node;
}


static struct dlist_node *
dlist_create_node(void *entry, size_t size)
{
	struct dlist_node	*node = NULL;

	if (NULL != (node = malloc(sizeof(struct dlist_node)))) {
		if (NULL != (node->entry = malloc(size))) {
			node->size = size;
			memcpy(node->entry, entry, size);
			node->next = NULL;
		} else {
			free(node);
			node = NULL;
		}
	}
	return node;
}


/*
 * Insert a new node into the list. Returns 0 on success and -1 on failure.
 */
int
dlist_insert(struct dlist_node **head, void *entry, size_t size)
{
	struct dlist_node	*node = NULL;

	if (NULL != (node = dlist_create_node(entry, size))) {
		node->next = *head;
		*head = node;
	}
	return 0;
}


/*
 * Append a new node onto the list.
 */
int
dlist_append(struct dlist_node **head, void *entry, size_t size)
{
	struct dlist_node	*node = NULL;
	struct dlist_node	*tail = NULL;

	if (NULL == (node = dlist_create_node(entry, size)))
		return -1;

	tail = dlist_tail(*head);
	if (tail != NULL)
		tail->next = node;
	else
		*head = node;
	return 0;
}


/*
 * Insert a node after the node passed in.
 */
int
dlist_insert_after(struct dlist_node *node, void *entry, size_t size)
{
	struct dlist_node	*new_node = NULL;
	struct dlist_node	*next = NULL;

	if (NULL == (new_node = dlist_create_node(entry, size)))
		return -1;

	next = node->next;
	node->next = new_node;
	new_node->next = next;
	return 0;
}


/*
 * Search the list for an entry. Returns the index of the node if it exists,
 * and -1 if the node isn't present in the list.
 */
ssize_t
dlist_search(struct dlist_node *head, void *entry, size_t size)
{
	struct dlist_node	*node = NULL;
	ssize_t			 pos = 0;
	int			 found = 0;

	node = head;
	while (node != NULL && !found) {
		if (node->size != size)
			continue;
		if (0 == memcmp(node->entry, entry, size))
			found = 1;
		else
			pos++;
		node = node->next;
	}

	if (!found)
		return -1;
	return pos;
}


/*
 * Return the node at the requested index. If the index is outside the bounds
 * of the list, returns NULL.
 */
struct dlist_node *
dlist_locate(struct dlist_node *head, size_t index)
{
	struct dlist_node	*node = NULL;
	size_t			 pos = 0;

	for (node = head; node != NULL && pos != index; node = node->next, pos++) ;
	return node;
}


/*
 * Remove the node from the list. Returns 0 on success, and -1 on failure.
 */
int
dlist_remove(struct dlist_node **head, void *entry, size_t size)
{

	struct dlist_node	*next = NULL;
	struct dlist_node	*node = NULL;
	struct dlist_node	*prev = NULL;
	int			 removed = 0;

	node = *head;
	if (node == NULL)
		return -1;

	for (node = *head; node != NULL; node = node->next) {
		if (size != node->size)
			continue;
		if (0 == memcmp(node->entry, entry, size)) {
			next = node->next;
			if (prev != NULL)
				prev->next = next;
			else
				*head = node->next;
			dlist_destroy_node(node);
			free(node);
			node = NULL;
			removed = 1;
			break;
		}
		prev = node;
	}
	return removed ? 0 : -1;
}


/*
 * Remove the list's head. Returns 0 on success, and -1 on failure.
 */
int
dlist_remove_head(struct dlist_node **head)
{
	struct dlist_node	*next = NULL;

	if (NULL == *head)
		return -1;

	next = (*head)->next;
	dlist_destroy_node(*head);
	free(*head);
	*head = next;
	return 0;
}


/*
 * Remove the list's tail. Returns 0 on success, and -1 on failure.
 */
int
dlist_remove_tail(struct dlist_node **head)
{
	struct dlist_node	*node;
	struct dlist_node	*tail;

	if (NULL == *head)
		return -1;
	if (NULL == (*head)->next) {
		dlist_destroy_node(*head);
		free(*head);
		*head = NULL;
		return 0;
	}

	tail = *head;
	node = tail->next;

	while (node->next != NULL) {
		tail = node;
		node = node->next;
	}

	dlist_destroy_node(node);
	free(node);
	tail->next = NULL;

	return 0;
}


/*
 * Returns the number of nodes in the list.
 */
size_t
dlist_length(struct dlist_node *head)
{
	size_t			 length = 0;
	struct dlist_node	*node = NULL;

	for (node = head; node != NULL; node = node->next)
		length++;
	return length;
}


/*
 * Destroy the list, making sure the list is properly deallocated.
 */
void
dlist_destroy(struct dlist_node **head)
{
	struct dlist_node	*node = NULL;

	node = *head;
	while (node != NULL) {
		dlist_destroy_node(node);
		free(node);
		node = node->next;
	}
}
