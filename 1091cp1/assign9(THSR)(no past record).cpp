#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME 25
#define STAT 23
#define CAR 12
#define ROW 20
#define COL 5

int accessed_stations[STAT] = {};
int people = 0; // how many different people reserve
int fail = 0; // whether the reservation fails
int stat1 = -1, stat2 = -1; // decide the direction
int some_success_but_fail = 0; // some success but fail in one reservation (to let the error massage not be printed out)

struct table{
	int status; // == 0: not accepted ststion; == 1: accepted ststion, but empty; == 2: accepted ststion and not empty
	int who; // the ith person on the seat
};
typedef struct table Table;
Table table[STAT][CAR][ROW*COL] = {}; // [which station][which car][which seat(which row(1~20) and column(A~E))];

int station_search(char station[20]){ // odd is each section
	if(strcmp(station, "Nangang") == 0) return 0;
	else if(strcmp(station, "Taipei") == 0) return 2;
	else if(strcmp(station, "Banqiao") == 0) return 4;
	else if(strcmp(station, "Taoyuan") == 0) return 6;
	else if(strcmp(station, "Hsinchu") == 0) return 8;
	else if(strcmp(station, "Miaoli") == 0) return 10;
	else if(strcmp(station, "Taichung") == 0) return 12;
	else if(strcmp(station, "Changhua") == 0) return 14;
	else if(strcmp(station, "Yunlin") == 0) return 16;
	else if(strcmp(station, "Chiayi") == 0) return 18;
	else if(strcmp(station, "Tainan") == 0) return 20;
	else if(strcmp(station, "Zuoying") == 0) return 22;
}

void num_to_station(int num){ // odd is each section
	if(num == 0) printf("Nangang");
	else if(num == 2) printf("Taipei");
	else if(num == 4) printf("Banqiao");
	else if(num == 6) printf("Taoyuan");
	else if(num == 8) printf("Hsinchu");
	else if(num == 10) printf("Miaoli");
	else if(num == 12) printf("Taichung");
	else if(num == 14) printf("Changhua");
	else if(num == 16) printf("Yunlin");
	else if(num == 18) printf("Chiayi");
	else if(num == 20) printf("Tainan");
	else if(num == 22) printf("Zuoying");
} 

void seat_process(int Start, int Dest, int somebody, int Car, int Seat){
		int next, Nn, Sn; // next section, north neighbor(section), south neighbor(section)
		if(stat1 - stat2 < 0){
			next = Start+1;
			Nn = Start-1;
			Sn = Dest+1;
		}
		else if(stat1 - stat2 > 0){
			next = Start-1;
			Nn = Dest-1;
			Sn = Start+1;
		}
		
		while(next != Dest){
			if(table[next][Car-1][Seat].status == 2){
				printf("RESERVE FAILED.... (repeat seats)\n"); // the seat has been reserved already
				fail = 1;
				return;
			}
			if(stat1 - stat2 < 0) ++next;
			else if(stat1 - stat2 > 0) --next;
		}
		
		if( ( Nn >= 0 && (table[Start][Car-1][Seat].status == 2 && table[Nn][Car-1][Seat].status == 2) ) // not tail
		|| ( Sn < STAT && (table[Dest][Car-1][Seat].status == 2 && table[Sn][Car-1][Seat].status == 2) )){ // not head
			printf("RESERVE FAILED.... (repeat seats)\n"); // the seat has been reserved already
			fail = 1;
			return;
		}
		
		if(stat1 - stat2 < 0) next = Start+1;
		else if(stat1 - stat2 > 0) next = Start-1;
		while(next != Dest){
			table[next][Car-1][Seat].status = 2; // ordered seat is empty
			table[next][Car-1][Seat].who = somebody;
			if(stat1 - stat2 < 0) ++next;
			else if(stat1 - stat2 > 0) --next;
		}
		
		if(stat1 - stat2 < 0) next = Start+1;
		else if(stat1 - stat2 > 0) next = Start-1;
		if(Nn >= 0 && Sn < STAT){ // whether the stations are merged (A->B + B->C == A->C)
			if(table[Start-1][Car-1][Seat].who == somebody && table[Start+1][Car-1][Seat].who == somebody){
				table[Start][Car-1][Seat].status = 2;
				table[Start][Car-1][Seat].who = somebody;
			}
			if(table[Dest-1][Car-1][Seat].who == somebody && table[Dest+1][Car-1][Seat].who == somebody){
				table[Dest][Car-1][Seat].status = 2;
				table[Dest][Car-1][Seat].who = somebody;
			}
		}
}

