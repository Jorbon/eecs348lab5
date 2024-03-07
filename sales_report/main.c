#include <stdio.h>

static const char INPUT_FILE_NAME[15] = "sales_data.txt";

static const char MONTH_NAMES[12][10] = {
	"January  ",
	"February ",
	"March    ",
	"April    ",
	"May      ",
	"June     ",
	"July     ",
	"August   ",
	"September",
	"October  ",
	"November ",
	"December "
};

int main() {
	
	// Read data from the file
	
	FILE* data_file = fopen(INPUT_FILE_NAME, "r");
	if (data_file == NULL) {
		// Handle case where input file does not exist
		printf("Data file '%s' not found.", INPUT_FILE_NAME);
		return 1;
	}
	
	float sales_data[12];
	
	// Variables for analysis as the data is read 
	int min_index = 0;
	int max_index = 0;
	float total_sales = 0.0;
	
	float value;
	for (int i = 0; i < 12; i++) {
		if (fscanf(data_file, "%f", &value) != 1) {
			// If scanf doesn't find a value when it should, exit with an error message
			printf("Not enough data found in file, %d values present out of 12 expected.\n", i);
			return 1;
		}
		
		// Store and process the data point
		sales_data[i] = value;
		total_sales += value;
		if (value < sales_data[min_index]) min_index = i; else
		if (value > sales_data[max_index]) max_index = i;
	}
	
	fclose(data_file);
	
	
	// Sort the indices to the data highest to lowest for the report
	
	int indices_sorted[12];
	for (int i = 0; i < 12; i++) indices_sorted[i] = i; // have to initialize the list properly first
	
	for (int i = 0; i < 11; i++) {
		// find index of index of max value
		int max_i = i;
		for (int j = i+1; j < 12; j++) {
			if (sales_data[indices_sorted[max_i]] < sales_data[indices_sorted[j]]) max_i = j;
		}
		
		// swap that index with the first one
		int temp = indices_sorted[i];
		indices_sorted[i] = indices_sorted[max_i];
		indices_sorted[max_i] = temp;
	}
	
	
	// Monthly sales report
	
	printf("\nMonthly sales report for 2022:\nMonth      Sales\n");
	for (int i = 0; i < 12; i++) {
		printf("%s  $%.2f\n", MONTH_NAMES[i], sales_data[i]);
	}
	
	// Sales summary
	
	// Trim the spaces off the end of the month names by replacing with 0 so the closing parenthesis are correct
	char min_month_trimmed[10] = {0};
	char max_month_trimmed[10] = {0};
	for (int i = 0; i < 9; i++) {
		min_month_trimmed[i] = MONTH_NAMES[min_index][i] == ' ' ? 0 : MONTH_NAMES[min_index][i];
		max_month_trimmed[i] = MONTH_NAMES[max_index][i] == ' ' ? 0 : MONTH_NAMES[max_index][i];
	}
	
	printf("\nSales summary:\n");
	printf("Minimum sales:    $%.2f    (%s)\n", sales_data[min_index], min_month_trimmed);
	printf("Maximum sales:    $%.2f    (%s)\n", sales_data[max_index], max_month_trimmed);
	printf("Average sales:    $%.2f\n", total_sales / 12.0);
	
	// Moving average report
	
	printf("\nSix-Month Moving Average Report:\n");
	for (int i = 0; i < 7; i++) {
		
		float moving_total = 0.0;
		for (int j = i; j < i + 6; j++) {
			moving_total += sales_data[j];
		}
		
		printf("%s  -  %s  $%.2f\n", MONTH_NAMES[i], MONTH_NAMES[i+5], moving_total / 6.0);
	}
	
	// Sales Report
	
	printf("\nSales Report (Highest to Lowest):\nMonth      Sales\n");
	for (int i = 0; i < 12; i++) {
		printf("%s  $%.2f\n", MONTH_NAMES[indices_sorted[i]], sales_data[indices_sorted[i]]);
	}
	
	
	return 0;
}