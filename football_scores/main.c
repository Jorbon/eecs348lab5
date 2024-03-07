#include <stdio.h>

static const int SCORES[] = { 8, 7, 6, 3, 2 };

void rec_find_combinations(int level, int remaining_score, int* score_list) {
	// Base case: print the score combination if it totals to the target score
	if (level == 5) {
		if (remaining_score == 0) {
			printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", score_list[0], score_list[1], score_list[2], score_list[3], score_list[4]);
		}
		return;
	}
	
	// Recursive case: branch for all possible score counts at the current level
	for (int s = 0; s <= remaining_score; s += SCORES[level]) {
		score_list[level] = s / SCORES[level];
		rec_find_combinations(level + 1, remaining_score - s, score_list);
	}
}

int main() {
	
	printf("\nEnter 0 or 1 to STOP");
	
	int score;
	int score_list[5] = {0};
	
	while (1) {
		printf("\nEnter the NFL score: ");
		
		// If the score is 1 or less, or if the score isn't read successfully, exit the program
		if (scanf("%d", &score) != 1) {
			printf("Invalid input score.\n");
			break;
		}
		if (score <= 1) break;
		
		// Start a recursive process to find all valid combinations
		rec_find_combinations(0, score, score_list);
	}
	
	return 0;
}