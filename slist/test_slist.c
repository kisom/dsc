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
	int			  target = 2;
	ssize_t			  seek = 0;
	struct slist_node	 *head = NULL;
	struct slist_node	 *node = NULL;

	for (i = 0; i < 100; i++) {
		if (-1 == slist_append(&head, seq[i], sizeof(int))) {
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
	print_list(head);

	printf("[+] testing slist_locate\n");
	node = slist_locate(head, 2);
	if (node == NULL)
		printf("[!] failed to locate node\n");
	else if (*(int *)node->entry != 2)
		printf("[!] wrong node value (expected 2, saw %d)\n",
		    *(int *)node->entry);
	else
		printf("[+] slist_locate succeeds\n");

	printf("[+] testing slist_search\n");
	node = NULL;
	if (target != (seek = slist_search(head, &target, sizeof(int))))
		printf("[!] failed to search node: expected %d, saw %ld\n",
		    target, (long)seek);
	else
		printf("[+] search succeeds\n");

	printf("[+] attempting to remove node\n");
	node = slist_locate(head, 2);
	if (node == NULL)
		printf("[!] failed to locate node\n");
	else if (-1 == slist_remove(&head, node->entry, node->size))
		printf("[!] failed to remove node\n");
	else
		printf("[+] removed node\n");
	print_list(head);

	slist_destroy(&head);
	destroy_seq(seq, 100);
	printf("[+] append complete\n");
}


static void
test_insert(void)
{
	size_t			  length = 0;
	int			**seq = new_sequence(0, 100);
	int			  i;
	struct slist_node	 *head = NULL;

	for (i = 0; i < 100; i++) {
		if (-1 == slist_insert(&head, seq[i], sizeof(int))) {
			printf("[!] failed to insert %d\n", *seq[i]);
		}
	}

	length = slist_length(head);
	if (length != 100) {
		printf("[!] expected a length of 100, actual is %lu\n",
			(long unsigned)length);
	}
	printf("[+] list length matches expected value\n");
	print_list(head);
	slist_destroy(&head);
	destroy_seq(seq, 100);
	printf("[+] insert complete\n");
}


static void
test_remove_tail(void)
{
	int			**seq = new_sequence(0, 10);
	int			  i = 0;
	struct slist_node	 *head = NULL;

	for (i = 0; i < 10; i++) {
		if (-1 == slist_append(&head, seq[i], sizeof(int)))
			printf("[!] failed to insert %d\n", *seq[i]);
	}

	print_list(head);
	printf("[+] destroying the list with remove_tail\n");
	for (i = 0; i < 10; i++) {
		if (-1 == slist_remove_tail(&head))
			printf("[!] failed to remove head!\n");
	}
	if (0 != (i = slist_length(head)))
		printf("[!] invalid list length %d (should be 0)\n", i);

	destroy_seq(seq, 10);
	printf("[+] remove_tail complete\n");
}


static void
test_remove_head(void)
{
	int			**seq = new_sequence(0, 10);
	int			  i = 0;
	struct slist_node	 *head = NULL;

	for (i = 0; i < 10; i++) {
		if (-1 == slist_append(&head, seq[i], sizeof(int)))
			printf("[!] failed to insert %d\n", *seq[i]);
	}

	printf("[+] destroying the list with remove_head\n");
	for (i = 0; i < 10; i++) {
		if (-1 == slist_remove_head(&head))
			printf("[!] failed to remove head!\n");
	}
	destroy_seq(seq, 10);
	printf("[+] remove_head complete\n");
}


static void
test_remove_head_node(void)
{
	int			**seq = new_sequence(0, 10);
	int			  i = 0;
	struct slist_node	 *head = NULL;
	struct slist_node	 *node = NULL;

	for (i = 0; i < 10; i++) {
		if (-1 == slist_append(&head, seq[i], sizeof(int)))
			printf("[!] failed to insert %d\n", *seq[i]);
	}

	node = slist_locate(head, 0);
	if (-1 == slist_remove(&head, node->entry, node->size))
		printf("[!] failed to remove node\n");
	print_list(head);
	slist_destroy(&head);
	destroy_seq(seq, 10);
	printf("[+] remove_head_node complete\n");
}


int
main(void)
{
	printf("[ -- TEST SLIST -- ]\n\n");
	printf("[+] test_append\n");
	test_append();
	printf("[+] test_insert\n");
	test_insert();
	printf("[+] test_tail\n");
	test_remove_tail();
	printf("[+] test_remove_head\n");
	test_remove_head();
	printf("[+] test_remove_head_node\n");
	test_remove_head_node();
	printf("[+] finished.\n");
}