void station_order(int station){ // open the permission of ordered station
	accessed_stations[station] = 1;
	for(int i = 0; i < CAR; ++i){
		for(int j = 0; j < ROW*COL; ++j){
			table[station][i][j].status = 1;
		}
	}
}

int cal_car(char queue[20][20], int order){ // calculate which car is ordered (0~11)
	int Car = 0;
	for(int i = 0; i < strlen(queue[order]); ++i){
		if(queue[order][i] >= '0' && queue[order][i] <= '9') Car = Car * 10 + (queue[order][i] - '0');
	}
	if(queue[order][0] == '-') Car *= -1;
	return Car;
}

int cal_seat(char queue[20][20], int order){ // calculate which seat is ordered (1A == 0, 1E == 4, 2A == 5, ..., 20E == 99)
	int num = 0, Seat = 0;
	for(int i = 0; i < strlen(queue[order]); ++i){
		if(queue[order][i] >= '0' && queue[order][i] <= '9') num = num*10 + (queue[order][i] - '0');
		else if(queue[order][i] >= 'A' && queue[order][i] <= 'E'){
			Seat = (num-1)*5 + queue[order][i]%5;
			break;
		}
		else if(queue[order][i] > 'E') Seat = -200;
	}
	if(queue[order][0] == '-') Seat *= -1;
	return Seat;
}

void reserve(int somebody, int ticket_order, char queue[20][20]){ // decide which seat is ordered
	int Start, Dest, Car, Seat;
	Start = station_search(queue[2]);
	Dest = station_search(queue[3]);
	Car = cal_car(queue, 5+ticket_order*2);
	Seat = cal_seat(queue, 6+ticket_order*2);
	seat_process(Start, Dest, somebody, Car, Seat);
	if(fail == 1) return;
}

void Remove(int Start, int Dest, int Car, int Seat){
	int begin = Start, end;
	if(stat1 - stat2 < 0) end = Dest+1;
	else if(stat1 - stat2 > 0) end = Dest-1;
	while(begin != end){
		if(accessed_stations[begin] == 1) table[begin][Car-1][Seat].status = 1;
		else table[begin][Car-1][Seat].status = 0;
		table[begin][Car-1][Seat].who = -1;
		if(stat1 - stat2 < 0) ++begin;
		else if(stat1 - stat2 > 0) --begin;
	}
}

void Remove_try(int Start, int Dest, int Car, int Seat){
	int Fi, La, Nn, Sn; // first section, last section, north neighbor(station), south neighbor(station)
	if(stat1 - stat2 < 0){
		Fi = Start+1;
		La = Dest-1;
		Nn = Start-2;
		Sn = Dest+2;
	}
	else if(stat1 - stat2 > 0){
		Fi = Start-1;
		La = Dest+1;
		Nn = Dest-2;
		Sn = Start+2;
	}
	
	if((Nn >= 0 && Sn < STAT) 
	&& (table[Nn][Car-1][Seat].status == 2 && table[Sn][Car-1][Seat].status == 2)){ // Remove middle, leave 2 sides
		Remove(Fi, La, Car, Seat);
	}
	else if((Nn >= 0 && Sn < STAT) 
	&& (table[Nn][Car-1][Seat].status != 2 && table[Sn][Car-1][Seat].status != 2)){ // Remove all
		Remove(Start, Dest, Car, Seat);
	}
	else if((Nn >= 0 && Sn < STAT) 
	&& (table[Nn][Car-1][Seat].status == 2 && table[Sn][Car-1][Seat].status != 2)){ // Remove tail
		Remove(Fi, Dest, Car, Seat);
	}
	else if((Nn >= 0 && Sn < STAT) 
	&& (table[Nn][Car-1][Seat].status != 2 && table[Sn][Car-1][Seat].status == 2)){ // Remove head
		Remove(Start, La, Car, Seat);
	}
	else if(Nn+2 == 0 && Sn < STAT){ // Nn: Nangang
		if(table[Sn][Car-1][Seat].status == 2){ // Remove head
			Remove(Start, La, Car, Seat);
		}
		else if(table[Sn][Car-1][Seat].status != 2){ // Remove all
			Remove(Start, Dest, Car, Seat);
		}
	}
	else if(Nn >= 0 && Sn-2 == STAT-1){ // Sn: Zuoying
		if(table[Nn][Car-1][Seat].status == 2){ // Remove tail
			Remove(Fi, Dest, Car, Seat);
		}
		else if(table[Nn][Car-1][Seat].status != 2){ // Remove all
			Remove(Start, Dest, Car, Seat);
		}
	}
	else if(Nn+2 == 0 && Sn-2 == STAT-1){ // Remove all
		Remove(Start, Dest, Car, Seat);
	}
}

