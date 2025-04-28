#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"

/**
 * copy_file - Copies the contents of one file to another.
 * @src: Path to the source file to be copied.
 * @dest: Path to the destination file where content
 * Return: void
 */

void copy_file(const char *src, const char *dest)
{
	int src_fd, dest_fd, nread;
	char buffer[1024];

	src_fd = open(src, O_RDONLY);
	if (src_fd < 0)
	{
		perror("Source file open failed");
		return;
	}
	dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (dest_fd < 0)
	{
		perror("Destination file open failed");
		close(src_fd);
		return;
	}

	while ((nread = read(src_fd, buffer, sizeof(buffer))) > 0)
	{
		if (write(dest_fd, buffer, nread) < 0)
		{
			perror("Write to destination failed");
			close(src_fd);
			close(dest_fd);
			return;
		}
	}
	close(src_fd);
	close(dest_fd);
}
