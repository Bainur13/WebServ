// // Assignment name  : aff_a
// // Expected files   : aff_a.c
// // Allowed functions: write
// // --------------------------------------------------------------------------------

// // Write a program that takes a string, and displays the first 'a' character it
// // encounters in it, followed by a newline. If there are no 'a' characters in the
// // string, the program just writes a newline. If the number of parameters is not
// // 1, the program displays 'a' followed by a newline.

// // Example:

// // $> ./aff_a "abc" | cat -e
// // a$
// // $> ./aff_a "dubO a POIL" | cat -e
// // a$
// // $> ./aff_a "zz sent le poney" | cat -e
// // $
// // $> ./aff_a | cat -e
// // a$

// #include <unistd.h>
// #include <stdio.h>

// int main(int ac, char **av)
// {
// 	if (ac != 2)
// 	{
// 		write(1, "a", 1);
// 	}
// 	else
// 	{
// 		int j;
// 		j = 0;
// 		while (av[1][j])
// 		{
// 			if (av[1][j] == 'a')
// 			{
// 				 write(1, "a", 1);
// 				 break;
// 			}
// 			j++;
// 		}
// 	}
// 	write (1, "\n", 1);
// 	return (0);
// }

// // [[nomduprogramme], [c  o  u  c  o  u  ], [salut], [bonjour]]
// //     av[0]                av[1]             av[2]     av[3]

// // 						str	['c', 'o', 'u', 'c', 'o',   'u']
// //						str[0] str[1] str[2] str[3] str[4]str[5]

// // group_str = [str, str1, str2];

// // group_str[0][0]


// // av[1] = "coucou"


// int ft_check_if_a(char *str) // str = "coucou";
// {
// 	int i;
// 	i = 0;
// 	while (str[i]) // NULL
// 	{
// 		if (str[i] != 'a')
//         	return (1);
// 	}
// 	return (0);
// }
// Assignment name  : ft_countdown
// Expected files   : ft_countdown.c
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a program that displays all digits in descending order, followed by a
// newline.

// Example:
// $> ./ft_countdown | cat -e
// 9876543210$
// $>

// #include <unistd.h>

// int main(void)
// {
//     char c;

//     c = 57;
//     while (c >= 48)
//     {
//         write (1, &c, 1);
//         c--;
//     }
// 	write (1, "\n", 1);
// }



// -------------------------------------------------------------------------------
// Assignment name  : maff_alpha
// Expected files   : maff_alpha.c
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a program that displays the alphabet, with even letters in uppercase, and
// odd letters in lowercase, followed by a newline.

// Example:

// $> ./maff_alpha | cat -e
// aBcDeFgHiJkLmNoPqRsTuVwXyZ$
// --------------------------------------------------------------------------------
// #include <stdio.h>
// #include <unistd.h>

// int         main(void)
// {
//     int i = 97;
// 	int j;
//     while (i <= 'z')
// 	{
// 		if (i % 2 == 0)
// 		{
// 			j = i - 32;
// 			write(1, &j, 1);
// 		}
//         else
// 		{
//             write(1, &i, 1);
// 		}
// 		i++;
//     }
// 	write(1, "\n", 1);
// }



// Assignment name  : aff_first_param
// Expected files   : aff_first_param.c
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a program that takes strings as arguments, and displays its first
// argument followed by a \n.

// If the number of arguments is less than 1, the program displays \n.

// Example:

// $> ./aff_first_param vincent mit "l'ane" dans un pre et "s'en" vint | cat -e
// vincent$
// $> ./aff_first_param "j'aime le fromage de chevre" | cat -e
// j'aime le fromage de chevre$
// $> ./aff_first_param
// $
#include <unistd.h>
int main(int ac, char **av)
{
	int i;
	if (ac >= 2)
	{
		i = 0;
		while (av[1][i])
		{
			write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}