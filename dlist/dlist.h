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


#ifndef __LIBSLIST_SLIST_H
#define __LIBSLIST_SLIST_H


#include <sys/types.h>
#include <stdlib.h>


struct dlist_node {
	 void			*entry;
	 size_t			 size;
	 struct dlist_node	*prev;
	 struct dlist_node	*next;
};


int			 dlist_insert(struct dlist_node **, void *, size_t);
int			 dlist_append(struct dlist_node **, void *, size_t);
int			 dlist_insert_after(struct dlist_node *, void *,
					    size_t);
ssize_t			 dlist_search(struct dlist_node *, void *, size_t);
struct dlist_node	*dlist_locate(struct dlist_node *, size_t);
int			 dlist_remove(struct dlist_node **, void *, size_t);
int			 dlist_remove_head(struct dlist_node **);
int			 dlist_remove_tail(struct dlist_node **);
size_t			 dlist_length(struct dlist_node *);
void			 dlist_destroy(struct dlist_node **);


#endif
