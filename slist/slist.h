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


struct slist_node {
	 void			*entry;
	 size_t			 size;
	 struct slist_node	*next;
};


int			 slist_insert(struct slist_node **, void *, size_t);
int			 slist_append(struct slist_node **, void *, size_t);
int			 slist_insert_after(struct slist_node *, void *,
					    size_t);
ssize_t			 slist_search(struct slist_node *, void *, size_t);
struct slist_node	*slist_locate(struct slist_node *, size_t);
int			 slist_remove(struct slist_node **, void *, size_t);
int			 slist_remove_head(struct slist_node **);
int			 slist_remove_tail(struct slist_node **);
size_t			 slist_length(struct slist_node *);
void			 slist_destroy(struct slist_node **);


#endif
