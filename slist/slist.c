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
#include <string.h>

#include "slist.h"


static void
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


static struct slist_node *
slist_create_node(void *entry, size_t size)
{
	struct slist_node	*node = NULL;

	if (NULL != (node = malloc(sizeof(struct slist_node)))) {
		if (NULL != (node->entry = malloc(size))) {
			node->size = size;
			memcpy(node->entry, entry, size);
		} else {
			free(node);
			node = NULL;
		}
	}
	return node;
}


int
slist_insert(struct slist_node **head, void *entry, size_t size)
{
	struct slist_node	*node = NULL;

	if (NULL != (node = slist_create_node(entry, size))) {
		node->next = *head;
		head = &node;
	}
	return 0;
}

struct slist_node	*slist_append(struct slist_node *, void *, size_t);
struct slist_node	*slist_insert_after(struct slist_node *, void *, size_t);
struct slist_node	*slist_search(struct slist_node *, void *, size_t);
struct slist_node	*slist_locate(struct slist_node *, size_t);
struct slist_node	*slist_remove(struct slist_node *, void *, size_t);
struct slist_node	*slist_remove_head(struct slist_node *, void *, size_t);
struct slist_node	*slist_remove_tail(struct slist_node *, void *, size_t);
size_t			 slist_length(struct slist_node *);
