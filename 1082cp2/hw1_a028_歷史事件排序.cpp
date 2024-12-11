#include <stdio.h>

int main(){
	int N; // how many events
	int sort_by_events_ans[21] = {}; // Which serial number does the event(event 1 ~ event N) happen?
	int sort_by_events_input[21] = {}; // Students input which serial number the event(event 1 ~ event N) happens.
	int sort_by_serial_ans[21] = {}; // the accurate event order (first happen ~ last happen)
	int sort_by_serial_input[21] = {}; // the inputed event order
	int ans_sorted[21] = {}; // store the orders (DP)
	int len[21] = {}; // record how many scores the student gets
	int max = 0;
	scanf("%d", &N);
	for(int i = 0; i < N; ++i){
		scanf("%d", &sort_by_events_ans[i]);
		sort_by_serial_ans[sort_by_events_ans[i] - 1] = i + 1;
	}

	while(scanf("%d", &sort_by_events_input[0]) != EOF){
		sort_by_serial_input[sort_by_events_input[0] - 1] = 1;
		for(int i = 1; i < N; ++i){
			scanf("%d", &sort_by_events_input[i]);
			sort_by_serial_input[sort_by_events_input[i] - 1] = i + 1;
		}

		for(int i = 0; i < N; ++i){
			for(int j = 0; j < N; ++j){
				if(sort_by_serial_input[i] == sort_by_serial_ans[j]){
					ans_sorted[i] = j;
					break;
				}
			}
//			printf("%d ", ans_sorted[i]);
		}
//		printf("\n");
		
		for(int i = 0; i < N; ++i){
			len[i] = 1;
			for(int j = 0; j < N; ++j){
				if(ans_sorted[j] < ans_sorted[i] && len[j] + 1 > len[i]){
					len[i] = len[j] + 1;
				}
			}
			if(len[i] > max){
				max = len[i];
			}
		}
			
		printf("%d\n", max);
		for(int i = 0; i < N; ++i){
			len[i] = 0;
		}
		max = 0;
	}

	return 0;
} 
