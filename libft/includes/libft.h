/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:05:09 by sheferna          #+#    #+#             */
/*   Updated: 2024/04/09 11:24:21 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

// --------------------- List Struct -----------------------------------------
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// --------------------- Basic Libc functions --------------------------------
/**
 * @brief Test for any character for which isupper(3) or
		islower(3) is true.
 * @param c The value to test.
 * @returns Returns True to indicate that it's an alphabetic character and
		returns False otherwise.
*/
int					ft_isalpha(int c);
/**
 * @brief Test for a decimal digit character.
 * @param c The value to test.
 * @returns Returns True to indicate that it's a decimal digit character and
		returns False otherwise.
*/
int					ft_isdigit(int c);
/**
 * @brief The isalnum() function tests for any character for which isalpha(3)
		or isdigit(3) is true.
 * @param c The value to test.
 * @returns Returns True to indicate that it's an alphanumeric character and
		returns False otherwise.
*/
int					ft_isalnum(int c);
/**
 * @brief Test for ASCII character between 0 to 127 both inclusive.
 * @param c The value to test.
 * @returns Returns True to indicate that it's an ASCII character and
		returns False otherwise.
*/
int					ft_isascii(int c);
/**
 * @brief Test for printing character test (space character inclusive)
		between 32 to 126 both inclusive. The value of the argument must be
		representable as an unsigned char or the value of EOF.
 * @param c The value to test.
 * @returns Returns True to indicate that it's a printing character and
		returns False otherwise.
*/
int					ft_isprint(int c);
/**
 * @brief Computes the length of  the string s.
 * @param str The string to compute the length.
 * @returns The number of characters that precede the terminating NULL
		character.
*/
size_t				ft_strlen(const char *s);
/**
 * @brief Writes len bytes of value c (converted to an unsigned char)
		to the string b.
 * @param b The string used.
 * @param c The value to write.
 * @param len Number of bytes.
 * @returns Its first argument.
*/
void				*ft_memset(void *b, int c, size_t len);
/**
 * @brief Writes n zeroed bytes to the string s.  If n is
		zero, bzero() does nothing. Operates on a block of memory,
		setting bytes to zero.
 * @param s The string s.
 * @param n The number of bytes.
*/
void				ft_bzero(void *s, size_t n);
/**
 * @brief Copies n bytes from memory area src to memory
		area dst.  If dst and src overlap, behavior is undefined.
		Applications in which dst and src might overlap should use
		memmove(3) instead.
 * @param dst The string dst.
 * @param src The string source.
 * @param n Number of bytes to copy.
 * @returns The original value of dst.
*/
void				*ft_memcpy(void *dst, const void *src, size_t n);
/**
 * @brief Copies len bytes from string src to string dst.
		The two strings may overlap; the copy is always done in a
		non-destructive manner.
 * @param dst The string dst.
 * @param src The string source.
 * @param len Number of bytes to copy.
 * @returns The original value of dst.
*/
void				*ft_memmove(void *dst, const void *src, size_t len);
/**
 * @brief Copy strings with the same input parameters
		and output result as snprintf(3).
 * @param dst The string dst.
 * @param src The string source.
 * @param size Number of bytes to copy.
 * @returns the length of src.
*/
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
/**
 * @brief Concatenate strings
		with the same input parameters and output result as snprintf(3).
 * @param dst The string dst.
 * @param src The string source.
 * @param size Number of bytes to concatenate.
 * @returns The initial length of dst plus the length of src in case of
		len_dst < dstsize, otherwise len_dst plus dstsize.
*/
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
/**
 * @brief Converts a lower-case letter to the corresponding
		upper-case letter.
 * @param c The letter to convert.
 * @returns If the argument is a lower-case letter,
		returns the corresponding upper-case letter if there is one; otherwise,
		the argument is returned unchanged.
*/
int					ft_toupper(int c);
/**
 * @brief Converts an upper-case letter to the corresponding
		lower-case letter.
 * @param c The letter to convert.
 * @returns If the argument is an upper-case letter, returns
		the corresponding lower-case letter if there is one; otherwise,
		the argument is returned unchanged.
*/
int					ft_tolower(int c);
/**
 * @brief Locates the first occurrence of c (converted
		to a char) in the string pointed to by s. The terminating null
		character is considered to be part of the string; therefore if c is
		'\0', the functions locate the terminating '\0'.
 * @param s The string to look into.
 * @param c The character fo look for.
 * @returns A pointer to the located
		character, or NULL if the character does not appear in the string.
*/
char				*ft_strchr(const char *s, int c);
/**
 * @brief Locates the last occurrence of c in the string pointed to by s.
		The terminating null character is considered to be part of the string;
		therefore if c is '\0', the functions locate the terminating '\0'.
 * @param s The string to look into.
 * @param c The character fo look for.
 * @returns A pointer to the located character, or NULL if the character
		does not appear in the string.
*/
char				*ft_strrchr(const char *s, int c);
/**
 * @brief Compares not more than n characters. Characters that appear after
		a '\0' character are not compared.
 * @param s1 The first string.
 * @param s2 The second string.
 * @param n The number of bytes to compare.
 * @returns An integer greater than,
		equal to, or less than 0, according as the string s1 is greater
		than, equal to, or less than the string s2. The comparison is done
		using unsigned characters, so that '\200' is greater than '\0'.
*/
int					ft_strncmp(const char *s1, const char *s2, size_t n);
/**
 * @brief Locates the first occurrence of c (converted
		to an unsigned char) in string s.
 * @param s The string used.
 * @param c The character lo locate.
 * @param len Number of bytes to look for.
 * @returns A pointer to the byte located, or NULL
		if no such byte exists within n bytes.
*/
void				*ft_memchr(const void *s, int c, size_t n);
/**
 * @brief Compares byte string s1 against byte string s2.
		Both strings are assumed to be n bytes long.
 * @param s1 The first string.
 * @param s2 The second string.
 * @param n The size.
 * @returns Zero if the two strings are identical, otherwise
	returns the difference between the first two differing bytes
	(treated as unsigned char values, so that '\200' is greater than '\0',
	for example). Zero-length strings are always identical. This behavior
	is not required by C and portable code should only depend on the sign of
	the returned value.
*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);
/**
 * @brief Locates the first occurrence of the null-terminated
		string needle in the string haystack, where not more than
		len characters are searched. Characters that appear after a '\0'
		character are not searched.
 * @param haystack The string to look into.
 * @param neddle The srting to look for.
 * @param len The number of bytes to search.
 * @returns If needle is an empty string, haystack is returned; if needle occurs
		nowhere in haystack, NULL is returned; otherwise a pointer to the
		first character of the first occurrence of needle is returned.
*/
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
/**
 * @brief Converts str to int representation.
 * @param str The string to convert.
 * @returns The int converted.
 */
