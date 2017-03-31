
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>
#include "hashtable.h"

char *trimspace(char *str)
{
	char *ptr;

	if (str == NULL)
		return NULL;

	while (*str)
	{
		if (*str != ' ')
			break;

		str++;
	}

	ptr = str + strlen(str) - 1;

	while (ptr >= str)
	{
		if (*ptr != ' ')
		{
			break;
		}

		*(ptr--) = 0;
	}

	return str;
}


int main(int argc, char **argv)
{
	struct hashtab *persontable = NULL;
	struct hashtab *friendtable = NULL;
	char inputstring[2048];
	char *name1, *name2;
	char *ptr;
	char ch;

	persontable = hashtab_create(NULL, NULL, 100);
	if (persontable == NULL)
	{
		printf("No enough memory\n");
		return -ENOMEM;
	}

	printf("Please input command:\n");

	while (1)
	{
		gets(inputstring);

		ptr = trimspace(inputstring);
		if (strlen(ptr) < 1)
			continue;

		ch = (char)toupper(*ptr);

		if (ch != 'X' && (*(ptr + 1) != ' '))
		{
			printf("Invalid command\n");
			continue;
		}

		switch (ch)
		{
		case 'P':

			name1 = ptr + 2;
			name1 = trimspace(name1);

			if (name1 == NULL)
			{
				printf("Please input one person name\n");
				continue;
			}

			friendtable = hashtab_create(NULL, NULL, 100);
			if (friendtable == NULL)
			{
				printf("hashtab_create: No enough memory\n");
				continue;
			}

			int ret = hashtab_insert(persontable, strdup(name1), friendtable);
			if (ret != 0)
			{
				printf("hashtab_insert error: %d\n", ret);
				continue;
			}

			break;

		case 'F':

			name1 = ptr + 2;
			name1 = trimspace(name1);
			name2 = strchr(name1, ' ');
			if (name2)
			{
				*(name2++) = 0;
				name2 = trimspace(name2);
			}

			if (name1 == NULL || name2 == NULL)
			{
				printf("Please input two person names\n");
				continue;
			}

			friendtable = hashtab_search(persontable, name1);
			if (friendtable)
			{
				int ret = hashtab_insert(friendtable, strdup(name2), strdup("1"));
				if (ret != 0)
					printf("hashtab_insert error: %d\n", ret);
			}

			friendtable = hashtab_search(persontable, name2);
			if (friendtable)
			{
				int ret = hashtab_insert(friendtable, strdup(name1), strdup("1"));
				if (ret != 0)
					printf("hashtab_insert error: %d\n", ret);
			}

			break;

		case 'U':

			name1 = ptr + 2;
			name1 = trimspace(name1);
			name2 = strchr(name1, ' ');
			if (name2)
			{
				*(name2++) = 0;
				name2 = trimspace(name2);
			}

			if (name1 == NULL || name2 == NULL)
			{
				printf("Please input two person names\n");
				continue;
			}

			friendtable = hashtab_search(persontable, name1);
			if (friendtable)
				hashtab_delete(friendtable, name2);

			friendtable = hashtab_search(persontable, name2);
			if (friendtable)
				hashtab_delete(friendtable, name1);

			break;

		case 'L':

			name1 = ptr + 2;
			name1 = trimspace(name1);

			if (name1 == NULL)
			{
				printf("Please input the person name\n");
				continue;
			}

			friendtable = hashtab_search(persontable, name1);
			if (friendtable)
			{
				int count = hashtab_print_all_keys(friendtable);
				//printf("\n%s has %d friends\n", name1, count);
				printf("\n");
			}

			break;

		case 'Q':

			name1 = ptr + 2;
			name1 = trimspace(name1);
			name2 = strchr(name1, ' ');
			if (name2)
			{
				*(name2++) = 0;
				name2 = trimspace(name2);
			}

			if (name1 == NULL || name2 == NULL)
			{
				printf("Please input two person names\n");
				continue;
			}

			friendtable = hashtab_search(persontable, name1);
			if (friendtable)
			{
				int *tmp = (int *)hashtab_search(friendtable, name2);
				printf("%s\n", tmp ? "YES" : "NO");
			}
			break;

		case 'X':

			hashtab_destroy(persontable, 1);

			return 0;

		default:

			break;
		}
	}
	return 0;
}