void cancel(int somebody, char queue[20][20]){
	int Start = station_search(queue[2]);
	int Dest = station_search(queue[3]);
	int Car = 0, Seat = 0, num = 0;
	
	Car = cal_car(queue, 4);
	Seat = cal_seat(queue, 5);
	
	if( Start == Dest || // start == destination
		(table[Start][Car-1][Seat].status == 0 || table[Dest][Car-1][Seat].status == 0) || // either start or destination isn't accessed
		!( (Start - Dest > 0) && (stat1 - stat2 > 0) || ( (Start - Dest < 0) && (stat1 - stat2 < 0) ) ) ){  // not the same direction
		printf("CANCELLATION FAILED.... (cannot find the stations information)\n");
		return;
	}
	
	if((Car < 1 || Car > 12) || (Seat < 0 || Seat > 99)){
		printf("CANCELLATION FAILED.... (cannot find the seat information)\n");
		return;
	}
	
	int next; // next section
	if(stat1 - stat2 < 0) next = Start+1;
	else if(stat1 - stat2 > 0) next = Start-1;
	while(next != Dest){
		if(table[next][Car-1][Seat].status != 2 || table[next][Car-1][Seat].who != somebody){
			printf("CANCELLATION FAILED.... (cannot find the seat information)\n"); // cancel empty seat or wrong person
			return;
		}
		if(stat1 - stat2 < 0) ++next;
		else if(stat1 - stat2 > 0) --next;
	}
	
	Remove_try(Start, Dest, Car, Seat);
	if(some_success_but_fail == 0) printf("CANCELLATION SUCCESSED!! %s %s (%s - %s)\n", queue[4], queue[5], queue[2], queue[3]);
}

void check(int somebody, char queue[20][20]){
	int Car = 0, Seat = 0, num = 0;
	Car = cal_car(queue, 2);
	Seat = cal_seat(queue, 3);
	if((Car < 1 || Car > 12) || (Seat < 0 || Seat > 99)){
		printf("CHECK FAILED.... (cannot find the reservation data)\n");
		return;
	}
	
	int empty = 1; // doesn't reserve any ordered station
	int printed = 0;
	
	int begin, end;
	if(stat1 - stat2 < 0){
		begin = 0;
		end = STAT;
	}
	else if(stat1 - stat2 > 0){
		begin = STAT-1;
		end = -1;
	}
	while(begin != end){
		if(table[begin][Car-1][Seat].status == 2 && table[begin][Car-1][Seat].who == somebody){
			empty = 0;
			if(printed == 0){
				printf("CHECK %s %s %s ->", queue[1], queue[2], queue[3]); // only need to print once
				printed = 1;
			}
			
			int itr = begin;
			while(itr != end){
				int next;
				if(stat1 - stat2 < 0) next = itr+1;
				else if(stat1 - stat2 > 0) next = itr-1;
				
				if(next == end || (table[next][Car-1][Seat].status != 2 || table[next][Car-1][Seat].who != somebody) ){
					int origin, terminal;
					if(begin % 2 == 0) origin = begin;
					else if(begin % 2 != 0 && stat1 - stat2 < 0) origin = begin-1;
					else if(begin % 2 != 0 && stat1 - stat2 > 0) origin = begin+1;
					if(itr % 2 == 0) terminal = itr;
					else if(itr % 2 != 0 && stat1 - stat2 < 0) terminal = itr+1;
					else if(itr % 2 != 0 && stat1 - stat2 > 0) terminal = itr-1;
					printf(" (");
					num_to_station(origin);
					printf(" - ");
					num_to_station(terminal);
					printf(")");
					begin = itr;
					break;
				}
				if(stat1 - stat2 < 0) ++itr;
				else if(stat1 - stat2 > 0) --itr;
			}
		}
		if(stat1 - stat2 < 0) ++begin;
		else if(stat1 - stat2 > 0) --begin;
	}
	if(empty == 1) printf("CHECK FAILED.... (cannot find the reservation data)\n");
	else printf("\n");
}

void clean(int Start, int Dest, int Tickets, char queue[20][20]){
	some_success_but_fail = 1;
	for(int i = 0; i < Tickets; ++i){
		int Car = cal_car(queue, 5+i*2);
		int Seat = cal_seat(queue, 6+i*2);
		Remove_try(Start, Dest, Car, Seat);
	}
	some_success_but_fail = 0;
}