int					ft_atoi(const char *str);
/**
 * @brief Allocates memory with the requested alignment. The allocated memory
		is aligned such that it can be used for any data type.
 * @param count Number of objets.
 * @param size Size of objects.
 * @returns If successful, return a pointer to allocated memory.
		If there is an error, they return a NULL pointer and set errno to
		ENOMEM.
*/
void				*ft_calloc(size_t count, size_t size);
/**
 * @brief Allocates sufficient memory for a copy of the
		string s1, does the copy, and returns a pointer to it.  The pointer
		may subsequently be used as an argument to the function free(3). If
		insufficent memory is available, NULL is returned.
 * @param s1 The string to copy.
 * @returns The copied string.
*/
char				*ft_strdup(const char *s);

// ---------------------- Additional functions libft -------------------------
/**
 * @brief Using malloc, returns a substring of the string 's' which
		starts at the 'start' index and have 'len' bytes of size.
 * @param s The string to look into.
 * @param start The start of the substring.
 * @param len The size of the subtring.
 * @returns The new string. Returns NULL if malloc fails.
*/
char				*ft_substr(char const *s, unsigned int start, size_t len);
/**
 * @brief Using malloc, creates an array of strings made up by the
		the concatenation of 's1' and 's2'.
 * @param s1 The first string.
 * @param s2 The second string to join to s1.
 * @returns The string resulting from the concatenation.
		Returns NULL if malloc fails.
*/
char				*ft_strjoin(char const *s1, char const *s2);
/**
 * @brief Using malloc, deletes all the characters of the string
	'set' from the beginning and the end of 's1', until find a
	character that doesn't belong to 'set'.
 * @param s1 The string to look into.
 * @param set The string with the characters to remove.
 * @returns The trimmed string. Returns NULL if malloc fails.
*/
char				*ft_strtrim(char const *s1, char const *set);
/**
 * @brief Using malloc, creates an array of strings made up by separating
		the string s in subtrings using the character 'c' as delimiter.
		The array has to finish with a NULL pointer.
 * @param s The string to split.
 * @param c The character used as dellimiter.
 * @returns The array of strings resulting from the separation.
		Returns NULL if malloc fails.
*/
char				**ft_split(char const *str, char c);
/**
 * @brief Using malloc(3), creates a string that represents the integer
		value received as an argument. Negative numbers must be handled.
 * @param n The integer number to convert.
 * @returns The string that represent the number. Returns
		NULL if malloc fails.
*/
char				*ft_itoa(int n);
/**
 * @brief Apply the function 'f' to each character in the string 's',
		passing the index of each character within 's' and the character
		itself as parameters to 'f'.
 * @param s The string to iterate.
 * @param f The function to apply to each character.
 * @returns Generate a new string with the result of the successive use of 'f'.
		Returns NULL if malloc fails.
*/
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/**
 * @brief To each character of the string 's', applies the function 'f'
		given as parameters the index of each character itself and the
		adress of the character itself.
 * @param s The string to iterate.
 * @param f Pointer to the function 'f' to apply.
*/
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
/**
 * @brief Sends the character 'c' to the file descriptor given as parameter.
 * @param c The character to send.
 * @param fd The file descriptor.
 */
