#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item{
	char *item;
	struct Item *pre;
	struct Item *next;
}T_Item, *PT_Item;

static PT_Item g_ptItemHead;

void add_item(PT_Item ptAdd)
{
	PT_Item ptCur;
	
	if(g_ptItemHead == NULL)
		{
			g_ptItemHead = ptAdd;
		}
	else
		{
			ptCur = g_ptItemHead;
			while(ptCur->next)
			{
				ptCur = ptCur->next;
			}
			ptCur->next = ptAdd;
			ptAdd->pre = ptCur;
		}
}

void del_item(PT_Item ptDel)
{
	PT_Item ptCur;
	PT_Item ptNext;
	PT_Item ptPre;
	
	if(g_ptItemHead == ptDel)
		{
			ptCur = ptDel->next;
			g_ptItemHead = ptCur;
			ptCur->pre = NULL;
			return;
		}
	else
		{
			ptCur = g_ptItemHead->next;
			while(ptCur)
			{
				if(ptCur == ptDel)
					{
						ptPre = ptCur->pre;
						ptNext = ptCur->next;
						ptPre->next = ptNext;
						if(ptNext)
							{
								ptNext->pre = ptPre;
							}
						break;
					}
				else
					{
						ptCur = ptCur->next;
					}
			}
		}
		
	free(ptDel->item);
	free(ptDel);
}

PT_Item get_item(char *item)
{
	PT_Item ptCur;
	if(g_ptItemHead == NULL)
		{
			return NULL;
		}
	else
		{
			ptCur = g_ptItemHead;
			do
			{
				if(strcmp(ptCur->item, item) == 0)
					return ptCur;
				else
					ptCur = ptCur->next;
			}while(ptCur);
		}
	return NULL;
}

/* allocate memory, add to linked list */
void add_one_item(void)
{
	PT_Item ptNew;
	char *str;
	char item[128];
	
	printf("Enter the item:");
	scanf("%s", item);
	
	/* get the input */
	str = malloc(strlen(item) + 1);
	strcpy(str, item);
	
	/* allocate memory for the new struct, initatite it */
	ptNew = malloc(sizeof(T_Item));
	ptNew->item = str;
	ptNew->pre = NULL;
	ptNew->next = NULL;
	
	/* add to linked list */
	add_item(ptNew);
}

void del_one_item(void)
{
	PT_Item ptFind;
	char item[128];
	
	printf("Enter the item:");
	scanf("%s", item);
	
	ptFind = get_item(item);
	if(ptFind == NULL)
		{
			printf("there is no this item\n");
			return;
		}
	del_item(ptFind);
}

void list_all_items(void)
{
	PT_Item ptCur;
	int i = 0;
	ptCur = g_ptItemHead;
	while(ptCur)
	{
		printf("%02d : %s\n", i++, ptCur->item);
		ptCur = ptCur->next;
	}
}

int main(int argc, char **argv)
{
	char c;
	
	while(1)
	{
		printf("<l> List all the items\n");
		printf("<a> Add one item\n");
		printf("<d> Delete one item\n");
		printf("<x> Exit\n");
		
		printf("Enter your choice: ");
		c = getchar();
		switch(c)
		{
			case 'l':
				{
					list_all_items();
					break;
				}
			case 'a':
				{
					add_one_item();
					break;
				}
			case 'd':
				{
					del_one_item();
					break;
				}
			case 'x':
				{
					return 0;
					break;
				}
			default:
				break;
		}
	}
	
	return 0;
}