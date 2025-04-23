#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct path_node - Node for a linked list of PATH directories.
 * @dir: Pointer to a string containing a directory path.
 * @next: Pointer to the next node in the list.
 *
 * Description: Each node holds a duplicated string of a directory
 *              found in the PATH environment variable.
 */
typedef struct path_node
{
	char *dir;
	struct path_node *next;
} path_node_t;

/**
 * add_node_end - Adds a new node at the end of a path_node_t list.
 * @head: Double pointer to the head of the list.
 * @str: The directory string to duplicate and add.
 *
 * Return: Address of the new element, or NULL if it failed.
 */

path_node_t *add_node_end(path_node_t **head, const char *str)
{
	path_node_t *new_node;
	path_node_t *temp;
	if (!head ||!str){
		return NULL;
	}
	/*Allocate memory for the new node*/
	new_node = malloc(sizeof(path_node_t));
	if(!new_node)
	{
		perror("add_node_end: malloc node failed");
		return NULL;
	}

	/*Duplicate the dir string*/
	new_node->dir = strdup(str);
	if (!new_node->dir)
	{
		perror("add_node_end: strdup failed");
		free(new_node);
		return NULL;
	}
	new_node->next = NULL;

	/*if the list is empty, make the new node the head*/
	if (*head == NULL)
	{
		*head = new_node;
	} else {
	/*traverse to the end of list*/
		temp = *head;
		while (temp->next != NULL)
		{temp = temp->next;}

	/*Link the new node at the end */
	temp->next = new_node;
	}
	return new_node;
}

/**
 * free_path_list - Frees a path_node_t linked list.
 * @head: Pointer to the head of the list to be freed.
 */

void free_path_list(path_node_t *head)
{
	path_node_t *current;
	path_node_t *next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->dir);
		free(current);
		current = next_node;
	}
}

/**
 * build_path_list - Builds a linked list of PATH directories.
 *
 * Return: Pointer to the head of the newly created linked list,
 *         or NULL on failure or if PATH is not set/empty.
 *
 * Description: This function gets the PATH environment variable,
 *              parses it using ':' as a delimiter, and creates
 *              a linked list where each node contains one directory.
 *              It handles potential empty paths or paths starting/ending
 *              with ':'. The caller is responsible for freeing the
 *              returned list using free_path_list().
 */

path_node_t *build_path_list(void)
{
	char *path_env;
	char *path_copy;
	char *token;
	path_node_t *head = NULL;
	const char *delimiter = ":";

	/*Get the Path encironment variable*/
	path_env = getenv("PATH");
	if (path_env == NULL || *path_env == '\0')
	{
		return (NULL);
	}
	/*Duplicate the PATH string (because strtok modifies the string)*/
	path_copy = strdup(path_env);
	if(path_copy == NULL)
	{
		perror("build_path_list: strdup failed");
		return (NULL);
	}
	
	/*Tokenize the duplicate string*/
	token = strtok(path_copy, delimiter);
	while (token != NULL)
	{
		if(add_node_end(&head, token) == NULL)
		{
			fprintf(stderr, "build_path_list: Failed to add node\n");
			free(path_copy);
			free_path_list(head);
			return (NULL);
		}
	
	/* Get the nest token*/
	token = strtok(NULL, delimiter);
	}
	/*Free the duplicated PATH string (no longer needed)*/
	free(path_copy);
	/*Return the head of the list*/
	return (head);
}

int main(void) {
    path_node_t *path_list_head;
    path_node_t *current;
    int count = 0;

    printf("Building PATH directory list...\n");
    path_list_head = build_path_list();

    if (path_list_head == NULL) {
        printf("PATH list could not be built (PATH not set, empty, or memory error).\n");
        return 1;
    }

    printf("PATH Directories:\n");
    current = path_list_head;
    while (current != NULL) {
        count++;
        printf("[%d]: %s\n", count, current->dir ? current->dir : "(null string!)");
        current = current->next;
    }

    printf("\nFreeing the list...\n");
    free_path_list(path_list_head);
    printf("List freed.\n");

    return 0;
}