void				ft_putchar_fd(char c, int fd);
/**
 * @brief Sends the string 's' to the file descriptor given as parameter.
 * @param s The string to send.
 * @param fd The file descriptor.
 * @returns The number of bytes written.
 */
void				ft_putstr_fd(char *s, int fd);
/**
 * @brief Sends the string 's' to the file descriptor given as parameter,
		followed by a newline character.
 * @param s The string to send.
 * @param fd The file descriptor.
 */
void				ft_putendl_fd(char *s, int fd);
/**
 * @brief Sends the number 'n' to the file descriptor given as parameter.
 * @param n The number to send.
 * @param fd The file descriptor.
 */
void				ft_putnbr_fd(int n, int fd);

// -------------------- Bonus: lists functions --------------------------------

/**
 * @brief Creates a new node using malloc(3). The variable 'content' is
		initialized with the content of the 'content' parameter and the
		variable 'next' with NULL.
 * @param content The content to fill the new node.
 * @returns The new node.
*/
t_list				*ft_lstnew(void *content);
/**
 * @brief Add the node 'new' to the end of the linked list 'lst'.
 * @param lst The pointer to the first node of the linked list.
 * @param new The pointer to the node to add at the beginning to the linked list.
 */
void				ft_lstadd_front(t_list **lst, t_list *new);
/**
 * @brief Counts the numer of nodes of a list.
 * @param lst The beggining of the list.
 * @returns The length of the list.
 */
int					ft_lstsize(t_list *lst);
/**
 * @brief Returns the last node of a linked list.
 * @param lst The beginning of the linked list.
 * @returns The last node of the linked list.
 */
t_list				*ft_lstlast(t_list *lst);
/**
 * @brief Add the node 'new' to the beginning of the linked list 'lst'.
 * @param lst The pointer to the first node of the linked list.
 * @param new The pointer to the node to add to the linked list.
 */
void				ft_lstadd_back(t_list **lst, t_list *new);
/**
 * @brief Free the content of the node using the function given as
		parameter and also free the node. The memory of next mustn't be freed.
 * @param lst The node to free.
 * @param f Pointer to the function to apply.
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));
/**
 * @brief Deletes and frees the given 'lst' node and all subsequent nodes,
		using the 'del' function and free(3).
 * @param lst The address of a pointer to a node.
 * @param f Pointer to the function to apply.
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));
/**
 * @brief Iterate the linked list 'lst' and applies the function 'f' at the
		content of each node.
 * @param lst The pointer to the first node.
 * @param f Pointer to the function to apply.
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));
/**
 * @brief Iterates the linked list 'lst' and applies the funciont 'f'
		to the content of each node. Creates a list given by the correct
		and sucessive application of the function 'f' in each node. The
		function 'del' is used to delete the content of a node if it's
		necessary.
 * @param dst A pointer to a node.
 * @param f The address of a pointer to a function used in the iteration of
		each node of the list.
 * @param del A pointer to the function used to delete the content of the node,
		if necessary.
 * @returns The new list. Returns NULL if the memory allocation fails.
*/
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
/**
 * @brief Converts string 'str' to a long integer.
 * @param str String with the representation of an integer.
 * @returns Converted long integer value.
 */