void construct(int somebody, char queue[20][20]){
	fail = 0;
	int wrong_ticket;
	int Start = station_search(queue[2]);
	int Dest = station_search(queue[3]);
	if( Start == Dest || // start == destination
		(table[Start][0][0].status == 0 || table[Dest][0][0].status == 0) || // either start or destination aren't accessed
		!( ( (Start - Dest > 0) && (stat1 - stat2 > 0) ) || ( (Start - Dest < 0) && (stat1 - stat2 < 0) ) ) ){  // not the same direction
		printf("RESERVE FAILED.... (station information has something wrong)\n");
		return;
	}
	
	int Tickets = 0;
	for(int i = 0; i < strlen(queue[4]); ++i) 
		if(queue[4][i] >= '0' && queue[4][i] <= '9') Tickets = Tickets * 10 + (queue[4][i] - '0');
	
	if(Tickets > 4){
		printf("RESERVE FAILED.... (too many seats)\n");
		return;
	}
	for(int i = 0; i < Tickets-1; ++i){
		for(int j = i+1; j < Tickets; ++j){
			if(strcmp(queue[5+i*2], queue[5+j*2]) == 0 && strcmp(queue[6+i*2], queue[6+j*2]) == 0){ // reserve same seats in one reservation
				printf("RESERVE FAILED.... (repeat seats)\n");
				return;
			}
		}
	}
	for(int i = 0; i < Tickets; ++i){
		reserve(somebody, i, queue);
		if(fail == 1){
			wrong_ticket = i;
			break;
		}
	}
	if(fail == 1) clean(Start, Dest, wrong_ticket, queue);
	else{
		for(int i = 0; i < Tickets; ++i) 
			printf("RESERVE SUCCESSED!! -> %s %s %s (%s - %s)\n", queue[1], queue[5+i*2], queue[6+i*2], queue[2], queue[3]);
		if(somebody == people) ++people; // newly successfully reserved person +1
	}
}

int main(){
	int stations, somebody;
	char station_seq[100] = {}, str[100] = {}, name[200][NAME] = {};
	for(int i = 0; i < STAT; ++i){
		for(int j = 0; j < CAR; ++j){
			for(int k = 0; k < ROW*COL; ++k){ // table initialize
				table[i][j][k].status = 0;
				table[i][j][k].who = -1;
			}
		}
	}
	fgets(str, 100, stdin); // =====(TRAIN INFORMATION BEGIN)=====
	scanf("%d", &stations);
	for(int i = 0; i < stations; ++i){
		scanf("%s", station_seq);
		for(int j = 0; j < strlen(station_seq); ++j){
			if(station_seq[j] == ',') station_seq[j] = '\0';
		}
		station_order(station_search(station_seq));
		if(stat1 == -1) stat1 = station_search(station_seq);
		else{
			if(stat2 == -1) stat2 = station_search(station_seq);
		}
	}
	getchar();
	fgets(str, 100, stdin); // ======(TRAIN INFORMATION END)======
	fgets(str, 100, stdin); // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	fgets(str, 100, stdin); // ==========(REQUEST BEGIN)==========
	char request[100] = {};
	char end[50] = "===========(REQUEST END)===========\n";
	while(fgets(request, 100, stdin)){ // input request
		if(strlen(request) == 1 && request[0] == 10) break;
		for(int i = 0; i < 100; ++i){
			if(request[i] == '\n'){
				request[i] = '\0';
				break;
			}
		}
		char queue[20][20] = {}; // [the ith string][length of each string]
		int count = 0;
		char * pch = NULL;
		pch = strtok (request,", ");
		while (pch != NULL){
			strcpy(queue[count++], pch);
		    pch = strtok (NULL, ", ");
		}
		
		if(strcmp(queue[0], "RESERVE") == 0){
			somebody = people; // (default) first reserved
			for(int i = 0; i < people; ++i){
				if(strcmp(name[i], queue[1]) == 0){
					somebody = i;
					break;
				}
			}
			if(somebody == people) strcpy(name[somebody], queue[1]);
			construct(somebody, queue);
			if(fail == 1 && somebody == people) memset(name[somebody], 0, NAME); // the new person reserves failed, avoid the name is incompletely covered by other people
		}
		else if(strcmp(queue[0], "CANCEL") == 0){
			somebody = -1;
			for(int i = 0; i < people; ++i){
				if(strcmp(name[i], queue[1]) == 0){
					somebody = i;
					break;
				}
			}
			if(somebody == -1){
				printf("CANCELLATION FAILED.... (cannot find the seat information)\n");
				continue;
			}
			cancel(somebody, queue);
		}
		else if(strcmp(queue[0], "CHECK") == 0){
			somebody = -1; // (default) first reserved
			for(int i = 0; i < people; ++i){
				if(strcmp(name[i], queue[1]) == 0){
					somebody = i;
					break;
				}
			}
			if(somebody == -1) printf("CHECK FAILED.... (cannot find the reservation data)\n");
			else check(somebody, queue);
		}
		if(strcmp(request, end) == 0) break; 
	}
	return 0;
} 
