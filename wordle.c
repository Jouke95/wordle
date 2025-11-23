#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define GREEN	"\033[0;32m"
#define YELLOW	"\033[0;33m"
#define GRAY	"\033[0;90m"
#define RESET	"\033[0m"
#define BOLD	"\033[1m"

#define WORD_LENGTH 5
#define MAX_TRIES 6
#define MAX_WORDS 1000


const char* pick_random_word(const char *word_list[], int num_words)
{
	const char *word = word_list[rand() % num_words];
	return (word);
}

int check_if_won(const char *input, const char *secret_word, int *won) {
	if (strcmp(input, secret_word) == 0) {
		printf("Congratulations! You won! 🎉\n");
		*won = 1;
	}
	return (0);
}

int print_letters(const char *input, const char *secret_word) {
	for (int i = 0; i < WORD_LENGTH; i++) {
		if (input[i] == secret_word[i])
			printf(GREEN "%c" RESET, input[i] );
		else if (strchr(secret_word, input[i]))
			printf(YELLOW "%c" RESET, input[i]);
		else
			printf(GRAY "%c" RESET, input[i]);
	}
	printf("\n");
	return (0);
}

int	game_loop(const char *secret_word) {
	char	input[100];
	int		tries = 0;
	int		won = 0;
	int		attempt = 1;

	while (tries < MAX_TRIES && !won) {
		printf("Attempt %i/6: ", attempt);
		scanf("%99s", input);

		for (int i = 0; input[i]; i++)
			input[i] = tolower(input[i]);

		if (strlen(input) != WORD_LENGTH) {
			printf("Error: must be 5 letters\n");
			continue;
		}
		print_letters(input, secret_word);
		tries++;
		attempt++;
		check_if_won(input, secret_word, &won);
	}
	if (!won)
		printf("\n😢 Game Over! The word was: %s\n", secret_word);
	return (0);
}

int main(void) {
	srand(time(NULL));

	const char *word_list[] = { "house", "crane", "slant", "crate", "sleep",
								"train", "snake", "print", "brake", "ghost",
								"storm", "bread", "flesh", "grape", "horse" };
	int num_words = sizeof(word_list) / sizeof(word_list[0]);

	while (1) {
		printf("🎮 WELCOME TO WORDLE! 🎮\n\n");
		const char *secret_word = pick_random_word(word_list, num_words);
		game_loop(secret_word);
		printf("\nPlay again? (y/n): ");
		char choice;
		scanf(" %c", &choice);
		if (choice == 'n' || choice == 'N')
			break ;
	}
	printf("Thanks for playing! 👋\n");
	return (0);
}