// ----------------- Extra functions ----------------------------------------

long				ft_atol(const char *str);
/**
 * @brief Checks for any whitespace character. Whitespace characters are: 
 * 		  space, form-feed ('\f'), newline ('\n'), carriage return ('\r'), 
 * 		  horizontal tab ('\t'), and vertical tab ('\v').
 * @param c The character to check.
 * @returns Non-zero if the character is a whitespace character, 0 otherwise.
 */
int					ft_isspace(int c);

char				*strtok(char *str, const char *sep);

void				ft_free_matrix(char **matrix);

// ----------------- ft_printf functions ------------------------------------
/**
 * @brief Outputs the string 'format' to the standard output, replacing
 * 		  any format specifiers with the values from the additional arguments.
 * @param format The format string containing the text to be written 
 * 		  to stdout and the format specifiers, 
 * 		  which define how subsequent arguments are converted for output.
 * @returns The number of characters printed (excluding the null byte 
 * 			used to end
 *          output to strings).
 */
int					ft_printf(char const *format, ...);
/**
 * @brief Handles the printing of various types based on the 'format' specifier.
 * @param format The format specifier character (e.g., 's' for string, 
 * 		'd' for decimal integer).
 * @param ap A va_list representing the arguments passed to the format string.
 * @returns The number of characters printed for the given format.
 */
int					print_format(char format, va_list ap);
/**
 * @brief Prints a single character to the standard output.
 * @param c The character to print.
 * @returns The number of characters printed.
 */
int					ft_putchar_pf(int c);
/**
 * @brief Prints a string to the standard output. If the string is NULL, 
 * 		  prints "(null)".
 * @param str The string to print.
 * @returns The number of characters printed.
 */
int					ft_putstr_pf(char *str);
/**
 * @brief Prints the address pointed to by 'ptr' in hexadecimal format.
 * @param ptr The pointer whose address is to be printed.
 * @returns The number of characters printed.
 */
int					ft_putptr_pf(unsigned long ptr);
/**
 * @brief Prints 'n' in 'base' using 'base_digits'.
 * @param n Number to print.
 * @param base Base for printing.
 * @param base_digits Digits for the base.
 * @returns Printed character count.
 */
int					ft_putnbrbase_pf(long n, int base, const char *base_digits);
/**
 * @brief Prints 'n' in 'base' with 'base_digits', for pointer addresses.
 * @param n Number to print.
 * @param base Numerical base for printing.
 * @param base_digits Digits characters for the base.
 * @returns Number of characters printed.
 */
int					ft_putnbrbase_ptr_pf(unsigned long n, int base,
						const char *base_digits);

// ------------------ get_next_line functions --------------------------------
/**
 * @brief Frees a string pointed to by 'str' and sets it to NULL.
 * @param str The address of the string to be freed and set to NULL.
 * @returns Always returns NULL, to easily terminate functions that need to
 *          return NULL after freeing a string.
 */
char				*ft_free(char **str);
/**
 * @brief Searches for 'c' in 's', including the terminating null byte.
 * @param s The string to search in.
 * @param c The character to find.
 * @returns Pointer to the character found, or NULL if not found.
 */
char				*ft_strchr_gnl(char *s, int c);
/**
 * @brief Concatenates the string 's1' with 's2' into a new string, which is
 *        allocated with malloc.
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @returns The new string. NULL if the allocation fails.
 */
char				*ft_strjoin_gnl(char *s1, char *s2);
/**
 * @brief Allocates and returns a substring from the string 's'.
 *        The substring begins at index 'start' and is of maximum size 'len'.
 * @param s The string from which to create the substring.
 * @param start The start index of the substring in the string 's'.
 * @param len The maximum length of the substring.
 * @returns The substring. NULL if the allocation fails.
 */
char				*ft_substr_gnl(char *s, unsigned int start, size_t len);
/**
 * @brief Reads a line from a file descriptor.
 * @param fd The file descriptor to read from.
 * @returns A line read or NULL on EOF or error.
 */
char				*get_next_line(int fd);

#endif