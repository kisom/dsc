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

static int **
new_sequence(int start, int end)
{
	int **seq = NULL;
	int  *entry = NULL;
	int   i = 0;

	seq = malloc(sizeof(int) * (end - start));
	if (NULL == seq)
		return NULL;

	for (i = start; i != end; i++) {
		entry = malloc(sizeof(int));
		*entry = i;
		seq[i - start] = entry;
	}
	return seq;
}

static void
destroy_seq(int **seq, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++) {
		free(seq[i]);
		seq[i] = NULL;
	}
	free(seq);
}

static void
test_append(void)
{
	size_t			  length = 0;
	int			**seq = new_sequence(0, 100);
	int			  i;
	struct slist_node	 *head = NULL;

	printf("[+] testing append\n");
	for (i = 0; i < 100; i++) {
		if (NULL == (head = slist_append(head, seq[i], sizeof(int)))) {
			printf("[!] failed to append %d\n", *seq[i]);
			break;
		}
	}

	length = slist_length(head);
	if (length != 100) {
		printf("[!] expected a length of 100, actual is %lu\n",
			(long unsigned)length);
	}
	printf("[+] list length matches expected value\n");
	slist_destroy(head);
	destroy_seq(seq, 100);
}


static void
test_insert(void)
{
	size_t			  length = 0;
	int			**seq = new_sequence(0, 100);
	int			  i;
	struct slist_node	 *head = NULL;

	printf("[+] testing insert\n");
	for (i = 0; i < 100; i++) {
		if (NULL == (head = slist_insert(head, seq[i], sizeof(int)))) {
			printf("[!] failed to insert %d\n", *seq[i]);
			break;
		}
		print_list(head);
	}

	length = slist_length(head);
	if (length != 100) {
		printf("[!] expected a length of 100, actual is %lu\n",
			(long unsigned)length);
	}
	printf("[+] list length matches expected value\n");
	slist_destroy(head);
	destroy_seq(seq, 100);
}

int
main(void)
{
	test_append();
	test_insert();
}
